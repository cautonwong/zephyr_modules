
/**
  * @file    tcp_server_test.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
#include "tcp_server_test.h" 
#include <stdio.h>
#include <string.h>  
#include "lwip_comm.h"  


uint8_t tcp_server_recvbuf[TCP_SERVER_RX_BUFSIZE] = {0};	


#define TCP_INIT_TASK_STK_SIZE            (512)
#define TCP_INIT_TASK_PRI                 (configMAX_PRIORITIES - 3)
#define TCP_INIT_TASK_NAME                "tcp_init"

osThreadId_t tcpInitHandle;
const osThreadAttr_t tcpInit_attributes = {
  .name = TCP_INIT_TASK_NAME,
  .priority = (osPriority_t) (TCP_INIT_TASK_PRI),
  .stack_size = TCP_INIT_TASK_STK_SIZE
};

struct sockaddr_in g_ClientAddr = {0};



int tcp_servers_init(void)
{
  int sock = 0;;
  struct sockaddr_in SerAddr;

  sock = socket(AF_INET, SOCK_STREAM, 0);

  SerAddr.sin_family = AF_INET;
  SerAddr.sin_port = htons(TCP_SERVER_PORT);
  SerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(sock, (struct sockaddr *)&SerAddr, sizeof(SerAddr));

  listen(sock, MEMP_NUM_TCP_PCB_LISTEN); 

  return sock;
}



void tcpTask(void* arg)
{
  int sock = 0;
  int bytes = 0;
  socklen_t AddLen = 0;
  int ClientSock = 0;
  int optval = 1;
  static uint8_t errCount = 0;
  int error = 0;
  int errorLimit = 0;
  uint32_t delayTime = 0;

  osDelay(1000);
  sock = tcp_servers_init();
  AddLen = sizeof(g_ClientAddr);

  for (;;)
  {

    bytes = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, NULL, 0);
    ClientSock = accept(sock, (struct sockaddr *)&g_ClientAddr, &AddLen);  

    if (ClientSock == -1)
    {
      continue;
    }       

    if ((bytes = recv(ClientSock, tcp_server_recvbuf, sizeof(tcp_server_recvbuf) - 1, 0)) <= 0)
    {
      close(ClientSock);
      continue;
    }
    
    tcp_server_recvbuf[bytes] = 0;	
    send(ClientSock, tcp_server_recvbuf, bytes, 0);  

    close(ClientSock);
  }

}


void tcp_task_create(void)
{
  uint8_t err = 0;
  tcpInitHandle = osThreadNew(tcpTask, NULL, &tcpInit_attributes); 
}


