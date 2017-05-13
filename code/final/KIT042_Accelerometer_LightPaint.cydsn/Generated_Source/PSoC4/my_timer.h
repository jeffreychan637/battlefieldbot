/*******************************************************************************
* File Name: my_timer.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_my_timer_H)
#define CY_CLOCK_my_timer_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void my_timer_StartEx(uint32 alignClkDiv);
#define my_timer_Start() \
    my_timer_StartEx(my_timer__PA_DIV_ID)

#else

void my_timer_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void my_timer_Stop(void);

void my_timer_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 my_timer_GetDividerRegister(void);
uint8  my_timer_GetFractionalDividerRegister(void);

#define my_timer_Enable()                         my_timer_Start()
#define my_timer_Disable()                        my_timer_Stop()
#define my_timer_SetDividerRegister(clkDivider, reset)  \
    my_timer_SetFractionalDividerRegister((clkDivider), 0u)
#define my_timer_SetDivider(clkDivider)           my_timer_SetDividerRegister((clkDivider), 1u)
#define my_timer_SetDividerValue(clkDivider)      my_timer_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define my_timer_DIV_ID     my_timer__DIV_ID

#define my_timer_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define my_timer_CTRL_REG   (*(reg32 *)my_timer__CTRL_REGISTER)
#define my_timer_DIV_REG    (*(reg32 *)my_timer__DIV_REGISTER)

#define my_timer_CMD_DIV_SHIFT          (0u)
#define my_timer_CMD_PA_DIV_SHIFT       (8u)
#define my_timer_CMD_DISABLE_SHIFT      (30u)
#define my_timer_CMD_ENABLE_SHIFT       (31u)

#define my_timer_CMD_DISABLE_MASK       ((uint32)((uint32)1u << my_timer_CMD_DISABLE_SHIFT))
#define my_timer_CMD_ENABLE_MASK        ((uint32)((uint32)1u << my_timer_CMD_ENABLE_SHIFT))

#define my_timer_DIV_FRAC_MASK  (0x000000F8u)
#define my_timer_DIV_FRAC_SHIFT (3u)
#define my_timer_DIV_INT_MASK   (0xFFFFFF00u)
#define my_timer_DIV_INT_SHIFT  (8u)

#else 

#define my_timer_DIV_REG        (*(reg32 *)my_timer__REGISTER)
#define my_timer_ENABLE_REG     my_timer_DIV_REG
#define my_timer_DIV_FRAC_MASK  my_timer__FRAC_MASK
#define my_timer_DIV_FRAC_SHIFT (16u)
#define my_timer_DIV_INT_MASK   my_timer__DIVIDER_MASK
#define my_timer_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_my_timer_H) */

/* [] END OF FILE */
