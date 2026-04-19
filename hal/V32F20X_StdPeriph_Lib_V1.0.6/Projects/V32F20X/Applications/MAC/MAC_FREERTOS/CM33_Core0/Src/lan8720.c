
/**
  * @file    lan8720.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Lan8720 driver.
******************************************************************************/

#include "lan8720.h"
#include "target.h"
#include "lib_eth.h"
#include "lwipopts.h"
#include "lib_syscfg.h"

extern void lwip_packet_handler(void);
extern uint32_t rxflg;

extern ETH_DMADESCTypeDef  *DMATxDescToSet;		
extern ETH_DMADESCTypeDef  *DMARxDescToGet; 	
extern ETH_DMA_Rx_Frame_infos *DMA_RX_FRAME_infos;	


ETH_DMADESCTypeDef DMARxDscrTab[ETH_RXBUFNB] __attribute__((aligned(4))) = {0};
ETH_DMADESCTypeDef DMATxDscrTab[ETH_TXBUFNB] __attribute__((aligned(4))) = {0};
uint8_t Rx_Buff[ETH_RX_BUF_SIZE*ETH_RXBUFNB] __attribute__((aligned(4))) = {0};
uint8_t Tx_Buff[ETH_TX_BUF_SIZE*ETH_TXBUFNB] __attribute__((aligned(4))) = {0};

				
FrameTypeDef frame1;


// LAN8720 init
// return:0,success
//    other,fail
uint8_t LAN8720_Init(void)
{
  GPIO_InitType GPIO_InitStructure;
  uint8_t rval = 0;
  uint32_t rtmp = 0;

  if (ETH0 == USER_ETH)
  {        
    //ETH IO init
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF11_RMII0_CLK_IN);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF11_RMDIO0);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF11_RMII0_RX_DV);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF11_RMDPPS_OUT0);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF11_RMII0_TX_EN);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF11_RMII0_TXD0);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF11_RMII0_TXD1);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource1, GPIO_AF11_RMDCLK0);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource4, GPIO_AF11_RMII0_RXD0);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF11_RMII0_RXD1);

    /*PA1 CLK  PA2 MDIO  PA7 RX_DV */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    /*PB11 TX_EN  PB12 TXD0  PB13 TXD1 PB5 ETH_PPS_OUT*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	


    /*PC1 MCLK  PC4 RXD0  PC5 RXD1 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
  }
  else
  {
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF11_RMII1_RXD1);

    GPIO_PinAFConfig(GPIOH, GPIO_PinSource2, GPIO_AF11_RMII1_TX_EN);
    GPIO_PinAFConfig(GPIOH, GPIO_PinSource3, GPIO_AF11_RMII1_TXD0);

    GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF11_RMDCLK1);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF11_RMDIO1);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource10, GPIO_AF11_RMII1_RX_DV);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource0, GPIO_AF11_RMII1_CLK_IN);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF11_RMII1_RXD0);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF11_RMII1_RXD1);

    //GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF11_ETH1);  //PPS_OUT
    /*PA1 CLK  PA2 MDIO  PA7 RX_DV */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOH, &GPIO_InitStructure);	

    /*PB11 TX_EN  PB12 TXD0  PB13 TXD1 PB5 ETH_PPS_OUT*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOF, &GPIO_InitStructure);	

    /*PC1 MCLK  PC4 RXD0  PC5 RXD1 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    // GPIO_Init(GPIOE, &GPIO_InitStructure);
  }

  rval=ETH_MACDMA_Config(); 
  return !rval;		
}

// get lan8720 speed
// return:
// 001:10M half duplex
// 101:10M full duplex
// 010:100M half duplex
// 110:100M duplex
// other:error
uint8_t LAN8720_Get_Speed(void)
{
	uint8_t speed = 0;
    
	speed=((ETH_ReadPHYRegister(USER_ETH, 0x00,31)&0x1C) >> 2); 
	return speed;
}   


// ETH MAC and dma init
// return:ETH_ERROR,send fail(0)
//		ETH_SUCCESS,send success(1)
uint8_t ETH_MACDMA_Config(void)
{
	uint8_t rval = 0;
	uint32_t temp = 0;
	ETH_InitTypeDef ETH_InitStructure = {0}; 
  
  if (ETH0 == USER_ETH)
  {
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_MAC0, ENABLE);
  }
  else
  {
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_MAC1, ENABLE);
  }
	
  ETH_DeInit(USER_ETH);  							
  ETH_SoftwareReset(USER_ETH);  				
  while (ETH_GetSoftwareResetStatus(USER_ETH) == SET);
  ETH_StructInit(&ETH_InitStructure); 
  ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable; 
  ETH_InitStructure.ETH_Speed = ETH_Speed_100M;
  ETH_InitStructure.ETH_Mode =  ETH_Mode_FullDuplex;   
  ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;	
  ETH_InitStructure.ETH_RetryTransmission = ETH_RetryTransmission_Disable; 	
  ETH_InitStructure.ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable; 	
  ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Disable;	
  ETH_InitStructure.ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Enable ;
  ETH_InitStructure.ETH_PromiscuousMode = ETH_PromiscuousMode_Disable;
  ETH_InitStructure.ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_Perfect; 
  ETH_InitStructure.ETH_UnicastFramesFilter = ETH_UnicastFramesFilter_Perfect;
  ETH_InitStructure.ETH_ChecksumOffload = ETH_ChecksumOffload_Disable; 	
#ifdef CHECKSUM_BY_HARDWARE
	ETH_InitStructure.ETH_ChecksumOffload = ETH_ChecksumOffload_Enable; 	   
#endif

  ETH_InitStructure.ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Enable;
	ETH_InitStructure.ETH_ReceiveStoreForward = ETH_ReceiveStoreForward_Enable;      
	ETH_InitStructure.ETH_TransmitStoreForward = ETH_TransmitStoreForward_Enable;    
	ETH_InitStructure.ETH_ForwardErrorFrames = ETH_ForwardErrorFrames_Disable;     
	ETH_InitStructure.ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Disable;	
	ETH_InitStructure.ETH_SecondFrameOperate = ETH_SecondFrameOperate_Disable;  		
	ETH_InitStructure.ETH_AddressAlignedBeats = ETH_AddressAlignedBeats_Enable;  
	ETH_InitStructure.ETH_FixedBurst = ETH_FixedBurst_Enable;            		
	ETH_InitStructure.ETH_FixedBurst = ETH_FixedBurst_Disable;            		
	ETH_InitStructure.ETH_RxDMABurstLength = ETH_RxDMABurstLength_32Beat;     		
	ETH_InitStructure.ETH_TxDMABurstLength = ETH_TxDMABurstLength_32Beat;			
	ETH_InitStructure.ETH_DMAArbitration = ETH_DMAArbitration_RoundRobin_RxTx_2_1;
	ETH_InitStructure.Sys_Clock_Freq= CLK_GetHCLK0Freq();

	rval=ETH_Init(USER_ETH,&ETH_InitStructure,LAN8720_PHY_ADDRESS);

	if(rval==ETH_SUCCESS)
	{
		ETH_DMAINTConfig(USER_ETH, ETH_DMA_INT_NIS|ETH_DMA_INT_R,ENABLE);
	}
    
	return rval;
}


#ifdef USER_ETH0
void MAC0_SBD_IRQHandler(void)
#endif
#ifdef USER_ETH1
void MAC1_SBD_IRQHandler(void)
#endif
{
	while(ETH_GetRxPktSize(DMARxDescToGet)!=0) 
	{ 	       
		lwip_packet_handler();
	} 
    

  ETH_DMAClearINTPendingBit(USER_ETH, ETH_DMA_INT_R);
  ETH_DMAClearINTPendingBit(USER_ETH, ETH_DMA_INT_AIS);
  ETH_DMAClearINTPendingBit(USER_ETH, ETH_DMA_INT_NIS); 
}



FrameTypeDef ETH_Rx_Packet(void)
{ 
	uint32_t framelength=0;
	FrameTypeDef frame={0,0};   
  
	if((DMARxDescToGet->Status&ETH_DMARxDesc_OWN)!=(uint32_t)RESET)
	{	
		frame.length=ETH_ERROR; 
		if ((USER_ETH->DMASR&ETH_DMASR_RBUS)!=(uint32_t)RESET)  
		{ 
			USER_ETH->DMASR = ETH_DMASR_RBUS;
			USER_ETH->DMARPDR=0;
		}
		return frame;
	}  
	if(((DMARxDescToGet->Status&ETH_DMARxDesc_ES)==(uint32_t)RESET)&& 
	((DMARxDescToGet->Status & ETH_DMARxDesc_LS)!=(uint32_t)RESET)&&  
	((DMARxDescToGet->Status & ETH_DMARxDesc_FS)!=(uint32_t)RESET))  
	{       
		framelength=((DMARxDescToGet->Status&ETH_DMARxDesc_FL)>>ETH_DMARxDesc_FrameLengthShift)-4;
 		frame.buffer = DMARxDescToGet->Buffer1Addr;
	}
  else
  {
    framelength=ETH_ERROR;
  }
	frame.length=framelength; 
	frame.descriptor=DMARxDescToGet;  

	DMARxDescToGet=(ETH_DMADESCTypeDef*)(DMARxDescToGet->Buffer2NextDescAddr);  
  
	return frame;  
}


// Sends a packet
// FrameLength:packet len
// return:ETH_ERROR
//		ETH_SUCCESS
uint8_t ETH_Tx_Packet(uint16_t FrameLength)
{ 
	DMATxDescToSet->Status &=~ ETH_DMATxDesc_OWN;
	// Check the current descriptor
	if((DMATxDescToSet->Status&ETH_DMATxDesc_OWN)!=(uint32_t)RESET)
  {
    return ETH_ERROR;
  }
    DMATxDescToSet->ControlBufferSize = (FrameLength & ETH_DMATxDesc_TBS1);
	DMATxDescToSet->Status|=ETH_DMATxDesc_LS|ETH_DMATxDesc_FS;
  	DMATxDescToSet->Status|=ETH_DMATxDesc_OWN; // Sets the OWN bit of the Tx descriptor,Buff owned by dma
    
		/* Enable the DMA transmission */
	if((USER_ETH->DMASR&ETH_DMASR_TBUS)!=(uint32_t)RESET) // Wthen Tx Buffer TBUS bit was setting ,reset.Restore transport
	{ 
		USER_ETH->DMASR=ETH_DMASR_TBUS; // Reset the ETH DMA TBUS
		USER_ETH->DMATPDR=0; // Restore the DMA send
	} 
	else
	{

//	ETH->DMASR&=~ETH_DMASR_TBUS;//
//	ETH->DMASR&=~ETH_DMASR_AIS;
//	ETH->DMASR&=~ETH_DMASR_TPSS;
//   USER_ETH->DMATPDR=0;
	}
    

	DMATxDescToSet=(ETH_DMADESCTypeDef*)(DMATxDescToSet->Buffer2NextDescAddr);   
	return ETH_SUCCESS;   
}

// Get the current descriptor Tx buff address
// return: Tx buffer address
uint32_t ETH_GetCurrentTxBuffer(void)
{  
  return DMATxDescToSet->Buffer1Addr;
}





