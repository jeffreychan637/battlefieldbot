/*******************************************************************************
* File Name: Trigr.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Trigr_H) /* Pins Trigr_H */
#define CY_PINS_Trigr_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Trigr_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Trigr_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Trigr_Read(void);
void    Trigr_Write(uint8 value);
uint8   Trigr_ReadDataReg(void);
#if defined(Trigr__PC) || (CY_PSOC4_4200L) 
    void    Trigr_SetDriveMode(uint8 mode);
#endif
void    Trigr_SetInterruptMode(uint16 position, uint16 mode);
uint8   Trigr_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Trigr_Sleep(void); 
void Trigr_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Trigr__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Trigr_DRIVE_MODE_BITS        (3)
    #define Trigr_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Trigr_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Trigr_SetDriveMode() function.
         *  @{
         */
        #define Trigr_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Trigr_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Trigr_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Trigr_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Trigr_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Trigr_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Trigr_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Trigr_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Trigr_MASK               Trigr__MASK
#define Trigr_SHIFT              Trigr__SHIFT
#define Trigr_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Trigr_SetInterruptMode() function.
     *  @{
     */
        #define Trigr_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Trigr_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Trigr_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Trigr_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Trigr__SIO)
    #define Trigr_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Trigr__PC) && (CY_PSOC4_4200L)
    #define Trigr_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Trigr_USBIO_DISABLE              ((uint32)(~Trigr_USBIO_ENABLE))
    #define Trigr_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Trigr_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Trigr_USBIO_ENTER_SLEEP          ((uint32)((1u << Trigr_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Trigr_USBIO_SUSPEND_DEL_SHIFT)))
    #define Trigr_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Trigr_USBIO_SUSPEND_SHIFT)))
    #define Trigr_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Trigr_USBIO_SUSPEND_DEL_SHIFT)))
    #define Trigr_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Trigr__PC)
    /* Port Configuration */
    #define Trigr_PC                 (* (reg32 *) Trigr__PC)
#endif
/* Pin State */
#define Trigr_PS                     (* (reg32 *) Trigr__PS)
/* Data Register */
#define Trigr_DR                     (* (reg32 *) Trigr__DR)
/* Input Buffer Disable Override */
#define Trigr_INP_DIS                (* (reg32 *) Trigr__PC2)

/* Interrupt configuration Registers */
#define Trigr_INTCFG                 (* (reg32 *) Trigr__INTCFG)
#define Trigr_INTSTAT                (* (reg32 *) Trigr__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Trigr_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Trigr__SIO)
    #define Trigr_SIO_REG            (* (reg32 *) Trigr__SIO)
#endif /* (Trigr__SIO_CFG) */

/* USBIO registers */
#if !defined(Trigr__PC) && (CY_PSOC4_4200L)
    #define Trigr_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Trigr_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Trigr_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Trigr_DRIVE_MODE_SHIFT       (0x00u)
#define Trigr_DRIVE_MODE_MASK        (0x07u << Trigr_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Trigr_H */


/* [] END OF FILE */
