/*
 * main.c
 *
 *  Created on: Dec 5, 2020
 *      Author: Osama Elmorady
 */


#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/DELAY.h"

#include "MRCC/MRCC_Interface.h"
#include "MGPIO/MGPIO_Interface.h"
#include "MNVIC/MNVIC_Interface.h"
#include "MSTK/MSTK_Interface.h"



void fun1(void) ;
//void fun2(void) ;


int main (void)
{


MRCC_InitSysClk() ;
MSTK_EnuTimerInit() ;

MRCC_voidEnablePeriphClock( MRCC_GPIO ) ;

MGPIO_EnuSetPinDir( PIN0 , OUTPUT_10MHZ_PP ) ;
MGPIO_EnuSetPinDir( PIN1 , OUTPUT_10MHZ_PP ) ;

MGPIO_EnuSetPinVal(PIN0,LOW) ;
MGPIO_EnuSetPinVal(PIN1,LOW) ;


MSTK_EnuPeriodicInterval(200000,fun1) ;

//MSTK_EnuSingleInterval(1000000,fun2) ;


while(1)
{



}





return 0 ;
}



void fun1(void)
{
	MGPIO_EnuTogglePinVal(PIN0) ;

}

/*
void fun2(void)
{
	MGPIO_EnuTogglePinVal(PIN1) ;

}
*/
















