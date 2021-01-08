/*
 * STMU_Interface.h
 *
 *  Created on: Dec 22, 2020
 *      Author: Osama
 */

#ifndef _STMU_INTERFACE_H_
#define _STMU_INTERFACE_H_



#include "LIB/ERROR_STATE.h"


/************************************************************************/
typedef struct 
{
	void ( * xTaskFunPTR )(void)  ;
	
	u8 xTaskPeriodicity ;
	
} xTask_t ;





/************************************************************************/
ErrorState   STMU_EnuInit ( void )  ;






/************************************************************************/
ErrorState   STMU_EnuAddTask ( xTask_t  xTask )  ;
 

 
 
 
 


 
 /************************************************************************/
 ErrorState   STMU_EnuStartScheduler ( u32  xPeriod_ms )  ;










#endif /* STMU_INTERFACE_H_ */
