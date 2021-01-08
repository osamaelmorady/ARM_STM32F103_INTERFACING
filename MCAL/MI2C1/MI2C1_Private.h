#ifndef 	_MI2C1_PRIVATE_H_
#define 	_MI2C_PRIVATE_H_




typedef struct
{
	volatile u32 CR1	;
	volatile u32 CR2 	;
	volatile u32 OAR1 	;
	volatile u32 OAR2 	;
	volatile u32 DR 	;
	volatile u32 SR1 	;
	volatile u32 SR2 	;
	volatile u32 CCR 	;
	volatile u32 TRISE  ;
	
} MI2C1_TYPE  ;

#define  MI2C1  ( ( volatile MI2C1_TYPE * ) 0x40005400  )



/*************************************************************************/
/*************************************************************************/
#ifndef		F_CPU
	#define F_CPU	8000000UL
#endif
/*************************************************************************/
/*************************************************************************/

#define  I2C_FREQ_2_MHZ			2
#define  I2C_FREQ_4_MHZ         4
#define  I2C_FREQ_6_MHZ         6
#define  I2C_FREQ_8_MHZ         8
#define  I2C_FREQ_10_MHZ        10
#define  I2C_FREQ_12_MHZ        12
#define  I2C_FREQ_14_MHZ        14
#define  I2C_FREQ_16_MHZ        16
#define  I2C_FREQ_18_MHZ        18
#define  I2C_FREQ_20_MHZ        20
#define  I2C_FREQ_22_MHZ		22
#define  I2C_FREQ_26_MHZ        26
#define  I2C_FREQ_28_MHZ        28
#define  I2C_FREQ_30_MHZ        30
#define  I2C_FREQ_32_MHZ        32
#define  I2C_FREQ_34_MHZ        34
#define  I2C_FREQ_36_MHZ        36




/*************************************************************************/
/*************************************************************************/
#define  MI2C_MCU_SLAVE		0
#define  MI2C_MCU_MASTER	1

/*************************************************************************/
/*************************************************************************/
#define   MI2C_STANDARD_MODE	0
#define   MI2C_SPEED_MODE		1


/*************************************************************************/
/*************************************************************************/
#define  SLAVE_TARGET_FREQ_100_KHZ		100000UL
#define  SLAVE_TARGET_FREQ_400_KHZ		400000UL




/*************************************************************************/
/*************************************************************************/
#define  TLOW_BY_THIGH_1_2			3
#define  TLOW_BY_THIGH_16_9			25/16


/*************************************************************************/
#if MI2C_MASTER_MODE == MI2C_STANDARD_MODE

	#define  SCLK_CCR_FACTOR    ( ( MI2C_FREQENCY * 1000000UL  ) / ( SLAVE_TARGET_FREQ * 2) )

	/* MAX_SCL_RISE_TIME	= 1000 */
	#define	 TRISE_VAL		( (1000 / ( 1000 / MI2C_FREQENCY )  ) + 1 )
	
#elif	MI2C_MASTER_MODE == MI2C_SPEED_MODE 

	#define  SCLK_CCR_FACTOR    ( ( MI2C_FREQENCY  ) / SLAVE_TARGET_FREQ * MI2C_SPEED_MODE_DUTY )				

	/* MAX_SCL_RISE_TIME	= 1000 */
	#define	 TRISE_VAL		( (1000 / ( 1000 / MI2C_FREQENCY )  ) + 1 )
	
#endif	
/*************************************************************************/



/*************************************************************************/
/*************************************************************************/
#define  MI2C_ADDRESS_7_BITS		0
#define  MI2C_ADDRESS_10_BITS		1




/*************************************************************************/
/*************************************************************************/
#define   MI2C_GENERAL_CALL_DISABLED	0
#define   MI2C_GENERAL_CALL_ENABLED		1




/*************************************************************************/
/*************************************************************************/
#define  MI2C_STRETCHING_ENABLED		0
#define  MI2C_STRETCHING_DISABLED		1



/*************************************************************************/
/*************************************************************************/
#define  MI2C_SOFTWARE_RESET_DISABLED	0
#define  MI2C_SOFTWARE_RESET_ENABLED	1



/*************************************************************************/
/*************************************************************************/	
#if 	MI2C_MASTER_MODE == MI2C_SPEED_MODE  &&  MI2C_FREQENCY == I2C_FREQ_2_MHZ

	#error	" Attention, FREQ_2_MHZ Not Supported For MI2C_SPEED_MODE "
	
#endif



/*************************************************************************/
/*************************************************************************/	
#define  MI2C_ACK_DISABLED	0
#define  MI2C_ACK_ENABLED	1








/*************************************************************************/
/************************ Register Bits  *********************************/
/*************************************************************************/


/*************************		CR1		**********************************/
#define 	SWRST		15
#define		ALERT		13
#define		PEC			12
#define		POS			11
#define 	ACK			10
#define 	STOP		9
#define 	START		8
#define 	NOSTRETCH	7
#define 	ENGC		6
#define		ENPEC		5
#define		ENARP		4
#define		SMBTYPE		3
#define		SMBUS		1
#define 	PE			0



/*************************		CR2		**********************************/
#define		FREQ	0


/*************************		OAR1		******************************/
#define		ADDMODE		15
#define		ADD0		0


/*************************		OAR2		******************************/




/*************************		SR1		**********************************/
#define		SMBALERT	15
#define		TIMEOUT		14
#define		PECERP		12
#define		OVR			11
#define		AF			10
#define		ARLO		9
#define		BERR		8
#define		TXE			7
#define		RXNE		6
#define		STOPF		4
#define		ADD10		3
#define		BTF			2
#define		ADDR		1
#define		SB			0


/*************************		SR2		**********************************/
#define		DUALF		7
#define		SMBHOST		6
#define		SMBDEFAULT	5
#define		GENCALL		4
#define		TRA			2
#define		BUSY		1
#define		MSL			0


/*************************		CCR		**********************************/
#define		FS		15
#define		DUTY	14




/*************************************************************************/
/*************************************************************************/	


#endif
