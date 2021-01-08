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


void EXTI0_IRQHandler(void)
{
	MGPIO_EnuSetPinVal(PIN0,HIGH) ;

	;

}



int main (void)
{


MRCC_InitSysClk() ;

MRCC_voidEnablePeriphClock( MRCC_GPIO ) ;



MNVIC_EnuInit() ;

MNVIC_EnuEnableIRQ(MNVIC_EXTI0) ;



MGPIO_EnuSetPinDir( PIN0 , OUTPUT_10MHZ_PP ) ;

MNVIC_EnuSetPendingIRQ(MNVIC_EXTI0) ;


MGPIO_EnuSetPinVal(PIN0,LOW) ;

/*delay*/
//delay_ms(500) ;










while(1)
{



}





return 0 ;
}























