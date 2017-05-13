/*******************************************************************************
* File Name: Trigr.h  
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

#if !defined(CY_PINS_Trigr_ALIASES_H) /* Pins Trigr_ALIASES_H */
#define CY_PINS_Trigr_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Trigr_0			(Trigr__0__PC)
#define Trigr_0_PS		(Trigr__0__PS)
#define Trigr_0_PC		(Trigr__0__PC)
#define Trigr_0_DR		(Trigr__0__DR)
#define Trigr_0_SHIFT	(Trigr__0__SHIFT)
#define Trigr_0_INTR	((uint16)((uint16)0x0003u << (Trigr__0__SHIFT*2u)))

#define Trigr_INTR_ALL	 ((uint16)(Trigr_0_INTR))


#endif /* End Pins Trigr_ALIASES_H */


/* [] END OF FILE */
