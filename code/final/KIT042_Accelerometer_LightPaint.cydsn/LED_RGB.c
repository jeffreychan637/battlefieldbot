/* ========================================
 *
 * The following firmware was developed by Cypress Semiconductor
 * This work is licensed under a Creative Commons Attribution 3.0 Unported License.
 * 
 * http://creativecommons.org/licenses/by/3.0/deed.en_US
 * 
 * You are free to:
 * -To Share — to copy, distribute and transmit the work 
 * -To Remix — to adapt the work 
 * -To make commercial use of the work
 *
 * ========================================
 */

/* ========================================
 * CY8CKIT-042 LED RGB Driver Module
 * By MAXK
 * Version *B
 * Updated 6/26/2013
 *
 * CY8CKIT-042 LED RGB Driver Module
 * This module was designed to drive the RGB LEDs on the KIT-042 with pleasing
 * colors. This module requires that three 16- or 8-bit PWMs be placed and named
 * PWM_R, PWM_G, and PWM_B. Their outputs should be inverted because the LEDs on
 * the kit are sunk by the PSoC 4 GPIOs. LEDs are on P1[6], P0[2], P0[3] (RGB).
 * The PWMs should be clocked at a rate such that the output frequency is 45 Hz
 * or greater to avoid weird blinking.
 * ========================================
 */

#include <LED_RGB.h>

/* PWM resolution is Initialized to the historical default value of 16 bits.  *
 * Change with LED_RGB_SetResolutionBits() API                                */
uint8 LED_RGB_PWM_ResolutionBits = 16; 

/*****************************************************************************
* Function Name: LED_RGB_Start()
******************************************************************************
* Summary:
*  Starts the LED PWM components.
*
*****************************************************************************/
void LED_RGB_Start(void)
{
    PWM_R_Start();
    PWM_G_Start();
    PWM_B_Start();
}

/*****************************************************************************
* Function Name: LED_RGB_Stop()
******************************************************************************
* Summary:
*  Stops the LED PWM components.
*
*****************************************************************************/
void LED_RGB_Stop(void)
{
    PWM_R_Stop();
    PWM_G_Stop();
    PWM_B_Stop();
}

/*****************************************************************************
* Function Name: LED_RGB_Sleep()
******************************************************************************
* Summary:
*  Configures pins for low power, and puts the LED PWM components to sleep.
*
*****************************************************************************/
void LED_RGB_Sleep(void)
{
    Pin_LEDRed_SetDriveMode(Pin_LEDRed_DM_ALG_HIZ);
    Pin_LEDGreen_SetDriveMode(Pin_LEDRed_DM_ALG_HIZ);
    Pin_LEDBlue_SetDriveMode(Pin_LEDRed_DM_ALG_HIZ);
    LED_RGB_SetColorRGB(0,0,0);
    PWM_R_Sleep();
    PWM_G_Sleep();
    PWM_B_Sleep();
}

/*****************************************************************************
* Function Name: LED_RGB_Wakeup()
******************************************************************************
* Summary:
*  Restores the configuration to the active state.
*
*****************************************************************************/
void LED_RGB_Wakeup(void)
{
    PWM_R_Wakeup();
    PWM_G_Wakeup();
    PWM_B_Wakeup();
    Pin_LEDRed_SetDriveMode(Pin_LEDRed_DM_STRONG);
    Pin_LEDGreen_SetDriveMode(Pin_LEDRed_DM_STRONG);
    Pin_LEDBlue_SetDriveMode(Pin_LEDRed_DM_STRONG);
}

/*****************************************************************************
* Function Name: LED_RGB_SetResolutionBits()
******************************************************************************
* Summary:
*  Sets the resolution for the LED drive PWMs.
*
* Parameters:
*  resolutionBits: Describes how many bits the PWM compare value is, full scale
*   Should be between 1 and 16 bits, inclusive. 
*   The PWM period should be equal to (2^resolutionBits)-1. 
*   For example, a 16 bit PWM should have a period of 65,535.
*
*****************************************************************************/
void LED_RGB_SetResolutionBits(uint8 resolutionBits)
{
    /* Set the new resolution. */
    LED_RGB_PWM_ResolutionBits = resolutionBits;
    
    /* Validate the new resolution. Resolutions above 16 are not supported. */
    if(LED_RGB_PWM_ResolutionBits>16)
    {
        LED_RGB_PWM_ResolutionBits = 16;
    }
}

/*****************************************************************************
* Function Name: LED_RGB_DCWrite()
******************************************************************************
* Summary:
*  Writes one of the three LED color duty cycles
*
* Parameters:
*  LED_Color: Describes which LED color is to be written.
*   Use the LED_RED/GREEN/BLUE constants provided in the .h file.
*  LED_NewDutyCycle: Describes the new duty cycle to be written to the PWM.
*   Duty cycle should be 16 bits full scale. It will be shifted down to fit
*   the resolution set using the LED_RGB_SetResolutionBits() API.
*
*****************************************************************************/
void LED_RGB_DCWrite(uint8 LED_Color, uint16 LED_NewDutyCycle)
{
    if(LED_RGB_PWM_ResolutionBits==16)
    {
        switch(LED_Color)
        {
        case LED_RED:
            PWM_R_WriteCompare(LED_NewDutyCycle);
            break;
        case LED_GREEN:
            PWM_G_WriteCompare(LED_NewDutyCycle);
            break;
        case LED_BLUE:
            PWM_B_WriteCompare(LED_NewDutyCycle);
            break;
        default:
            break;
        }
    }
    else
    {    
        switch(LED_Color)
        {
        case LED_RED:
            PWM_R_WriteCompare(LED_NewDutyCycle>>(16 - LED_RGB_PWM_ResolutionBits));
            break;
        case LED_GREEN:
            PWM_G_WriteCompare(LED_NewDutyCycle>>(16 - LED_RGB_PWM_ResolutionBits));
            break;
        case LED_BLUE:
            PWM_B_WriteCompare(LED_NewDutyCycle>>(16 - LED_RGB_PWM_ResolutionBits));
            break;
        default:
            break;
        }
    }
}

/*****************************************************************************
* Function Name: LED_RGB_SetColorRGB()
******************************************************************************
* Summary:
*  Writes all three of the LED duty cycles at once
*
* Parameters:
*  redIntensity: Describes the new red LED intensity
*  greenIntensity: Describes the new green LED intensity
*  blueIntensity: Describes the new blue LED intensity
*
*  Note: Each intensity value should be 0-65535 dark to bright full scale.
*
*****************************************************************************/
void LED_RGB_SetColorRGB(uint16 redIntensity, uint16 greenIntensity, uint16 blueIntensity)
{     
    LED_RGB_DCWrite(LED_RED, (uint32) redIntensity);
    LED_RGB_DCWrite(LED_GREEN, (uint32) greenIntensity);
    LED_RGB_DCWrite(LED_BLUE, (uint32) blueIntensity);
}

/*****************************************************************************
* Function Name: LED_RGB_SetColorCircle()
******************************************************************************
* Summary:
*  Sets the three LEDs to produce the specified hue at 100% saturation and
* value. This will produce the most saturated version of the color.
*
* Parameters:
*  hue: Describes the LED color hue 
*   (0-65535 full scale, red->green->blue->red)
*
*****************************************************************************/
void LED_RGB_SetColorCircle(uint16 hue)
{
    uint16 redIntensity, greenIntensity, blueIntensity;

    if(hue < UINT16_1_6TH_MAX)
    {
        //red on, green increasing
        redIntensity = UINT16_MAX;
        greenIntensity = hue * 6;
        blueIntensity = 0;
    }
    else if(hue < UINT16_2_6TH_MAX)
    {
        //green on, red decreasing
        redIntensity = (UINT16_2_6TH_MAX - hue) * 6;
        greenIntensity = UINT16_MAX;
        blueIntensity = 0;
    }
    else if(hue < UINT16_3_6TH_MAX)
    {
        //green on, blue increasing
        redIntensity = 0;
        greenIntensity = UINT16_MAX;
        blueIntensity = (hue - UINT16_2_6TH_MAX) * 6;
    }
    else if(hue < UINT16_4_6TH_MAX)
    {
        //blue on, green decreasing
        redIntensity = 0;
        greenIntensity = (UINT16_4_6TH_MAX - hue) * 6;
        blueIntensity = UINT16_MAX;
    }
    else if(hue < UINT16_5_6TH_MAX)
    {
        //blue on, red increasing
        redIntensity =  (hue - UINT16_4_6TH_MAX) * 6;
        greenIntensity = 0;
        blueIntensity = UINT16_MAX;
    }
    else
    {
        //red on, blue decreasing
        redIntensity = UINT16_MAX;
        greenIntensity = 0;
        blueIntensity = (UINT16_MAX - hue) * 6;
    }
    
    LED_RGB_SetColorRGB(redIntensity, greenIntensity, blueIntensity);
}

/*****************************************************************************
* Function Name: LED_RGB_SetColorCircleHSV()
******************************************************************************
* Summary:
*  Sets the three LEDs to produce the specified hue, saturation and value.
*
* Parameters:
*  hue: Describes the LED array hue (color)
*   (0-65535 full scale, red->green->blue->red)
*  saturation: Describes the LED array saturation (un-whiteness)
*   (0-65535 full scale, white->hue)
*  value: Describes the LED array value (un-blackness)
*   (0-65535 full scale, black->hue)
*
*****************************************************************************/
void LED_RGB_SetColorCircleHSV(uint16 hue, uint16 saturation, uint16 value)
{
    int32 redIntensity, greenIntensity, blueIntensity;
    
    uint32 dominantIntensityC = ((uint32)saturation) * value / UINT16_MAX;
    
    int32 intensityShiftM = ((int32)value) - dominantIntensityC;
    
    if(hue < UINT16_1_6TH_MAX)
    {
        //red on, green increasing
        redIntensity = dominantIntensityC;
        greenIntensity = (hue * 6) * dominantIntensityC / UINT16_2_6TH_MAX ;
        blueIntensity = 0;
    }
    else if(hue < UINT16_2_6TH_MAX)
    {
        //green on, red decreasing
        redIntensity = (UINT16_2_6TH_MAX - hue) * dominantIntensityC / UINT16_1_6TH_MAX;
        greenIntensity = dominantIntensityC;
        blueIntensity = 0;
    }
    else if(hue < UINT16_3_6TH_MAX)
    {
        //green on, blue increasing
        redIntensity = 0;
        greenIntensity = dominantIntensityC;
        blueIntensity = (hue - UINT16_2_6TH_MAX) * dominantIntensityC / UINT16_1_6TH_MAX;
    }
    else if(hue < UINT16_4_6TH_MAX)
    {
        //blue on, green decreasing
        redIntensity = 0;
        greenIntensity = (UINT16_4_6TH_MAX - hue) * dominantIntensityC / UINT16_1_6TH_MAX;
        blueIntensity = dominantIntensityC;
    }
    else if(hue < UINT16_5_6TH_MAX)
    {
        //blue on, red increasing
        redIntensity =  (hue - UINT16_4_6TH_MAX) * dominantIntensityC / UINT16_1_6TH_MAX;
        greenIntensity = 0;
        blueIntensity = dominantIntensityC;
    }
    else
    {
        //red on, blue decreasing
        redIntensity = dominantIntensityC;
        greenIntensity = 0;
        blueIntensity = (UINT16_MAX - hue) * dominantIntensityC / UINT16_1_6TH_MAX;
    }

    /* Scale for Saturation and Value */
    redIntensity += intensityShiftM;
    greenIntensity += intensityShiftM;
    blueIntensity += intensityShiftM;
    
    /* fix the overflow and underflow cases */
    if(redIntensity>UINT16_MAX)
    {
        redIntensity=UINT16_MAX;
    }
    else if(redIntensity<0)
    {
        redIntensity=0;
    }
    
    if(greenIntensity>UINT16_MAX)
    {
        greenIntensity=UINT16_MAX;
    }
    else if(greenIntensity<0)
    {
        greenIntensity=0;
    }
    
    if(blueIntensity>UINT16_MAX)
    {
        blueIntensity=UINT16_MAX;
    }
    else if(blueIntensity<0)
    {
        blueIntensity=0;
    }
    
    LED_RGB_SetColorRGB(redIntensity, greenIntensity, blueIntensity);
}

/* [] END OF FILE */
