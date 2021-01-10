#ifndef		_MFPEC_PRIVATE_H_
#define 	_MFPEC_PRIVATE_H_



typedef struct 
{
	volatile u32 ACR ;
	volatile u32 KEYR ;
	volatile u32 OPTKEYR ;
	volatile u32 SR ;
	volatile u32 CR ;	
	volatile u32 AR ;
	volatile u32 RESERVED ;
	volatile u32 OBR ;
	volatile u32 WRPR ;
	
}MFPEC_TYPE ;



#define  MFPEC	((volatile MFPEC_TYPE *) 0x40022000  )




/*************** CONTROL REGISTER ( CR ) *****************/
#define 	PG			0
#define 	PER			1
#define 	MER			2
#define 	START		6
#define 	LOCK		7
#define 	EOPIE		12


/*************** STATUS REGISTER ( SR ) *****************/
#define 	BSY			0
#define 	EOP			5


/*************** UNLOCK KEYS *****************/
#define 	KEY1	0x45670123
#define 	KEY2	0xCDEF89AB




/*****************************************************************************************************/
/********************************  MFPEC Erase The ROM By Page Num  **********************************/
/*****************************************************************************************************/
static ErrorState   MFPEC_EnuErasePage ( u8 Copy_U8Page )  ;


#endif
