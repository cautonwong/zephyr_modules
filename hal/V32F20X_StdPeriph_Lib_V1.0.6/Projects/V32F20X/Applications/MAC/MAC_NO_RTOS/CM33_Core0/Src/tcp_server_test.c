
/**
  * @file    tcp_server_test.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief
******************************************************************************/
#include "tcp_server_test.h" 
#include "timer.h"
#include "stdio.h"
#include "string.h"  
#include "lwip_comm.h"  


extern void tcp_pcb_purge(struct tcp_pcb *pcb);	
extern struct tcp_pcb *tcp_active_pcbs;		 
extern struct tcp_pcb *tcp_tw_pcbs;	





uint8_t tcp_server_recvbuf[TCP_SERVER_RX_BUFSIZE] = {0};
uint8_t tcp_server_sendbuf[TCP_SERVER_RX_BUFSIZE] = {0};

uint8_t tcp_server_flag = 0;
 
 
void tcp_server_init(void)
{
	err_t err = 0;  
	struct tcp_pcb *tcppcbnew = NULL;
	struct tcp_pcb *tcppcbconn = NULL;
	
    
	tcppcbnew = tcp_new();	  // creat a new pcb
	if(tcppcbnew)			  
	{ 
		err = tcp_bind(tcppcbnew,IP_ADDR_ANY,TCP_SERVER_PORT);
		if(ERR_OK == err)	  
		{
			tcppcbconn = tcp_listen(tcppcbnew); 	
			tcp_accept(tcppcbconn, tcp_server_accept); 	         
		}
  }
}



err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	err_t ret_err = 0;
	struct tcp_server_struct *es = NULL; 
                                    
 	LWIP_UNUSED_ARG(arg);
	LWIP_UNUSED_ARG(err);
	tcp_setprio(newpcb, TCP_PRIO_MIN);          
	es = (struct tcp_server_struct*)mem_malloc(sizeof(struct tcp_server_struct));   
 	if(es != NULL)                             
	{
		es->state = ES_TCPSERVER_ACCEPTED;  
		es->pcb = newpcb;
		es->p = NULL;
		
		tcp_arg(newpcb, es);
		tcp_recv(newpcb, tcp_server_recv);	                            
		tcp_err(newpcb, tcp_server_error); 	                            
		tcp_poll(newpcb, tcp_server_poll, 1);	                        
		tcp_sent(newpcb, tcp_server_sent);  	                       
		  
		tcp_server_flag |= 1<<5;				                              // a client is connected
		lwipdev.remoteip[0] = newpcb->remote_ip.addr & 0xff; 		      // IADDR4
		lwipdev.remoteip[1] = (newpcb->remote_ip.addr >> 8) & 0xff;  	// IADDR3
		lwipdev.remoteip[2] = (newpcb->remote_ip.addr >> 16) & 0xff; 	// IADDR2
		lwipdev.remoteip[3] = (newpcb->remote_ip.addr >> 24) & 0xff; 	// IADDR1 
		ret_err = ERR_OK;
	}
    else 
    {
        ret_err = ERR_MEM;
    }
    
	return ret_err;
}


// lwIP tcp_recv() callback
err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
  err_t ret_err = 0;
  uint32_t data_len = 0;
  struct pbuf *q = NULL;
  struct tcp_server_struct *es = NULL;


  LWIP_ASSERT("arg != NULL", arg != NULL);
  es = (struct tcp_server_struct *)arg;
  if(NULL == p)                            // New data is received from the client
  {
    es->state = ES_TCPSERVER_CLOSING;      // Need to close TCP connection
    es->p = p; 
    ret_err = ERR_OK;
  }
  else if(err != ERR_OK)	                
  {
    if(p)
    {
      pbuf_free(p);	                
    }
    
    ret_err = err;
  }
  else if(ES_TCPSERVER_ACCEPTED == es->state) 	               // In a connected state
  {
    if(p!=NULL)                                              
    {
      memset(tcp_server_recvbuf, 0, TCP_SERVER_RX_BUFSIZE);
      for(q = p; q != NULL; q = q->next)                  
      {
        if(q->len > (TCP_SERVER_RX_BUFSIZE - data_len)) 
        {
          memcpy((tcp_server_recvbuf + data_len), q->payload, (TCP_SERVER_RX_BUFSIZE - data_len)); 
        }
        else
        {
          memcpy((tcp_server_recvbuf + data_len), q->payload, q->len);
        }

        data_len += q->len;  	
        if(data_len > TCP_SERVER_RX_BUFSIZE)
        {
          break;                                   
        }
      }

      tcp_server_flag |= 1u << 6;	                                // Received the data
      lwipdev.remoteip[0] = tpcb->remote_ip.addr & 0xff; 		      // IADDR4
      lwipdev.remoteip[1] = (tpcb->remote_ip.addr >> 8) & 0xff;   // IADDR3
      lwipdev.remoteip[2] = (tpcb->remote_ip.addr >> 16) & 0xff;  // IADDR2
      lwipdev.remoteip[3] = (tpcb->remote_ip.addr >> 24) & 0xff;  // IADDR1 
      tcp_recved(tpcb, p->tot_len);                               // Access to the data received

      tcp_server_flag |= 1u << 7;                                 // There are data needs to be sent
      memcpy(tcp_server_sendbuf, tcp_server_recvbuf, p->tot_len);
      tcp_server_sendbuf[p->tot_len] = 0;
      pbuf_free(p);  
      ret_err = ERR_OK;
    }
  }
  else // The server is close
  {
    tcp_recved(tpcb, p->tot_len);       // Access to the data received
    es->p = NULL;
    pbuf_free(p);                      
    ret_err = ERR_OK;
  }

  return ret_err;
}


// lwIP tcp_err callback
void tcp_server_error(void *arg, err_t err)
{  
  LWIP_UNUSED_ARG(err);  
  printf("tcp error:%x\r\n",(uint32_t)arg);
  if(arg != NULL)
  {
    mem_free(arg);                      
  }
} 


// lwIP tcp_poll callback
err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb)
{
  err_t ret_err = 0;
  struct tcp_server_struct *es = NULL; 

  es = (struct tcp_server_struct *)arg; 
  if(es != NULL)
  {
    if(tcp_server_flag&(1u << 7))	                // Whether there is data to be sent
    {
      es->p = pbuf_alloc(PBUF_TRANSPORT, strlen((char*)tcp_server_sendbuf), PBUF_POOL); 
      pbuf_take(es->p, (char*)tcp_server_sendbuf, strlen((char*)tcp_server_sendbuf));
      tcp_server_senddata(tpcb, es); 		       
      tcp_server_flag &= ~(1 << 7);  			    // Clear data send bit
      if(es->p != NULL)
      {
        pbuf_free(es->p); 	                   
      }
    }
    else if(ES_TCPSERVER_CLOSING == es->state)     
    {
      tcp_server_connection_close(tpcb, es);      
    }

      ret_err = ERR_OK;
  }
  else
  {
    tcp_abort(tpcb);                               
    ret_err = ERR_ABRT; 
  }
  
  return ret_err;
} 


// lwIP tcp_sent callback
err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, uint16_t len)
{
  struct tcp_server_struct *es = NULL;

  LWIP_UNUSED_ARG(len); 
  es = (struct tcp_server_struct *)arg;
  if(es->p)
  {
    tcp_server_senddata(tpcb, es);      
  }

  return ERR_OK;
}


// send data
void tcp_server_senddata(struct tcp_pcb *tpcb, struct tcp_server_struct *es)
{
  struct pbuf *ptr = NULL;
  uint16_t plen = 0;
  err_t wr_err = ERR_OK;

  while((ERR_OK == wr_err) && es->p && (es->p->len <= tcp_sndbuf(tpcb)))
  {
    ptr = es->p;
    wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);  
    if(ERR_OK == wr_err)
    { 
      plen = ptr->len;
      es->p = ptr->next;			                    
      if(es->p)
      {
        pbuf_ref(es->p);	                        
      }

      pbuf_free(ptr);
      tcp_recved(tpcb,plen); 		                    
    }
    else if(ERR_MEM == wr_err)
    {
      es->p = ptr;
    }

    tcp_output(tpcb);                                 
  }
}


// Closing the TCP connection
void tcp_server_connection_close(struct tcp_pcb *tpcb, struct tcp_server_struct *es)
{
  tcp_close(tpcb);
  tcp_arg(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  tcp_poll(tpcb, NULL, 0);

  if(es)
  {
    mem_free(es);
  }

  tcp_server_flag &= ~(1u << 5);                       
}



void tcp_server_remove_timewait(void)
{
  struct tcp_pcb *pcb = NULL;
  struct tcp_pcb *pcb2 = NULL; 
  uint8_t t = 0;

  while((tcp_active_pcbs != NULL) && (t < 200))
  {
    lwip_periodic_handle();	                         
    t++;
    delay_5ms(2);			                        
  }

  pcb = tcp_tw_pcbs;
  while(pcb != NULL)                                   
  {
    tcp_pcb_purge(pcb); 
    tcp_tw_pcbs=pcb->next;
    pcb2=pcb;
    pcb=pcb->next;
    memp_free(MEMP_TCP_PCB,pcb2);	
  }
}


