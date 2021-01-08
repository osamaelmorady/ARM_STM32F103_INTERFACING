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

void Flashing(void) ;
void Ping_Pong(void) ;
void Flower(void) ;



int main (void)
{


MRCC_InitSysClk() ;
MSTK_EnuTimerInit() ;
_7SEG_EnuInit() ;



MRCC_voidEnablePeriphClock( MRCC_GPIO ) ;



for (u8 PIN_NUM=0 ; PIN_NUM < PIN34 ; PIN_NUM++)
	MGPIO_EnuSetPinDir( PIN_NUM , OUTPUT_10MHZ_PP ) ;


while(1)
{

	MSTK_EnuBusyDelay(500000) ;




	Ping_Pong() ;
	MSTK_EnuBusyDelay(500000) ;






	Flashing() ;
	MSTK_EnuBusyDelay(500000) ;







	Flower() ;
	MSTK_EnuBusyDelay(500000) ;

}





return 0 ;
}



void Flashing(void)
{
for (u8 i=0 ; i<4 ;i++)

{
	for (u8 PIN_NUM=0 ; PIN_NUM <8 ; PIN_NUM++)
		MGPIO_EnuSetPinVal(PIN_NUM,HIGH) ;

	MSTK_EnuBusyDelay(200000) ;

	_7SEG_EnuShowNumber(i+1) ;

	for (u8 PIN_NUM=0 ; PIN_NUM <8 ; PIN_NUM++)
		MGPIO_EnuSetPinVal(PIN_NUM,LOW) ;

	MSTK_EnuBusyDelay(200000) ;


}

_7SEG_EnuShowNumber(0) ;
}




void Flower(void)
{

	for (u8 i=0 ; i<4 ;i++)

	{
		for (u8 PIN_NUM=0 ; PIN_NUM <4 ; PIN_NUM++)

			{
				MGPIO_EnuSetPinVal(PIN_NUM,HIGH) ;
				MGPIO_EnuSetPinVal(7-PIN_NUM,HIGH) ;
				MSTK_EnuBusyDelay(100000) ;

				MGPIO_EnuSetPinVal(PIN_NUM,LOW) ;
				MGPIO_EnuSetPinVal(7-PIN_NUM,LOW) ;
				MSTK_EnuBusyDelay(100000) ;
			}

		_7SEG_EnuShowNumber(i+1) ;


		for (s8 PIN_NUM=3 ; PIN_NUM >=0 ; PIN_NUM--)

			{
				MGPIO_EnuSetPinVal(PIN_NUM,HIGH) ;
				MGPIO_EnuSetPinVal(7-PIN_NUM,HIGH) ;
				MSTK_EnuBusyDelay(100000) ;

				MGPIO_EnuSetPinVal(PIN_NUM,LOW) ;
				MGPIO_EnuSetPinVal(7-PIN_NUM,LOW) ;
				MSTK_EnuBusyDelay(100000) ;

			}


	}


	_7SEG_EnuShowNumber(0) ;


}



void Ping_Pong(void)
{

for (u8 i=0 ; i<4 ; i++)
{
	for (u8 PIN_NUM=0 ; PIN_NUM <=7 ; PIN_NUM++)

	{
		MGPIO_EnuSetPinVal(PIN_NUM,HIGH) ;
		MSTK_EnuBusyDelay(100000) ;
		MGPIO_EnuSetPinVal(PIN_NUM,LOW) ;
		MSTK_EnuBusyDelay(100000) ;
	}

	_7SEG_EnuShowNumber(i+1) ;

	for (s8 PIN_NUM=7 ; PIN_NUM >=0 ; PIN_NUM--)

		{
			MGPIO_EnuSetPinVal(PIN_NUM,HIGH) ;
			MSTK_EnuBusyDelay(100000) ;
			MGPIO_EnuSetPinVal(PIN_NUM,LOW) ;
			MSTK_EnuBusyDelay(100000) ;
		}


}

_7SEG_EnuShowNumber(0) ;

}









