/*******************************************************************************
* File Name: Right_out.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Right_out.h"

static Right_out_BACKUP_STRUCT  Right_out_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Right_out_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Right_out_SUT.c usage_Right_out_Sleep_Wakeup
*******************************************************************************/
void Right_out_Sleep(void)
{
    #if defined(Right_out__PC)
        Right_out_backup.pcState = Right_out_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Right_out_backup.usbState = Right_out_CR1_REG;
            Right_out_USB_POWER_REG |= Right_out_USBIO_ENTER_SLEEP;
            Right_out_CR1_REG &= Right_out_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Right_out__SIO)
        Right_out_backup.sioState = Right_out_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Right_out_SIO_REG &= (uint32)(~Right_out_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Right_out_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Right_out_Sleep() for an example usage.
*******************************************************************************/
void Right_out_Wakeup(void)
{
    #if defined(Right_out__PC)
        Right_out_PC = Right_out_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Right_out_USB_POWER_REG &= Right_out_USBIO_EXIT_SLEEP_PH1;
            Right_out_CR1_REG = Right_out_backup.usbState;
            Right_out_USB_POWER_REG &= Right_out_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Right_out__SIO)
        Right_out_SIO_REG = Right_out_backup.sioState;
    #endif
}


/* [] END OF FILE */
