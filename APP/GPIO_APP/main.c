/*
 * main.c
 *
 *  Created on: Dec 5, 2020
 *      Author: Osama Elmorady
 */


#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MRCC/MRCC_Interface.h"
#include "MGPIO/MGPIO_Interface.h"




int main (void)
{


MRCC_InitSysClk() ;

MRCC_voidEnablePeriphClock( MRCC_GPIO ) ;



for (u8 PIN_NUM=0 ; PIN_NUM<PIN34 ; PIN_NUM++)

	MGPIO_EnuSetPinDir(PIN_NUM,OUTPUT_10MHZ_PP) ;



while(1)
{

for (u8 PIN_NUM=0;PIN_NUM<PIN34;PIN_NUM++)

	{MGPIO_EnuSetPinVal(PIN_NUM,HIGH) ;}



/*delay*/
for (u64 i=0;i<400000;i++)	{asm("nop") ;}




for (u8 PIN_NUM=0;PIN_NUM<PIN34;PIN_NUM++)

	{MGPIO_EnuSetPinVal(PIN_NUM,LOW) ;}



/*delay*/
for (u64 i=0;i<400000;i++)	{asm("nop") ;}

}





return 0 ;
}























