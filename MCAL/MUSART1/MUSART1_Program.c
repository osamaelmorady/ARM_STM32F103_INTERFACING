
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/ERROR_STATE.h"


#include "MUSART1/MUSART1_Interface.h"
#include "MUSART1/MUSART1_Private.h"
#include "MUSART1/MUSART1_Config.h"

#include "MRCC/MRCC_Interface.h"
#include "MGPIO/MGPIO_Interface.h"






/******************************************************************************/
/******************************************************************************/
ErrorState  MUSART1_EnuInit (void) 
{
	/******* USART Clock Enable ********/
	MRCC_EnuEnablePeriphClock(MRCC_GPIO) ;
	MRCC_EnuEnablePeriphClock(MRCC_AFIO) ;
	MRCC_EnuEnablePeriphClock(MRCC_USART1) ;

	MGPIO_EnuSetPinDir(PIN_A9,OUTPUT_10MHZ_PP_AF) ;
	MGPIO_EnuSetPinDir(PIN_A10,INPUT_FLOAT) ;

	/******* Baud Rate Setup ********/
	u32 Local_U32Mantissa =  MUSART1_USARTDIV_VAL /100   ;
	
	u32 Local_U32Fractional =  ( MUSART1_USARTDIV_VAL %100 ) * 16  ;
	
	if ( Local_U32Fractional >= 1552 )

		{ Local_U32Mantissa += 1 ;   Local_U32Fractional = 0  ;    }
	


	/******* Reset all Flags to zero *******/
	MUSART1 -> SR  = 0 ;		/* Clear all flags by writing 1 */
		
	

	/******* MUSART1_WORD_LENGTH ********/
	#if MUSART1_WORD_LENGTH == MUSART1_DATA_LENGTH_8_BITS
		
		CLR_BIT ( MUSART1 -> CR1 , 12 )  ;
	
	#elif  MUSART1_WORD_LENGTH == MUSART1_DATA_LENGTH_9_BITS
	
		SET_BIT ( MUSART1 -> CR1 , 12 )  ;
	
	#else 
		#error "Attention, Wrong MUSART1_WORD_LENGTH !!"
	#endif
	

	
	
	
		/******* MUSART1_COMPLETE_TRANSMIT_INT ********/
	#if		 MUSART1_COMPLETE_TRANSMIT_INT == MUSART1_COMPLETE_TRANSMIT_INT_DISABLED
		
		CLR_BIT ( MUSART1 -> CR1 , 6 )  ;
	
	#elif  MUSART1_COMPLETE_TRANSMIT_INT == MUSART1_COMPLETE_TRANSMIT_INT_ENABLED
	
		SET_BIT ( MUSART1 -> CR1 , 6 )  ;
	
	#else 
		#error "Attention, Wrong MUSART1_COMPLETE_TRANSMIT_INT !!"
	#endif
	
	
	
	
		/******* MUSART1_TRANSMIT_INT ********/
	#if	 MUSART1_TRANSMIT_INT == MUSART1_TRANSMIT_INT_DISABLED
		
		CLR_BIT ( MUSART1 -> CR1 , 7 )  ;
	
	#elif  MUSART1_TRANSMIT_INT == MUSART1_TRANSMIT_INT_ENABLED
		
		SET_BIT ( MUSART1 -> CR1 , 7 )  ;
	
	#else 
		#error "Attention, Wrong MUSART1_TRANSMIT_INT !!"
	#endif
	
	
	
	
		/******* MUSART1_RECEIVER_INT ********/
	#if	 MUSART1_RECEIVER_INT == MUSART1_RECEIVER_INT_DISABLED
		
			CLR_BIT ( MUSART1 -> CR1 , 5 )  ;
	
	#elif  MUSART1_RECEIVER_INT == MUSART1_RECEIVER_INT_ENABLED
	
		SET_BIT ( MUSART1 -> CR1 , 5 )  ;
	
	#else 
		#error "Attention, Wrong MUSART1_RECEIVER_INT !!"
	#endif
	
	
	
	
		/******* MUSART1_PARITY ********/
	#if	 MUSART1_PARITY == MUSART1_PARITY_DISABLED
		
		CLR_BIT ( MUSART1 -> CR1 , 10 )  ;
	
	#elif  MUSART1_PARITY == MUSART1_PARITY_EVEN
	
		SET_BIT ( MUSART1 -> CR1 , 10 )  ;
		CLR_BIT ( MUSART1 -> CR1 , 9 )  ;


	#elif  MUSART1_PARITY == MUSART1_PARITY_ODD

		SET_BIT ( MUSART1 -> CR1 , 10 )  ;
		SET_BIT ( MUSART1 -> CR1 , 9 )  ;
		
	#else 
		#error "Attention, Wrong MUSART1_PARITY !!"
	#endif
	
	
	
	
		/******* MUSART1_STOP_BITS ********/
	#if	 MUSART1_STOP_BITS == MUSART1_STOP_BITS_1
		
		CLR_BIT ( MUSART1 -> CR2 , 12 )  ;
		CLR_BIT ( MUSART1 -> CR2 , 13 )  ;
	
	#elif  MUSART1_STOP_BITS == MUSART1_STOP_BITS_0_5
	
		SET_BIT ( MUSART1 -> CR1 , 12 )  ;
		CLR_BIT ( MUSART1 -> CR1 , 13 )  ;
	
	#elif  MUSART1_STOP_BITS == MUSART1_STOP_BITS_1_5
	
		CLR_BIT ( MUSART1 -> CR1 , 12 )  ;
		SET_BIT ( MUSART1 -> CR1 , 13 )  ;
	
	#elif  MUSART1_STOP_BITS == MUSART1_STOP_BITS_2
	
		SET_BIT ( MUSART1 -> CR1 , 12 )  ;
		SET_BIT ( MUSART1 -> CR1 , 13 )  ;
	
	#else 
		#error "Attention, Wrong MUSART1_PARITY !!"
	#endif


		/******* MUSART1_DATA_GATE ********/
#if MUSART1_DATA_GATE == MUSART1_TX_RX_GATE_EN
	/* Enable Transmit Gate */
		SET_BIT ( MUSART1 -> CR1 , 3 ) ;
	/* Enable Receive Gate */
		SET_BIT ( MUSART1 -> CR1 , 2 ) ;


#elif MUSART1_DATA_GATE == MUSART1_TX_RX_GATE_DIS
	/* Disable Transmit Gate */
		CLR_BIT ( MUSART1 -> CR1 , 3 ) ;
	/* Disable Receive Gate */
		CLR_BIT ( MUSART1 -> CR1 , 2 ) ;


#elif MUSART1_DATA_GATE == MUSART1_RX_GATE_EN
	/* Disable Transmit Gate */
		CLR_BIT ( MUSART1 -> CR1 , 3 ) ;
	/* Enable Receive Gate */
		SET_BIT ( MUSART1 -> CR1 , 2 ) ;


#elif MUSART1_DATA_GATE == MUSART1_TX_GATE_EN
	/* Enable Transmit Gate */
		SET_BIT ( MUSART1 -> CR1 , 3 ) ;
	/* Disable Receive Gate */
		CLR_BIT ( MUSART1 -> CR1 , 2 ) ;


#else
	#error  "Attention, Wrong MUSART1_DATA_GATE !!"

#endif




	/******* MUSART1_CLK (Synchronous) - (Asynchronous) ********/
#if	 MUSART1_CLK == MUSART1_CLK_DISABLED

	/* Disable Clock (Asynchronous) */
	CLR_BIT ( MUSART1 -> CR2 , 11 )  ;

#elif  MUSART1_CLK == MUSART1_CLK_ENABLED

	MUSART1 -> CR2 &=  0xF9FF  ;

	/* Clock Polarity */
	MUSART1 -> CR2 &= MUSART1_CLK_POL ;

	/* Clock Phase */
	MUSART1 -> CR2 &= MUSART1_CLK_PHASE  ;

	/* Enable Clock (Synchronous) */
	SET_BIT ( MSUART1 -> CR2 , 11 )  ;

#else
	#error "Attention, Wrong MUSART1_CLK !!"
#endif



	/******* MUSART1_CTS_HW ********/
#if	 MUSART1_CTS_HW == MUSART1_CTS_HW_DISABLE

	CLR_BIT ( MUSART1 -> CR3 , 9 )  ;

#elif  MUSART1_CTS_HW == MUSART1_CTS_HW_ENABLE

	SET_BIT ( MUSART1 -> CR3 , 9 )  ;

#else
	#error "Attention, Wrong MUSART1_CTS_HW !!"
#endif



	/******* MUSART1_RTS_HW ********/
#if	 MUSART1_RTS_HW == MUSART1_RTS_HW_DISABLE

	CLR_BIT ( MUSART1 -> CR3 , 8 )  ;

#elif  MUSART1_RTS_HW == MUSART1_RTS_HW_ENABLE

	SET_BIT ( MUSART1 -> CR3 , 8 )  ;

#else
	#error "Attention, Wrong MUSART1_RTS_HW !!"
#endif



	/******* Baud Rate Configuration *******/
	MUSART1 -> BRR = (( Local_U32Mantissa << 4 ) | ( Local_U32Fractional /100 )   ) ; 	//MUSART1 -> BRR = 0x341 ;

	/******* Enable The USART1 *******/
	SET_BIT ( MUSART1 -> CR1 , 13 ) ;

	return ES_OK ;
}




/******************************************************************************/
/******************************************************************************/
ErrorState  MUSART1_EnuDisable(void) 
{
		/******* Enable The USART1 *******/
	CLR_BIT ( MUSART1 -> CR1 , 13 ) ;
	
	return ES_OK ;
}





/******************************************************************************/
/******************************************************************************/
ErrorState  MUSART1_EnuSendChar (u8 Copy_U8CharToSend) 
{
	MUSART1 -> DR  = Copy_U8CharToSend ;
	
	while ( GET_BIT(  MUSART1 -> SR , 6) == 0  )  ;
	
	CLR_BIT ( MUSART1 -> SR , 6 ) ;
	
	return ES_OK ;
	
}



/******************************************************************************/
/******************************************************************************/
ErrorState  MUSART1_EnuSendString (u8 * Copy_PU8ArrayToSend) 
{
	u32 Local_U8Counter = 0 ;
	
	while ( Copy_PU8ArrayToSend[Local_U8Counter] !='\0')
		{
			MUSART1_EnuSendChar( Copy_PU8ArrayToSend[Local_U8Counter] )  ;
			
			Local_U8Counter ++ ;
		}
	
	return ES_OK ;
	
}



/******************************************************************************/
/******************************************************************************/
ErrorState  MUSART1_EnuReceiveChar (u8 * Copy_PU8CharToReceive) 
{
	while ( GET_BIT(  MUSART1 -> SR , 5) == 0  )  ;
	
	* Copy_PU8CharToReceive = (u8)MUSART1 -> DR    ;
	
	CLR_BIT ( MUSART1 -> SR , 5 ) ;
	
	return ES_OK ;
	
}



/******************************************************************************/
/******************************************************************************/
ErrorState  MUSART1_EnuReceiveString (u8 * Copy_PU8StringToReceive , u8 Copy_U8StopChar) 
{
	u8 Local_U8Counter = 0 ;
	
	do 
	{
		MUSART1_EnuReceiveChar(&Copy_PU8StringToReceive[ Local_U8Counter ])  ;
		
		Local_U8Counter++ ;
		
	} while ( Copy_PU8StringToReceive[ Local_U8Counter -1 ] != Copy_U8StopChar ) ;
	
	
	return ES_OK ;	
}

/******************************************************************************/
/******************************************************************************/
static void (* CallBackPTR[3])(void) ;


ErrorState  MUSART1_EnuSetCallBack ( u8 Copy_U8InterruptType ,void (* Pfun)(void) ) 
{
	CallBackPTR[Copy_U8InterruptType]  =  Pfun ;
	
	return ES_OK ;	
	
}




void USART1_IRQHandler(void) 
{
	
	if ( GET_BIT (MUSART1 -> SR , 7) )
	{
		CallBackPTR[MUSART1_INT_TXE]() ;
		
		MUSART1 -> DR  = 0 ;		/* To Reset TXE Bit , Write a value on Data Register*/
		
	}

	if ( GET_BIT (MUSART1 -> SR , 6) )
	{	
		CallBackPTR[MUSART1_INT_TC]() ;
		
		CLR_BIT ( MUSART1 -> SR , 6 ) ;
	}

	if ( GET_BIT (MUSART1 -> SR , 5) )
	{
		CallBackPTR[MUSART1_INT_RXE]() ;
		
		CLR_BIT ( MUSART1 -> SR , 5 ) ;
	}	
		
			
}



















