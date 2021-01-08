#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/ERROR_STATE.h"


#include "MDMA/MDMA_Interface.h"
#include "MDMA/MDMA_Private.h"
#include "MDMA/MDMA_Config.h"







ErrorState 	MDMA_EnuSetConfiguration ( u8 Copy_U8ChannelNum 	, u8 Copy_U8ChannelPriority , u8 Copy_U8DataDirection  , u8 Copy_U8CircularityMode ,
									   u8 Copy_U8MemorySize 	, u8 Copy_U8PeripheralSize  , u8 Copy_U8MemoryInc 		,  u8 Copy_U8PeriperalInc  )										
{
	
	/* Reset all Configurations, MAke Sure DMA is Disabled to begin Configuration */
	MDMA -> CHANNEL[Copy_U8ChannelNum].CCR = 0x00000000 ;

	/* Priority Level  */
	MDMA -> CHANNEL[Copy_U8ChannelNum].CCR |= ( Copy_U8ChannelPriority & 0b11 ) << 12 ;
	
	
	/*  Data Direction */
	MDMA -> CHANNEL[Copy_U8ChannelNum].CCR |= (( (Copy_U8DataDirection & 0b10) >> 1 ) << 14  )   |   ( ( Copy_U8DataDirection & 0b1 ) <<4 )   ;
	
	
	/*  Circularity Mode   -->  Single Operation - Circular Operations */
	MDMA -> CHANNEL[Copy_U8ChannelNum].CCR |= ( Copy_U8CircularityMode & 1 ) << 5 ;
	
	
	
	/* Memory Size   -->   1 - 2 - 4 Bytes*/
	MDMA -> CHANNEL[Copy_U8ChannelNum].CCR |= ( Copy_U8MemorySize & 0b11 ) << 10 ;
	
	
	/* Peripheral Size   -->   1 - 2 - 4 Bytes*/
	MDMA -> CHANNEL[Copy_U8ChannelNum].CCR |= ( Copy_U8PeripheralSize & 0b11 ) << 8 ;
	
	
	
	/* Memory Increment Control  */
	MDMA -> CHANNEL[Copy_U8ChannelNum].CCR |= ( Copy_U8MemoryInc & 1 ) << 7 ;
	
	/* Peripheral Increment Control  */
	MDMA -> CHANNEL[Copy_U8ChannelNum].CCR |= ( Copy_U8PeriperalInc & 1 ) << 6 ;
	

	return ES_OK ;
}








ErrorState 	MDMA_EnuChannelEnable (u8 Copy_U8ChannelNum) 
{
	/*  Clear All Flags  */
	MDMA_EnuClearIntFlag ( Copy_U8ChannelNum , MDMA_TRANSFER_GLOBALL_FLAG ) ;
	
	SET_BIT( MDMA -> CHANNEL[Copy_U8ChannelNum].CCR , 0 )  ;
	
	
	return ES_OK ;
}





ErrorState 	MDMA_EnuChannelDisable (u8 Copy_U8ChannelNum) 
{
	
	CLR_BIT( MDMA -> CHANNEL[Copy_U8ChannelNum].CCR , 0 )  ;
	
	
	return ES_OK ;
	
}





ErrorState 	MDMA_EnuChannelInterruptEnable (u8 Copy_U8ChannelNum , u8 Copy_U8TransferInterrupt) 
{
	MDMA -> CHANNEL[Copy_U8ChannelNum].CCR  |= ( Copy_U8TransferInterrupt & 0b1110 )   ;

	return ES_OK ;
}






ErrorState 	MDMA_EnuChannelInterruptDisable (u8 Copy_U8ChannelNum , u8 Copy_U8TransferInterrupt) 
{
	MDMA -> CHANNEL[Copy_U8ChannelNum].CCR  &= ~( Copy_U8TransferInterrupt & 0b1110 )   ;
	
	return ES_OK ;
}








ErrorState 	MDMA_EnuSetAddress (u8 Copy_U8ChannelNum ,  u32 * Copy_U32SourceAddress , u32 * Copy_U32DestinationAddress , u16 Copy_U16TransactionsNum )
{
	
	MDMA -> CHANNEL[Copy_U8ChannelNum].CMAR		= (u32)Copy_U32SourceAddress		;
	
	MDMA -> CHANNEL[Copy_U8ChannelNum].CPAR		= (u32)Copy_U32DestinationAddress   ;
	
	MDMA -> CHANNEL[Copy_U8ChannelNum].CNDTR	=  Copy_U16TransactionsNum	 ;

	return ES_OK ;
}






ErrorState 	MDMA_EnuClearIntFlag (u8 Copy_U8ChannelNum , u8 Copy_U8TransferInterruptFlag ) 
{
	Copy_U8ChannelNum *= 4   ;
	
	MDMA -> IFCR  &= ~ ( ( Copy_U8TransferInterruptFlag & 0b1111 ) << Copy_U8ChannelNum ) ;

	return ES_OK ;
	
}





ErrorState 	MDMA_EnuGetFlag( u8 Copy_U8ChannelNum , u8 Copy_U8TransferInterruptFlag , u8 * Copy_U8FlagStatus ) 
{
	Copy_U8ChannelNum *= 4   ;
	
	switch ( Copy_U8TransferInterruptFlag )
	{
		case MDMA_TRANSFER_GLOBALL_FLAG  :	* Copy_U8FlagStatus = GET_BIT( MDMA -> ISR , ( 0 + Copy_U8ChannelNum ) )  ;  break  ;
		
		case MDMA_TRANSFER_COMPLETE_FLAG :	* Copy_U8FlagStatus = GET_BIT( MDMA -> ISR , ( 1 + Copy_U8ChannelNum ) )  ;  break  ;
		
		case MDMA_TRANSFER_HALF_FLAG 	:	* Copy_U8FlagStatus = GET_BIT( MDMA -> ISR , ( 2 + Copy_U8ChannelNum ) )  ;  break  ;
		
		case MDMA_TRANSFER_ERROR_FLAG	:	* Copy_U8FlagStatus = GET_BIT( MDMA -> ISR , ( 3 + Copy_U8ChannelNum ) )  ;  break  ;
		
		default  :  return ES_OUT_RANGE ;
		
	}
	
	return ES_OK ;
	
}







static void (* CallBackPTR[7][4])(void) ;


ErrorState 	MDMA_EnuSetCallBack(u8 Copy_U8ChannelNum , u8 Copy_U8TransferInterruptFlag , void (* PFun )(void)  ) 
{
	CallBackPTR[Copy_U8ChannelNum][Copy_U8TransferInterruptFlag] = PFun  ;
	
	return ES_OK ;
	
}





void DMA1_Channel1_IRQHandler(void) 
{
	if (GET_BIT( MDMA -> ISR , 1))
	{
		CallBackPTR[0][1]()   ;
		
		SET_BIT( MDMA -> IFCR , 1  )   ;
	}
	
	else if (GET_BIT( MDMA -> ISR , 2))
	{
		CallBackPTR[0][2]()   ;
		
		SET_BIT( MDMA -> IFCR , 2  )   ;
	}
	else if (GET_BIT( MDMA -> ISR , 3))
	{
		CallBackPTR[0][3]()   ;
		
		SET_BIT( MDMA -> IFCR , 3  )   ;
	}
	
}




void DMA1_Channel2_IRQHandler(void) 
{
	if (GET_BIT( MDMA -> ISR , 5))
	{
		CallBackPTR[0][1]()   ;
		
		SET_BIT( MDMA -> IFCR , 5  )   ;
	}
	
	else if (GET_BIT( MDMA -> ISR , 6))
	{
		CallBackPTR[0][2]()   ;
		
		SET_BIT( MDMA -> IFCR , 6  )   ;
	}
	else if (GET_BIT( MDMA -> ISR , 7))
	{
		CallBackPTR[0][3]()   ;
		
		SET_BIT( MDMA -> IFCR , 7  )   ;
	}
	
}



void DMA1_Channel3_IRQHandler(void) 
{
	if (GET_BIT( MDMA -> ISR , 9))
	{
		CallBackPTR[0][1]()   ;
		
		SET_BIT( MDMA -> IFCR , 9  )   ;
	}
	
	else if (GET_BIT( MDMA -> ISR , 10))
	{
		CallBackPTR[0][2]()   ;
		
		SET_BIT( MDMA -> IFCR , 10  )   ;
	}
	else if (GET_BIT( MDMA -> ISR , 11))
	{
		CallBackPTR[0][3]()   ;
		
		SET_BIT( MDMA -> IFCR , 11  )   ;
	}
	
}



void DMA1_Channel4_IRQHandler(void) 
{
	if (GET_BIT( MDMA -> ISR , 13))
	{
		CallBackPTR[0][1]()   ;
		
		SET_BIT( MDMA -> IFCR , 13  )   ;
	}
	
	else if (GET_BIT( MDMA -> ISR , 14))
	{
		CallBackPTR[0][2]()   ;
		
		SET_BIT( MDMA -> IFCR , 14  )   ;
	}
	else if (GET_BIT( MDMA -> ISR , 15))
	{
		CallBackPTR[0][3]()   ;
		
		SET_BIT( MDMA -> IFCR , 15  )   ;
	}
	
}



void DMA1_Channel5_IRQHandler(void) 
{
	if (GET_BIT( MDMA -> ISR , 17))
	{
		CallBackPTR[0][1]()   ;
		
		SET_BIT( MDMA -> IFCR , 17  )   ;
	}
	
	else if (GET_BIT( MDMA -> ISR , 18))
	{
		CallBackPTR[0][2]()   ;
		
		SET_BIT( MDMA -> IFCR , 18  )   ;
	}
	else if (GET_BIT( MDMA -> ISR , 19))
	{
		CallBackPTR[0][3]()   ;
		
		SET_BIT( MDMA -> IFCR , 19  )   ;
	}
	
}



void DMA1_Channel6_IRQHandler(void) 
{
	if (GET_BIT( MDMA -> ISR , 21))
	{
		CallBackPTR[0][1]()   ;
		
		SET_BIT( MDMA -> IFCR , 21  )   ;
	}
	
	else if (GET_BIT( MDMA -> ISR , 22))
	{
		CallBackPTR[0][2]()   ;
		
		SET_BIT( MDMA -> IFCR , 22  )   ;
	}
	else if (GET_BIT( MDMA -> ISR , 23))
	{
		CallBackPTR[0][3]()   ;
		
		SET_BIT( MDMA -> IFCR , 23  )   ;
	}
	
}



void DMA1_Channel7_IRQHandler(void) 
{
	if (GET_BIT( MDMA -> ISR , 25))
	{
		CallBackPTR[0][1]()   ;
		
		SET_BIT( MDMA -> IFCR , 25  )   ;
	}
	
	else if (GET_BIT( MDMA -> ISR , 26) )
	{
		CallBackPTR[0][2]()   ;
		
		SET_BIT( MDMA -> IFCR , 26  )   ;
	}
	else if (GET_BIT( MDMA -> ISR , 27) )
	{
		CallBackPTR[0][3]()   ;
		
		SET_BIT( MDMA -> IFCR , 27  )   ;
	}
	
}

















