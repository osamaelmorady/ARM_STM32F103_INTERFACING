#ifndef 	_MDMA_PRIVATE_H_
#define 	_MDMA_PRIVATE_H_




typedef struct 
{
	volatile u32 CCR		;
	volatile u32 CNDTR		;
	volatile u32 CPAR		;
	volatile u32 CMAR		;
	volatile u32 RESERVED	;
	
}CH_REG ;



typedef struct 
{
	volatile u32 ISR  ;
	volatile u32 IFCR ;

	CH_REG  CHANNEL[7] ;

}MDMA_TYPE ;


#define		MDMA   ( (volatile MDMA_TYPE * )0x40020000)











#endif