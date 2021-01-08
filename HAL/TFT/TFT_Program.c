

#include  "LIB/BIT_MATH.h"
#include  "LIB/STD_TYPES.h"
#include  "LIB/ERROR_STATE.h"
#include  "LIB/DELAY.h"


#include "MRCC/MRCC_Interface.h"
#include "MGPIO/MGPIO_Interface.h"
#include "MSPI/MSPI_Interface.h"
#include "MSTK/MSTK_Interface.h"


u8 HTFT_U8Temp ;

ErrorState	HTFT_EnuInit(void) 
{	

	MRCC_EnuInit()  ;
	
	MSTK_EnuInit()  ;
	
	MRCC_EnuEn
	
	
	/*  */
	MGPIO_EnuSetPinDir(TFT_RESET_PIN , OUTPUT_10MHZ_PP ) ;
	MGPIO_EnuSetPinDir(TFT_A0_PIN , OUTPUT_10MHZ_PP ) ;
	MGPIO_EnuSetPinDir(TFT_SCLK_PIN , OUTPUT_10MHZ_PP_AF ) ;
	MGPIO_EnuSetPinDir(TFT_RESET_PIN , OUTPUT_10MHZ_PP_AF ) ;
	
	
	/* Reset Sequence */
	MGPIO_EnuSetPinVal( TFT_RESET_PIN , HIGH )  ;
	
	MGPIO_EnuSetPinVal( TFT_RESET_PIN , HIGH )  ;
	
	MGPIO_EnuSetPinVal( TFT_RESET_PIN , HIGH )  ;
	
	MGPIO_EnuSetPinVal( TFT_RESET_PIN , HIGH )  ;
	
	MGPIO_EnuSetPinVal( TFT_RESET_PIN , HIGH )  ;
	
	
	return ES_OK ;
}



ErrorState	HTFT_EnuDisplayImage(const u16 * Copy_U16Image) 
{
	
	
	
	
	
	
}



static void	HTFT_EnuSendCommand(u8 Copy_U8Command) 
{
	MGPIO_EnuSetPinVal( TFT_A0_PIN , LOW ) ;
	
	MSPI1_EnuSendReceiveSync( Copy_U8Command , &HTFT_U8Temp ) ;
	
	return ES_OK ;
}






static void	HTFT_EnuSendData(u8 Copy_U8Data) 
{
	MGPIO_EnuSetPinVal( TFT_A0_PIN , HIGH ) ;
	
	MSPI1_EnuSendReceiveSync( Copy_U8Data , &HTFT_U8Temp ) ;
	
	return ES_OK ;
	
}


