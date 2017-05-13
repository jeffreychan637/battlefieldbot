/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_UART_Debug_H)
#define CY_SCB_PVT_UART_Debug_H

#include "UART_Debug.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_Debug_SetI2CExtClkInterruptMode(interruptMask) UART_Debug_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_Debug_ClearI2CExtClkInterruptSource(interruptMask) UART_Debug_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_Debug_GetI2CExtClkInterruptSource()                (UART_Debug_INTR_I2C_EC_REG)
#define UART_Debug_GetI2CExtClkInterruptMode()                  (UART_Debug_INTR_I2C_EC_MASK_REG)
#define UART_Debug_GetI2CExtClkInterruptSourceMasked()          (UART_Debug_INTR_I2C_EC_MASKED_REG)

#if (!UART_Debug_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_Debug_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_Debug_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_Debug_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_Debug_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_Debug_GetExtSpiClkInterruptSource()                 (UART_Debug_INTR_SPI_EC_REG)
    #define UART_Debug_GetExtSpiClkInterruptMode()                   (UART_Debug_INTR_SPI_EC_MASK_REG)
    #define UART_Debug_GetExtSpiClkInterruptSourceMasked()           (UART_Debug_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_Debug_CY_SCBIP_V1) */

#if(UART_Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_Debug_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_Debug_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_Debug_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_Debug_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_Debug_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_Debug_CUSTOM_INTR_HANDLER) */
#endif /* (UART_Debug_SCB_IRQ_INTERNAL) */

extern UART_Debug_BACKUP_STRUCT UART_Debug_backup;

#if(UART_Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_Debug_scbMode;
    extern uint8 UART_Debug_scbEnableWake;
    extern uint8 UART_Debug_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_Debug_mode;
    extern uint8 UART_Debug_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_Debug_rxBuffer;
    extern uint8   UART_Debug_rxDataBits;
    extern uint32  UART_Debug_rxBufferSize;

    extern volatile uint8 * UART_Debug_txBuffer;
    extern uint8   UART_Debug_txDataBits;
    extern uint32  UART_Debug_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_Debug_numberOfAddr;
    extern uint8 UART_Debug_subAddrSize;
#endif /* (UART_Debug_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (UART_Debug_SCB_MODE_I2C_CONST_CFG || \
        UART_Debug_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 UART_Debug_IntrTxMask;
#endif /* (! (UART_Debug_SCB_MODE_I2C_CONST_CFG || \
              UART_Debug_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_Debug_SCB_MODE_I2C_RUNTM_CFG     (UART_Debug_SCB_MODE_I2C      == UART_Debug_scbMode)
    #define UART_Debug_SCB_MODE_SPI_RUNTM_CFG     (UART_Debug_SCB_MODE_SPI      == UART_Debug_scbMode)
    #define UART_Debug_SCB_MODE_UART_RUNTM_CFG    (UART_Debug_SCB_MODE_UART     == UART_Debug_scbMode)
    #define UART_Debug_SCB_MODE_EZI2C_RUNTM_CFG   (UART_Debug_SCB_MODE_EZI2C    == UART_Debug_scbMode)
    #define UART_Debug_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_Debug_SCB_MODE_UNCONFIG == UART_Debug_scbMode)

    /* Defines wakeup enable */
    #define UART_Debug_SCB_WAKE_ENABLE_CHECK       (0u != UART_Debug_scbEnableWake)
#endif /* (UART_Debug_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_Debug_CY_SCBIP_V1)
    #define UART_Debug_SCB_PINS_NUMBER    (7u)
#else
    #define UART_Debug_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_Debug_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_Debug_H) */


/* [] END OF FILE */
