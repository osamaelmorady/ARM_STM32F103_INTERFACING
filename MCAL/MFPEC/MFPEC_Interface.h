#ifndef		_MFPEC_INTERFACE_H_
#define 	_MFPEC_INTERFACE_H_


#include "LIB/ERROR_STATE.h"








/**********************************************************************************************************/
/********************************  MFPEC Erase The Whole ROM APP Memory  **********************************/
/**********************************************************************************************************/
ErrorState   MFPEC_EnuEraseAppArea ( void )  ;







/*****************************************************************************************************/
/********************************  MFPEC Erase The ROM By Page Num  **********************************/
/*****************************************************************************************************/
ErrorState   MFPEC_EnuErasePage ( u8 Copy_U8Page )  ;






/*****************************************************************************************************/
/************************************  MFPEC Write on The ROM   **************************************/
/*****************************************************************************************************/
ErrorState   MFPEC_EnuFlashWrite ( u32 Copy_u32Address , u16 * Copy_PU16Data , u8 Copy_U8DataLength )  ;












#endif
