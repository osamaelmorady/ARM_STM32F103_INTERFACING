/*
 * PARSER_Private.h
 *
 *  Created on: Dec 26, 2020
 *      Author: Osama Elmorady
 */

#ifndef _PARSER_PRIVATE_H_
#define _PARSER_PRIVATE_H_


#include "LIB/ERROR_STATE.h"

/****************************************************************************************************/
/****************************************************************************************************/
static ErrorState  PARSE_EnuASCiiToHex( u8 Copy_U8Data , u8 * Copy_PU8HexData) ;





/****************************************************************************************************/
/****************************************************************************************************/
static ErrorState  PARSE_EnuParseCharCount( u8 * Copy_U8Record , u8 *Copy_Pu8ParsedCC ) ;





/****************************************************************************************************/
/****************************************************************************************************/
static ErrorState  PARSE_EnuParseAddress( u8 * Copy_U8Record , u16 * Copy_Pu8ParsedAddress ) ;




/****************************************************************************************************/
/****************************************************************************************************/
static ErrorState  PARSE_EnuParseData( u8 * Copy_U8Record , u8 Copy_Pu8CharCounts , u16 * Copy_Pu16ParsedData  )  ;




#endif /* PARSER_PRIVATE_H_ */
