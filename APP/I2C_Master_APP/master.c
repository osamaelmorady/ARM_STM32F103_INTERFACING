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
#include "MAFIO/MAFIO_Interface.h"
#include "MI2C1/MI2C1_Interface.h"


int main (void)
{
MRCC_InitSysClk() ;

MI2C1_EnuInit() ;

MGPIO_EnuSetPinDir(PIN_C13,OUTPUT_2MHZ_PP) ;


while(1)
{
	MI2C1_EnuStartCondition() ;
	MI2C1_EnuMasterSendAddress(0x50,1) ;
	MI2C1_EnuMasterSendData('A') ;
	MI2C1_EnuStopCondition() ;

	_delay_ms(500) ;

	MGPIO_EnuTogglePinVal(PIN_C13) ;

}

return 0 ;
}





