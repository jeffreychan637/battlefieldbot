#include <device.h>
#include <math.h>

//I2C Constants
#define I2C_ACK             0x00
#define I2C_NACK            0xff
#define I2C_WRITE           0x00
#define I2C_READ            0xff

//accelerometer I2C address
#define ACCEL_I2C_ADDR      0x1D

//accelerometer register addresses
#define ACCEL_STATUS_REG    0x00
#define ACCEL_SYSMOD_REG    0x0B
#define ACCEL_XYZ_DATA_CFG  0x0E
#define ACCEL_CTRL_REG1     0x2A

//accelerometer configuration codes
#define ACCEL_MODE_STANDBY  0x00
#define ACCEL_MODE_WAKE     0x01
#define ACCEL_MODE_SLEEP    0x02
#define ACCEL_CTRL_REG_MODE 0x01
#define ACCEL_SCALE_2G      0x00
#define ACCEL_SCALE_4G      0x01
#define ACCEL_SCALE_8G      0x02

#define CR 0x0D
#define LF 0x0A

/* Used to insert a carriage return and line feed */
#define NewLine() UART_UartPutChar(CR); UART_UartPutChar(LF);

typedef struct 
{
    int value; // 1 for true, 0 for false
} Boolean;

typedef struct
{
    char state; // i for init, n for normsl, a for avoidance, g for goal
    int currX; // X of current pos
    int currY; // Y of current pos
    int destY; // Y of dest, how far to travel
    int32 accelX; // X from accelerometer
    int32 accelY; // Y from accelerometer
    Boolean goal_reached; // Achieved the goal
} Robot_State_Struct;

void putdata ( void* p, char c)
{
	UART_UartPutChar(c);
}

uint32 ms_count = 0;
uint16 seconds = 0;

CY_ISR(MY_ISR) 
{
    ms_count++;
    if (ms_count % 1000 == 0) {
        LED_Write(!LED_Read()); // Toggle LED
        seconds++;
        printf("ms elapsed : %d\n", ms_count);
   }
}

void Truck_Stop() 
{
    Forward_out_Write(0);
    Reverse_out_Write(0);
    Left_out_Write(0);
    Right_out_Write(0);
}

void Truck_Forward(Robot_State_Struct *robot) 
{
    robot->currY += 1;
}

void Truck_Reverse() 
{
    Forward_out_Write(0);
    Reverse_out_Write(1);
}

void Truck_Right(Robot_State_Struct *robot) 
{
    robot->currX += 1;
    
    Left_out_Write(0);
    Right_out_Write(1);
}

void Truck_Left(Robot_State_Struct *robot) 
{
    robot->currX -= 1;
    
    Right_out_Write(0);
    Left_out_Write(1);
}

void Truck_Straight() 
{
    Right_out_Write(0);
    Left_out_Write(0);
}  


int range = 2200;

int detectObstacle() 
{
    int count = 0;
    Trigr_Write(1);
    CyDelayUs(10);
    Trigr_Write(0);
    while(Echo_Read() == 0)
    {
    }
    while(Echo_Read() == 1)
    {
        count++; 
        if (count > range) 
        {
            LED_Write(1);
            return 0;
        }
    }
    printf("sonar_dist : %d\n", count);
    if(count <= range)
    {
        LED_Write(0); 
        return 1;
    }
    return 0;
}

int detectObstacle2() 
{
    int count2 = 0;
    Trigr_1_Write(1);
    CyDelayUs(10);
    Trigr_1_Write(0);
    while(Echo_1_Read() == 0)
    {
    }
    while(Echo_1_Read() == 1)
    {
        count2++; 
        if (count2 > range) 
        {
            LED_1_Write(1);
            return 0;
        }
    }
    printf("sonar_dist : %d\n", count2);
    if(count2 <= range)
    {
        LED_1_Write(0); 
        return 1;
    }
    return 0;
}

void firstMove(Robot_State_Struct *robot) {
    Reverse_out_Write(0);
    Forward_out_Write(1);
    Truck_Forward(robot);
}

int moveRobot(Robot_State_Struct *robot) // dont forgot about equals y but not X
{
    printf("curr : (%d, %d)\n", robot->currX, robot->currY);
    Truck_Forward(robot);
    Truck_Straight();
    
    // Keep moving on
    if (robot->currY >= robot->destY) {
        return 1;
    }
    
    // Done, stop moving
    return 0;
}

int32 square(int x) {
    return x * x;
}

int avoidObs(Robot_State_Struct *robot) 
{   
    Truck_Forward(robot);
    Truck_Straight();
    
    int slow_down = sqrt(square(robot->accelX + robot->accelY));
    PWM_2_WriteCompare(PWM_2_ReadCompare() - slow_down);
        
    // Obstacle on right 
    if (detectObstacle()) {
        Truck_Left(robot);
        return 0;
    }
    //Obstacle on left
    else if (detectObstacle2()) {
        Truck_Right(robot);
        return 0;
    }
    
    // No obstacle anymore
    return 1;
}

void getAccel(Robot_State_Struct *robot, int I2C_Status) 
{
    uint8 accelStatus;
    uint8 accelX_MSB, accelX_LSB, accelY_MSB, accelY_LSB, accelZ_MSB, accelZ_LSB;
    int16 accelX, accelY, accelZ;
    uint16 accelXAbs, accelYAbs, accelZAbs;
    uint16 accelXAbsIIR, accelYAbsIIR, accelZAbsIIR;
    Trigr_Write(0);

    /* Start the I2C register reads by writing the target register */
    I2C_Status = I2C_Accel_I2CMasterSendStart(ACCEL_I2C_ADDR, I2C_WRITE);
    I2C_Status = I2C_Accel_I2CMasterWriteByte(ACCEL_STATUS_REG);
    /* Start the register read */
    I2C_Status = I2C_Accel_I2CMasterSendRestart(ACCEL_I2C_ADDR, I2C_READ);
    /* Read out 7 bytes of status and X and Y acceleration data */
    accelStatus = I2C_Accel_I2CMasterReadByte(I2C_ACK);
    accelX_MSB = I2C_Accel_I2CMasterReadByte(I2C_ACK);
    accelX_LSB = I2C_Accel_I2CMasterReadByte(I2C_ACK);
    accelY_MSB = I2C_Accel_I2CMasterReadByte(I2C_ACK);
    accelY_LSB = I2C_Accel_I2CMasterReadByte(I2C_ACK);
    /* Send a stop condition to end the I2C transaction */
    I2C_Status = I2C_Accel_I2CMasterSendStop();
        
    /* Convert the acceleration MSBs and LSBs to signed ints */
    accelX = ((int16)((accelX_MSB<<8) + accelX_LSB))>>4;
    accelY = ((int16)((accelY_MSB<<8) + accelY_LSB))>>4;
    
    robot->accelX = accelX;
    robot->accelY = accelY;
}

void main()
{
    CyGlobalIntEnable;
    PWM_2_Start();
    
    // Warming up
    CyDelay(250);
    
    UART_Start();
    init_printf(NULL,putdata);
    
// Timer for functions
//    Clock_1_Enable();
//    Clock_1_Start();
//    isr_1_StartEx(MY_ISR);
    
    I2C_Accel_Start();
    
    int I2C_Status;
   
    /* Perform 1 time configuration of the Accelerometer */
    /* Put the accelerometer in standby mode so we can configure it */
    I2C_Status = I2C_Accel_I2CMasterSendStart(ACCEL_I2C_ADDR, I2C_WRITE);
    I2C_Status = I2C_Accel_I2CMasterWriteByte(ACCEL_SYSMOD_REG);
    I2C_Status = I2C_Accel_I2CMasterWriteByte(ACCEL_MODE_STANDBY);
    I2C_Status = I2C_Accel_I2CMasterSendStop();
    //set the system control mode for 800 Hz sampling
    I2C_Status = I2C_Accel_I2CMasterSendStart(ACCEL_I2C_ADDR, I2C_WRITE);
    I2C_Status = I2C_Accel_I2CMasterWriteByte(ACCEL_CTRL_REG1);
    I2C_Status = I2C_Accel_I2CMasterWriteByte(ACCEL_CTRL_REG_MODE);
    I2C_Status = I2C_Accel_I2CMasterSendStop();
    //set the system mode to active
    I2C_Status = I2C_Accel_I2CMasterSendStart(ACCEL_I2C_ADDR, I2C_WRITE);
    I2C_Status = I2C_Accel_I2CMasterWriteByte(ACCEL_SYSMOD_REG);
    I2C_Status = I2C_Accel_I2CMasterWriteByte(ACCEL_MODE_WAKE);
    I2C_Status = I2C_Accel_I2CMasterSendStop();
    
     Robot_State_Struct robot = 
    {
        0, // init state 
        0, // destY 
        0, // currX 
        0, // currY
        0, // accelX
        0 // accelY
    };

    robot.destY = 50;
    firstMove(&robot);
    printf("state : INIT\n");
   
    // Object right in front of us during init
    if (detectObstacle()) {
        robot.state = 'a';
        printf("state : AVOIDANCE\n");
    }
    else {
        robot.state = 'n';
        printf("state : NORMAL\n");
    }
    
    while (robot.state != 'g') {
        // Normal state
        if (robot.state == 1) {
            if (detectObstacle() || detectObstacle2()) {
                robot.state = 'a';
                printf("state : AVOIDANCE\n");
            }
            else {
                // Robot is at the end destination
                if (moveRobot(&robot)) {
                    robot.state = 'g';
                    printf("state : GOAL\n");
                }
            }
        }
        // Avoidance State 
        else if (robot.state == 'a') {
            getAccel(&robot, I2C_Status);
            // No more obstacle
            if (avoidObs(&robot)) {
                int speed_up = sqrt(square(robot.accelX + robot.accelY));
                PWM_2_WriteCompare(PWM_2_ReadCompare() - speed_up);
                robot.state = 'n';
                printf("state : NORMAL\n");
            }
            CyDelay(30);
        }
    }
//     Robot is at the end goal 
    Truck_Stop();
    I2C_Accel_Stop();
}

/* [] END OF FILE */
