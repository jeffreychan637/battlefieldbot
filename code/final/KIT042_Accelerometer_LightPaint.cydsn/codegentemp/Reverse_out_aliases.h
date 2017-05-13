/*******************************************************************************
* File Name: Reverse_out.h  
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

#if !defined(CY_PINS_Reverse_out_ALIASES_H) /* Pins Reverse_out_ALIASES_H */
#define CY_PINS_Reverse_out_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Reverse_out_0			(Reverse_out__0__PC)
#define Reverse_out_0_PS		(Reverse_out__0__PS)
#define Reverse_out_0_PC		(Reverse_out__0__PC)
#define Reverse_out_0_DR		(Reverse_out__0__DR)
#define Reverse_out_0_SHIFT	(Reverse_out__0__SHIFT)
#define Reverse_out_0_INTR	((uint16)((uint16)0x0003u << (Reverse_out__0__SHIFT*2u)))

#define Reverse_out_INTR_ALL	 ((uint16)(Reverse_out_0_INTR))


#endif /* End Pins Reverse_out_ALIASES_H */


/* [] END OF FILE */
