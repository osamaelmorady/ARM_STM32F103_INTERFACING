#ifndef	  _MAFIO_CONFIG_H_
#define   _MAFIO_CONFIG_H_







typedef struct 
{
	volatile u32 EVCR 		;
	volatile u32 MAPR 		;
	volatile u32 EXTICR[4]  ;
	volatile u32 MAPR2 		;
	
}AFIO_TYPE  ;






#define AFIO  ( ( volatile AFIO_TYPE * ) 0x40010000 )










#define 	MAFIO_EXTI_PORTA_REMAP 	0b0000
#define 	MAFIO_EXTI_PORTB_REMAP 	0b0001
#define 	MAFIO_EXTI_PORTC_REMAP 	0b0010













#endif









