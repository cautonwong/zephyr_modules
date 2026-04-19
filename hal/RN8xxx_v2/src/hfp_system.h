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
#ifndef SYS__H
#define SYS__H


#include "hfp_def.h"
#include "hfp_cpu_def.h"
#define CODE

enum hfp_unit_type_t
{
    unit_year      = 1,
    unit_month     = 2,
    unit_week      = 3,
    unit_day       = 4,
    unit_hour      = 5,
    unit_minute    = 6,
    unit_second    = 7,
    unit_angle     = 8,   /**< 度 */
    unit_tempture  = 9,   /**< 温度 */
    unit_currency  = 10,  /**< 货币 */
    unit_W         = 27,  /**< 有功功率,W */
    unit_kW        = 28,  /**< 有功功率,kW */
    unit_VA        = 29,  /**< 视在功率,VA */
    unit_kVA       = 30,  /**< 视在功率,kVA */
    unit_var       = 31,  /**< 无功功率,var */
    unit_kvar      = 32,  /**< 无功功率,kvar */
    unit_kWh       = 33,  /**< 有功电能,kWh */
    unit_kVAh      = 34,  /**< 视在电能,kVAh */
    unit_kvarh     = 35,  /**< 无功电能,kvarh */
    unit_A         = 36,  /**< 电流（ I） */
    unit_V         = 38,  /**< 电压（ U） */
    unit_Hz        = 47,  /**< 频率 */
    unit_percent   = 51,  /**< 百分比 % */
    unit_byte      = 52,  /**< 字节 */
    unit_price     = 54,  /**< 电价 */
    unit_Ah        = 55,  /**< 安时 */
                          
    unit_ohters    = 254, /**< 其他单位 */
    unit_undefined = 255  /**< 无单位、缺单位、计数 */
};

struct unit_decmail_t
{
    uint8 unit;
    int8 decmail;
};

enum hfp_data_type_t
{
    DT_NULL                 = 0,
    DT_ARRAY                = 1,
    DT_STRUCTURE            = 2,
    DT_BOOLEAN              = 3,
    DT_BIT_STRING           = 4,
    DT_DOUBLE_LONG          = 5,   /**< int32 */
    DT_DOUBLE_LONG_UNSIGNED = 6,   /**< uint32 */
    DT_FLOATING_POINT       = 7,
    DT_OCTET_STRING         = 9,
    DT_VISIBLE_STRING       = 10,
    DT_UTF8_STRING          = 12,
    DT_BCD                  = 13,
    DT_INTEGER              = 15,   /**< int8 */
    DT_LONG                 = 16,   /**< int16 */
    DT_INTEGER_UNSIGNED     = 17,   /**< uint8 */
    DT_LONG_UNSIGNED        = 18,   /**< uint16 */
    DT_COMPACT_ARRAY        = 19,
    DT_LONG64               = 20,   /**< int64 */
    DT_LONG64_UNSIGNED      = 21,   /**< uint64 */
    DT_ENUM                 = 22,
    DT_FLOAT32              = 23,
    DT_FLOAT64              = 24,
    DT_DATE_TIME            = 25,
    DT_DATE                 = 26,
    DT_TIME                 = 27,
    DT_DATETIME_S           = 28,
    DT_OI                   = 80,
    DT_OAD                  = 81,
    DT_ROAD                 = 82,
    DT_OMD                  = 83,
    DT_TI                   = 84,
    DT_TSA                  = 85,
    DT_MAC                  = 86,
    DT_RN                   = 87,
    DT_REGION               = 88,
    DT_SCALER_UNIT          = 89,
    DT_RSD                  = 90,
    DT_CSD                  = 91,
    DT_MS                   = 92,
    DT_SID                  = 93,
    DT_SID_MAC              = 94,
    DT_COMDCB               = 95,
    DT_RCSD                 = 96,


	/* 自定义数据类型 */
	DT_NOT_CARE				= 243,
	DT_SPECIAL_PROCESS		= 244,
	DT_PUSH_PROCESS         = 245,  /*事件上报标志 特殊标志*/
    DT_ERROR                = 255,
};

/**
 *
 */
struct rtc_t
{
    uint8 second;   /**< seconds after the minute - [0,59] */
    uint8 minute;   /**< minutes after the hour - [0,59] */
    uint8 hour;     /**< hours since midnight - [0,23] */
    uint8 day;      /**< day of the month - [1,31] */
    uint8 month;    /**< months since January - [1,12] */
    uint8 year;     /**< years since 1900 */
    uint8 week;     /**< days since Sunday - [0,6] */
    uint8 status;   /**< rtc status: daylight savings time flag, clock invalid , rtc err and so on */
};
extern struct rtc_t hfp_time;
extern uint32       system_tick_cnt;


struct standalone_timing_node_t
{
    uint8 standalone_loops;
    uint8 second;   /**< seconds after the minute - [0,59] */
    uint8 minute;   /**< minutes after the hour - [0,59] */
    uint8 hour;     /**< hours since midnight - [0,23] */
    uint8 day;      /**< day of the month - [1,31] */
    uint8 month;    /**< months since January - [0,11] */
    uint8 year;     /**< years since 1900 */
    uint8 week;
};

/**
 * @interface module_execute_t
 * @brief   内核模块的插件接口.
 *          所有通信协议务必实现此接口,已支持以下等协议通信模式.
 *  - 一问一答
 *  - 一问多答
 *  - 主动推送
 *  -
 * @attention 此列表一定要加上{__NULL,__NULL}为结束符，不然会死机
 */
struct module_execute_t
{
    /**
     * @brief 定时或轮循判断点
     */
    const struct standalone_timing_node_t CODE *rtc_mount_node;

    /**
     * @brief 定时或轮循判断点
     */
    void               (*execute)(void);
};

/**
 * @interface module_t
 * @brief   内核模块的插件接口.
 *          所有通信协议务必实现此接口,已支持以下等协议通信模式.

 */
struct module_t
{
    /**
     * @brief   模块执行体表头.
     *
     *          在系统初始化时调用
     *
     * @return	- 头指针.如果初始化成功
     * @return	- NULL.如果初始化失败
     */
    const struct module_execute_t CODE *execute_list;            /**/

    /**
     * @brief   模块复位初始化.
     *
     *          在系统初始化时调用
     * @note
     */
    void                          (*reset_init)(void);

    /**
     * @brief   模块预上电处理.
     *
     *          在系统初始化时调用
     * @note
     */
    void                          (*pre_power_on)(void);
    void                          (*power_on)(void);             /**< 上电处理	    */
    void                          (*msg_handler)(uint16 msg_id); /**< 消息分解	    */
    void                          (*pre_power_off)(void);        /**< 预掉电处理    */
    uint16                         (*power_off)(uint8 *buf);       /**< 掉电处理 */
    void                          (*timing_awaken_handler)(void); /**定时唤醒处理 */ 
    //int32                          (*ram_integrity)(void);         /**ram可靠性检查*/
    void                          (*get_version)(uint8 *data);   /**< 获取插件版本号 */
};

/**< 内核模块名称 */
enum module_name_t
{
    name_energy  = 0, /**< months since January - [0,11] */
    name_clock  = 1, /**< months since January - [0,11] */
    name_demand  = 2, /**< months since January - [0,11] */
    name_datapro = 3, /**< months since January - [0,11] */
    name_display = 4, /**< months since January - [0,11] */
    name_ctrl    = 5, /**< months since January - [0,11] */
    name_comm    = 6, /**< months since January - [0,11] */
    name_instantaneous = 7,
    name_para_change  = 8,
	name_rtc = 9,
    notify_num
};


struct module_config_t
{
    const struct module_t CODE *module;
    enum module_name_t           name;
    uint16                       attribute;
};



/**
 * @interface hardware_platform_t
 * @brief   硬件的抽象接口.
 *          所有通信协议务必实现此接口,已支持以下等协议通信模式.
 *  - 一问一答
 *  - 一问多答
 *  - 主动推送
 */
struct machine_interface_t
{
    void  (*mcu_init_config)(void);
    void  (*disable_interrupt_all)(void);
    void  (*enable_interrupt_all)(void);
    void  (*user_isr_ctrl)(uint8 business_request , uint8 cmd);
    void  (*clear_watchdog)(void);
    void  (*mcu_enter_sleep)(void);
    void  (*mcu_exit_sleep)(void);
    uint8 (*mcu_delay_us)(volatile uint16 count);
    uint8 (*power_off_check)(void);
    uint8 (*power_on_check)(void);
    void  (*enter_low_power)(void);
    void  (*enter_normal_power)(void);    
    uint8  (*adc_start_one)(uint8 chl_type);
    uint32 (*read_adc_measure_value)(uint8 chl_type , uint32 *adc_measure);
    void  (*mcu_debug_breakpoint)(void);
    
    void  (*get_hardware_version)(uint8 *hardware_version);
};
extern const struct machine_interface_t CODE plugin_machine;

struct board_interface_t
{
    void  (*enter_low_power)(void);
    void  (*enter_normal_power)(void);
    void  (*wakeup)(void);
    void  (*power_off_start_hook)(void);
    void  (*power_off_end_hook)(void);
    void  (*power_on_start_hook)(void);
    void  (*power_on_end_hook)(void);
    void  (*tick_hook)(void);
    void  (*reset_hook)(void);
};

extern const struct board_interface_t CODE plugin_board;



struct hfp_tick_timer_t
{
    void  (*init)(void);
    uint8 (*create)(uint8 (*tickfunc)(void *), void *tickpara, uint16 timeout, uint8 stoped);
    uint8 (*start)(uint8 timerid);
    uint8 (*startone)(uint8 timerid, uint16 count);
    void  (*tick)(void);
    uint8 (*stop)(uint8 timerid);
};

extern const struct hfp_tick_timer_t CODE hfp_tick_timer;

struct message_box_t
{
    uint16 rdy;
    uint8  msg[8];
    void   *content;
};


struct hfp_message_ops_t
{
    void  (*init)(void);
    uint8 (*send)(uint8 msg);
    uint8 (*get)(void);
};
extern const struct hfp_message_ops_t CODE hfp_message;


struct heap_mem_ops_t
{
    void (*malloc_init)(void);
    void *(*malloc)(uint16 size, uint8 reset);
    void (*malloc_hook)(void *r, uint16 size);
};

extern const struct heap_mem_ops_t CODE hfp_heap;

/***********************************************************
 * @总线传输方式
 **********************************************************/
enum bus_class_t
{
    BUS_IIC  = 1,
    BUS_SPI  = 2,
    BUS_UART = 3,
    BUS_7816
};

enum
{
    UART_PARITY_NO  = 0x00,                    /**< 无校验 */
    UART_PARITY_ODD = 0x01,                    /**< 奇校验 */
    UART_PARITY_EVEN= 0x02                     /**< 偶校验 */
};

enum
{
    UART_MODE_NORMAL = 0x00,
    UART_MODE_IR     = 0x01,
    UART_MODE_7816   = 0x02
};
/***********************************************************
 * @设备编号
 **********************************************************/
enum device_id_t
{
    DEVICE_EEPROM        = 1,
    DEVICE_FRAM          ,
    DEVICE_FLASH         ,
    DEVICE_EMU           ,
    DEVICE_ESAM_698      ,
    DEVICE_CARD          ,
    DEVICE_RTC           ,
    DEVICE_LCD           ,
    DEVICE_RS4851        ,
    DEVICE_RS4852        ,
    DEVICE_IR            ,
    DEVICE_PLC           ,
    DEVICE_GPRS          ,
    DEVICE_RF            ,
    DEVICE_PAGE_UP       ,
    DEVICE_PAGE_DOWN     ,    
    DEVICE_COVER         ,
    DEVICE_TERM          ,
    DEVICE_MAGNETIC      ,
    
    DEVICE_BACKLIGHT     ,
    DEVICE_BUZZER        ,
    DEVICE_RELAY_LED     ,
    DEVICE_ALARM_LED     ,
    DEVICE_SURPLUS_LED   ,
    DEVICE_RELAY         ,
    DEVICE_LEVEL_RELAY   ,
    DEVICE_EVEN_OUT      ,

    DEVICE_RAM           ,
    DEVICE_CHAR          ,
    DEVICE_ENERGY        ,
    DEVICE_INSTANTANEOUS ,
    DEVICE_DEMAND        ,
    DEVICE_645READDEMAND ,
	DEVICE_MEM_RTC       ,
	DEVICE_DLT645	     ,
	DEVICE_CTRL	         ,
	DEVICE_TARIFF	     ,
	DEVICE_METER	     ,
    DEVICE_DISPLAY       ,
	DEVICE_DLT698        ,
	DEVICE_RUNSTATUS     ,
	DEVICE_ALARM_STATUS  ,
	DEVICE_ESAM          ,
	DEVICE_STATISTIC     ,
	DEVICE_PREPAY        ,
	DEVICE_CARD_APPLY    ,
	DEVICE_SNAPSHOT
};

/**
 * @struct gpio_pin_t
 * @brief   IO的抽象接口.
 */
struct gpio_pin_t
{
    /**
     * @struct gpio_pin_t
     * @brief   IO的抽象接口.
     */
    gpio_port_t *lat_out;
    gpio_port_t *port_in;
    gpio_port_t *direct;
    void        (*out)(gpio_port_t *direct, gpio_port_t pin_bit);
    void        (*in)(gpio_port_t *direct, gpio_port_t pin_bit);
    void        (*active_out)(gpio_port_t *lat_out, gpio_port_t pin_bit);
    void        (*non_active_out)(gpio_port_t *lat_out, gpio_port_t pin_bit);
    gpio_port_t  pin_bit;
};




struct iic_bus_resource_t
{
    const struct gpio_pin_t CODE *sda;
    const struct gpio_pin_t CODE *scl;
};

struct iic_bus_ops_t
{
    uint8  (*init)(const struct iic_bus_resource_t CODE *iic_bus_resource);
    void  (*iic_start)(const struct iic_bus_resource_t CODE *iic_bus_resource);
    void  (*iic_stop)(const struct iic_bus_resource_t CODE *iic_bus_resource);
    uint8  (*tx_byte)(uint8 send_data, const struct iic_bus_resource_t CODE *iic_bus_resource);
    uint8  (*rx_byte)(uint8 ack_enable, const struct iic_bus_resource_t CODE *iic_bus_resource);
};



/*
struct synchronization_bus_ops_t
{
    uint8 (*init)(const void CODE * bus_resource);
    void  (*start)(const void CODE * bus_resource);
    void  (*stop)(const void CODE * bus_resource);
    uint8  (*tx_byte)(uint8 send_data, const void CODE * bus_resource);
    uint8  (*rx_byte)(uint8 ack_enable, const void CODE * bus_resource);
};
*/

struct spi_bus_resource_t
{
    const struct gpio_pin_t CODE *clk;
    const struct gpio_pin_t CODE *miso;
    const struct gpio_pin_t CODE *mosi;
};


struct spi_bus_ops_t
{
    uint8  (*init)(const struct spi_bus_resource_t CODE *spi_bus_resource);
    void  (*start)(const struct spi_bus_resource_t CODE *spi_bus_resource);
    void  (*stop)(const struct spi_bus_resource_t CODE *spi_bus_resource);
    uint8  (*tx_byte)(uint8 send_data, const struct spi_bus_resource_t CODE *spi_bus_resource);
    uint8  (*rx_byte)(uint8 ctrl, const struct spi_bus_resource_t CODE *spi_bus_resource);
};


struct uart_config_t
{
    uint16 baud_rate;
    uint8  data_bits;
    uint8  parity;
    uint8  stop_bits;
    uint8  mode;
};

/***********************************************************
 * @普通串口资源结构
 **********************************************************/
struct uart_resource_t
{
#ifdef WIN32
    const char CODE     *device_name;
#endif
    const struct gpio_pin_t CODE *recive_active;
    const struct gpio_pin_t CODE *rx_pin;
    const struct gpio_pin_t CODE *tx_pin;
    const struct gpio_pin_t CODE *reset_pin;
    uint8        mcu_uart_index;
};

struct connection_setting_t
{
    uint16 baud_rate;                   /**< 通讯波特率 */
    uint16 rx_tx_buffer_size;           
    uint8  *rx_buffer_ptr;              /**< 接收缓存地址 */
    uint8  *tx_buffer_ptr;              /**< 发送缓存地址 */
};

struct mcu_uart_ops_t
{
    uint8 (*config_init)(struct uart_config_t *config, const struct uart_resource_t CODE *uart_resource);
    void  (*rx_enable)(uint8 enable, const struct uart_resource_t CODE *uart_resource);
    void  (*tx_enable)(uint8 enable, const struct uart_resource_t CODE *uart_resource);
    void  (*tx_byte)(uint8 send_data, const struct uart_resource_t CODE *uart_resource);
    uint8  (*rx_byte)(const struct uart_resource_t CODE *uart_resource , uint8 *byte);
    uint8  (*set_uart_baud)(uint16 baud, const struct uart_resource_t CODE *uart_resource);
    uint8  (*close)(const struct uart_resource_t CODE *uart_resource);
};

/***********************************************************
 * @EEPROM 硬件配置
 **********************************************************/
struct eeprom_hal_cfg_t
{
    uint32 size;            /**< 存储器大小 */
    uint16 page_size;       /**< 页写尺寸 */
    uint8  hard_addr;       /**< 器件地址低3位 */
};

/***********************************************************
 * @FRAM 硬件配置
 **********************************************************/
struct fram_hal_cfg_t
{
    uint32 size;            /**< 存储器大小 */
    uint16 page_size;       /**< 页写尺寸 */
    uint8  hard_addr;       /**< 器件地址低3位 */
};

/***********************************************************
 * @FLASH 硬件配置
 **********************************************************/
struct flash_hal_cfg_t
{
    uint32              size;           /**< FLASH 容量 */
    uint16              page_size;      /**< 页写尺寸 */
    uint16              section_size;
    const struct gpio_pin_t CODE *power_ctrl;   /**< FALSH 电源控制IO */
    const struct gpio_pin_t CODE *cs;           /**< FALSH 片选控制 */
};
/***********************************************************
 * @EMU 硬件配置
 **********************************************************/
struct emu_hal_cfg_t
{
    const struct gpio_pin_t CODE *power_ctrl;   /**< FALSH 电源控制IO */
    const struct gpio_pin_t CODE *cs;           /**< FALSH 片选控制 */
    //const struct gpio_pin_t CODE *sleep_ctrl; 
    const struct gpio_pin_t CODE *reset;
};

struct esam698_hal_cfg_t
{
    const struct gpio_pin_t CODE *power_ctrl;   /**< ESAM 电源控制IO */
    const struct gpio_pin_t CODE *cs;           /**< ESAM 片选控制 */ 
};

enum
{
    BUTTON_CHECK_TYPE_INT =  0x01,
    BUTTON_CHECK_TYPE_SCANF= 0x02
};

struct button_resource_t
{
	const struct gpio_pin_t CODE *button;
    uint8 mcu_int_index;
    uint8 button_check_type;
    uint8 button_index;
};

struct button_hal_cfg_t
{
    uint16 active_time;
	uint8 active_state;
	uint8 request_id;
};
struct relay_resource_t
{
	const struct gpio_pin_t CODE *connect_pin;
	const struct gpio_pin_t CODE *disconnect_pin;
    const struct gpio_pin_t CODE *relay_check;
    const struct gpio_pin_t CODE *relay_extern_check;
};

struct relay_hal_cfg_t
{
    uint16						driver_width;
    uint16                      chk_connect_level;
};

struct rtc_hal_cfg_t
{
    const struct gpio_pin_t CODE *multifunction_port;
};

struct relay_ctrl_parameter_t
{
    uint16  driver_width;
};

/***********************************************************
 * @设备模型
 **********************************************************/
struct hfp_device_t
{
    enum device_id_t      device_id;                /**< 器件ID */
    enum bus_class_t      bus_class;                /**< 传输类别 */
    const void CODE       *bus_driver;              /**< 总线驱动 */
    const void CODE       *resource;                /**< 器件占用CPU资源描述 */
    const void CODE       *hal_cfg;                 /**< 器件硬件配置描述 */
    const struct driver_t CODE *driver;             /**< 器件驱动挂载 */
};

/***********************************************************
 * @驱动接口
 **********************************************************/
struct driver_t
{
    uint8	(*init)	( const struct hfp_device_t CODE  *device , uint8 power_mode);
    uint8	(*read)	(uint32 addr, uint8 *buf, uint16 len, const struct hfp_device_t CODE *device);
    uint8	(*write)(uint32 addr, uint8 *buf, uint16 len, const struct hfp_device_t CODE *device);
    uint8	(*ioctrl)(uint8 cmd, const struct hfp_device_t CODE *device, void *ctrl_parameter);
};

struct uart_ctrl_t
{
    uint16 baud;
    uint16 delete_len;
};

struct buzzer_set_t
{
    uint16 active_width;
    uint16 active_num;
};

/** 唯一全局可见的可直接访问的数据结构 */
enum power_state_t
{
    BATTER_SUPPLY  = 1,    /**< 电池供电 */
    ACPOWER_SETUP  = 2,    /**< 上电前三秒 */
    ACPOWER_SUPPLY = 3,    /**< 交流供电 */
    BATTER_SETUP   = 4     /**< 电池供电前三秒 */
};

enum meter_run_mode_t
{
    FACTORY_MODE = 0x5A3B,      /**< 厂内模式 */
    USER_MODE    = 0x0000       /**< 用户模式 */
};

enum current_tariff_t
{
    TARIFF_1 = 1,
    TARIFF_2 = 2,
    TARIFF_3 = 3,
    TARIFF_4 = 4
};

struct meter_context_t
{
    uint32 batter_use_time;
    
};

/**系统故障定义*/
#define ERR_EEPROM      BIT0
#define ERR_RTC         BIT1
#define ERR_FLASH       BIT2
#define ERR_RELAY       BIT3
#define ERR_ESAM        BIT4
#define ERR_EMU         BIT5


/**通讯状态定义*/
#define  INFRARED_BUSY  BIT0
#define  RS485_BUSY     BIT1
#define  MODULE_BUSY    BIT2

/**显示状态定义*/
enum display_status
{
    DISPLAY_STA_OFF,    /**< 关机模式 */
    DISPLAY_STA_ON,     /**< 上电运行模式 */
    DISPLAY_STA_SLEEP,  /**< 休眠静止模式 */
    DISPLAY_STA_AWAKEN  /**< 唤醒运行模式 */
};

#define WAKEUP_HIGH_OSC  0x5A
#define SLEEP_HIGH_OSC   0xA5


/*通用状态字*/
#define  HARD_TEST_ENBLE   0x01


struct system_state_t
{
    uint16 error_word;
    uint16 common_word;
    enum power_state_t power_state;
    uint32 standalone_loops;
    uint32 power_off_sencond;
    uint8  communcation;
    uint8  display;
    uint8  power_fail_interrupt;
    uint8  this_sleep_osc_mode;
    uint8  next_wakeup_osc_mode;
};
extern struct system_state_t hfp_system_state;



struct meter_state_t
{
    enum meter_run_mode_t run_mode;
    enum current_tariff_t current_tariff;
};

struct specification_t
{
    uint16 un;          /**< 额定电压,0.01V */
    uint16 un_1_2;      /**< 120%电压，0.01V */
    uint16 ib;          /**< 额定电流, 1毫安 */
    uint16 u_start;     /**< 临界电压 ,0.01V */
    uint16 u_60;        /**< 60%电压，0.01V */
    uint16 u_68;        /**< 68%电压，0.01V */
    uint16 i_start;     /**< 启动电流, 1毫安 */
    uint16 ib_005;      /**< 5%额定电流，毫安 */
    uint16 i_max;       /**< 最大电流，0.1A */
};

struct parameter_attr_t
{
    uint16          parameter_fsid;
    uint16          len;
    void            *parameter_data;
    uint16          *mac;
    uint16          (*mac_calculate)(uint8 *ptr, uint16 len);
    const void CODE *parameter_default;
    uint8           offset;
};

struct rtc_adj_t
{
	int16  err_ppm;
	uint32 adj_para;
};

struct aync_isr_msg_t
{
     uint8 isr;
     uint8 msg_id;
     uint8 lowpower_enable;
};

struct esam_apdu_t
{
    uint8  *tx_apdu;
    uint8  *tx_data;
    uint8  *rx_buf;
    uint16  data_tx_len;
    uint16  *data_rx_len;
    uint16  sw;
};

struct esam_security_t
{
    uint8 *apdu;                /*待加解密的数据指针*/
    uint16 apdu_len;            /*待加解密的数据长度*/
    uint8 sid[1 + 4];           /*数据标识  ，第一个字节为长度，第一个字节为0表示SID不存在*/
    uint8 attach[1 + 32];       /*附加数据  ，第一个字节为长度，第一个字节为0表示附加数据不存在*/
    uint8 mac[1 + 16];          /*消息校验码，第一个字节为长度，第一个字节为0表示MAC不存在*/
    uint8 rn[1 + 64];           /*随机数    ，第一个字节为长度，第一个字节为0表示随机数不存在*/
};

struct esam_wallet_t
{
    int8 type;                  /*操作类型 0—开户 1—充值 2-退费*/
    int32 buy_money;            /*购电金额*/
    uint32 buy_count;           /*购电次数*/
    uint8 customer_number[17];  /*户号，第一个字节为长度*/
    uint8 sid[1 + 4];           /*数据标识  ，第一个字节为长度，第一个字节为0表示SID不存在*/
    uint8 attach[1 + 32];       /*附加数据  ，第一个字节为长度，第一个字节为0表示附加数据不存在*/
    uint8 mac[1 + 16];          /*消息校验码，第一个字节为长度，第一个字节为0表示MAC不存在*/
    uint8 meter_number[1 + 8];  /*表号，第一个字节为长度*/
};

struct esam_infrared_auth_t
{
    uint8 rn1_cipher[1 + 64];   /*随机数1加密后的数据，第一个字节为长度，第一个字节为0表示RN不存在*/
    uint8 rn2[1 + 32];          /*随机数2，第一个字节为长度，第一个字节为0表示RN不存在*/
    uint8 meter_number[1 + 8];  /*表号，第一个字节为长度*/
    uint8 esam_sn[1 + 8];       /*ESAM序列号，第一个字节为长度*/
};

/** data-assess-result */
enum dl698_dar_t
{
    DAR_SUCCESS = 0,                        /**< 成功 （ 0）， */
    DAR_HARDWARE_INVALID = 1,               /**< 硬件失效 （ 1）， */
    DAR_TEMP_INVALID = 2,                   /**< 暂时失效 （ 2）， */
    DAR_RW_REJECT = 3,                      /**< 拒绝读写 （ 3）， */
    DAR_OBJECT_UNDEF = 4,                   /**< 对象未定义 （ 4）， */
    DAR_IC_ERROR = 5,                       /**< 对象接口类不符合 （ 5）， */
    DAR_OBJECT_NOT_EXIST = 6,               /**< 对象不存在 （ 6）， */
    DAR_TYPE_NOT_MATCH = 7,                 /**< 类型不匹配 （ 7）， */
    DAR_BUFFER_OVERFLOW = 8,                /**< 越界 （ 8）， */
    DAR_BLOCK_DATA_UNUSED = 9,              /**< 数据块不可用 （ 9）， */
    DAR_BLOCK_TRANSFER_CANCEL = 10,         /**< 分帧传输已取消 （ 10）， */
    DAR_NOT_IN_BLOCK_TRANSFER_STATE = 11,   /**< 不处于分帧传输状态 （ 11）， */
    DAR_BLOCK_WRITE_CANCEL = 12,            /**< 块写取消 （ 12）， */
    DAR_BLOCK_WRITE_STATE_NOT_EXIST = 13,   /**< 不存在块写状态 （ 13）， */
    DAR_BLOCK_NUM_INVALID = 14,             /**< 数据块序号无效 （ 14）， */
    DAR_UNAUTHORIZED = 15,                  /**< 密码错/未授权 （ 15）， */
    DAR_COMM_SPEED_CANNOT_CHANGE = 16,      /**< 通信速率不能更改 （ 16）， */
    DAR_TIME_ZONE_EXCEED = 17,              /**< 年时区数超 （ 17）， */
    DAR_DAY_INTERVAL_EXCEED = 18,           /**< 日时段数超 （ 18）， */
    DAR_TARIFF_NUM_EXCEED = 19,             /**< 费率数超 （ 19）， */
    DAR_SECURITY_AUTH_NOT_MATCH = 20,       /**< 安全认证不匹配       （20）， */
    DAR_REPEAT_TOPUP = 21,                  /**< 重复充值 */
    DAR_ESAM_CHECK_FAILED = 22,             /**< ESAM验证失败        （22）, */
    DAR_SECURITY_AUTH_FAILED = 23,          /**< 安全认证失败        （23）， */
    DAR_CUSTOMER_NUM_NOT_MATCH = 24,        /**< 客户编号不匹配      （24）， */
    DAR_TOPUP_TIMES_ERROR = 25,             /**< 充值次数错误        （25）， */
    DAR_TOPUP_EXCEED_MAX_VALUE = 26,        /**< 购电超囤积 */
    DAR_ADDRESS_ABNORMAL = 27,              /**< 地址异常 */
    DAR_SYMMETRIC_DESCRYPT_ERROR = 28,      /**< 对称解密错误        （28）， */
    DAR_ASYMMETRIC_DESCRYPT_ERROR = 29,     /**< 非对称解密错误      （29）， */
    DAR_SIGNATURE_ERROR = 30,               /**< 签名错误            （30）， */
    DAR_METER_SUSPEND = 31,                 /**< 电能表挂起 */
    DAR_TIME_TAG_INVALID = 32,              /**< 时间标签无效         (32)， */
    DAR_REQUEST_TIMEOUT = 33,               /**< 请求超时             （33），*/
    DAR_ESAM_P1P2_ERROR = 34,               /**< ESAM的P1P2不正确    （34），*/
    DAR_ESAM_LC_ERROR = 35,                 /**< ESAM的LC错误        （35），*/

    /*自扩*/
    DAR_EX_TAG_ERROR = 251,                 /**< tag错误（252），*/
    DAR_EX_OI_INVALID = 252,                /**< OI无效   （252），*/
    DAR_EX_STORAGE_DEPTH_ERROR = 253,       /**< 分钟冻结存储空间不足（253），*/
    DAR_EX_READ_WRITE_ERROR = 254,          /**< fs读写函数错        （254），*/
    /*自扩结束*/

    
    DAR_OTHERS_ERROR = 255,                 /**< 其它 （ 255） */
};

/** 下面是void *flag的数据接口 */
enum decimals_t
{
    UNIT_0   = 5,   /**< 0位小数，倍率=1 */
    UNIT_1   = 6,   /**< 1位小数，倍率=1 */
    UNIT_2   = 7,   /**< 2位小数，倍率=1 */
    UNIT_3   = 8,   /**< 3位小数，倍率=1 */
    UNIT_4   = 9,   /**< 4位小数，倍率=1 */

    UNIT_0_K = 2,   /**< 0位小数，倍率=1000 */
    UNIT_1_K = 3,   /**< 1位小数，倍率=1000 */
    UNIT_2_K = 4,   /**< 2位小数，倍率=1000 */
    UNIT_3_K = 5,   /**< 3位小数，倍率=1000 */
    UNIT_4_K = 6,   /**< 4位小数，倍率=1000 */

    UNIT_1_M = 0,   /**< 1位小数，倍率=1000000 */
    UNIT_2_M = 1,   /**< 2位小数，倍率=1000000 */
    UNIT_3_M = 2    /**< 3位小数，倍率=1000000 */
};

/********************the event code*********************/
enum event_code_t
{
    /* Standard Event Log */
    PowerDown                  = 0x0001,
    PowerUp                    = 0x0002,
    ClockAdjust1               = 0x0003,
    ClockAdjust2               = 0x0004,
    ClockInvalid               = 0x0005,
    BatteryOk                  = 0x0006,
    ReplaceBattery             = 0x0007,
    WatchdogError              = 0x0008,
    FirmwareReady              = 0x0009,
    FirmwareActivated          = 0x000A,
    Parameterchanged           = 0x000B,
    Securitykeychanged         = 0x000C,
    /* Fraud (Security) Event Log */
    MeterClear                 = 0x0011,/**< 电能表清零事件 */   
    MeterCoverOpened           = 0x0012,/**< 电能表开盖事件 */
    MeterCoverClosed           = 0x0013,/**< 电能表开盖事件结束 */
    TerminalCoverOpened        = 0x0014,/**< 电能表开端钮盒事件 */
    TerminalCoverClosed        = 0x0015,/**< 电能表开端钮盒事件结束 */
    SwitchOut                  = 0x0016,/**< 电能表跳闸事件 */   
    SwitchOn                   = 0x0017,/**< 电能表合闸事件 */ 
    TimingRecord               = 0x0018,/**< 电能表校时事件 */ 
    MeterReadingRecord         = 0x0019,/**< 电能表结算日编程事件 */
    WeekdayRecord              = 0x001A,/**< 电能表周休日编程事件 */
    DCDetected                 = 0x001F,/**< 电能表电源异常事件 */     
    DCRemoved                  = 0x0020,/**< 电能表电源异常事件结束 */     
    SeasontablePro             = 0x0021,/**< 电能表时区表编程事件 */     
    DaytablePro                = 0x0022,/**< 电能表时段表编程事件 */    
    DemandClear                = 0x0023,/**< 电能表需量清零事件 */    
    VoltageLostAll             = 0x0024,/**< 电能表全失压事件 */     
    VoltageLostAllEnd          = 0x0025,/**< 电能表全失压事件结束 */   
    Lpfallphases               = 0x0026,/**< 电能表掉电事件 */  
    LpfallphasesEnd            = 0x0027,/**< 电能表掉电事件结束 */  
    AssistPowerlost            = 0x0028,/**< 电能表辅助电源掉电事件 */    
    AssistPowerlostEnd         = 0x0029,/**< 电能表辅助电源掉电事件结束 */ 
    EventClear                 = 0x002A,/**< 电能表事件清零事件 */   
    MeterWritePara             = 0x002B,/**< 电能表编程事件 */    
    ActivePowerBytePro         = 0x002C,/**< 电能表有功组合方式编程事件 */  
    ReactivePowerBytePro       = 0x002D,/**< 电能表无功组合方式编程事件 */  
    TariffPricePro             = 0x002E,/**< 电能表费率参数表编程事件 */  
    StairPricePro              = 0x002F,/**< 电能表阶梯表编程事件 */     
    SecretkeyPro               = 0x0030,/**< 电能表密钥更新事件 */       
    PlugCardErr                = 0x0031,/**< 电能表异常插卡事件 */       
    RechargeRecord             = 0x0032,/**< 电能表购电记录 */           
    RefundRecord               = 0x0033,/**< 电能表退费记录 */           
    /* Voltage Quality Statistics Flag */
    VQualityAllL               = 0x0034, /**< 总电压超下限 */
    VQualityAllH               = 0x0035, /**< 总电压超上限 */
    VQualityAllRange           = 0x0036, /**< 总电压考核范围内 */
    VQualityL1L                = 0x0037, /**< A相电压超下限 */
    VQualityL1H                = 0x0038, /**< A相电压超上限 */
    VQualityL1Range            = 0x0039, /**< A相电压考核范围内 */
    VQualityL2L                = 0x003A, /**< B相电压超下限 */
    VQualityL2H                = 0x003B, /**< B相电压超上限 */
    VQualityL2Range            = 0x003C, /**< B相电压考核范围内 */
    VQualityL3L                = 0x003D, /**< C相电压超下限 */
    VQualityL3H                = 0x003E, /**< C相电压超上限 */
    VQualityL3Range            = 0x003F, /**< C相电压考核范围内 */

	HolidayPro                 = 0x0040, /**< 电能表节假日编程事件 */
    /* Power Quality Event Log */
    LostVoltageL1              = 0x0101,/**< A相电能表失压事件 */
    LostVoltageL2              = 0x0102,/**< B相电能表失压事件 */
    LostVoltageL3              = 0x0103,/**< C相电能表失压事件 */
    LostVoltageEndL1           = 0x0104,/**< A相电能表失压事件结束 */
    LostVoltageEndL2           = 0x0105,/**< B相电能表失压事件结束 */
    LostVoltageEndL3           = 0x0106,/**< C相电能表失压事件结束 */

    UnderVoltageL1             = 0x0107,/**< A相电能表欠压事件 */
    UnderVoltageL2             = 0x0108,/**< B相电能表欠压事件 */
    UnderVoltageL3             = 0x0109,/**< C相电能表欠压事件 */
    UnderVoltageEndL1          = 0x010A,/**< A相电能表欠压事件结束 */
    UnderVoltageEndL2          = 0x010B,/**< B相电能表欠压事件结束 */
    UnderVoltageEndL3          = 0x010C,/**< C相电能表欠压事件结束 */

    OverVoltageL1              = 0x010D,/**< A相电能表过压事件 */
    OverVoltageL2              = 0x010E,/**< B相电能表过压事件 */
    OverVoltageL3              = 0x010F,/**< C相电能表过压事件 */
    OverVoltageEndL1           = 0x0110,/**< A相电能表过压事件结束 */
    OverVoltageEndL2           = 0x0111,/**< B相电能表过压事件结束 */
    OverVoltageEndL3           = 0x0112,/**< C相电能表过压事件结束 */

    MissVoltageL1              = 0x0113,/**< A相电能表断相事件 */
    MissVoltageL2              = 0x0114,/**< B相电能表断相事件 */
    MissVoltageL3              = 0x0115,/**< C相电能表断相事件 */
    MissVoltageEndL1           = 0x0116,/**< A相电能表断相事件结束 */
    MissVoltageEndL2           = 0x0117,/**< B相电能表断相事件结束 */
    MissVoltageEndL3           = 0x0118,/**< C相电能表断相事件结束 */

    LostCurrentL1              = 0x0119,/**< A相电能表失流事件 */
    LostCurrentL2              = 0x011A,/**< B相电能表失流事件 */
    LostCurrentL3              = 0x011B,/**< C相电能表失流事件 */
    LostCurrentEndL1           = 0x011C,/**< A相电能表失流事件结束 */
    LostCurrentEndL2           = 0x011D,/**< B相电能表失流事件结束 */
    LostCurrentEndL3           = 0x011E,/**< C相电能表失流事件结束 */

    OverCurrentL1              = 0x011F,/**< A相电能表过流事件 */
    OverCurrentL2              = 0x0120,/**< B相电能表过流事件 */
    OverCurrentL3              = 0x0121,/**< C相电能表过流事件 */
    OverCurrentEndL1           = 0x0122,/**< A相电能表过流事件结束 */
    OverCurrentEndL2           = 0x0123,/**< B相电能表过流事件结束 */
    OverCurrentEndL3           = 0x0124,/**< C相电能表过流事件结束 */

    MissCurrentL1              = 0x0125,/**< A相电能表断流事件 */
    MissCurrentL2              = 0x0126,/**< B相电能表断流事件 */
    MissCurrentL3              = 0x0127,/**< C相电能表断流事件 */
    MissCurrentEndL1           = 0x0128,/**< A相电能表断流事件结束 */
    MissCurrentEndL2           = 0x0129,/**< B相电能表断流事件结束 */
    MissCurrentEndL3           = 0x012A,/**< C相电能表断流事件结束 */

    PowerReverseL1             = 0x012B,/**< A相电能表功率反向事件 */
    PowerReverseL2             = 0x012C,/**< B相电能表功率反向事件 */
    PowerReverseL3             = 0x012D,/**< C相电能表功率反向事件 */
    PowerReverseEndL1          = 0x012E,/**< A相电能表功率反向事件结束 */
    PowerReverseEndL2          = 0x012F,/**< B相电能表功率反向事件结束 */
    PowerReverseEndL3          = 0x0130,/**< C相电能表功率反向事件结束 */
    OverLoadL1                 = 0x0131,/**< A相电能表过载事件 */
    OverLoadL2                 = 0x0132,/**< B相电能表过载事件 */
    OverLoadL3                 = 0x0133,/**< C相电能表过载事件 */
    OverLoadEndL1              = 0x0134,/**< A相电能表过载事件结束 */
    OverLoadEndL2              = 0x0135,/**< B相电能表过载事件结束 */
    OverLoadEndL3              = 0x0136,/**< C相电能表过载事件结束 */
    LoadUnbalance              = 0x0137,/**< 电能表电流不平衡事件 */   
    LoadUnbalanceEnd           = 0x0138,/**< 电能表电流不平衡事件结束 */   
    LoadUnbalanceSeverit       = 0x0139,/**< 电能表电流严重不平衡事件 */   
    LoadUnbalanceSeveritEnd    = 0x013A,/**< 电能表电流严重不平衡事件结束 */   
    VoltageUnbalance           = 0x013B,/**< 电能表电压不平衡事件 */   
    VoltageUnbalanceEnd        = 0x013C,/**< 电能表电压不平衡事件结束 */   
    Powerdirectionchanged      = 0x013D,/**< 电能表潮流反向事件 */   
    BadPowerFactor             = 0x013E,/**< 电能表功率因数超下限事件 */  
    BadPowerFactorEnd          = 0x013F,/**< 电能表功率因数超下限事件结束 */ 
    PositiveDemandOver         = 0x0140,/**< 正向有功需量超限事件*/   
    PositiveDemandOverEnd      = 0x0141,/**< 正向有功需量超限事件结束*/  
    ReverseDemandOver          = 0x0142,/**< 反向有功需量超限事件*/  
    ReverseDemandOverEnd       = 0x0143,/**< 反向有功需量超限事件结束*/  
    Quadrant1DemandOver        = 0x0144,/**< 1象限无功需量超限事件*/  
    Quadrant1DemandOverEnd     = 0x0145,/**< 1象限无功需量超限事件结束*/  
    Quadrant2DemandOver        = 0x0146,/**< 2象限无功需量超限事件*/  
    Quadrant2DemandOverEnd     = 0x0147,/**< 2象限无功需量超限事件结束*/
    Quadrant3DemandOver        = 0x0148,/**< 3象限无功需量超限事件*/  
    Quadrant3DemandOverEnd     = 0x0149,/**< 3象限无功需量超限事件结束*/
    Quadrant4DemandOver        = 0x014A,/**< 4象限无功需量超限事件*/  
    Quadrant4DemandOverEnd     = 0x014B,/**< 4象限无功需量超限事件结束*/

    Voltagesequencereversal    = 0x014C,/**< 电能表电压逆相序事件 */  
    VoltagesequencereversalEnd = 0x014D,/**< 电能表电压逆相序事件结束 */  
    CurrentReversal            = 0x014E,/**< 电能表电流逆相序事件 */  
    CurrentReversalEnd         = 0x014F,/**< 电能表电流逆相序事件结束 */  

    MagneticDisturb            = 0x0150,/**< 电能表恒定磁场干扰事件 */  
    MagneticDisturbEnd         = 0x0151,/**< 电能表恒定磁场干扰事件结束 */  

    ReplayError                = 0x0152,/**< 电能表负荷开关误动作事件 */  
    ReplayErrorEnd             = 0x0153,/**< 电能表负荷开关误动作事件结束 */  

    EVENT_CODE_NUM
};

enum
{
    CTRL_DEVICE_RESET = 1,
    CTRL_DEVICE_OPEN,
    CTRL_DEVICE_SLEEP,
    CTRL_DEVICE_AWAKEN,
    CTRL_DEVICE_CLOSE,
    CTRL_DEVICE_SPECIAL,
    
    CTRL_FLS_SECTOR_ERASE,
    CTRL_FLS_BLOCK_ERASE,
     
    CTRL_EMU_ADJ_INIT,
    
    CTRL_EMU_ADJ_A_SELF,
    CTRL_EMU_ADJ_B_SELF,
    CTRL_EMU_ADJ_C_SELF,
    CTRL_EMU_ADJ_N_SELF,
    
    CTRL_EMU_ADJ_A_SET,
    CTRL_EMU_ADJ_B_SET,
    CTRL_EMU_ADJ_C_SET,
    CTRL_EMU_ADJ_N_SET,
    
    CTRL_EMU_DATA_SYNC,
    CTRL_EMU_PARA_CHECK,
    CTRL_EMU_CONFIG_DEFAULT,
    CTRL_EMU_COMPENSATE,
    
    CTRL_UART_BAUD_SET,
    CTRL_UART_BAUD_CHG,
    CTRL_UART_FIFO_DEL,

    CTRL_RELAY_CN,
    CTRL_RELAY_DIS_CN,

    CTRL_RTC_ADJ,
    CTRL_RTC_PLUSE_EN,
    CTRL_RTC_PLUSE_DIS,
    CTRL_RTC_MULT_PLUSE,
    CTRL_RTC_COMPENSATE,
    CTRL_RTC_TEMP_COMPENSATE,
    
    CTRL_RELAY_CONNECT,
    CTRL_RELAY_DISCONNECT,
    CTRL_EXT_RELAY_ACTIVE,
    CTRL_EXT_RELAY_NON_ACTIVE,
    
    CTRL_DATA_CLEAR,
    CTRL_TEST
};

enum meter_type_enum_t
{
    SGCC_General = 1,         /**< 国网智能表 */     
    SGCC_Remote_Ctrl,         /**< 国网远程费控表 */
    SGCC_Prepay_Card,         /**< 国网本地预付费电能表 */
    SGCC_CHARGE_EC_WAY,       /**< 国网电量型预付费表 */ 
    Meter_type_num
};

struct cpu_card_t
{
    uint8  Buffer[300];       /**< CPU卡通讯数据缓存 */
    uint8  ICRstBuffer[8];    /**< CPU卡分散因子 */
    uint8  ESAMRstBuffer[8];  /**< ESAM模块分散因子 */
    uint8  RandBuffer[8];     /**< 8字节随机数 */
    uint8  CommRandBuffer[4]; /**< 远程身份认证命令带下的随机数的高4字节 */
    uint8  CardType;          /**< 卡类型 */
    uint8  UserCardType;      /**< 用户卡类型 */
    uint8  ParaFlag;          /**< 参数更新标志位 */
    uint8  CardMeterNumber[6];/**< 用户卡表号 */
    uint8  CardUserNumber[6]; /**< 用户卡客户编号 */
    uint8  Paravality;        /**< 户头、表号、返写信息文件合法性*/ 
    uint8  BuyTimeVality;     /**< 购电次数合法性*/
    uint8  ErrHead[5];        /**< 异常插卡操作命令头 */
    uint8  handler_id[4];     /**< 操作者代码 */
    uint8  MeterState;        /**< 电能表开户状态 */
    uint32 BuyAmount;         /**< 本次购电金额 */
    uint32 BuyTimes;          /**< 本次购电次数 */
};

enum multi_io_t
{
    SECOUT,                   /**< 多功能口 秒脉冲输出 */
    DEMANDOUT,                /**< 多功能口 需量投切*/
    TARIFFOUT,                /**< 多功能口 时段投切 */
};

struct software_comparison_comm_para_t
{
    uint8   cpu_serial_number; /*CPU编号*/
    uint8   secret_key_index;  /*密钥索引*/
    uint32  divisor_addr;      /*比对因子起始地址*/
    uint32  data_addr;         /*比对数据起始地址*/
    uint16  data_len;          /*待加密数据长度*/
    uint8   *dest;             /*加密后数据*/
    uint16  dest_len;          /*返回密文长度*/
    uint8   mac[5];            /*返回MAC+长度*/
};

extern enum multi_io_t multifunctional_io_out_way;/*多功能口输出方式*/


#define	        REAlID_P_A              0x00
#define	        REAlID_Q_A              0x01
#define	        REAlID_S_A              0x02
#define	        REAlID_U_A              0x03
#define         REAlID_I_A              0x04
#define	        REAlID_PF_A             0x05
#define         REAlID_UI_ANGEL_A       0x06
#define	        REAlID_ANGEL_A          0xFF // 无效
#define         REAlID_I_T              0x07 
#define	        REAlID_PLS_P_A          0x08
#define         REAlID_PLS_Q_A          0x09



#define	        REAlID_P_B              0x10
#define	        REAlID_Q_B              0x11
#define	        REAlID_S_B              0x12
#define	        REAlID_U_B              0x13
#define         REAlID_I_B              0x14
#define	        REAlID_PF_B             0x15
#define         REAlID_UI_ANGEL_B       0x16
#define	        REAlID_ANGEL_B          0x17
#define	        REAlID_PLS_P_B          0x18
#define         REAlID_PLS_Q_B          0x19


#define	        REAlID_P_C              0x20
#define	        REAlID_Q_C              0x21
#define	        REAlID_S_C              0x22
#define	        REAlID_U_C              0x23
#define         REAlID_I_C              0x24
#define	        REAlID_PF_C             0x25
#define         REAlID_UI_ANGEL_C       0x26
#define	        REAlID_ANGEL_C          0x27
#define	        REAlID_PLS_P_C          0x28
#define         REAlID_PLS_Q_C          0x29

 
#define	        REAlID_P_T              0x30
#define	        REAlID_Q_T              0x31
#define	        REAlID_S_T              0x32
#define	        REAlID_FRE              0x33
#define         REAlID_I_N              0x34
#define	        REAlID_PF_T             0x35
#define         USER1                   0x36
#define	        USER2                   0x37
#define	        REAlID_PLS_P_T          0x38
#define         REAlID_PLS_Q_T          0x39


extern void hfp_run(void);
extern void hfp_init(void);


extern uint8 in_factory_mode(void);



#endif
/** @} */
