
/**
  * @file    lwip_comm.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   
******************************************************************************/

#include "lwip_comm.h" 
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "ethernetif.h" 
#include "lwip/timers.h"
#include "lwip/tcp_impl.h"
#include "lwip/ip_frag.h"
#include "lwip/tcpip.h" 
#include "lan8720.h"
#include "lwip/inet.h"  
#include <stdio.h>
#include <stdint.h> 


struct netif lwip_netif = {0}; 
uint32_t TCPTimer = 0;			// TCP query timer
uint32_t ARPTimer = 0;			// ARP query timer
__IO uint32_t lwip_localtime = 0;
#if LWIP_DHCP
__lwip_dev lwipdev = {0};	//lwip
#endif


void lwip_packet_handler(void)
{
	ethernetif_input(&lwip_netif);
}


// LWIP init
// return:0,successful
//      1,LAN8720 init fail
//      2,Add the network card fail.
uint8_t lwip_comm_init(void)
{
  struct netif *Netif_Init_Flag = NULL;		
  struct ip_addr ipaddr = {0};  			
  struct ip_addr netmask = {0};   			
  struct ip_addr gw = {0};        	
    
	
  if(LAN8720_Init())
  {
    return 1;
  } 

  tcpip_init(NULL,NULL);

  ipaddr.addr = inet_addr(IP_ADDR);
  netmask.addr = inet_addr(NET_MASK);
  gw.addr = inet_addr(DEFAULT_GATEWAY);

  Netif_Init_Flag=netif_add(&lwip_netif,&ipaddr,&netmask,&gw,NULL,&ethernetif_init,&ethernet_input);

	
  if(Netif_Init_Flag==NULL)
  {
    return 2;
  }
  else
  {
    netif_set_default(&lwip_netif); 
    netif_set_up(&lwip_netif);
  }
    
  return 0;
} 



void lwip_periodic_handle(void)
{
#if LWIP_TCP
	if (lwip_localtime-TCPTimer>=TCP_TMR_INTERVAL)
	{
		TCPTimer=lwip_localtime;
		tcp_tmr();
	}
#endif
	if ((lwip_localtime - ARPTimer)>=ARP_TMR_INTERVAL)
	{
		ARPTimer=lwip_localtime;
		etharp_tmr();
	} 
#if LWIP_DHCP 
	if (lwip_localtime - DHCPfineTimer >= DHCP_FINE_TIMER_MSECS)
	{
		DHCPfineTimer=lwip_localtime;
		dhcp_fine_tmr();
		if ((lwipdev.dhcpstatus!=2)&&(lwipdev.dhcpstatus!=0XFF))
		{ 
			lwip_dhcp_process_handle(); 
		}
	} 
	
	if (lwip_localtime - DHCPcoarseTimer >= DHCP_COARSE_TIMER_MSECS)
	{
		DHCPcoarseTimer =  lwip_localtime;
		dhcp_coarse_tmr();
	}  
#endif
} 



#if LWIP_DHCP
void lwip_dhcp_process_handle(void)
{
	u32 ip=0,netmask=0,gw=0;
	switch(lwipdev.dhcpstatus)
	{
		case 0: 	// open DHCP
			dhcp_start(&lwip_netif);
			lwipdev.dhcpstatus = 1;		
			printf("Look for the DHCP server\r\n");  
			break;
		case 1:		// Waiting for the IP address
 			ip=lwip_netif.ip_addr.addr;	
			netmask=lwip_netif.netmask.addr;
			gw=lwip_netif.gw.addr;		
			if(ip!=0)	
			{
				lwipdev.dhcpstatus=2;	
				printf("mac addr: %d.%d.%d.%d.%d.%d\r\n",lwipdev.mac[0],lwipdev.mac[1],lwipdev.mac[2],lwipdev.mac[3],lwipdev.mac[4],lwipdev.mac[5]);
				lwipdev.ip[3]=(uint8_t)(ip>>24); 
				lwipdev.ip[2]=(uint8_t)(ip>>16);
				lwipdev.ip[1]=(uint8_t)(ip>>8);
				lwipdev.ip[0]=(uint8_t)(ip);
				printf("ip addr: %d.%d.%d.%d\r\n",lwipdev.ip[0],lwipdev.ip[1],lwipdev.ip[2],lwipdev.ip[3]);
				lwipdev.netmask[3]=(uint8_t)(netmask>>24);
				lwipdev.netmask[2]=(uint8_t)(netmask>>16);
				lwipdev.netmask[1]=(uint8_t)(netmask>>8);
				lwipdev.netmask[0]=(uint8_t)(netmask);
				printf("net mask: %d.%d.%d.%d\r\n",lwipdev.netmask[0],lwipdev.netmask[1],lwipdev.netmask[2],lwipdev.netmask[3]);
				lwipdev.gateway[3]=(uint8_t)(gw>>24);
				lwipdev.gateway[2]=(uint8_t)(gw>>16);
				lwipdev.gateway[1]=(uint8_t)(gw>>8);
				lwipdev.gateway[0]=(uint8_t)(gw);
				printf("default gateway: %d.%d.%d.%d\r\n",lwipdev.gateway[0],lwipdev.gateway[1],lwipdev.gateway[2],lwipdev.gateway[3]);
			}else if(lwip_netif.dhcp->tries>LWIP_MAX_DHCP_TRIES)
			{
				lwipdev.dhcpstatus=0XFF;
				// Using a static IP address
				IP4_ADDR(&(lwip_netif.ip_addr),lwipdev.ip[0],lwipdev.ip[1],lwipdev.ip[2],lwipdev.ip[3]);
				IP4_ADDR(&(lwip_netif.netmask),lwipdev.netmask[0],lwipdev.netmask[1],lwipdev.netmask[2],lwipdev.netmask[3]);
				IP4_ADDR(&(lwip_netif.gw),lwipdev.gateway[0],lwipdev.gateway[1],lwipdev.gateway[2],lwipdev.gateway[3]);
				printf("DHCP time out,Using a static IP address!\r\n");
				printf("mac addr: %d.%d.%d.%d.%d.%d\r\n",lwipdev.mac[0],lwipdev.mac[1],lwipdev.mac[2],lwipdev.mac[3],lwipdev.mac[4],lwipdev.mac[5]);
				printf("ip addr: %d.%d.%d.%d\r\n",lwipdev.ip[0],lwipdev.ip[1],lwipdev.ip[2],lwipdev.ip[3]);
				printf("net mask: %d.%d.%d.%d\r\n",lwipdev.netmask[0],lwipdev.netmask[1],lwipdev.netmask[2],lwipdev.netmask[3]);
				printf("default gateway: %d.%d.%d.%d\r\n",lwipdev.gateway[0],lwipdev.gateway[1],lwipdev.gateway[2],lwipdev.gateway[3]);
			}
			break;
		default : 
			break;
	}
}
#endif 

