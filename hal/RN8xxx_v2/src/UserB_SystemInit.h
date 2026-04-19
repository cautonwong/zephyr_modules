#ifndef  _UserB_SystemInit_H
#define  _UserB_SystemInit_H

#define	PLL_Clock

#define Read    0
#define Write   1
//------------------------IAP√¸¡Ó-------------------------------------------
#define	Read_Flash				 ((u8  *) FLASH_MEMORY_BASE    )

#define	fnDelay_1us()			{__NOP();__NOP();__NOP();__NOP();}
extern	void fnUserB_SystemInit(void);
extern	void fnRTCDrive_Delay(void);
extern	void SystemDelay(u16 t);
extern	u16 fnUserB_StampThrough(u16 Ago);
extern	void SystemInit(void);
extern	void fnUserB_TC1(void);
#endif
