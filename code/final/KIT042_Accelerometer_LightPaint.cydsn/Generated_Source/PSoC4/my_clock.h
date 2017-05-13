/*******************************************************************************
* File Name: my_clock.h
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

#if !defined(CY_CLOCK_my_clock_H)
#define CY_CLOCK_my_clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void my_clock_StartEx(uint32 alignClkDiv);
#define my_clock_Start() \
    my_clock_StartEx(my_clock__PA_DIV_ID)

#else

void my_clock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void my_clock_Stop(void);

void my_clock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 my_clock_GetDividerRegister(void);
uint8  my_clock_GetFractionalDividerRegister(void);

#define my_clock_Enable()                         my_clock_Start()
#define my_clock_Disable()                        my_clock_Stop()
#define my_clock_SetDividerRegister(clkDivider, reset)  \
    my_clock_SetFractionalDividerRegister((clkDivider), 0u)
#define my_clock_SetDivider(clkDivider)           my_clock_SetDividerRegister((clkDivider), 1u)
#define my_clock_SetDividerValue(clkDivider)      my_clock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define my_clock_DIV_ID     my_clock__DIV_ID

#define my_clock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define my_clock_CTRL_REG   (*(reg32 *)my_clock__CTRL_REGISTER)
#define my_clock_DIV_REG    (*(reg32 *)my_clock__DIV_REGISTER)

#define my_clock_CMD_DIV_SHIFT          (0u)
#define my_clock_CMD_PA_DIV_SHIFT       (8u)
#define my_clock_CMD_DISABLE_SHIFT      (30u)
#define my_clock_CMD_ENABLE_SHIFT       (31u)

#define my_clock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << my_clock_CMD_DISABLE_SHIFT))
#define my_clock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << my_clock_CMD_ENABLE_SHIFT))

#define my_clock_DIV_FRAC_MASK  (0x000000F8u)
#define my_clock_DIV_FRAC_SHIFT (3u)
#define my_clock_DIV_INT_MASK   (0xFFFFFF00u)
#define my_clock_DIV_INT_SHIFT  (8u)

#else 

#define my_clock_DIV_REG        (*(reg32 *)my_clock__REGISTER)
#define my_clock_ENABLE_REG     my_clock_DIV_REG
#define my_clock_DIV_FRAC_MASK  my_clock__FRAC_MASK
#define my_clock_DIV_FRAC_SHIFT (16u)
#define my_clock_DIV_INT_MASK   my_clock__DIVIDER_MASK
#define my_clock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_my_clock_H) */

/* [] END OF FILE */
