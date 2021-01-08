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
#include "MEXTI/MEXTI_Interface.h"
#include "MAFIO/MAFIO_Interface.h"

void fun(void) {

	MGPIO_EnuTogglePinVal(PIN_A1) ;

	/*Remove Debouncing */
	//_delay_ms(50) ;

	;
}

int main (void)
{


MRCC_InitSysClk() ;


MRCC_voidEnablePeriphClock( MRCC_GPIO ) ;
MRCC_voidEnablePeriphClock( MRCC_AFIO ) ;



MGPIO_EnuSetPinDir(PIN_B0,INPUT_PULL_UP ) ;


MGPIO_EnuSetPinDir(PIN_A1,OUTPUT_10MHZ_PP ) ;
MGPIO_EnuSetPinVal(PIN_A1,LOW) ;


MNVIC_EnuEnableIRQ( MNVIC_EXTI0_INT ) ;


MEXTI_EnuSetCallBack( MEXTI_CH0, fun ) ;


MEXTI_EnuInit(MEXTI_CH0 , MEXTI_TRIGGER_FALLING) ;







//MNVIC_EnuSetPendingIRQ(MNVIC_EXTI0_INT) ;



while(1)
{


	//MEXTI_EnuChannelSoftWareTrigger(MEXTI_CH0) ;


}





return 0 ;
}





