#ifndef 	_MSPI1_CONFIG_H_
#define 	_MSPI1_CONFIG_H_




/******************************************************************************************************/
#define F_CPU	8000000UL
/******************************************************************************************************/
/*
	00- MSPI1_DUPLEX_FULL
	01- MSPI1_DUPLEX_HALF_RECIEVE
	02- MSPI1_DUPLEX_HALF_TRANSMIT
*/
#define  MSPI1_DUPLEX_DIRECTION		MSPI1_DUPLEX_FULL





/******************************************************************************************************/
/*
	00- MSPI1_CPOL_LOW_0
	01- MSPI1_CPOL_HIGH_0
*/
#define		MSPI1_CPOL		MSPI1_CPOL_LOW_0





/******************************************************************************************************/
/*
	00- MSPI1_READ_WRITE
	01- MSPI1_WRITE_READ
*/
#define		MSPI1_CPHA		MSPI1_WRITE_READ







/******************************************************************************************************/
/*
	00- MSPI1_LSB
	01- MSPI1_MSB
*/
#define		MSPI1_DATA_FRAME_FORMAT		MSPI1_LSB




/******************************************************************************************************/
/*
	00- MSPI1_DATA_SIZE_8_BITS
	01- MSPI1_DATA_SIZE_16_BITS
*/
#define		MSPI1_DATA_SIZE		MSPI1_DATA_SIZE_8_BITS








/******************************************************************************************************/
/*
	00- BAUD_RATE_FCLK_DIV_2
	01- BAUD_RATE_FCLK_DIV_4
	02- BAUD_RATE_FCLK_DIV_8
	03- BAUD_RATE_FCLK_DIV_16
	04- BAUD_RATE_FCLK_DIV_32
	05- BAUD_RATE_FCLK_DIV_64
	06- BAUD_RATE_FCLK_DIV_128
	07- BAUD_RATE_FCLK_DIV_256
*/
#define MSPI1_BAUD_RATE			BAUD_RATE_FCLK_DIV_64







/******************************************************************************************************/
/*
	00- MSPI1_MODE_MASTER
	01- MSPI1_MODE_SLAVE
*/
#define  MSPI1_MODE_TYPE		MSPI1_MODE_MASTER






/******************************************************************************************************/
/*
	00- SSM_CONFIG_HARDWARE
	01- SSM_CONFIG_SOFTWARE

*/
#define 	SSM_CONFIG		SSM_CONFIG_HARDWARE






/******************************************************************************************************/

#if  ( MSPI1_MODE_TYPE 	== MSPI1_MODE_SLAVE ) && ( SSM_CONFIG ==  SSM_CONFIG_SOFTWARE )

/*
	00- NSS_CONFIG_SLAVE_SELECTED
	01- NSS_CONFIG_SLAVE_NOT_SELECTED

*/

	#define 	NSS_CONFIG		NSS_CONFIG_SLAVE_SELECTED



#endif




/******************************************************************************************************/
/*
	00- MSPI1_TX_RX_INT_DISABLED
	01- MSPI1_TX_INT_ENABLED
	02- MSPI1_RX_INT_ENABLED
	03- MSPI1_TX_RX_INT_ENABLED

*/
#define  MSPI1_TX_RX_INTERUPT			MSPI1_TX_RX_INT_DISABLED






/******************************************************************************************************/
/*
	00- MSPI1_MULTI_MASTER_ENABLE
	01- MSPI1_MULTI_MASTER_DISABLE

*/
#define 	MSPI1_MULTI_MASTER		MSPI1_MULTI_MASTER_DISABLE






#endif
