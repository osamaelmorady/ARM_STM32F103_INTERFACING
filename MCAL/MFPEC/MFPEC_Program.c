#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/ERROR_STATE.h"


#include "MRCC/MRCC_Interface.h"
#include "MRCC/MRCC_Private.h"

#include "MFPEC/MFPEC_Interface.h"
#include "MFPEC/MFPEC_Private.h"
#include "MFPEC/MFPEC_Config.h"




#define BASE_ADDRESS	0x08000000

#define BL_FIRST_PAGE	0
#define BL_LAST_PAGE	5

#define APP_FIRST_PAGE	6
#define APP_LAST_PAGE	64






/**********************************************************************************************************/
/********************************************  MFPEC Init   **********************************************/
/**********************************************************************************************************/
ErrorState   MFPEC_EnuInit ( void )
{
	/* Switch to HSI System Clock */
		MRCC ->	CFGR = 0x00000000  ;

	/* SET HSION=1  , HSITRIM as Standard = (10000) , Bypass HSEBYP=0 for INT RC */
		MRCC -> CR =0x00000081 ;

	/* Wait for the flag to be fired */
		while( !GET_BIT( MRCC -> CR , CR_HSIRDY )	) ;

	MRCC_EnuEnablePeriphClock( MRCC_FLITF ) ; /* Flash Interface */

	return ES_OK ;
}





/**********************************************************************************************************/
/********************************  MFPEC Erase The Whole ROM APP Memory  **********************************/
/**********************************************************************************************************/
ErrorState   MFPEC_EnuEraseApp ( void )
{
	for (u8 Local_U8Iterator = APP_FIRST_PAGE ; Local_U8Iterator < APP_LAST_PAGE  ; Local_U8Iterator++ )
	{
		MFPEC_EnuErasePage ( Local_U8Iterator ) ;
	}

	return ES_OK ;
}






/*****************************************************************************************************************/
/********************************  MFPEC Erase The Whole ROM Boatloader Memory  **********************************/
/*****************************************************************************************************************/
ErrorState   MFPEC_EnuEraseBoatloader ( void )
{
	for (u8 Local_U8Iterator = BL_FIRST_PAGE ; Local_U8Iterator < BL_LAST_PAGE  ; Local_U8Iterator++ )
	{
		MFPEC_EnuErasePage ( Local_U8Iterator ) ;
	}

	return ES_OK ;
}








/*****************************************************************************************************/
/********************************  MFPEC Erase The ROM By Page Num  **********************************/
/*****************************************************************************************************/
ErrorState   MFPEC_EnuErasePage ( u8 Copy_U8Page )
{
	if (GET_BIT(MFPEC -> CR , LOCK ) == 1 )
	{
		MFPEC -> KEYR = KEY1 ;
		MFPEC -> KEYR = KEY2 ;
	}

	/* Page Erase Option Select */
	SET_BIT( MFPEC -> CR , PER )  ;

	/* Set Page Number To erase */
	MFPEC -> AR = BASE_ADDRESS + ( Copy_U8Page * 1024 )  ;

	/* Start Erase */
	SET_BIT( MFPEC -> CR , START )  ;

	/* Wait on Busy Flag */
	while ( GET_BIT(MFPEC -> SR , BSY ) == 1 )  ;

	/* Clear the EOP BIT */
	SET_BIT( MFPEC -> SR , EOP )  ;

	/* Page Erase Option Deselect */
	CLR_BIT( MFPEC -> CR , PER )  ;


	return ES_OK ;
}





/*****************************************************************************************************/
/********************************  MFPEC Erase The ROM ( Mass Erase )  **********************************/
/*****************************************************************************************************/
ErrorState   MFPEC_EnuMassErase (void )
{
	if (GET_BIT(MFPEC -> CR , 7 ) == 1 )
	{
		MFPEC -> KEYR = KEY1 ;
		MFPEC -> KEYR = KEY2 ;
	}

	/* Mass Erase Option Select */
	SET_BIT( MFPEC -> CR , MER )  ;

	/* Start Erase */
	SET_BIT( MFPEC -> CR , START )  ;

	/* Wait on Busy Flag */
	while ( GET_BIT(MFPEC -> SR , BSY ) == 1 )  ;

	/* Clear the EOP BIT */
	SET_BIT( MFPEC -> SR , EOP )  ;

	/* Page Erase Option Deselect */
	CLR_BIT( MFPEC -> CR , MER )  ;


	return ES_OK ;
}






/*****************************************************************************************************/
/************************************  MFPEC Write on The ROM   **************************************/
/*****************************************************************************************************/
ErrorState   MFPEC_EnuFlashWrite ( u32 Copy_u32Address , u16 * Copy_PU16Data , u8 Copy_U8DataLength )
{
	/* Wait on Busy Flag */
	while ( GET_BIT(MFPEC -> SR , BSY ) == 1 )  ;

	if (GET_BIT(MFPEC -> CR , LOCK ) == 1 )
	{
		MFPEC -> KEYR = KEY1 ;
		MFPEC -> KEYR = KEY2 ;
	}

	/* Flashing Option Select */
	SET_BIT( MFPEC -> CR , PG )  ;

	for (u8 Local_U8Iterator=0 ; Local_U8Iterator < Copy_U8DataLength  ; Local_U8Iterator++ )
	{
		/* Write Data on Address */
		*((volatile u16 *)Copy_u32Address) = Copy_PU16Data[Local_U8Iterator] ;

		/* ROM is 1 Byte Width, But FPEC Access 2Bytes(u16) Per Time */
		Copy_u32Address += 2   ;

		/* Wait on Busy Flag */
		while ( GET_BIT(MFPEC -> SR , BSY ) == 1 )  ;

		/* Clear the EOP BIT */
		SET_BIT( MFPEC -> SR , EOP )  ;

	}

	/* Flashing Option Deselect */
	CLR_BIT( MFPEC -> CR , PG )  ;

	/* lOCK FPEC */
	SET_BIT( MFPEC -> CR , LOCK )  ;

	return ES_OK ;
}








/*********************************************************************************/
/********************************  IRQ Handlers  *********************************/
/*********************************************************************************/
void FLASH_IRQHandler(void)
{
	
}


