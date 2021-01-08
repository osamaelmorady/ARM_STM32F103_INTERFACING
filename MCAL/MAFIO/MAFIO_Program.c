#include  "LIB/STD_TYPES.h"
#include  "LIB/BIT_MATH.h"
#include  "LIB/ERROR_STATE.h"


#include  "MAFIO/MAFIO_Interface.h"
#include  "MAFIO/MAFIO_Private.h"
#include  "MAFIO/MAFIO_Config.h"









/*******************************************************************************************************/
/********************************* Alternating Functions Initialization ********************************/
/*******************************************************************************************************/

ErrorState  MAFIO_EnuInit(void)  
{
	AFIO -> EXTICR[0] = 0x00000000	;
	AFIO -> EXTICR[1] = 0x00000000	;
	AFIO -> EXTICR[2] = 0x00000000	;
	AFIO -> EXTICR[3] = 0x00000000	;
	
	return ES_OK ;
}






/**********************************************************************************************************/
/*********************************  Alternating EXTI (External Interrupt)  ********************************/
/**********************************************************************************************************/

ErrorState	MAFIO_EnuEXTIMapping (u8 Copy_U8EXTIChannel,u8 Copy_U8EXTIDesiredPort) 
{
	/* Copy_U8EXTIChannel Remapped only by Port and Parralel Pin , Offset by 16 between PORTS from PORTA : PORTC */
	if ( Copy_U8EXTIDesiredPort >= 0 && Copy_U8EXTIChannel <= 3)
	{
		/* Clear the Last Values */
		AFIO -> EXTICR[Copy_U8EXTIChannel/4]  &= ~( 0b1111 << ( (Copy_U8EXTIChannel%4) * 4) )  	;
		
		/*  Set the new Values */
		AFIO -> EXTICR[Copy_U8EXTIChannel/4]  |=  ( Copy_U8EXTIDesiredPort << ( (Copy_U8EXTIChannel%4) * 4) )  	;
	}
	
	else 
	{
		return ES_OUT_RANGE ;
	}
	
	
	return ES_OK ;
	
}








/***********************************************************************************************************/
/*******************************  Alternating USART1 ( A9 - A10) to ( B6 - B7 ) ****************************/
/***********************************************************************************************************/

ErrorState	MAFIO_EnuUSART1Mapping (u8 Copy_U8PortMapping) 
{
	/* Copy_U8PortMapping Remapped only by Port and Parralel Pin , Offset Tx Rx  from PORTA : PORTB */
	if ( Copy_U8PortMapping == MAFIO_PORTA_MAPPING )
	/* PORTA Remapping */
	{
		CLR_BIT( AFIO -> MAPR , 2 ) 	;
	}
	
	else if  ( Copy_U8PortMapping == MAFIO_PORTB_MAPPING ) 
	/* PORTB Remapping */
	{
		SET_BIT( AFIO -> MAPR , 2 ) 	;
	}
	
	else 
	{
		return ES_OUT_RANGE ;
	}
	
	
	return ES_OK ;
	
}






/**********************************************************************************************************/
/*****************************  Alternating SPI1 ( A4 : A7) to ( A15 - B3 : B5 ) **************************/
/**********************************************************************************************************/

ErrorState	MAFIO_EnuSPI1Mapping (u8 Copy_U8PortMapping)
{
	/* Copy_U8PortMapping Remapped only by Port and Parralel Pin , Offset Tx Rx  from PORTA : PORTB */
	if ( Copy_U8PortMapping == MAFIO_PORTA_MAPPING )
	/* PORTA Remapping */
	{
		CLR_BIT( AFIO -> MAPR , 0 ) 	;
	}
	
	else if  ( Copy_U8PortMapping == MAFIO_PORTB_MAPPING ) 
	/* PORTB Remapping */
	{
		SET_BIT( AFIO -> MAPR , 0 ) 	;
	}
	
	else 
	{
		return ES_OUT_RANGE ;
	}
	
	
	return ES_OK ;
	
	
}











