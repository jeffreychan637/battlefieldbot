/*******************************************************************************
* File Name: back_wheels.h  
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

#if !defined(CY_PINS_back_wheels_ALIASES_H) /* Pins back_wheels_ALIASES_H */
#define CY_PINS_back_wheels_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define back_wheels_0			(back_wheels__0__PC)
#define back_wheels_0_PS		(back_wheels__0__PS)
#define back_wheels_0_PC		(back_wheels__0__PC)
#define back_wheels_0_DR		(back_wheels__0__DR)
#define back_wheels_0_SHIFT	(back_wheels__0__SHIFT)
#define back_wheels_0_INTR	((uint16)((uint16)0x0003u << (back_wheels__0__SHIFT*2u)))

#define back_wheels_INTR_ALL	 ((uint16)(back_wheels_0_INTR))


#endif /* End Pins back_wheels_ALIASES_H */


/* [] END OF FILE */
