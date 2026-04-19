

#include "hfp_system.h"
#include "rn831x_rn861x_mcu.h"


#define  BITBAND_ADDR(X , Y)   ((X & 0xFC000000) + 0x02000000 + (Y<<2) + ((X<<5) & 0x03FFFFFF))



void gpio_dir_out(gpio_port_t *direct, gpio_port_t pin_bit)
{
    *direct = 0;
}

void gpio_dir_in(gpio_port_t *direct, gpio_port_t pin_bit)
{
    *direct = 1;
}

void gpio_out_high(gpio_port_t *lat_out, gpio_port_t pin_bit)
{
    *lat_out = 1;
}

void gpio_out_low(gpio_port_t *lat_out, gpio_port_t pin_bit)
{
    *lat_out = 0;
}

const struct gpio_pin_t CODE pin_scl = 
{
   (gpio_port_t*)BITBAND_ADDR(GPIO_PA,29),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PA,29),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PMA,29),
   gpio_dir_out,
   gpio_dir_in,
   gpio_out_high,
   gpio_out_low,
   0x01,
};

const struct gpio_pin_t CODE pin_sda = 
{
   (gpio_port_t*)BITBAND_ADDR(GPIO_PA,28),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PA,28),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PMA,28),
   gpio_dir_out,
   gpio_dir_in,
   gpio_out_high,
   gpio_out_low,
   0x01,
};


extern const struct iic_bus_ops_t CODE iic_bus_driver;

const struct eeprom_hal_cfg_t CODE eeprom_hal_cfg =
{
    0xFFFF,
    0x80,
    0x00,
};

const struct iic_bus_resource_t CODE iic_bus_resource =
{
  &pin_sda,
  &pin_scl,
};


const struct hfp_device_t CODE eeprom = 
{
    DEVICE_EEPROM,
    BUS_IIC,
    &iic_bus_driver,
    &iic_bus_resource,
    &eeprom_hal_cfg,
    __NULL,
};

/** flash SPI */

const struct gpio_pin_t CODE pin_clk_flash = 
{
   (gpio_port_t*)BITBAND_ADDR(GPIO_PB , 20),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PB , 20),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PMB , 20),
   gpio_dir_out,
   gpio_dir_in,
   gpio_out_high,
   gpio_out_low,
   0x01,

};
const struct gpio_pin_t CODE pin_miso_flash = 
{
   (gpio_port_t*)BITBAND_ADDR(GPIO_PB, 19),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PB, 19),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PMB , 19),
   gpio_dir_out,
   gpio_dir_in,
   gpio_out_high,
   gpio_out_low,
   0x01,
};
const struct gpio_pin_t CODE pin_mosi_flash=
{
   (gpio_port_t*)BITBAND_ADDR(GPIO_PB, 18),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PB, 18),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PMB , 18),
   gpio_dir_out,
   gpio_dir_in,
   gpio_out_high,
   gpio_out_low,
   0x01,
};
const struct gpio_pin_t CODE pin_cs_flash = 
{
   (gpio_port_t*)BITBAND_ADDR(GPIO_PB,21),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PB,21),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PMB,21),
   gpio_dir_out,
   gpio_dir_in,
   gpio_out_high,
   gpio_out_low,
   0x01,
};

const struct gpio_pin_t CODE pin_power_flash = 
{
   (gpio_port_t*)BITBAND_ADDR(GPIO_PB,17),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PB,17),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PMB,17),
   gpio_dir_out,
   gpio_dir_in,
   gpio_out_low,
   gpio_out_high,
   0x01,
};

const struct gpio_pin_t CODE pin_relay_led =
{
   (gpio_port_t*)BITBAND_ADDR(GPIO_PA,10),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PA,10),
   (gpio_port_t*)BITBAND_ADDR(GPIO_PMA,10),
   gpio_dir_out,
   gpio_dir_in,
   gpio_out_high,
   gpio_out_low,
   0x01,
};

const struct flash_hal_cfg_t CODE flash_hal_cfg =
{
    0x7FFFFF,
    0x100,
    0x1000,
    &pin_power_flash,
    &pin_cs_flash,
};

const struct spi_bus_resource_t CODE spi_bus_resource =
{
  &pin_clk_flash,
  &pin_miso_flash,
  &pin_mosi_flash,
};

extern const struct spi_bus_ops_t CODE spi_mode3_bus_driver;

const struct hfp_device_t CODE ext_flash = 
{
    DEVICE_FLASH,
    BUS_SPI,
    &spi_mode3_bus_driver,
    &spi_bus_resource,
    &flash_hal_cfg,
    __NULL,
};