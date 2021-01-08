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
#include "7SEG/_7SEG_Interface.h"


int main (void)
{


MRCC_InitSysClk() ;
MRCC_voidEnablePeriphClock( MRCC_GPIO ) ;


_7SEG_EnuInit( ) ;



MGPIO_EnuSetPinDir(PIN_B0,OUTPUT_10MHZ_PP) ;
MGPIO_EnuSetPinDir(PIN_B1,OUTPUT_10MHZ_PP) ;




while(1)
{

for (u8 i=0;i<10;i++)
{
	MGPIO_EnuSetPinVal(PIN_B0,HIGH) ;
	_7SEG_EnuShowNumber(i) ;
	_delay_ms(400) ;
	MGPIO_EnuSetPinVal(PIN_B0,LOW) ;
}

_delay_ms(10) ;

for (u8 i=0;i<10;i++)
{
	MGPIO_EnuSetPinVal(PIN_B1,HIGH) ;
	_7SEG_EnuShowNumber(i) ;
	_delay_ms(400) ;
	MGPIO_EnuSetPinVal(PIN_B1,LOW) ;
}


_delay_ms(500) ;

u8 i,j ;

for (u8 i=0;i<10;i++)
{
	MGPIO_EnuSetPinVal(PIN_B0,HIGH) ;
	_7SEG_EnuShowNumber(i) ;
	_delay_ms(300) ;
	MGPIO_EnuSetPinVal(PIN_B0,LOW) ;

	for (u8 j=0;j<10;j++)
	{


		MGPIO_EnuSetPinVal(PIN_B1,HIGH) ;
		_7SEG_EnuShowNumber(j) ;
		_delay_ms(10) ;
		MGPIO_EnuSetPinVal(PIN_B1,LOW) ;

	}

}














}

return 0 ;
}





