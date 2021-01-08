#include  "STD_TYPES.h"
#include  "BIT_MATH.h"


#include	"USART/USART_Interface.h"










ErrorState	ESP_EnuInit() 
{
	u8 Local_U8Result = 0  ;
	
	MUSART1_EnuInit() ;
	
	while( Local_U8Result == 0 )
	{
		/* Disable Echo */
		MUSART1_EnuSendString("ATE0\r\n")  ;
		
		/* Validate REsult */
		Local_U8Result = ESP_vValidateCMD()   ;
		
		
	}
	
	
	
	
	
	
	
	
}


static ErrorState  ESP_EnuValidateCMD() ;

static ErrorState  ESP_EnuValidateCMD() 
{
	ErrorState error = ES_NOK ;
	
	u8 Local_Response[100] ={0}   ;
	
	u8 Local_U8Count = 0 ;
	
	while ( MUSART1_EnuReceiveChar(Local_Response[Local_U8Count]) )
	{
		Local_U8Count ++ ;
		
	}
	
	if ( Local_Response[0]=='O' && Local_Response[1]=='K'  )
	{
		error =  ES_OK  ;
	}
	else
	{
		error = ES_NOK  ;
	}
	
	return error ;
	
}







ErrorState	ESP_EnuSendData(u8 * Copy_U8DataToSend) 
{
	
	
	
	
	
}






ErrorState	ESP_EnuReceiveData(u8 * Copy_U8DataToReceive) 
{
	
	
	
	
	
	
	
}












/******************************************************************************/
/******************************************************************************/
ErrorState  MUSART1_EnuReceiveChar (u8 * Copy_PU8CharToReceive) 
{
	u16 Local_TimeOut = 0 ;
	
	while ( GET_BIT(  MUSART1 -> SR , 5) == 0 )  
	{
		if ( Local_TimeOut > 10000 )
		{
			return ES_NOK ;	
		}
		
		Local_TimeOut++ ;
		
	}
	
	* Copy_PU8CharToReceive = (u8)MUSART1 -> DR    ;
	
	CLR_BIT ( MUSART1 -> SR , 5 ) ;
	
	return ES_OK ;
	
}

