#ifndef _LWIP_COMM_H
#define _LWIP_COMM_H 
#include <stdint.h>   

/* IP address, netmask and MAC address for MAC0 or MAC1 when there is only one active MAC*/
#define   IP_ADDR            "192.168.1.30"
#define   DEFAULT_GATEWAY    "192.168.1.1"
#define   NET_MASK           "255.255.255.0"
#define   MAC_ADDR_0         (0x02)
#define   MAC_ADDR_1         (0x00)
#define   MAC_ADDR_2         (0x00)
#define   MAC_ADDR_3         (0x28)
#define   MAC_ADDR_4         (0x00)
#define   MAC_ADDR_5         (0x64)


#if LWIP_DHCP
#define LWIP_MAX_DHCP_TRIES	 4

typedef struct  
{
	uint8_t mac[6];
	uint8_t remoteip[4];
	uint8_t ip[4];
	uint8_t netmask[4];
	uint8_t gateway[4];
	
	uint8_t dhcpstatus;.
}__lwip_dev;
extern __lwip_dev lwipdev;
#endif 

void lwip_packet_handler(void);

#if defined(LWIP_MULTI_MAC)
void lwip_packet_eth1_handler(void);
#endif

void lwip_periodic_handle(void); 

uint8_t lwip_comm_mem_malloc(void);
void lwip_comm_mem_free(void);
uint8_t lwip_comm_init(void);

#if LWIP_DHCP
void lwip_dhcp_process_handle(void);
void lwip_comm_default_ip_set(__lwip_dev *lwipx);
#endif
#endif












