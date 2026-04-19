/**
  ******************************************************************************
  * @file    lwip_comm.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-21
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */


#ifndef _LWIP_COMM_H
#define _LWIP_COMM_H 
#include <stdint.h>    
   
#define LWIP_MAX_DHCP_TRIES  4
#define LWIP_TCP_SERVERDEMO  0X80
#define LWIP_TCP_CLIENTDEMO  0X40
#define LWIP_UDP_DEMO        0X20

#define   IP_ADDR            "192.168.1.30"
#define   DEFAULT_GATEWAY    "192.168.1.1"
#define   NET_MASK           "255.255.255.0"
#define   MAC_ADDR_0         (0x02)
#define   MAC_ADDR_1         (0x00)
#define   MAC_ADDR_2         (0x00)
#define   MAC_ADDR_3         (0x28)
#define   MAC_ADDR_4         (0x00)
#define   MAC_ADDR_5         (0x64)


typedef struct  
{
  uint8_t mac[6];
  uint8_t remoteip[4];
  uint8_t ip[4];
  uint8_t netmask[4];
  uint8_t gateway[4];

  uint8_t dhcpstatus;
}__lwip_dev;
extern __lwip_dev lwipdev;
 
void lwip_packet_handler(void);
void lwip_periodic_handle(void); 
void lwip_comm_default_ip_set(__lwip_dev *lwipx);
uint8_t lwip_comm_mem_malloc(void);
void lwip_comm_mem_free(void);
uint8_t lwip_comm_init(void);
void lwip_dhcp_process_handle(void);

#endif













