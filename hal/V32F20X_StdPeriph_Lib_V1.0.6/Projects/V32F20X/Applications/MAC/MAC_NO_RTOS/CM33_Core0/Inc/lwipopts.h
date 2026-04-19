#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__


#define SYS_LIGHTWEIGHT_PROT    0


#define NO_SYS                  1 

#define MEM_ALIGNMENT           4  


#define MEM_SIZE                16000


#define MEMP_NUM_PBUF           10
#define MEMP_NUM_UDP_PCB        6
#define MEMP_NUM_TCP_PCB        10
#define MEMP_NUM_TCP_PCB_LISTEN 6
#define MEMP_NUM_TCP_SEG        15
#define MEMP_NUM_SYS_TIMEOUT    8

#define PBUF_POOL_SIZE          20
#define PBUF_POOL_BUFSIZE       512


/* ---------- TCP---------- */
#define LWIP_TCP                1 
#define TCP_TTL                 255


#define TCP_QUEUE_OOSEQ         0


#define TCP_MSS                 (1500 - 40)
#define TCP_SND_BUF             (4*TCP_MSS)

#define TCP_SND_QUEUELEN        (2* TCP_SND_BUF/TCP_MSS)
#define TCP_WND                 (2*TCP_MSS)
#define LWIP_ICMP               1
#define LWIP_DHCP               0
#define LWIP_UDP                1
#define UDP_TTL                 255


/* ---------- Statistics options ---------- */
#define LWIP_STATS 0
#define LWIP_PROVIDE_ERRNO 1

#define CHECKSUM_BY_HARDWARE 


#ifdef CHECKSUM_BY_HARDWARE

  #define CHECKSUM_GEN_IP                 0
  #define CHECKSUM_GEN_UDP                0
  #define CHECKSUM_GEN_TCP                0
  #define CHECKSUM_CHECK_IP               0
  #define CHECKSUM_CHECK_UDP              0
  #define CHECKSUM_CHECK_TCP              0
#else
  /* CHECKSUM_GEN_IP==1: Generate checksums in software for outgoing IP packets.*/
  #define CHECKSUM_GEN_IP                 1
  /* CHECKSUM_GEN_UDP==1: Generate checksums in software for outgoing UDP packets.*/
  #define CHECKSUM_GEN_UDP                1
  /* CHECKSUM_GEN_TCP==1: Generate checksums in software for outgoing TCP packets.*/
  #define CHECKSUM_GEN_TCP                1
  /* CHECKSUM_CHECK_IP==1: Check checksums in software for incoming IP packets.*/
  #define CHECKSUM_CHECK_IP               1
  /* CHECKSUM_CHECK_UDP==1: Check checksums in software for incoming UDP packets.*/
  #define CHECKSUM_CHECK_UDP              1
  /* CHECKSUM_CHECK_TCP==1: Check checksums in software for incoming TCP packets.*/
  #define CHECKSUM_CHECK_TCP              1
#endif


#define LWIP_NETCONN                    0

/*
   ------------------------------------
   ---------- Socket API----------
   ------------------------------------
*/

#define LWIP_SOCKET                     0
#define LWIP_COMPAT_MUTEX               1
#define LWIP_SO_RCVTIMEO                1


/*
   ----------------------------------------
   ---------- Lwip----------
   ----------------------------------------
*/
//#define LWIP_DEBUG                     1 
#define ICMP_DEBUG                      LWIP_DBG_OFF

#endif /* __LWIPOPTS_H__ */

