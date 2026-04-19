/******************************************************************************
 * @file     nvm.c
 * @brief    non-valatile memory driver source code file for RN821x series SOC
 * @author   Renergy Technology
 * @version  V1.00
 * @date     2012-11-29
 *
 * @note
 * Copyright (C) 2008, Renergy Technology Inc. All rights reserved.
 *
 * 2017-4-11  1. re-design eepromProgram() for RA9103C2
 *
 ******************************************************************************/
#include "RN8318.h"
#include "system_RN8318.h"
#include "nvm.h"

/*
IAPÃüÁî	      ÃüÁî´úÂë
FlashÒ³²Á³ý	  0x50
Flash¿é²Á³ý	  0x51
flashÆ¬²Á³ý	  0x52
Flash¿é²é¿Õ	  0x53

EEPROMÒ³²Á³ý	0x54
EEPROM¿é²Á³ý	0x55
EEPROMÆ¬²Á³ý	0x56
EEPROM¿é²é¿Õ	0x57

Flash±à³Ì	    0x58
EEPROM±à³Ì	  0x59

NVMÊ¹ÄÜ       0x5a
Ä£ÄâÈí¼þ¸´Î»  0x5b
*/
#define  FL_PAGE_ERASE   0x50
#define  FL_SECT_ERASE   0x51

#define  EE_PAGE_ERASE   0x54
#define  EE_SECT_ERASE   0x55

#define  FL_PROG         0x58
#define  EE_PROG         0x59

#define  FL_TYPE         0
#define  EE_TYPE         1
  
/* IAP Call */
typedef void (*IAP_Entry) (unsigned long *cmd, unsigned long *stat);
#define IAP_OFFSET   0x1c01


#define CHIP_RA9103A   0
#define CHIP_RA9103D   1
#define CHIP_RA9103C   2
#define CHIP_RA9103E   3
#define CHIP_RA9103F   4

uint8_t __eepromProgram (uint32_t dst_addr,uint32_t src_addr,uint32_t byte_num);
/*
 * return:
 *   0 = RA9103A
 *   1 = RA9103D
 *   2 = RA9103C
 *   3 = RA9103E
 *   4 = RA9103F
 */
static uint8_t getChipid(void)
{
  uint8_t   chipid;
	uint16_t  die_ver;
	uint32_t  sys_ps_bak;
  uint32_t  mod0_en_bak;
	
	mod0_en_bak = SYSCTL->MOD0_EN;
	sys_ps_bak = SYSCTL->SYS_PS;
	
  SYSCTL->MOD0_EN |= (1 << 0);
	SYSCTL->SYS_PS = 0x75;
	die_ver = *(volatile uint32_t *)(0x40034074);
	
	switch(die_ver)
	{
		case 0xc0:
			chipid = CHIP_RA9103C;
		  break;
		case 0xe0:
			chipid = CHIP_RA9103E;
		  break;
		case 0xf0:
			chipid = CHIP_RA9103F;
		  break;
		default:
			*(volatile uint32_t *)(0x50010004) = 0xffffffff;
		  if(*(volatile uint32_t *)(0x50010004) == 0xffffffff)
			{
				*(volatile uint32_t *)(0x50010004) = 0x0;
				if(*(volatile uint32_t *)(0x50010004) == 0x0)
				{
				  chipid = CHIP_RA9103D;
				}
				else
				{
					chipid = CHIP_RA9103A;
				}
			}
			else
			{
				chipid = CHIP_RA9103A;
			}
			break;
	}
	
  SYSCTL->SYS_PS = 0x82;
		
  SYSCTL->MOD0_EN = mod0_en_bak;
	SYSCTL->SYS_PS = sys_ps_bak;
  return chipid;
}
/* mode = 0: FLASH, mode = 1: EEPROM, mode = 2: ROM */
static uint32_t getMipAddr(uint8_t mode)
{
  uint32_t ee_addr, fl_addr, rom_addr;
  switch (*(uint32_t *)(0x40034018) & 0x7)
  {
    case 0:
      ee_addr = 0x08000000;
      fl_addr = 0x0;
      rom_addr = 0x18000000;
      break;
    case 1:
      ee_addr = 0x0;
      fl_addr = 0x08000000;
      rom_addr = 0x18000000;
      break;
    case 2:
      ee_addr = 0x08000000;
      fl_addr = 0x10000000;
      rom_addr = 0x18000000;
      break;
    case 3:
      ee_addr = 0x08000000;
      fl_addr = 0x18000000;
      rom_addr = 0x0;
      break;
    default:
      ee_addr = 0x08000000;
      fl_addr = 0x0;
      rom_addr = 0x18000000;
      break;
  }
  return (mode == 0) ? fl_addr : (mode == 1) ? ee_addr : rom_addr;
}

uint8_t nvmWrEnable(uint8_t nvm_type)
{  
  struct sIAP {                  // IAP Structure
    unsigned long cmd;           // Command
    unsigned long par[4];        // Parameters
    unsigned long stat;          // Status
    unsigned long res[2];        // Result
  } IAP;
  uint32_t iap_addr;
  
  iap_addr = getMipAddr(2) + IAP_OFFSET;
  
  IAP.cmd = 0x5a;
  IAP.par[0] = nvm_type;
  (*(void (*)())(iap_addr))(&IAP.cmd, &IAP.stat);
  return (uint8_t)IAP.stat;
}

uint8_t flashPageErase(uint32_t pg)
{  
  struct sIAP {
    unsigned long cmd;
    unsigned long par[4];
    unsigned long stat;
    unsigned long res[2];
  } IAP;
  uint32_t iap_addr;
  
  iap_addr = getMipAddr(2) + IAP_OFFSET;
  
  IAP.cmd = FL_PAGE_ERASE;
  IAP.par[0] = pg;
  
  nvmWrEnable(FL_TYPE);
  (*(void (*)())(iap_addr))(&IAP.cmd, &IAP.stat);
  return (uint8_t)IAP.stat;
}

uint8_t flashSectorErase(uint32_t sec)
{  
  struct sIAP {
    unsigned long cmd;
    unsigned long par[4];
    unsigned long stat;
    unsigned long res[2];
  } IAP;
  uint32_t iap_addr;
  
  iap_addr = getMipAddr(2) + IAP_OFFSET;
  
  IAP.cmd = FL_SECT_ERASE;
  IAP.par[0] = sec;
  
  nvmWrEnable(FL_TYPE);
  (*(void (*)())(iap_addr))(&IAP.cmd, &IAP.stat);
  return (uint8_t)IAP.stat;
}
/*
uint8_t eepromPageErase(uint32_t pg)
{  
  struct sIAP {                  // IAP Structure
    unsigned long cmd;           // Command
    unsigned long par[4];        // Parameters
    unsigned long stat;          // Status
    unsigned long res[2];        // Result
  } IAP;
  uint32_t iap_addr;
  
	if(getChipid() != CHIP_RA9103F)
	{
		iap_addr = getMipAddr(2) + IAP_OFFSET;
		
		IAP.cmd = EE_PAGE_ERASE;
		IAP.par[0] = pg;
		
		nvmWrEnable(EE_TYPE);
		(*(void (*)())(iap_addr))(&IAP.cmd, &IAP.stat);
		return (uint8_t)IAP.stat;
	}
	else
	{
		return SRC_ADDR_NOT_MAPPED;
	}
}

uint8_t eepromSectorErase(uint32_t sec)
{  
  struct sIAP {
    unsigned long cmd;
    unsigned long par[4];
    unsigned long stat;
    unsigned long res[2];
  } IAP;
  uint32_t iap_addr;
  
	if(getChipid() != CHIP_RA9103F)
	{
		iap_addr = getMipAddr(2) + IAP_OFFSET;
		
		IAP.cmd = EE_SECT_ERASE;
		IAP.par[0] = sec;
		
		nvmWrEnable(EE_TYPE);
		(*(void (*)())(iap_addr))(&IAP.cmd, &IAP.stat);
		return (uint8_t)IAP.stat;
	}
	else
	{
		return SRC_ADDR_NOT_MAPPED;
	}
}
*/
uint8_t flashProgram(uint32_t dst_addr, uint32_t src_addr, uint32_t len)
{ 
  struct sIAP {
    unsigned long cmd;
    unsigned long par[4];
    unsigned long stat;
    unsigned long res[2];
  } IAP;
  uint32_t iap_addr;
  
  iap_addr = getMipAddr(2) + IAP_OFFSET;
  
  
  IAP.cmd = FL_PROG;
	IAP.par[0] = dst_addr;
	IAP.par[1] = src_addr;
	IAP.par[2] = len;
  
  nvmWrEnable(FL_TYPE);
  (*(void (*)())(iap_addr))(&IAP.cmd, &IAP.stat);
  return (uint8_t)IAP.stat;
}

uint8_t eepromProgram(uint32_t dst_addr, uint32_t src_addr, uint32_t len)
{ 
  struct sIAP {
    unsigned long cmd;
    unsigned long par[4];
    unsigned long stat;
    unsigned long res[2];
  } IAP;
  uint32_t iap_addr;
  uint8_t  chip_id = getChipid();
	
	if((chip_id == CHIP_RA9103C) || (chip_id == CHIP_RA9103E))
	{
		nvmWrEnable(EE_TYPE);
		return __eepromProgram(dst_addr,src_addr,len);
	}
	else if(chip_id != CHIP_RA9103F)
	{
    iap_addr = getMipAddr(2) + IAP_OFFSET;
    
    IAP.cmd = EE_PROG;
	  IAP.par[0] = dst_addr;
	  IAP.par[1] = src_addr;
	  IAP.par[2] = len;
  
    nvmWrEnable(EE_TYPE);
    (*(void (*)())(iap_addr))(&IAP.cmd, &IAP.stat);
    return (uint8_t)IAP.stat;
	}
	else
	{
		return SRC_ADDR_NOT_MAPPED;
	}
}

void    eepromStandby(void)
{
  uint32_t reg,psw;
  
	if(getChipid() != CHIP_RA9103F)
	{
    reg = getMipAddr(1);
    psw = *(uint32_t *)(0X40034030);
    *(uint16_t *)(0X40034030) = 0x75;
    switch (*(uint16_t *)(0X40034074) & 0xff)
    {      
        case 0xc0:
          *(volatile uint32_t *)(reg + 0x00800000) = 0xfeed000f;
          break;
        default:  
          *(volatile uint32_t *)(reg + 0x00800000) = 0xfeed0007;
    }
     *(uint32_t *)(0X40034030) = psw;
	}
}

void    eepromWakeup(void)
{
  uint32_t reg;
  
	if(getChipid() != CHIP_RA9103F)
	{
    reg = getMipAddr(1);
    *(volatile uint32_t *)(reg + 0x00800000) = 0xfeed0004;
	}
}

void    cacheOff(void)
{
  uint32_t reg;
  if(getChipid() == CHIP_RA9103F)
	{
		reg = 0x50014060;
	}
	else
	{
    reg = getMipAddr(0) + 0x0080001c;
	}
	
  *(volatile uint32_t *)(reg) = 0xfeed0000;
}

void    cacheOn(void)
{
  uint32_t reg;
  if(getChipid() == CHIP_RA9103F)
	{
		reg = 0x50014060;
	}
	else
	{
    reg = getMipAddr(0) + 0x0080001c;
	}
	
  *(volatile uint32_t *)(reg) = 0xfeed0001;
}

