
/**
  * @file    tcp_server_test.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-14
  * @brief   
******************************************************************************/

#ifndef __TCP_SERVER_DEMO_H
#define __TCP_SERVER_DEMO_H


#include "cmsis_os.h"
#include "lwip/sockets.h"

 
#define TCP_SERVER_RX_BUFSIZE  1400
#define TCP_SERVER_PORT        8081
 
void tcp_task_create(void);


#endif 


