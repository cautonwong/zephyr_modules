/**
 * @defgroup    
 * @ingroup     
 * @ingroup     
 * @brief       
 *
 * @{
 * @file
 *
 */
#ifndef HFP_BDEF_H_
#define HFP_BDEF_H_



/**********************************************************************************************************
*                   数据类型1
**********************************************************************************************************/
typedef signed char      int8;       /**< 8位有符号数 */
typedef unsigned char    uint8;      /**< 8位无符号数 */
typedef short            int16;      /**< 16位有符号数 */
typedef unsigned short   uint16;     /**< 16位无符号数 */
typedef long             int32;      /**< 32位有符号数 */
typedef unsigned long    uint32;     /**< 32位无符号数 */
typedef void *           Object;     /**< 定义任意类型为Object */
typedef const char *     String;     /**< 定义字符串类型 (在RAM区) */
typedef int8             TResult;    /**< 返回的结果类型 */
typedef void (*TCallback)(void);


#ifndef bool
typedef uint8            bool;
#endif

typedef String           string;

#define  CODE


/**********************************************************************************************************
*                   数据类型2
**********************************************************************************************************/
typedef unsigned char    INT8U;               /**< 无符号8位整型变量 */
typedef signed char      INT8S;               /**< 有符号8位整型变量 */
typedef unsigned short   INT16U;              /**< 无符号16位整型变量 */
typedef signed short     INT16S;              /**< 有符号16位整型变量 */
typedef unsigned int     INT32U;              /**< 无符号32位整型变量 */
typedef signed int       INT32S;              /**< 有符号32位整型变量 */
typedef float            FP32;                /**< 单精度浮点数(32位长度) */
typedef double           FP64;                /**< 双精度浮点数(64位长度) */



/**********************************************************************************************************
*                    数据类型4
**********************************************************************************************************/
typedef union
{
    uint16 word;
    uint8  byte[2];
} Word16;


typedef union
{
    uint32 lword;
    uint16 word[2];
    uint8  byte[4];
} Word32;



/**********************************************************************************************************
*                    数据常量
**********************************************************************************************************/

#ifndef true
#define true    (uint8)1
#endif

#ifndef false
#define false    (uint8)0
#endif

#ifndef __NULL
#define __NULL    ((void *)0)
#endif

#ifndef NULL
#define    NULL    0
#endif



/*********************************************************
 **定义系统函数返回结果
 **********************************************************/
#define ES_ERR_OK         0           /**< 没有错误 */
#define ES_ERR_EXIST      (1)         /**< 不存在 */
#define ES_ERR_FT         (2)         /**< 其他致命错误 */
#define ES_ERR_NRES       (3)         /**< 还有资源被占用无法删除 */
#define ES_ERR_PRIOR      (4)         /**< 优先级错误 */
#define ES_ERR_TIME       (5)         /**< 超时错误 */
#define ES_ERR_NE         (6)         /**< 数量不足 */
#define ES_ERR_GT         (7)         /**< 数量越限 */
#define ES_ERR_NSUSP      (8)         /**< 进程没有挂起 */
#define ES_ERR_TYPE       (10)        /**< 类型不匹配 */
#define ES_ERR_VAR        (11)        /**< 参数错误 */
#define ES_ERR_CHK        (12)        /**< 验证不正确 */
#define ES_ERR_MAIN       (13)        /**< 主存储区错误 */
#define ES_ERR_BACK       (14)        /**< 备份存储区错误 */
#define ES_ERR_WAIT       (15)        /**< 等待 */
#define ES_ERR_DEF        (16)        /**< 使用默认数据 */
#define ES_ERR_NOREPLY    (17)        /**< 无需回复 */
#define ES_ERR_DATA       (18)        /**< 带数据 */
#define ES_ERR_UNKNOW     (127)

#define ER(X)      (ES_ERR_OK == (X))

#define ES_VAR_CHECK(X)             \
    { if (X) { return ES_ERR_VAR; } \
    }
#define ES_OK()    { return ES_ERR_OK; }

/******************************************************************************
**定义比特位宏
******************************************************************************/
#define LBIT(X)    (1ul << (X))

//#ifndef BIT
//#define BIT(x)     LBIT(x)
//#endif



#define NO_BITS    0x00
#define BIT0       0x01
#define BIT1       0x02
#define BIT2       0x04
#define BIT3       0x08
#define BIT4       0x10
#define BIT5       0x20
#define BIT6       0x40
#define BIT7       0x80
#define BIT8       0x0100
#define BIT9       0x0200
#define BIT10      0x0400
#define BIT11      0x0800
#define BIT12      0x1000
#define BIT13      0x2000
#define BIT14      0x4000
#define BIT15      0x8000
#define BIT16      0x010000L
#define BIT17      0x020000L
#define BIT18      0x040000L
#define BIT19      0x080000L
#define BIT20      0x100000L
#define BIT21      0x200000L
#define BIT22      0x400000L
#define BIT23      0x800000L
#define BIT24      0x01000000L
#define BIT25      0x02000000L
#define BIT26      0x04000000L
#define BIT27      0x08000000L
#define BIT28      0x10000000L
#define BIT29      0x20000000L
#define BIT30      0x40000000L
#define BIT31      0x80000000L



/** MAINTASK消息编号 */




#define IO_MSGID_KEY_PAGE_UP        0x01
#define IO_MSGID_KEY_PAGE_DOWN      0x02
#define IO_MSGID_AUTO_PAGE_UP       0x03
#define SYS_MSGID_SEC               0x04         /**< RTC 过秒消息 */
#define METER_MSGID_PLS_OK          0x05         /**电能脉冲消息*/
#define METER_MSGID_EMU_OK          0x06
    
#define IO_MSGID_CARD_INSERT        0x07
#define IO_MSGID_CARD_EXTRACT       0x08
#define IO_MSGID_MD_RST             0x09
#define IO_MSGID_KEY_PAGE_UP_3S     0x0A
#define IO_MSGID_KEY_PAGE_DOWN_3S   0x0B


#endif
/** @} */
