#ifndef  _MUSART1_PRIVATE_H_
#define  _MUSART1_PRIVATE_H_



typedef struct
{
	volatile u32 SR ;
	volatile u32 DR ;
	volatile u32 BRR ;
	volatile u32 CR1 ;
	volatile u32 CR2 ;
	volatile u32 CR3 ;
	volatile u32 GTPR ;
	
}MUSART1_TYPE ;


#define  MUSART1		( ( volatile MUSART1_TYPE * ) 0x40013800 )






/***************************************************************************************/
#ifndef  F_CPU
	#define F_CPU 	8000000UL
#endif


#define MUSART1_USARTDIV_VAL		( (F_CPU *100) / ( MSUART1_BAUD_RATE*16 ) )
/***************************************************************************************/









/***************************************************************************************/
/***************************************************************************************/
#define 	MUSART1_RX_GATE_EN			0
#define 	MUSART1_TX_GATE_EN			1
#define 	MUSART1_TX_RX_GATE_EN		2
#define 	MUSART1_TX_RX_GATE_DIS		3



/***************************************************************************************/
#define 	MUSART1_DATA_LENGTH_8_BITS		0
#define 	MUSART1_DATA_LENGTH_9_BITS		1




/***************************************************************************************/
#define 	MUSART1_TRANSMIT_INT_DISABLED	0
#define 	MUSART1_TRANSMIT_INT_ENABLED		1



/***************************************************************************************/
#define 	MUSART1_RECEIVER_INT_DISABLED		0
#define 	MUSART1_RECEIVER_INT_ENABLED		1


/***************************************************************************************/
#define 	MUSART1_COMPLETE_TRANSMIT_INT_DISABLED		0
#define 	MUSART1_COMPLETE_TRANSMIT_INT_ENABLED		1





/***************************************************************************************/
#define 	MUSART1_PARITY_DISABLED			0
#define 	MUSART1_PARITY_ODD				1
#define 	MUSART1_PARITY_EVEN				2





/***************************************************************************************/
#define 	MUSART1_STOP_BITS_1				0
#define 	MUSART1_STOP_BITS_2				1
#define 	MUSART1_STOP_BITS_0_5			2
#define 	MUSART1_STOP_BITS_1_5			3



/***************************************************************************************/
#define 	MUSART1_CLK_DISABLED		0
#define 	MUSART1_CLK_ENABLED 		1





/***************************************************************************************/
#define 	MUSART1_CLK_POL_LOW 		0
#define 	MUSART1_CLK_POL_HIGH		1





/***************************************************************************************/
#define 	MUSART1_CLK_PHASE_READ_WRITE		0
#define 	MUSART1_CLK_PHASE_WRITE_READ		1





/***************************************************************************************/
#define 	MUSART1_CTS_HW_DISABLE			0
#define 	MUSART1_CTS_HW_ENABLE			1


/***************************************************************************************/
#define 	MUSART1_RTS_HW_DISABLE			0
#define 	MUSART1_RTS_HW_ENABLE			1









#endif
