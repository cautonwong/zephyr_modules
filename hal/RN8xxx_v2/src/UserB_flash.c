#define  __UserB_Flash_H_GLOBALS
#include <UserB_LIB.h>
#include "hfp_system.h"
extern	u8	FlashBuf[128];
/*****************************************************************************
** Function name:	fnCheckFlash
**
** Description:		比较读取或写入的FLASH数据是否正确
**
** Parameters:		Address--取数源地址
**					Buff -- 比较的数据缓冲区目标指针 
**					Length -- 比较数据长度
**
** Returned value:	SUCCESS成功，ERROR失败
**
******************************************************************************/
u8 fnCheckFlash(u32 Address,u8 *Buff,u32 Length)
{
	u32 i;
	u8 Data;
	
	for(i=0;i<Length;i++){
		Data=*(Read_Flash + Address + i);    
		if(Data!=Buff[i]){return false;}
	}
	return true;
}

/*****************************************************************************
** Function name:	fnOperateFlash
**
** Description:		FLASH操作函数
**
** Parameters:		Read_Write--读或写
**					Address -- 取数源地址
**					Buff -- 取数缓冲区目标指针
**					Length -- 比较数据长度
**					Repeat -- 失败重试次数
**
** Returned value:	SUCCESS成功，ERROR失败
**
******************************************************************************/
ErrorStatus fnOperateFlash(BOOL Read_Write,u32 Address,u8 *Buff,u32 Length,u8 Repeat)
{
	u32 i;
	u8 ReReadTimes;
	u32 AddressTemp;
	if (Length==0) {return ERROR;}
	
	AddressTemp = Address;
	for(ReReadTimes=0;ReReadTimes<=Repeat;ReReadTimes++)
	{
		if(Read==Read_Write)
		{
			for(i=0;i<Length;i++)
			{
				*(Buff+i) = *(Read_Flash + AddressTemp + i);
			}
		}
		else
		{
			i = flashPageErase((FLASH_MEMORY_BASE + Address)>>9);
			if(i) continue;
			
			i = flashProgram(FLASH_MEMORY_BASE + AddressTemp , (uint32_t)Buff , Length);
			if(i) continue;
		}
		if((fnCheckFlash(Address,Buff,Length)==true)||(ReReadTimes>Repeat)) {break; }
	}
 	
 	if(ReReadTimes>=Repeat){return ERROR;}
 	return(SUCCESS);
}

/*****************************************************************************
** Function name:	fnFlash_Read
**
** Description:		FLASH读函数
**
** Parameters:		*Dst--取数缓冲区目标指针
**					Src -- 取数源地址
**					DatLen -- 比较数据长度
**					Repeat -- 失败重试次数
**
** Returned value:	SUCCESS成功，ERROR失败
**
******************************************************************************/
ErrorStatus fnFlash_Read(u8 *Dst , u32 Src , u32 DatLen , u8 Repeat)
{
    if (DatLen==0) return(ERROR);
	if ( FLASH_MAXSize <= (Src+DatLen))  return(ERROR);

	if(fnOperateFlash(Read,Src,Dst,DatLen,Repeat) == ERROR)
	{
		return(ERROR);
	}
	return(SUCCESS);
}

/*****************************************************************************
** Function name:	fnFlash_Write
**
** Description:		FLASH写函数
**
** Parameters:		*Dst--取数源地址
**					Src -- 取数缓冲区目标指针
**					DatLen -- 比较数据长度
**					Repeat -- 失败重试次数
**
** Returned value:	SUCCESS成功，ERROR失败
**
******************************************************************************/
ErrorStatus fnFlash_Write(u32 Dst , u8 *Src , u32 DatLen , u8 Repeat)
{
	u32 B;
	u16 AddingTimes=0;
	
    if (DatLen==0) return(ERROR);
	if ( FLASH_MAXSize < (Dst+DatLen))  return(ERROR);
	if(Dst%512) return(ERROR);			// 地址必须为页首地址
	
	while(DatLen)
	{
		WDT->EN = 0xbb;	
		if(++AddingTimes>1536) return(ERROR); //防止死循环
		if(DatLen < Flash_PageSize) B = DatLen;
		else B = Flash_PageSize;
		if(fnOperateFlash(Write,Dst,Src,B,Repeat) == ERROR)
		{
			return(ERROR);
		}
		Dst+=Flash_PageSize;
		Src+=B;
		DatLen-=B;
	}
	return(SUCCESS);
}
