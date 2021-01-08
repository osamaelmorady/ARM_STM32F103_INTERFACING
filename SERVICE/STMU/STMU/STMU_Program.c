/*
 * STMU_Program.c
 *
 *  Created on: Dec 22, 2020
 *      Author: Osama
 */

/************************************************************************/
/*                               Includes                               */
/************************************************************************/

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "STMU/STMU_Interface.h"
#include "STMU/STMU_Private.h"
#include "STMU/STMU_Config.h"



#include "MSTK/MSTK_Interface.h"

/************************************************************************/

xTask_t	 List[TASK_NUMS] ;








/************************************************************************/
ErrorState   STMU_EnuInit ( void )  
{
	MSTK_EnuInit() ;
	
	return ES_OK ;
	
}







/************************************************************************/
ErrorState   STMU_EnuAddTask ( xTask_t  xTask )  
{
	
	
	
	return ES_OK ;
}
 

 
 
 
 


 
 /************************************************************************/
 ErrorState   STMU_EnuStartScheduler ( u32  xPeriod_ms )  
 {
	
	

	
	return ES_OK ;
 }























