#ifndef 	_MSPI1_INTERFACE_H_
#define 	_MSPI1_INTERFACE_H_


#include "LIB/ERROR_STATE.h"




/*************************************************************************/
/*************************************************************************/
ErrorState		MSPI1_EnuInit( void ) ;




/*************************************************************************/
/*************************************************************************/
ErrorState		MSPI1_EnuDisable( void ) ;




/*************************************************************************/
/*************************************************************************/
ErrorState		MSPI1_EnuSendData( u8 Copy_U8DataToSend )  ;




/*************************************************************************/
/*************************************************************************/
ErrorState		MSPI1_EnuReceiveData( u8 * Copy_PU8DataToReceive )  ;





/*************************************************************************/
/*************************************************************************/
ErrorState		MSPI1_EnuSendReceiveSync( u8 Copy_U8DataToSend , u8 * Copy_PU8DataToReceive )  ;







/*************************************************************************/
/*************************************************************************/
ErrorState		MSPI1_EnuSendReceiveAsync( u8 Copy_U8DataToSend , void (* Copy_VoidCallBackPFun)( u8 Copy_U8DataToReceive )  )  ;









ErrorState		MSPI1_EnuSendData( u8 Copy_U8DataToSend ) ;





#endif
