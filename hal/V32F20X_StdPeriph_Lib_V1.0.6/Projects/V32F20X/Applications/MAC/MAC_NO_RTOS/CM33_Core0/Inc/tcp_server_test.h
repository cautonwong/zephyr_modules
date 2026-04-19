
/**
  * @file    tcp_server_test.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-14
  * @brief   
******************************************************************************/

#ifndef __TCP_SERVER_DEMO_H
#define __TCP_SERVER_DEMO_H

#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/memp.h"
#include "lwip/mem.h"
#include "lwip_comm.h"

 
#define TCP_SERVER_RX_BUFSIZE   1400
#define TCP_SERVER_PORT         8081

enum tcp_server_states
{
	ES_TCPSERVER_NONE = 0,
	ES_TCPSERVER_ACCEPTED,
	ES_TCPSERVER_CLOSING,
}; 

struct tcp_server_struct
{
	uint8_t state;
	struct tcp_pcb *pcb;
	struct pbuf *p;
}; 

void tcp_server_init(void);
err_t tcp_server_accept(void *arg,struct tcp_pcb *newpcb,err_t err);
err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
void tcp_server_error(void *arg,err_t err);
err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb);
err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
void tcp_server_senddata(struct tcp_pcb *tpcb, struct tcp_server_struct *es);
void tcp_server_connection_close(struct tcp_pcb *tpcb, struct tcp_server_struct *es);
void tcp_server_remove_timewait(void);
#endif 
