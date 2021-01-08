/*
 * lcd.c

 *
 *  Created on: Dec 18, 2020
 *      Author: Osama Elmorady
 */
#include "LIB/STD_TYPES.h"
#include "LIB/DELAY.h"
#include "LIB/BIT_MATH.h"

#include "MRCC/MRCC_Interface.h"
#include "MGPIO/MGPIO_Interface.h"
#include "MAFIO/MAFIO_Interface.h"
#include "LCD/LCD_Interface.h"
#include "MI2C1/MI2C1_Interface.h"


u8 Rec='\0'   ;


int main ()
{
MRCC_InitSysClk() ;
MI2C1_EnuInit() ;


MGPIO_EnuSetPinDir(PIN_C13,OUTPUT_2MHZ_PP) ;
MGPIO_EnuSetPinVal(PIN_C13,LOW) ;

LCD_EnuInit() ;
LCD_EnuSetPosition(0,0) ;
LCD_EnuWriteString("Data Transfered ") ;
_delay_ms(1000) ;
LCD_EnuSendCommand(0x01) ;


while(1)
{
	Rec='\0' ;

	MI2C1_EnuSlaveReceiveData(&Rec) ;

	if (Rec)
	{
		LCD_EnuSendData(Rec) ;

		MGPIO_EnuTogglePinVal(PIN_C13)   ;
	}

}
return 0 ;

}
