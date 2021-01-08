/*
 * main.c
 *
 *  Created on: Dec 31, 2020
 *      Author: Osama Elmorady
 */

#include "LIB/STD_TYPES.h"
#include "LIB/DELAY.h"

#include "MRCC/MRCC_Interface.h"
#include "MEXTI/MEXTI_Interface.h"
#include "MGPIO/MGPIO_Interface.h"
#include "MNVIC/MNVIC_Interface.h"
#include "MSTK/MSTK_Interface.h"

#include "LCD/LCD_Interface.h"



u32 ElabsedTime = 0 ;
u16 distance = 0 ;



void SendSignal(void)
{

	MEXTI_EnuChannelEnable(MEXTI_CH0) ;

	MGPIO_EnuSetPinVal(PIN_A1,HIGH) ;

	ElabsedTime = 0 ;

}

void ReadDistance(void)
{
	MEXTI_EnuChannelDisable(MEXTI_CH0) ;

	MGPIO_EnuSetPinVal(PIN_A1,LOW) ;

	MSTK_EnuGetElapsedTime(&ElabsedTime) ;

	distance = 0 ;

	distance =( (340 *100) * ElabsedTime/1000000 ) /2 ;

	LCD_EnuSendCommand(0x01)  ;

	LCD_EnuSetPosition(0,1) ;

	LCD_EnuWriteIntNum(distance) ;

}



void main(void)
{
MRCC_InitSysClk() ;
MSTK_EnuTimerInit() ;

MRCC_EnuEnablePeriphClock(MRCC_GPIO) ;
MRCC_EnuEnablePeriphClock(MRCC_AFIO) ;



MGPIO_EnuSetPinDir(PIN_A1,OUTPUT_10MHZ_PP)  ;
MGPIO_EnuSetPinDir(PIN_A0,INPUT_PULL_DOWN)  ;


MNVIC_EnuInit() ;
MNVIC_EnuEnableIRQ(MNVIC_EXTI0_INT) ;


MEXTI_EnuInit(MEXTI_CH0 , MEXTI_TRIGGER_RISING) ;

MEXTI_EnuSetCallBack(MEXTI_CH0,ReadDistance) ;


LCD_EnuInit() ;


MSTK_EnuPeriodicInterval(100000, SendSignal ) ;







while(1)
{

}


return;
}

