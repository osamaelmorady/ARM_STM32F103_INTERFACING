#ifndef 	_MSPI1_PRIVATE_H_
#define 	_MSPI1_PRIVATE_H_




typedef struct
{
	volatile u32 CR1	;
	volatile u32 CR2	;
	volatile u32 SR 	;
	volatile u32 DR 	;
	volatile u32 CRCPR 	;
	volatile u32 RXCRCR	;
	volatile u32 TXCRCR	;
	volatile u32 I2SCFGR;
	volatile u32 I2SPR   ;
	
} MSPI1_TYPE  ;





#define MSPI1  ( ( volatile MSPI1_TYPE * ) 0x40013000 )




/************************************************************/
/************************************************************/
#define 	MSPI1_DUPLEX_FULL				0
#define 	MSPI1_DUPLEX_HALF_RECIEVE		1
#define 	MSPI1_DUPLEX_HALF_TRANSMIT		2


/**********************************************/
#define 	MSPI1_CPOL_LOW_0		0
#define 	MSPI1_CPOL_HIGH_0		1


/**********************************************/
#define 	MSPI1_READ_WRITE		0
#define 	MSPI1_WRITE_READ		1


/**********************************************/
#define 	MSPI1_MSB			0
#define 	MSPI1_LSB			1


/**********************************************/
#define 	MSPI1_DATA_SIZE_8_BITS			0
#define 	MSPI1_DATA_SIZE_16_BITS			1




/************************************************************/
/************************************************************/
#define 	BAUD_RATE_FCLK_DIV_2		0
#define 	BAUD_RATE_FCLK_DIV_4		1
#define 	BAUD_RATE_FCLK_DIV_8		2
#define 	BAUD_RATE_FCLK_DIV_16		3
#define 	BAUD_RATE_FCLK_DIV_32		4
#define 	BAUD_RATE_FCLK_DIV_64		5
#define 	BAUD_RATE_FCLK_DIV_128		6
#define 	BAUD_RATE_FCLK_DIV_256		7





/************************************************************/
/************************************************************/
#define 	MSPI1_MODE_SLAVE		0
#define 	MSPI1_MODE_MASTER		1



/**********************************************/
#define 	SSM_CONFIG_HARDWARE		0
#define 	SSM_CONFIG_SOFTWARE		1



/**********************************************/
#define 	NSS_CONFIG_SLAVE_SELECTED		0
#define 	NSS_CONFIG_SLAVE_NOT_SELECTED	1




/************************************************************/
/************************************************************/
#define 	MSPI1_TX_RX_INT_DISABLED		0x00
#define 	MSPI1_RX_INT_ENABLED			0x40
#define 	MSPI1_TX_INT_ENABLED			0x80
#define 	MSPI1_TX_RX_INT_ENABLED			0xC0



/************************************************************/
/************************************************************/
#define 	MSPI1_MULTI_MASTER_ENABLE		0
#define 	MSPI1_MULTI_MASTER_DISABLE		1






#endif
