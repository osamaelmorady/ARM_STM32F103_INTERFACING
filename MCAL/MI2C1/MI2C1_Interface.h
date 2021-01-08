#ifndef 	_MI2C1_INTERFACE_H_
#define 	_MI2C1_INTERFACE_H_


#include "LIB/ERROR_STATE.h"



typedef enum
{
	DATA_READ =0	,	DATA_WRITE

}DATA_Direction ;



/*************************************************************************/
/*************************************************************************/
ErrorState		MI2C1_EnuInit( void ) ;









/*************************************************************************/
/*************************************************************************/
ErrorState		MI2C1_EnuStartCondition	( void ) ;
ErrorState		MI2C1_EnuReStartCondition ( void ) ;
ErrorState		MI2C1_EnuStopCondition	( void ) ;


/*************************************************************************/
ErrorState		MI2C1_EnuMasterSendAddress( u8 Copy_U8SlaveAddress , u8 Copy_U8Mode ) ;


/*************************************************************************/
/*************************************************************************/
ErrorState		MI2C1_EnuMasterSendData( u8 Copy_U8DataToSend ) ;
ErrorState		MI2C1_EnuMasterReceiveData( u8 * Copy_PU8DataToReceive ) ;






/*************************************************************************/
ErrorState		MI2C1_EnuSlaveCheckAddress( void ) ;


/*************************************************************************/
/*************************************************************************/
ErrorState		MI2C1_EnuSlaveSendData( u8 Copy_U8DataToSend ) ;
ErrorState		MI2C1_EnuSlaveReceiveData( u8 * Copy_PU8DataToReceive ) ;









#endif
