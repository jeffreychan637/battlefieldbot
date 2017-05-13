/***************************************************************************//**
* \file UART_Debug_BOOT.h
* \version 3.20
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_UART_Debug_H)
#define CY_SCB_BOOT_UART_Debug_H

#include "UART_Debug_PVT.h"

#if (UART_Debug_SCB_MODE_I2C_INC)
    #include "UART_Debug_I2C.h"
#endif /* (UART_Debug_SCB_MODE_I2C_INC) */

#if (UART_Debug_SCB_MODE_EZI2C_INC)
    #include "UART_Debug_EZI2C.h"
#endif /* (UART_Debug_SCB_MODE_EZI2C_INC) */

#if (UART_Debug_SCB_MODE_SPI_INC || UART_Debug_SCB_MODE_UART_INC)
    #include "UART_Debug_SPI_UART.h"
#endif /* (UART_Debug_SCB_MODE_SPI_INC || UART_Debug_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define UART_Debug_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_Debug) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (UART_Debug_SCB_MODE_I2C_INC)
    #define UART_Debug_I2C_BTLDR_COMM_ENABLED     (UART_Debug_BTLDR_COMM_ENABLED && \
                                                            (UART_Debug_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART_Debug_I2C_SLAVE_CONST))
#else
     #define UART_Debug_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (UART_Debug_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (UART_Debug_SCB_MODE_EZI2C_INC)
    #define UART_Debug_EZI2C_BTLDR_COMM_ENABLED   (UART_Debug_BTLDR_COMM_ENABLED && \
                                                         UART_Debug_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define UART_Debug_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART_Debug_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (UART_Debug_SCB_MODE_SPI_INC)
    #define UART_Debug_SPI_BTLDR_COMM_ENABLED     (UART_Debug_BTLDR_COMM_ENABLED && \
                                                            (UART_Debug_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART_Debug_SPI_SLAVE_CONST))
#else
        #define UART_Debug_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (UART_Debug_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (UART_Debug_SCB_MODE_UART_INC)
       #define UART_Debug_UART_BTLDR_COMM_ENABLED    (UART_Debug_BTLDR_COMM_ENABLED && \
                                                            (UART_Debug_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (UART_Debug_UART_RX_DIRECTION && \
                                                              UART_Debug_UART_TX_DIRECTION)))
#else
     #define UART_Debug_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART_Debug_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define UART_Debug_BTLDR_COMM_MODE_ENABLED    (UART_Debug_I2C_BTLDR_COMM_ENABLED   || \
                                                     UART_Debug_SPI_BTLDR_COMM_ENABLED   || \
                                                     UART_Debug_EZI2C_BTLDR_COMM_ENABLED || \
                                                     UART_Debug_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Debug_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void UART_Debug_I2CCyBtldrCommStart(void);
    void UART_Debug_I2CCyBtldrCommStop (void);
    void UART_Debug_I2CCyBtldrCommReset(void);
    cystatus UART_Debug_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_Debug_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (UART_Debug_SCB_MODE_I2C_CONST_CFG)
        #define UART_Debug_CyBtldrCommStart   UART_Debug_I2CCyBtldrCommStart
        #define UART_Debug_CyBtldrCommStop    UART_Debug_I2CCyBtldrCommStop
        #define UART_Debug_CyBtldrCommReset   UART_Debug_I2CCyBtldrCommReset
        #define UART_Debug_CyBtldrCommRead    UART_Debug_I2CCyBtldrCommRead
        #define UART_Debug_CyBtldrCommWrite   UART_Debug_I2CCyBtldrCommWrite
    #endif /* (UART_Debug_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Debug_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Debug_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART_Debug_EzI2CCyBtldrCommStart(void);
    void UART_Debug_EzI2CCyBtldrCommStop (void);
    void UART_Debug_EzI2CCyBtldrCommReset(void);
    cystatus UART_Debug_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_Debug_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (UART_Debug_SCB_MODE_EZI2C_CONST_CFG)
        #define UART_Debug_CyBtldrCommStart   UART_Debug_EzI2CCyBtldrCommStart
        #define UART_Debug_CyBtldrCommStop    UART_Debug_EzI2CCyBtldrCommStop
        #define UART_Debug_CyBtldrCommReset   UART_Debug_EzI2CCyBtldrCommReset
        #define UART_Debug_CyBtldrCommRead    UART_Debug_EzI2CCyBtldrCommRead
        #define UART_Debug_CyBtldrCommWrite   UART_Debug_EzI2CCyBtldrCommWrite
    #endif /* (UART_Debug_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Debug_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Debug_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void UART_Debug_SpiCyBtldrCommStart(void);
    void UART_Debug_SpiCyBtldrCommStop (void);
    void UART_Debug_SpiCyBtldrCommReset(void);
    cystatus UART_Debug_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_Debug_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (UART_Debug_SCB_MODE_SPI_CONST_CFG)
        #define UART_Debug_CyBtldrCommStart   UART_Debug_SpiCyBtldrCommStart
        #define UART_Debug_CyBtldrCommStop    UART_Debug_SpiCyBtldrCommStop
        #define UART_Debug_CyBtldrCommReset   UART_Debug_SpiCyBtldrCommReset
        #define UART_Debug_CyBtldrCommRead    UART_Debug_SpiCyBtldrCommRead
        #define UART_Debug_CyBtldrCommWrite   UART_Debug_SpiCyBtldrCommWrite
    #endif /* (UART_Debug_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Debug_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Debug_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void UART_Debug_UartCyBtldrCommStart(void);
    void UART_Debug_UartCyBtldrCommStop (void);
    void UART_Debug_UartCyBtldrCommReset(void);
    cystatus UART_Debug_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_Debug_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (UART_Debug_SCB_MODE_UART_CONST_CFG)
        #define UART_Debug_CyBtldrCommStart   UART_Debug_UartCyBtldrCommStart
        #define UART_Debug_CyBtldrCommStop    UART_Debug_UartCyBtldrCommStop
        #define UART_Debug_CyBtldrCommReset   UART_Debug_UartCyBtldrCommReset
        #define UART_Debug_CyBtldrCommRead    UART_Debug_UartCyBtldrCommRead
        #define UART_Debug_CyBtldrCommWrite   UART_Debug_UartCyBtldrCommWrite
    #endif /* (UART_Debug_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Debug_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Debug_BTLDR_COMM_ENABLED)
    #if (UART_Debug_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void UART_Debug_CyBtldrCommStart(void);
        void UART_Debug_CyBtldrCommStop (void);
        void UART_Debug_CyBtldrCommReset(void);
        cystatus UART_Debug_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus UART_Debug_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (UART_Debug_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_Debug)
        #define CyBtldrCommStart    UART_Debug_CyBtldrCommStart
        #define CyBtldrCommStop     UART_Debug_CyBtldrCommStop
        #define CyBtldrCommReset    UART_Debug_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_Debug_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_Debug_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_Debug) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Debug_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define UART_Debug_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define UART_Debug_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define UART_Debug_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define UART_Debug_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef UART_Debug_SPI_BYTE_TO_BYTE
    #define UART_Debug_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef UART_Debug_UART_BYTE_TO_BYTE
    #define UART_Debug_UART_BYTE_TO_BYTE  (175u)
#endif /* UART_Debug_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_UART_Debug_H) */


/* [] END OF FILE */
