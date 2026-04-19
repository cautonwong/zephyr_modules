/**
  ******************************************************************************
  * @file    udp_test.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-21
  * @brief 
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __UDP_TEST_H__
#define __UDP_TEST_H__

#include "lwip/sockets.h"
#include <stdint.h>
#include "cmsis_os.h"


#define UDP_REV_BUF_LEN          (1400)
#define UDP_SERVERS_PORT         (8080)
#define UDP_CLIENT_PORT          (8081)
#define UDP_SEND_DELAY_TIME_MS   (500)

#define UDP_SERVERS_IP      "192.168.1.22" 


void my_udp_task(void *pdata);
void udp_task_create(void);
struct udp_pcb* my_udp_client_init(void);
int my_udp_send_test(struct udp_pcb *upcb,uint8_t *buff,uint32_t len);
//void mac_power_down(void);

#endif //__UDP_TEST_H__

