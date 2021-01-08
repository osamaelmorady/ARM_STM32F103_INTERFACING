#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/ERROR_STATE.h"


#include "MSPI1/MSPI1_Interface.h"
#include "MSPI1/MSPI1_Private.h"
#include "MSPI1/MSPI1_Config.h"

#include "MRCC/MRCC_Interface.h"
#include  "MGPIO/MGPIO_Interface.h" 



/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
ErrorState		MSPI1_EnuInit( void ) 
{
	/***** MRCC Clock Enable  *****/
	MRCC_EnuEnablePeriphClock(MRCC_AFIO) ;
	MRCC_EnuEnablePeriphClock(MRCC_SPI1) ;
	MRCC_EnuEnablePeriphClock(MRCC_GPIO) ;

	/***** Reset All Configurations *****/
	MSPI1 -> CR1 =0x00 ;
	(void) MSPI1 -> SR ;


/* 1) ************ BAUD RATE CONFIG ***********************/
/************************************************************/
	MSPI1 -> CR1 &= 0xFFC7    ;

	MSPI1 -> CR1 |= MSPI1_BAUD_RATE << 3 ;

/* 2) ************  Clock Polarity  ***********************/
/************************************************************/
#if MSPI1_CPOL	==	MSPI1_CPOL_LOW_0

	CLR_BIT ( MSPI1 -> CR1 , 1 ) ;

#elif MSPI1_CPOL	==	MSPI1_CPOL_HIGH_1

	SET_BIT ( MSPI1 -> CR1 , 1 ) ;

#else

#endif



/* 2) ************  Clock Phase  ***********************/
/************************************************************/
	#if MSPI1_CPHA	==	MSPI1_READ_WRITE

		CLR_BIT ( MSPI1 -> CR1 , 0 ) ;

	#elif MSPI1_CPHA	==	MSPI1_WRITE_READ

		SET_BIT ( MSPI1 -> CR1 , 0 ) ;

	#else

	#endif





/* 3) ****************  Frame Format  ***************************/
/************************************************************/
#if MSPI1_DATA_FRAME_FORMAT	==	MSPI1_LSB

	SET_BIT ( MSPI1 -> CR1 , 7 ) ;

#elif MSPI1_DATA_FRAME_FORMAT	==	MSPI1_HSB

	CLR_BIT ( MSPI1 -> CR1 , 7 ) ;

#else

#endif





/* 4) ****************  Data Size  ***************************/
/************************************************************/
#if MSPI1_DATA_SIZE	==	MSPI1_DATA_SIZE_8_BITS

	CLR_BIT ( MSPI1 -> CR1 , 11 ) ;

#elif MSPI1_DATA_SIZE	==	MSPI1_DATA_SIZE_16_BITS

	SET_BIT ( MSPI1 -> CR1 , 11 ) ;

#else

#endif



/* 5) ************  Transmission Type  ***********************/
/************************************************************/
#if MSPI1_DUPLEX_DIRECTION	==	MSPI1_DUPLEX_FULL

	CLR_BIT ( MSPI1 -> CR1 , 15 ) ;

#elif MSPI1_DUPLEX_DIRECTION	==	MSPI1_DUPLEX_HALF_RECIEVE

	SET_BIT ( MSPI1 -> CR1 , 15 ) ;
	CLR_BIT ( MSPI1 -> CR1 , 14 ) ;


#elif MSPI1_DUPLEX_DIRECTION	==	MSPI1_DUPLEX_HALF_TRANSMIT

	SET_BIT ( MSPI1 -> CR1 , 15 ) ;
	SET_BIT ( MSPI1 -> CR1 , 14 ) ;

#else

#endif




/* 6) ************  MSPI1_MODE_TYPE (Master) (Slave)  ***********************/
/************************************************************/
#if MSPI1_MODE_TYPE	 ==	MSPI1_MODE_MASTER

	/* Pin Configurations  */
	MGPIO_EnuSetPinDir( PIN_A4 , OUTPUT_2MHZ_PP_AF)	;		//	NSSI
	MGPIO_EnuSetPinDir( PIN_A5 , OUTPUT_2MHZ_PP_AF)	;		//	SCK
	MGPIO_EnuSetPinDir( PIN_A6 , INPUT_FLOAT )			;	//	MISO
	MGPIO_EnuSetPinDir( PIN_A7 , OUTPUT_2MHZ_PP_AF)	;		//	MOSI


	#if  SSM_CONFIG  == SSM_CONFIG_HARDWARE

		/* SSM */
		CLR_BIT ( MSPI1 -> CR1 , 9 ) ;

	#elif 	SSM_CONFIG  == SSM_CONFIG_SOFTWARE

		/* SSM , Software */
		SET_BIT ( MSPI1 -> CR1 , 9 ) ;

		/* SSI , Slave Not Selected (Master Selected) */
		SET_BIT ( MSPI1 -> CR1 , 8 ) ;

	#else
		#error 	"Attention, Wrong SSM_CONFIG !!"
	#endif


	/* SSOE  , Set the NSS Pin With SW Automatically or Use NSS as Normal GPIO */
	#if MSPI1_MULTI_MASTER	==	MSPI1_MULTI_MASTER_ENABLE

		CLR_BIT ( MSPI1 -> CR2 , 2 ) ;

	#elif MSPI1_MULTI_MASTER	==	MSPI1_MULTI_MASTER_DISABLE

		SET_BIT ( MSPI1 -> CR2 , 2 ) ;

	#else
		#error 	"Attention, Wrong MSPI1_MULTI_MASTER !!"
	#endif

	/****** Enable Master Mode *******/
		SET_BIT ( MSPI1 -> CR1 , 2 ) ;




#elif MSPI1_MODE_TYPE	==	MSPI1_MODE_SLAVE



	/* Pin Configurations  */
	MGPIO_EnuSetPinDir( PIN_A5 , INPUT_FLOAT )	;				//	SCK
	MGPIO_EnuSetPinDir( PIN_A6 , OUTPUT_10MHZ_PP_AF )		;	//	MISO
	MGPIO_EnuSetPinDir( PIN_A7 , INPUT_FLOAT )	;				//	MOSI

	#if  SSM_CONFIG  == SSM_CONFIG_HARDWARE

		/* SSM */
		CLR_BIT ( MSPI1 -> CR1 , 9 ) ;

		MGPIO_EnuSetPinDir( PIN_A4 , INPUT_FLOAT )	;			//	NSSI

	#elif 	SSM_CONFIG  == SSM_CONFIG_SOFTWARE

		/* SSM */
		SET_BIT ( MSPI1 -> CR1 , 9 ) ;

		/* SSI */
		CLR_BIT ( MSPI1 -> CR1 , 8 ) ;
		MSPI1 -> CR1 |= NSS_CONFIG << 8   ;


	#else
		#error 	"Attention, Wrong SSM_CONFIG !!"
	#endif

	/* Enable Slave Mode */
		CLR_BIT ( MSPI1 -> CR1 , 2 ) ;
	/*********************************/

#else
	#error 	"Attention, Wrong MSPI1_MODE_TYPE !!"
#endif




	/******* Enable SPI ********/
		SET_BIT ( MSPI1 -> CR1 , 6 ) ;

	return ES_OK ;
}








/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
ErrorState		MSPI1_EnuDisable( void ) 
{
	/* Disable SPI */
	CLR_BIT ( MSPI1 -> CR1 , 6 ) ;
	
	return ES_OK ;
	
}



/********************************************************************************/
ErrorState		MSPI1_EnuSendData( u8 Copy_U8DataToSend  )
{

	/* Send Data */
	MSPI1 -> DR = Copy_U8DataToSend   ;

	/* Wait For RXNE Flag to Be 1 ,then send data */
	while ( GET_BIT( MSPI1 -> SR , 0  ) == 0  )  ;			/* Wait until RXNE become Not Empty */

	return ES_OK ;

}





/********************************************************************************/
ErrorState		MSPI1_EnuReceiveData( u8 * Copy_PU8DataToReceive )
{
	/* Wait ForTXE Flag to Be 1 ,then Receive the data */
		while ( GET_BIT( MSPI1 -> SR , 0  ) == 0  )  ;			/* Wait until RXE become Not Empty */

	/* Receive Data */
	* Copy_PU8DataToReceive   =   MSPI1 -> DR   ;

	return ES_OK ;
	
}






	
/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
ErrorState		MSPI1_EnuSendReceiveSync( u8 Copy_U8DataToSend , u8 * Copy_PU8DataToReceive ) 
{
	/* Interrupt Disabled */
	MSPI1 -> CR2 &= ~ 0xC0   ;
	
	/* Send Data */
	MSPI1 -> DR = Copy_U8DataToSend   ;

	/* Wait For Busy Flag to Be Cleared , So Bus Get Freed */
	while ( GET_BIT( MSPI1 -> SR , 7  ) == 1  )  ;			/* Wait until Not Busy */

	/* Receive Data */
	* Copy_PU8DataToReceive   =   MSPI1 -> DR   ;

	return ES_OK ;
}








/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
static void (* MSPI1_PFun)(u8 Copy_U8Data) ;


ErrorState		MSPI1_EnuSendReceiveAsync( u8 Copy_U8DataToSend , void (* Copy_VoidCallBackPFun)( u8 Copy_U8DataToReceive )  )
{
	MSPI1_PFun  =  Copy_VoidCallBackPFun  ;

	/* Interrupt Control Enabled */
	MSPI1 -> CR2 &= ~ 0xC0   ;
	MSPI1 -> CR2 |=  MSPI1_TX_RX_INTERUPT     ;
	
	/* Send Data */
	MSPI1 -> DR = Copy_U8DataToSend   ;

	return ES_OK ;
}









/********************************************************************************/
void SPI1_IRQHandler(void)
{
	MSPI1_PFun ( MSPI1 -> DR )  ;
	
}







