/**
  ******************************************************************************
  * @file    udp_test.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-21
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include <stdint.h>
#include "udp_test.h"
#include "main.h"



#define UDP_TASK_STK_SIZE 512

#define UDP_INIT_TASK_STK_SIZE            (512)
#define UDP_INIT_TASK_PRI                 (configMAX_PRIORITIES - 2)
#define UDP_INIT_TASK_NAME                "udp_init"

osThreadId_t udpInitHandle;
const osThreadAttr_t udpInit_attributes = {
  .name = UDP_INIT_TASK_NAME,
  .priority = (osPriority_t) (UDP_INIT_TASK_PRI),
  .stack_size = UDP_INIT_TASK_STK_SIZE
};


char myUdpBuff[UDP_REV_BUF_LEN] = {0};
 



int my_udp_send(char* buff, int len)
{
  int port = UDP_SERVERS_PORT;  
  int socket = 0;
  struct sockaddr_in address = {0};
  int ret = 0;

  if (NULL == buff)
  {
    return -1;
  }

  address.sin_family = AF_INET;  
  address.sin_addr.s_addr = inet_addr(UDP_SERVERS_IP);
  address.sin_port = htons(port);
  socket = socket(AF_INET,SOCK_DGRAM,0);
  ret = sendto(socket,buff,len,0,(struct sockaddr *)&address,sizeof(address)); 

  close(socket); 

  return ret;	
}



int my_udp_servers_init(void)
{
  int port = UDP_CLIENT_PORT; 
  int socket = 0;  
  int ret = 0;
  struct sockaddr_in sockIn = {0}; 
  socklen_t sin_len = 0; 


  sockIn.sin_family = AF_INET;  
  sockIn.sin_addr.s_addr = htonl(INADDR_ANY);  
  sockIn.sin_port = htons(port);  
  sin_len = sizeof(sockIn);  


  socket = socket(AF_INET,SOCK_DGRAM,0); 
  if (socket < 0)
  {
      return socket;
  }

  ret = bind(socket,(struct sockaddr *)&sockIn,sizeof(sockIn));
  if (ret < 0)
  {
      return ret;
  }

  return socket;
}



void my_udp_task(void *pdata)
{
  int ret = 0;
  int socket = 0; 
  struct sockaddr_in sockIn = {0};   
  socklen_t sin_len = sizeof(struct sockaddr);   

  socket = my_udp_servers_init();  

  while(1)
  {
    ret = recvfrom(socket,myUdpBuff,sizeof(myUdpBuff),0,(struct sockaddr *)&sockIn,&sin_len); 
    if (ret > 0) 
    {
      ret = sendto(socket,myUdpBuff,ret,0,(struct sockaddr *)&sockIn,sizeof(sockIn)); 
    }            
  }
}



/*==================================================================
* Function  : AppTaskCreate
* Description   : create UDP task
* Input Para    : None
* Output Para   : None
* Return Value: None
==================================================================*/
void udp_task_create(void)
{
  uint8_t err = 0;
  udpInitHandle = osThreadNew(my_udp_task, NULL, &udpInit_attributes); 
}





