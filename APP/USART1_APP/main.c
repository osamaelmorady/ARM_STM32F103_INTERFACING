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
#include "MUSART1/MUSART1_Interface.h"



int main (void)
{


MRCC_InitSysClk() ;
MRCC_EnuEnablePeriphClock( MRCC_GPIO ) ;


MUSART1_EnuInit() ;

u8 C = 'A' ;

while(1)
{

MUSART1_EnuReceiveChar(&C) ;

MUSART1_EnuSendChar(C) ;



}

return 0 ;
}





