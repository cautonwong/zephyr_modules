#ifndef  _UserB_Flash_H
#define  _UserB_Flash_H

//∂¡–¥∂®“Â
#define	Page_Size 64

//---------------------------------------------------
#define FLASH_MEMORY_BASE               ((uint32_t )0x00000000             )
#define	Read_Flash				((u8  *) FLASH_MEMORY_BASE    ) 
#define	FLASH_MAXSize			0x80000
#define Flash_PageSize  		512
#define	FlashBlock0Ad   		FLASH_MEMORY_BASE
#define	FlashBlock1Ad   		(FLASH_MEMORY_BASE + FLASH_MAXSize/2)
//---------------------------------------------------
extern ErrorStatus fnFlash_Read(u8 *Dst , u32 Src , u32 DatLen , u8 Repeat);
extern ErrorStatus fnFlash_Write(u32 Dst , u8 *Src , u32 DatLen , u8 Repeat);

#endif
