/*******************************************************************************
* File Name: front_wheels.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_front_wheels_ALIASES_H) /* Pins front_wheels_ALIASES_H */
#define CY_PINS_front_wheels_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define front_wheels_0			(front_wheels__0__PC)
#define front_wheels_0_PS		(front_wheels__0__PS)
#define front_wheels_0_PC		(front_wheels__0__PC)
#define front_wheels_0_DR		(front_wheels__0__DR)
#define front_wheels_0_SHIFT	(front_wheels__0__SHIFT)
#define front_wheels_0_INTR	((uint16)((uint16)0x0003u << (front_wheels__0__SHIFT*2u)))

#define front_wheels_INTR_ALL	 ((uint16)(front_wheels_0_INTR))


#endif /* End Pins front_wheels_ALIASES_H */


/* [] END OF FILE */
