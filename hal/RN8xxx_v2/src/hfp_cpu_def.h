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
#ifndef HFP_CPU_H_
#define HFP_CPU_H_


/* CPU 私有头文件包含区  */




/* CPU  PORT宽度类型定义  */
typedef volatile uint32  gpio_port_t;

/* CPU  栈宽度类型定义  */
typedef uint32  TStack;
#define STACK_INIT_VALUE 0xFFFFFFFF

/* CPU  CODE SIZE DEF  */
#define CODE_SIZE  0x40000   /**< 单片机 CODE 的 大小 */


/* CPU  堆分配长度定义，单位是双字(4bytes)  */
#define ES_HEAP0_LEN     5450


#define RESET_MODE              0
#define POWER_ON_MODE           1
#define POWER_OFF_MODE          2



enum
{
    MEASURE_IRQ = 1,
    SECOND_IRQ,
    PAGEUP_IRQ,
    PAGEUP_LONG_IRQ,
    PAGEDOWN_IRQ,
    PAGEDOWN_LONG_IRQ,
    CARD_INSERT_IRQ,
    CARD_EXTRACTION_IRQ,
    REQUEST_NUM
};



#define  BIT_BAND_EN





#endif
/** @} */


