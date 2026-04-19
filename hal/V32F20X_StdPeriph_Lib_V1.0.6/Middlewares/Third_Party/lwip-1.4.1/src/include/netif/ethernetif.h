#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__
#include "lwip/err.h"
#include "lwip/netif.h"
   
 
//Ethernet name
#define IFNAME0 'e'
#define IFNAME1 'n'

#define IFNAME10 'e'
#define IFNAME11 'w'
 

err_t ethernetif_init(struct netif *netif);
err_t ethernetif_input(struct netif *netif);

#if defined(LWIP_MULTI_MAC)
err_t ethernetif_init_eth1(struct netif *netif);
err_t ethernetif_input_eth1(struct netif *netif);
#endif
#endif
