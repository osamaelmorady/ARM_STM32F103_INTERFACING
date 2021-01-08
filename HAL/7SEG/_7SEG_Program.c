
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "LIB/ERROR_STATE.h"

#include "MGPIO/MGPIO_Interface.h"

#include "7SEG/_7SEG_Interface.h"
#include "7SEG/_7SEG_Config.h"
#include "7SEG/_7SEG_Private.h"



/****************************************************************/
/*************** Initialization of the 7 Segment ****************/
/****************************************************************/
ErrorState _7SEG_EnuInit(void)
{

	MGPIO_EnuSetPinDir( _7SEG_A   ,  OUTPUT_10MHZ_PP  ) ;
	MGPIO_EnuSetPinDir( _7SEG_B   ,  OUTPUT_10MHZ_PP  ) ;
	MGPIO_EnuSetPinDir( _7SEG_C   ,  OUTPUT_10MHZ_PP  ) ;
	MGPIO_EnuSetPinDir( _7SEG_D   ,  OUTPUT_10MHZ_PP  ) ;
	MGPIO_EnuSetPinDir( _7SEG_E   ,  OUTPUT_10MHZ_PP  ) ;
	MGPIO_EnuSetPinDir( _7SEG_F   ,  OUTPUT_10MHZ_PP  ) ;
	MGPIO_EnuSetPinDir( _7SEG_G   ,  OUTPUT_10MHZ_PP  ) ;
	MGPIO_EnuSetPinDir( _7SEG_DOT ,  OUTPUT_10MHZ_PP  ) ;

#if _7SEG_TYPE == K_TYPE

	MGPIO_EnuSetPinVal( _7SEG_A   ,  LOW ) ;
	MGPIO_EnuSetPinVal( _7SEG_B   ,  LOW ) ;
	MGPIO_EnuSetPinVal( _7SEG_C   ,  LOW ) ;
	MGPIO_EnuSetPinVal( _7SEG_D   ,  LOW ) ;
	MGPIO_EnuSetPinVal( _7SEG_E   ,  LOW ) ;
	MGPIO_EnuSetPinVal( _7SEG_F   ,  LOW ) ;
	MGPIO_EnuSetPinVal( _7SEG_G   ,  LOW ) ;
	MGPIO_EnuSetPinVal( _7SEG_DOT ,  LOW ) ;


#elif _7SEG_TYPE == A_TYPE

	MGPIO_EnuSetPinVal( _7SEG_A   ,  HIGH ) ;
	MGPIO_EnuSetPinVal( _7SEG_B   ,  HIGH ) ;
	MGPIO_EnuSetPinVal( _7SEG_C   ,  HIGH ) ;
	MGPIO_EnuSetPinVal( _7SEG_D   ,  HIGH ) ;
	MGPIO_EnuSetPinVal( _7SEG_E   ,  HIGH ) ;
	MGPIO_EnuSetPinVal( _7SEG_F   ,  HIGH ) ;
	MGPIO_EnuSetPinVal( _7SEG_G   ,  HIGH ) ;
	MGPIO_EnuSetPinVal( _7SEG_DOT ,  HIGH ) ;



#else
	#error "Wrong 7Segment Type Input"
#endif

	return ES_OK ;
}







/**************************************************************************/
/*************** Show A Number from 0-9 and '.' on 7Segment ***************/
/**************************************************************************/

static u8 _7SEGMENT_U8Numbers[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

ErrorState _7SEG_EnuShowNumber(u8 Local_U8ShowedNumber)
{
	ErrorState error = ES_NOK ;

#if _7SEG_TYPE == K_TYPE

	if ( Local_U8ShowedNumber>=0 && Local_U8ShowedNumber<=9 )
	{
		MGPIO_EnuSetPinVal ( _7SEG_A   , ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 0 ) &	1	) ) ;
		MGPIO_EnuSetPinVal ( _7SEG_B   , ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 1 ) &	1	) ) ;
		MGPIO_EnuSetPinVal ( _7SEG_C   , ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 2 ) &	1	) ) ;
		MGPIO_EnuSetPinVal ( _7SEG_D   , ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 3 ) &	1	) ) ;
		MGPIO_EnuSetPinVal ( _7SEG_E   , ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 4 ) &	1	) ) ;
		MGPIO_EnuSetPinVal ( _7SEG_F   , ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 5 ) &	1	) ) ;
		MGPIO_EnuSetPinVal ( _7SEG_G   , ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 6 ) &	1	) ) ;
		MGPIO_EnuSetPinVal ( _7SEG_DOT , LOW ) ;

		error = ES_OK ;
	}

	else if (Local_U8ShowedNumber=='.')
	{
		MGPIO_EnuSetPinVal ( _7SEG_DOT , HIGH ) ;

		error = ES_OK ;
	}

	else
	{
		error = ES_OUT_OF_RANGE ;
	}


#elif _7SEG_TYPE == A_TYPE

	if ( (Local_U8ShowedNumber >= 0) && (Local_U8ShowedNumber <= 9) )
		{
			MGPIO_EnuSetPinVal ( _7SEG_A   ,! ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 0 ) &	1	) ) ;
			MGPIO_EnuSetPinVal ( _7SEG_B   ,! ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 1 ) &	1	) ) ;
			MGPIO_EnuSetPinVal ( _7SEG_C   ,! ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 2 ) &	1	) ) ;
			MGPIO_EnuSetPinVal ( _7SEG_D   ,! ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 3 ) &	1	) ) ;
			MGPIO_EnuSetPinVal ( _7SEG_E   ,! ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 4 ) &	1	) ) ;
			MGPIO_EnuSetPinVal ( _7SEG_F   ,! ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 5 ) &	1	) ) ;
			MGPIO_EnuSetPinVal ( _7SEG_G   ,! ( ( _7SEGMENT_U8Numbers[Local_U8ShowedNumber] >> 6 ) &	1	) ) ;

			MGPIO_EnuSetPinVal ( _7SEG_DOT , HIGH ) ;

			error = ES_OK ;
		}

		else if (Local_U8ShowedNumber=='.')
		{
			MGPIO_EnuSetPinVal ( _7SEG_DOT , LOW ) ;

			error = ES_OK ;
		}
		else
		{
			error = ES_OUT_RANGE ;
		}

#else


#error "Wrong 7Segment Type Input"


#endif

	return error ;
}
