#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/ERROR_STATE.h"


#include "PARSER/PARSER_Interface.h"
#include "PARSER/PARSER_Private.h"
#include "PARSER/PARSER_Config.h"



u32 PARSER_U32Address = 0x08000000   ;

u16 PARSER_U16Data[8] = {0} ;


/****************************************************************************************************/
/****************************************************************************************************/
ErrorState  PARSE_EnuASCiiToHex( u8 Copy_U8Data , u8 * Copy_PU8HexData)
{
	ErrorState error ;

	if ( Copy_U8Data >= '0' && Copy_U8Data <= '9' )
	{
		* Copy_PU8HexData = Copy_U8Data - '0'   ;

		error = ES_OK ;
	}
	else if ( Copy_U8Data >= 'A' && Copy_U8Data <= 'F' )
	{
		* Copy_PU8HexData = Copy_U8Data - 'A' + 10   ;

		error = ES_OK ;
	}
	else
	{
		error = ES_OUT_RANGE ;
	}
	

	return error ;
}




/****************************************************************************************************/
/****************************************************************************************************/
ErrorState  PARSE_EnuParseCharCount( u8 * Copy_U8Record , u8 *Copy_Pu8ParsedCC )
{
	u8 Local_u8CCDigits[2]={0} ;

	/*CharCount Record */
	PARSE_EnuASCiiToHex ( Copy_U8Record[2] , &Local_u8CCDigits[0])  ;

	PARSE_EnuASCiiToHex ( Copy_U8Record[1] , &Local_u8CCDigits[1] ) ;

	* Copy_Pu8ParsedCC = Local_u8CCDigits[0] | ( Local_u8CCDigits[1] << 4 )  ;


	return ES_OK ;
}





/****************************************************************************************************/
/****************************************************************************************************/
ErrorState  PARSE_EnuParseAddress( u8 * Copy_U8Record , u16 * Copy_Pu16ParsedAddress )
{
	u8  Local_u8AdsDigits[4]={0} ;


	 /* Clear the First 4 Hex_digits and conserve the last 4 digits for the base address */
	PARSER_U32Address  =  (* Copy_Pu16ParsedAddress) & 0xFFFF0000   ;


	/*Address Record */
	for (u8 i=0 ; i < 4 ; i++)
	{
		PARSE_EnuASCiiToHex ( Copy_U8Record[(6-i)] , &Local_u8AdsDigits[i] )  ;


		* Copy_Pu16ParsedAddress |= ( Local_u8AdsDigits[i] << ( 4*i ) )  ;
	}

	return ES_OK ;
}





/****************************************************************************************************/
/****************************************************************************************************/
ErrorState  PARSE_EnuParseData( u8 * Copy_U8Record , u8 Copy_Pu8CharCounts , u16 * Copy_Pu16ParsedData  )
{
	u8  Local_u8DataDigits[4]={0} ;

	/* Data Record */
	for (u8 DataNum = 0 ; DataNum < ( Copy_Pu8CharCounts / 2 ) ; DataNum++ )   /* by 2 as it send 2 bytes by 2 bytes */
	{
		/* Load the 4 digits of each data */
		for (u8 j=0 ; j < 4 ; j++)
			{
				PARSE_EnuASCiiToHex ( Copy_U8Record[ 12+(4*DataNum) - j ] , &Local_u8DataDigits[ (4*DataNum) + j])  ;

				Copy_Pu16ParsedData[DataNum] |= ( Local_u8DataDigits[j] << (4 * j) )  ;   /* Little Indian */

			}

	#if  DATA_STORE	==	BIG_INDIAN

		/* Little Indian - To - Big Indian Transformation */
		PARSER_U16Data[DataNum] =  ( ( PARSER_U16Data[DataNum] << 8 ) |  ( PARSER_U16Data[DataNum] >> 8 ) ) ;

	#endif

	}

	return ES_OK ;
}







/****************************************************************************************************/
/***********************************  Record Parsing  ***********************************************/
/****************************************************************************************************/
ErrorState  PARSE_EnuParseRecord( u8 * Copy_U8Record , u16 * Copy_Pu8ParsedAddress , u16 * Copy_Pu16ParsedData , u8 * Copy_Pu8ParsedCC)
{
	ErrorState error ;
	
	* Copy_Pu8ParsedCC = 0 ;

	switch (Copy_U8Record[8])
	{
		case '0' :

			PARSE_EnuParseCharCount( Copy_U8Record , Copy_Pu8ParsedCC ) ;

			 PARSE_EnuParseAddress( Copy_U8Record , Copy_Pu8ParsedAddress ) ;

			 PARSE_EnuParseData( Copy_U8Record , * Copy_Pu8ParsedCC , Copy_Pu16ParsedData  ) ;

			error = ES_OK ;

		break ;

		case '4' :

			/* Set the High Address */

			/* PARSER_U32Address = NewStartingAddress    ; */

			error = ES_OK ;

		break ;

		default :

			error = ES_OUT_RANGE  ;

		break ;
	}

	return error ;
}








