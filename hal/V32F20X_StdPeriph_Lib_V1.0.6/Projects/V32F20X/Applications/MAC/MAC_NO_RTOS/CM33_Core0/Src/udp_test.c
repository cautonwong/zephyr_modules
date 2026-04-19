
/**
  * @file    udp_test.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

#include <stdint.h>
#include "udp_test.h"
#include "lwip/udp.h"
#include "lwip/inet.h"



// udp receives the callback
static void udp_server_receive_callback(void *arg, struct udp_pcb *upcb,
     struct pbuf *p, ip_addr_t *addr, u16_t port)
{ 
  if ((NULL == upcb) || (NULL == addr))
  {
    return;
  }

  if (p != NULL)
  { 
    udp_sendto(upcb, p, addr, port);
    pbuf_free(p);
  }  
}


 // udp server init
int my_udp_servers_init(void)
{
  struct udp_pcb *upcb = NULL;
  err_t err = 0;

  upcb = udp_new();

  if (upcb)
  {
    err = udp_bind(upcb, IP_ADDR_ANY, UDP_CLIENT_PORT);

    if(err == ERR_OK)
    {
      udp_recv(upcb, udp_server_receive_callback, NULL);
    }
    else
    {
      udp_remove(upcb);
      printf("can not bind pcb\r\n");
    }
  }

  return 0;
}


struct udp_pcb* my_udp_client_init(void)
{
  struct udp_pcb *upcb = NULL;
  struct ip_addr rmtipaddr = {0};

  rmtipaddr.addr = inet_addr(UDP_SERVERS_IP);
  upcb = udp_new();
  //err=udp_connect(upcb,&rmtipaddr,UDP_CLIENT_PORT);
  if (upcb)
  {
    //err = udp_bind(upcb, IP_ADDR_ANY, UDP_CLIENT_PORT);
    return upcb;
  }

  return NULL;
}


int my_udp_send_test(struct udp_pcb *upcb,uint8_t *buff,uint32_t len)
{
  static struct ip_addr destipaddr = {0};
  struct pbuf* p = NULL;

  p = pbuf_alloc(PBUF_TRANSPORT,0,PBUF_POOL);
  if (upcb)
  {
    p->payload = buff;
    p->len = p->tot_len = 1460;
    destipaddr.addr = inet_addr(UDP_SERVERS_IP);
    udp_sendto(upcb, p, &destipaddr, UDP_SERVERS_PORT);
    pbuf_free(p);
  } 

  return 0;
}



void my_udp_task(void)
{
   my_udp_servers_init();  
}









