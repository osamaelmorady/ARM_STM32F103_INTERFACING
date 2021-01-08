#ifndef		_MFPEC_PRIVATE_H_
#define 	_MFPEC_PRIVATE_H_



typedef struct 
{
	volatile u32 ACR ;
	volatile u32 KEYR ;
	volatile u32 OPTKEYR ;
	volatile u32 SR ;
	volatile u32 CR ;	
	volatile u32 RESERVED ;
	volatile u32 OBR ;
	volatile u32 WRPR ;
	
}MFPEC_TYPE ;



#define  MFPEC	((volatile MFPEC_TYPE *) 0x40022000  )














#endif