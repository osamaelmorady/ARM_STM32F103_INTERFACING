#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/ERROR_STATE.h"


#include "MI2C1/MI2C1_Interface.h"
#include "MI2C1/MI2C1_Private.h"
#include "MI2C1/MI2C1_Config.h"

#include "MRCC/MRCC_Interface.h"
#include "MGPIO/MGPIO_Interface.h"


u32 MI2C1_Temp = 0 ;


/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
ErrorState		MI2C1_EnuInit( void ) 
{
	
	/************  I2C Clock Peripheral Enable   *****************/
		MRCC_EnuEnablePeriphClock( MRCC_GPIO ) ;
		MRCC_EnuEnablePeriphClock( MRCC_I2C1 ) ;
		MRCC_EnuEnablePeriphClock(MRCC_AFIO) ;


/************  I2C Peripheral Disable   *****************/
	CLR_BIT ( MI2C1 -> CR1 , PE ) ;


/**************  MI2C_SOFTWARE_RESET   ******************/	
#if	 MI2C_SOFTWARE_RESET  ==  MI2C_SOFTWARE_RESET_DISABLED
	
	CLR_BIT ( MI2C1 -> CR1 , SWRST ) ;
	
#elif  	MI2C_SOFTWARE_RESET  ==  MI2C_SOFTWARE_RESET_ENABLED
	
	SET_BIT ( MI2C1 -> CR1 , SWRST ) ;
	
#else
	#error  "Attention, Wrong MI2C_SOFTWARE_RESET !!"
#endif	
	
	
	
/**************  MI2C_GENERAL_CALL   ********************/		
#if	 MI2C_GENERAL_CALL  ==  MI2C_GENERAL_CALL_DISABLED
	
	CLR_BIT ( MI2C1 -> CR1 , ENGC ) ;
	
#elif  	MI2C_GENERAL_CALL  ==  MI2C_GENERAL_CALL_ENABLED
	
	SET_BIT ( MI2C1 -> CR1 , ENGC ) ;
	
#else
	#error  "Attention, Wrong MI2C_GENERAL_CALL !!"
#endif	
	
	

/************  MI2C_STRETCHING_STATUS   *****************/
#if	 MI2C_STRETCHING_STATUS  ==  MI2C_STRETCHING_ENABLED
	
	CLR_BIT ( MI2C1 -> CR1 , NOSTRETCH ) ;
	
#elif  	MI2C_STRETCHING_STATUS  ==  MI2C_STRETCHING_DISABLED
	
	SET_BIT ( MI2C1 -> CR1 , NOSTRETCH ) ;
	
#else
	#error  "Attention, Wrong MI2C_STRETCHING_STATUS !!"
#endif	
	
		
	
/************  MI2C_ADDRESS_MODE   *****************/
#if	 MI2C_ADDRESS_MODE  ==  MI2C_ADDRESS_7_BITS
	
	CLR_BIT ( MI2C1 -> OAR1 , ADDMODE ) ;
	
#elif  	MI2C_ADDRESS_MODE  ==  MI2C_ADDRESS_10_BITS
	
	SET_BIT ( MI2C1 -> OAR1 , ADDMODE ) ;
	
#else
	#error  "Attention, Wrong MI2C_ADDRESS_MODE !!"
#endif	
	
	
	
/************  Set MI2C_FREQENCY   *****************/		
	
	/* Clear Frequency */
	MI2C1 -> CR2  &= 0xFFC0	;
	/* Set the new Frequency */
	MI2C1 -> CR2  |= MI2C_FREQENCY	;
	
		

/************  MI2C_MCU_Mode   *****************/
	/* Reset CCR */
	MI2C1 -> CCR =0x0000	;

#if	 MI2C_MCU_Mode  ==  MI2C_MCU_MASTER
	
	MGPIO_EnuSetPinDir(PIN_B6,OUTPUT_10MHZ_DRAIN_AF) ;
	MGPIO_EnuSetPinDir(PIN_B7,OUTPUT_10MHZ_DRAIN_AF) ;

	#if MI2C_MASTER_MODE == MI2C_STANDARD_MODE
	
		CLR_BIT ( MI2C1 -> CCR , FS ) ;
	
	#elif MI2C_MASTER_MODE == MI2C_SPEED_MODE
	
		SET_BIT ( MI2C -> CCR , FS ) ;
	
	#else
		#error  "Attention, Wrong MI2C_MCU_Mode !!"
	#endif	

/****  Set MI2C_FREQENCY   ****/	
	
	/* SCLK Frequency Factor */
	MI2C1 -> CCR |= ( SCLK_CCR_FACTOR & 0xFFF )		;

	/* TRISE , Max Rise Time ( Master Mode ) = 1000 nsec   with Freq 8 MHZ ->125 nsec  ->> factor of 8 then add 1   ((( Max rise time is 1000 nsec ))*/
	MI2C1 -> TRISE	=	TRISE_VAL  ;

#elif	 MI2C_MCU_Mode  ==  MI2C_MCU_SLAVE
	
	MGPIO_EnuSetPinDir(PIN_B6,OUTPUT_10MHZ_DRAIN_AF) ;
	MGPIO_EnuSetPinDir(PIN_B7,OUTPUT_10MHZ_DRAIN_AF) ;

#endif	


/************  MCU_ADDRESS   *****************/	
	/* Clear OAR1 Address Bits */
	MI2C1 -> OAR1 &= 0xFF01			;
	
	/* Assign the new address */
	MI2C1 -> OAR1 |= MCU_ADDRESS << 1  ;
	

/************  I2C Peripheral Enable   *****************/			
	SET_BIT ( MI2C1 -> CR1 , PE ) ;
	
	
/************  MI2C_ACK_STATUS   *****************/
	#if MI2C_ACK_STATUS	==  MI2C_ACK_DISABLED

		CLR_BIT ( MI2C1 -> CR1 , ACK ) ;

	#elif MI2C_ACK_STATUS	==  MI2C_ACK_ENABLED

		SET_BIT ( MI2C1 -> CR1 , ACK ) ;

	#else
		#error  "Attention, Wrong MI2C_ACK_STATUS !!"
	#endif


	return ES_OK ;
}






/****************************************************************************************************************/
/****************************************	Master Mode	***************************************************/
/****************************************************************************************************************/
#if MI2C_MCU_Mode  ==  MI2C_MCU_MASTER


/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
ErrorState		MI2C1_EnuStartCondition	( void ) 
{
	/* Start condition , by set start bit */
	SET_BIT (MI2C1 -> CR1 , START ) ;
	
	/* Wait on the starting flag (SB) or (MSL)  */
	while ( GET_BIT( MI2C1 -> SR1 , SB ) == 0 )		;
	
	return ES_OK ;
	
}


/********************************************************************/
ErrorState		MI2C1_EnuReStartCondition ( void ) 
{
	/* Start condition , by set start bit */
	SET_BIT (MI2C1 -> CR1 , START ) ;
	
	/* Wait on the starting flag (SB) */
	while ( GET_BIT( MI2C1 -> SR1 , SB ) == 0 )		;
	
	return ES_OK ;
	
}


/********************************************************************/
ErrorState		MI2C1_EnuStopCondition	( void ) 
{
	/* Stop condition , by set a stop bit */
	SET_BIT (MI2C1 -> CR1 , STOP ) ;
	
	/* Wait on the Stop flag (STOP) */
	while ( GET_BIT( MI2C1 -> SR1 , STOPF ) == 0 )		;
	
	return ES_OK ;
	
}








/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
ErrorState		MI2C1_EnuMasterSendAddress( u8 Copy_U8SlaveAddress , u8 Copy_U8Mode )
{
	/* Clear ( SB ) by reading SR1 then Write on DR */
		MI2C1_Temp =  MI2C1 -> SR1 ;

	/* LSB Indicate whether the master write data ( Set ) or read data from slave ( Clear ) */
	if (( Copy_U8Mode == 0 ) || (Copy_U8Mode == 1) )

		{ MI2C1 -> DR = ( ( Copy_U8SlaveAddress << 1 ) | Copy_U8Mode ) ; }

	else

		{ 	return ES_OUT_RANGE ; }

	/* Wait until Address Matched */
	while (GET_BIT( MI2C1 -> SR1 , ADDR  ) == 0) ;
	
	/* Clear ADDR */
	MI2C1_Temp = MI2C1 -> SR2  ;
	
	return ES_OK ;
}











/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
ErrorState		MI2C1_EnuMasterSendData( u8 Copy_U8DataToSend ) 
{
	/* Send Data from DR To Shift Register to SDA */
	MI2C1 -> DR = Copy_U8DataToSend ;
	
	/* Wait on TXE until it is being empty  */
	while (GET_BIT( MI2C1 -> SR1 , TXE  ) == 0) ;

	
	/*if no data in DR , wait on BTF,  Clear BTF*/
	/* TXE =1 , BTF = 1 mean Stop Condition */
	
	
	
	return ES_OK ;
}

/********************************************************************/
ErrorState		MI2C1_EnuMasterReceiveData( u8 * Copy_PU8DataToReceive ) 
{
	/* Wait on TXE until it is being empty  */
	while (GET_BIT( MI2C1 -> SR1 , RXNE  ) == 0) ;
	
	* Copy_PU8DataToReceive = MI2C1 -> DR ;
	
	/************  MI2C_ACK_STATUS   *****************/
	#if MI2C_ACK_STATUS	==  MI2C_ACK_DISABLED

		CLR_BIT ( MI2C1 -> CR1 , ACK ) ;

	#elif MI2C_ACK_STATUS	==  MI2C_ACK_ENABLED

		SET_BIT ( MI2C1 -> CR1 , ACK ) ;

	#else
		#error  "Attention, Wrong MI2C_ACK_STATUS !!"
	#endif


	return ES_OK ;
}








/****************************************************************************************************************/
/****************************************	Slave Mode	****************************************************/
/****************************************************************************************************************/
#elif MI2C_MCU_Mode  ==  MI2C_MCU_SLAVE





/********************************************************************/
ErrorState		MI2C1_EnuSlaveCheckAddress( void )
{
	/* Wait until Address Matched (ADDR) */
	while (GET_BIT( MI2C1 -> SR1 , ADDR  ) == 0) ;
	
	/* Clear ADDR */
	MI2C1_Temp = MI2C1 -> SR1  ;
	MI2C1_Temp = MI2C1 -> SR2  ;

	/************  MI2C_ACK_STATUS   *****************/
	#if MI2C_ACK_STATUS	==  MI2C_ACK_DISABLED

		CLR_BIT ( MI2C1 -> CR1 , ACK ) ;

	#elif MI2C_ACK_STATUS	==  MI2C_ACK_ENABLED

		SET_BIT ( MI2C1 -> CR1 , ACK ) ;

	#else
		#error  "Attention, Wrong MI2C_ACK_STATUS !!"
	#endif


		return ES_OK ;

	return ES_OK ;
}



/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
ErrorState		MI2C1_EnuSlaveSendData( u8 Copy_U8DataToSend ) 
{
	/* Send Data from DR To Shift Register to SDA */
	MI2C1 -> DR = Copy_U8DataToSend ;

	/* Wait on TXE until it is being empty  */
	while (GET_BIT( MI2C1 -> SR1 , TXE  ) == 0) ;

	
	return ES_OK ;
}


/********************************************************************/
ErrorState		MI2C1_EnuSlaveReceiveData( u8 * Copy_PU8DataToReceive ) 
{
	/* Wait on TXE until it is being empty  */
	while (GET_BIT( MI2C1 -> SR1 , RXNE  ) == 0) ;

	* Copy_PU8DataToReceive = MI2C1 -> DR ;


	/************  MI2C_ACK_STATUS   *****************/
	#if MI2C_ACK_STATUS	==  MI2C_ACK_DISABLED

		CLR_BIT ( MI2C1 -> CR1 , ACK ) ;

	#elif MI2C_ACK_STATUS	==  MI2C_ACK_ENABLED

		SET_BIT ( MI2C1 -> CR1 , ACK ) ;

	#else
		#error	#error  "Attention, Wrong MI2C_ACK_STATUS !!"
	#endif


	
	return ES_OK ;
}








#else
	#error "Attention, Wrong MI2C_MCU_Mode !!"
#endif




