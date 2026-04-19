/**
  ******************************************************************************
  * @file    ethernetif.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-21
  * @brief   Eth library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
#include "netif/ethernetif.h" 
#include "lan8720.h"  
#include "lwip_comm.h" 
#include "netif/etharp.h"  
#include <string.h>
#include "lib_eth.h"



extern ETH_DMADESCTypeDef DMARxDscrTab[ETH_RXBUFNB];
extern ETH_DMADESCTypeDef DMATxDscrTab[ETH_TXBUFNB];
extern uint8_t Rx_Buff[ETH_RX_BUF_SIZE*ETH_RXBUFNB];
extern uint8_t Tx_Buff[ETH_TX_BUF_SIZE*ETH_TXBUFNB];
extern ETH_DMADESCTypeDef  *DMATxDescToSet;
extern ETH_DMADESCTypeDef  *DMARxDescToGet;

#if defined(LWIP_MULTI_MAC)
extern ETH_DMADESCTypeDef DMARxDscrTabEth1[ETH_RXBUFNB];
extern ETH_DMADESCTypeDef DMATxDscrTabEth1[ETH_TXBUFNB];
extern uint8_t Rx_BuffEth1[ETH_RX_BUF_SIZE*ETH_RXBUFNB];
extern uint8_t Tx_BuffEth1[ETH_TX_BUF_SIZE*ETH_TXBUFNB];
extern ETH_DMADESCTypeDef  *DMATxDescToSetEth1;		
extern ETH_DMADESCTypeDef  *DMARxDescToGetEth1; 	
#endif	


static err_t low_level_init(struct netif *netif)
{ 
#ifdef CHECKSUM_BY_HARDWARE
  int i; 
#endif 
  netif->hwaddr_len = ETHARP_HWADDR_LEN; 

  netif->hwaddr[0]=MAC_ADDR_0; 
  netif->hwaddr[1]=MAC_ADDR_1; 
  netif->hwaddr[2]=MAC_ADDR_2;
  netif->hwaddr[3]=MAC_ADDR_3;
  netif->hwaddr[4]=MAC_ADDR_4;
  netif->hwaddr[5]=MAC_ADDR_5;

  netif->mtu=1500; 
  netif->flags = NETIF_FLAG_BROADCAST|NETIF_FLAG_ETHARP|NETIF_FLAG_LINK_UP;

  ETH_MACAddressConfig(USER_ETH, ETH_MAC_Address0, netif->hwaddr); 

  /* Set the DMATxDescToSet pointer with the first one of the DMATxDescTab list */
  DMATxDescToSet = DMATxDscrTab;
  ETH_DMATxDescChainInit(USER_ETH, DMATxDscrTab, Tx_Buff, ETH_TXBUFNB);

  /* Set the DMARxDescToGet pointer with the first one of the DMARxDescTab list */
  DMARxDescToGet = DMARxDscrTab; 
  ETH_DMARxDescChainInit(USER_ETH, DMARxDscrTab, Rx_Buff, ETH_RXBUFNB);
    
#ifdef CHECKSUM_BY_HARDWARE 
  for(i=0;i<ETH_TXBUFNB;i++)	
  {
    ETH_DMATxDescChecksumInsertionConfig(&DMATxDscrTab[i], ETH_DMATxDesc_ChecksumTCPUDPICMPFull);
  }
#endif
  ETH_Start(USER_ETH); 	
  return ERR_OK;
} 

#if defined(LWIP_MULTI_MAC)
static err_t low_level_init_eth1(struct netif *netif)
{ 
#ifdef CHECKSUM_BY_HARDWARE
  int i; 
#endif 
  netif->hwaddr_len = ETHARP_HWADDR_LEN; 

  netif->hwaddr[0]=MAC_ADDR1_0; 
  netif->hwaddr[1]=MAC_ADDR1_1; 
  netif->hwaddr[2]=MAC_ADDR1_2;
  netif->hwaddr[3]=MAC_ADDR1_3;
  netif->hwaddr[4]=MAC_ADDR1_4;
  netif->hwaddr[5]=MAC_ADDR1_5;

  netif->mtu=1500; 
  netif->flags = NETIF_FLAG_BROADCAST|NETIF_FLAG_ETHARP|NETIF_FLAG_LINK_UP;

  ETH_MACAddressConfig(ETH1, ETH_MAC_Address0, netif->hwaddr); 

  /* Set the DMATxDescToSetEth1 pointer with the first one of the DMATxDscrTabEth1 list */
  DMATxDescToSetEth1 = DMATxDscrTabEth1;
  ETH_DMATxDescChainInit(ETH1, DMATxDscrTabEth1, Tx_BuffEth1, ETH_TXBUFNB);

  /* Set the DMARxDescToGetEth1 pointer with the first one of the DMARxDscrTabEth1 list */
  DMARxDescToGetEth1 = DMARxDscrTabEth1; 
  ETH_DMARxDescChainInit(ETH1, DMARxDscrTabEth1, Rx_BuffEth1, ETH_RXBUFNB);
    
#ifdef CHECKSUM_BY_HARDWARE 
  for(i=0;i<ETH_TXBUFNB;i++)	
  {
    ETH_DMATxDescChecksumInsertionConfig(&DMATxDscrTabEth1[i], ETH_DMATxDesc_ChecksumTCPUDPICMPFull);
  }
#endif
  ETH_Start(ETH1); 	
  return ERR_OK;
} 
#endif



static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
  uint8_t res;
  struct pbuf *q;
  int l = 0;
  uint8_t *buffer=(uint8_t *)ETH_GetCurrentTxBuffer(); 
  for(q=p;q!=NULL;q=q->next) 
  {
    memcpy((uint8_t*)&buffer[l], q->payload, q->len);
    l=l+q->len;
  } 
  res = ETH_Tx_Packet(l); 
  if(res==ETH_ERROR)
  {
    return ERR_MEM;
  }
  return ERR_OK;
} 

#if defined(LWIP_MULTI_MAC)
static err_t low_level_output_eth1(struct netif *netif, struct pbuf *p)
{
  uint8_t res;
  struct pbuf *q;
  int l = 0;
  uint8_t *buffer=(uint8_t *)ETH1_GetCurrentTxBuffer(); 
  for(q=p;q!=NULL;q=q->next) 
  {
    memcpy((uint8_t*)&buffer[l], q->payload, q->len);
    l=l+q->len;
  } 
  res=ETH1_Tx_Packet(l); 
  if(res==ETH_ERROR)
  {
    return ERR_MEM;
  }
  return ERR_OK;
} 
#endif

static struct pbuf * low_level_input(struct netif *netif)
{  
  struct pbuf *p, *q;
  uint16_t len;
  int l =0;
  FrameTypeDef frame;
  uint8_t *buffer;
  
  p = NULL;
  frame = ETH_Rx_Packet();
  len=frame.length;
  buffer=(uint8_t *)frame.buffer;
  p=pbuf_alloc(PBUF_RAW,len,PBUF_POOL);
  if(p!=NULL)
  {
    for(q=p;q!=NULL;q=q->next)
    {
      memcpy((uint8_t*)q->payload,(uint8_t*)&buffer[l], q->len);
      l=l+q->len;
    }
  }
  frame.descriptor->Status=ETH_DMARxDesc_OWN;
  if((USER_ETH->DMASR&ETH_DMASR_RBUS)!=(uint32_t)RESET)
  { 
    USER_ETH->DMASR=ETH_DMASR_RBUS;
    USER_ETH->DMARPDR=0;
  }
  return p;
} 

#if defined(LWIP_MULTI_MAC)
static struct pbuf * low_level_input_eth1(struct netif *netif)
{  
  struct pbuf *p, *q;
  uint16_t len;
  int l =0;
  FrameTypeDef frame;
  uint8_t *buffer;
  
  p = NULL;
  frame=ETH1_Rx_Packet();
  len=frame.length;
  buffer=(uint8_t *)frame.buffer;
  p=pbuf_alloc(PBUF_RAW,len,PBUF_POOL);
  if(p!=NULL)
  {
    for(q=p;q!=NULL;q=q->next)
    {
      memcpy((uint8_t*)q->payload,(uint8_t*)&buffer[l], q->len);
      l = l+q->len;
    }
  }
  frame.descriptor->Status=ETH_DMARxDesc_OWN;
  if((ETH1->DMASR&ETH_DMASR_RBUS)!=(uint32_t)RESET)
  { 
    ETH1->DMASR = ETH_DMASR_RBUS;
    ETH1->DMARPDR = 0;
  }
  return p;
}
#endif

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
err_t ethernetif_input(struct netif *netif)
{
  err_t err;
  struct pbuf *p;
  p=low_level_input(netif);
  if(p==NULL) return ERR_MEM;
  err=netif->input(p, netif);
  if(err!=ERR_OK)
  {
    LWIP_DEBUGF(NETIF_DEBUG,("ethernetif_input: IP input error\n"));
    pbuf_free(p);
    p = NULL;
  } 
  return err;
}

#if defined(LWIP_MULTI_MAC)
err_t ethernetif_input_eth1(struct netif *netif)
{
  err_t err;
  struct pbuf *p;
  p=low_level_input_eth1(netif);
  if(p==NULL) return ERR_MEM;
  err=netif->input(p, netif);
  if(err!=ERR_OK)
  {
    LWIP_DEBUGF(NETIF_DEBUG,("ethernetif_input: IP input error\n"));
    pbuf_free(p);
    p = NULL;
  } 
  return err;
}
#endif

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t ethernetif_init(struct netif *netif)
{
  LWIP_ASSERT("netif!=NULL",(netif!=NULL));
#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname="lwip";  
#endif  /* LWIP_NETIF_HOSTNAME */
  netif->name[0]=IFNAME0;
  netif->name[1]=IFNAME1;
  netif->output=etharp_output;
  netif->linkoutput=low_level_output;
  /* initialize the hardware */
  low_level_init(netif);
  return ERR_OK;
}

#if defined(LWIP_MULTI_MAC)

err_t ethernetif_init_eth1(struct netif *netif)
{
  LWIP_ASSERT("netif!=NULL",(netif!=NULL));
#if LWIP_NETIF_HOSTNAME    //LWIP_NETIF_HOSTNAME 
  netif->hostname="lwip1";
#endif 
  netif->name[0]=IFNAME10;
  netif->name[1]=IFNAME11;
  netif->output=etharp_output;
  netif->linkoutput=low_level_output_eth1;
  low_level_init_eth1(netif);
  return ERR_OK;
}
#endif



