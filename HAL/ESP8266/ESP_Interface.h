#ifndef		_ESP_INTERFACE_H_
#define		_ESP_INTERFACE_H_



#include "ERROR_STATE.h"







ErrorState	ESP_EnuInit() ;






ErrorState	ESP_EnuSendData(u8 * Copy_U8DataToSend) ;






ErrorState	ESP_EnuReceiveData(u8 * Copy_U8DataToReceive) ;






















#endif






