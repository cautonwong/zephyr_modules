#include "hfp_system.h"
#ifndef  _UserB_LIB_H
#define  _UserB_LIB_H

#ifdef   _UserB_LIB_GLOBALS
	#define  UserB_LIB_EXT
#else
	#define  UserB_LIB_EXT  extern 
#endif

//#include <stdio.h>
#include <string.h>
//#include <stdlib.h>

#include <rn831x_rn861x_mcu.h>
#include <Dat_Types.h>
#include <rn8xxx_v2_lib.h>
#include <UserB_SystemInit.h>
#include <UserB_Flash.h>
#include <UserB_AllInt.h>

struct boot_info_t
{
	uint32   sign;               // 刷新标志  0x5A6B7C8D 表示有刷新					    				  	
	uint32   destaddr;           // 目标烧写地址
	int32    length;             // 升级总长度
	uint32   srcaddr;            // 源地址
	uint16   codechecksum;       // 代码累加和校验
	uint16   upchecksum;         // 以上数据的累加和校验(包括保留字节)
};

struct image_transfer_state_t
{
	uint8 	transfer_enable;	/*	0x5a: 使能打开  0x00:使能关闭 						*/
	uint8	transfer_mode;		/*	0x01升级模式一为针对载波、RF等通信方式，imageBlockSize
								固定为64字节；0x02升级模式二为针对光电、RS485、GPRS等通
								信方式，imageBlockSize固定为192字节。*/
	uint8 	block_size;			/*	block长度					  						*/
	uint8 	last_blocksize;		/*	最后一帧长度										*/

	uint8 	file_type;			/*	文件类型											*/
	uint8 	encryption_type;	/*	加密类型											*/
	uint8 	check_type;			/*	校验类型											*/
	uint8 	version[20];		/*	版本信息，高字节在后								*/
	uint8 	code_crc[16];		/*	程序校验码，高字节在后								*/

	uint8 	enable_rst[4];		/*	是否开始升级标志，0x5aa5校验通过开始升级，0000不升级*/
	uint8   block_num[4];		/*	block总数											*/

	uint8   datatime[4];		/*	激活时间，转换为秒*/
	uint8	image_enable[4];	/*处于升级模式*/
};

enum image_transfer_step_t
{
	transfer_not_initiated,

	transfer_initiated,

	transfer_set_mode,

	image_identify,

	transfer_image_data,

	transfer_bit_map,

	verification_initiated,

	verification_successful,

	verification_failed,

	activation_initiated,

	activation_successful,

	activation_failed,
};

enum boot_process_step_t
{
    Boot_Exe_Init,
    Boot_Exe_Updateflag_Check_Successful,
    Boot_Exe_End,
};

extern void rn8318_init(void);
extern void sys_clock_sleep(void);
extern void sys_clock_normal(void);
extern uint8 power_on_check(void);
extern uint8 flash_init(const struct hfp_device_t CODE *device , uint8 power_mode);
extern void flash_power_ctrl(const struct hfp_device_t CODE *device , uint8 power_mode);
extern const struct hfp_device_t CODE ext_flash;
extern uint8 flash_read(uint32 addr, uint8 *buf, uint16 len, const struct hfp_device_t CODE *device);
extern uint8 flash_erase(uint32 address, const struct hfp_device_t CODE *device , uint8 erase_mode);
extern const struct hfp_device_t CODE eeprom;
extern uint8 write_i2c_mem(uint32 addr, uint8 *buf, uint16 len, const struct hfp_device_t CODE *device);
extern uint8 read_i2c_mem(uint32 addr, uint8 *buf, uint16 len, const struct hfp_device_t CODE *device);
extern void heap_init(void);

extern const struct gpio_pin_t CODE pin_relay_led;




#define APP_ADDR	        0x012B000
#define APP_ADDR_DIFF	    0x0773000
#define APP_MAX_SIZE        (0x80000-0x8000)

#define APP_ADDR_NEWFILE_CRC (APP_ADDR_DIFF + 1024)
#define APP_ADDR_DIFFFILE    (APP_ADDR_DIFF + 1024 + 64 + 2)

#define BOOT_INFO_ADDR     0x1DE7 // 地址
#define MCU_FLASH_PAGE     512
#define FLASH_WRITE_REPEAT       0x05
#define FLASH_FREQ         20
#define	IMAGE_ENABLE_FLAG			0x5A6B7C8D	/*处于升级模式*/
#define LOWPOWER_RST_TIMER          72000   /*1 hour*/
#define CODE_BUF_LEN      1024

extern uint8 code_buffer[CODE_BUF_LEN];
extern uint16 newfile_crc16;
#endif

