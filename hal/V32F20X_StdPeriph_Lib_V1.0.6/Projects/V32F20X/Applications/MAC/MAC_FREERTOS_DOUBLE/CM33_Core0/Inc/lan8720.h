/**
  ******************************************************************************
  * @file    lan8720.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-21
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */


#ifndef __LAN8720_H
#define __LAN8720_H

#include "target.h"
#include "lib_eth.h"

#define USER_ETH     ETH0  

#define LAN8720_PHY_ADDRESS  	0x00				//LAN8720 PHY addr




uint8_t LAN8720_Init(void);
uint8_t LAN8720_Get_Speed(void);
uint8_t ETH_MACDMA_Config(void);
FrameTypeDef ETH_Rx_Packet(void);
uint8_t ETH_Tx_Packet(u16 FrameLength);
uint32_t ETH_GetCurrentTxBuffer(void);

#if defined(LWIP_MULTI_MAC)
FrameTypeDef ETH1_Rx_Packet(void);
uint8_t ETH1_Tx_Packet(u16 FrameLength);
uint32_t ETH1_GetCurrentTxBuffer(void);
#endif

#endif 

