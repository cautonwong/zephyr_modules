/**
 * @ingroup    drivers_spi_bus
 * @brief      spi ×ÜÏßÇý¶¯
 *
 * @{
 * @file
 *
 */
#include "hfp_system.h"
#include "rn831x_rn861x_mcu.h"

#ifdef  BIT_BAND_EN
#define  DO_SCK_HIGH()     {*pin_clk = H;}
#define  DO_SCK_LOW()      {*pin_clk = L;}

#define  DO_CLK_HIGH()     {*pin_clk = 1;}
#define  DO_CLK_LOW()      {*pin_clk = 0;}

#define  DO_MOSI_HIGH()    {*pin_mosi = 1;}
#define  DO_MOSI_LOW()     {*pin_mosi = 0;}
#define  DO_MISO_RD()      (*miso)
#else
#define  DO_SCK_HIGH()     {*pin_clk |= clk_bit;}
#define  DO_SCK_LOW()      {*pin_clk &= ~clk_bit;}

#define  DO_MOSI_HIGH()    {*pin_mosi |= mosi_bit;}
#define  DO_MOSI_LOW()     {*pin_mosi &= ~mosi_bit;}
#define  DO_MISO_RD()      (*miso & miso_bit)
#endif


#define SPI_DELAY()        {__NOP(); __NOP(); __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}



uint8 spi_bus_init(const struct spi_bus_resource_t CODE *spi_bus_resource)
{
    gpio_port_t *pin_mosi = spi_bus_resource->mosi->lat_out;
    gpio_port_t *pin_clk = spi_bus_resource->clk->lat_out;
    gpio_port_t *miso = spi_bus_resource->miso->port_in;
    register uint32 L = 0;    
    spi_bus_resource->miso->in(spi_bus_resource->miso->direct , spi_bus_resource->miso->pin_bit);
    spi_bus_resource->mosi->out(spi_bus_resource->mosi->direct , spi_bus_resource->mosi->pin_bit);
    DO_MOSI_HIGH();
    
    spi_bus_resource->clk->out(spi_bus_resource->clk->direct , spi_bus_resource->clk->pin_bit);
    DO_SCK_LOW();
    
    if (DO_MISO_RD())
    {
        return true;
    }
    
    return false;
}


uint8 spi_send_byte_mode3(uint8 byte , const struct spi_bus_resource_t CODE *spi_bus_resource)
{
    register gpio_port_t *pin_mosi = spi_bus_resource->mosi->lat_out;
    register gpio_port_t *pin_clk = spi_bus_resource->clk->lat_out;
    register uint32 H = 1;
    register uint32 L = 0;

    
    
    *pin_mosi = (byte>>7);
    DO_SCK_HIGH();
    DO_SCK_LOW();
    *pin_mosi = (byte>>6);
    DO_SCK_HIGH();
    DO_SCK_LOW();
    *pin_mosi = (byte>>5);
    DO_SCK_HIGH();
    DO_SCK_LOW();
    *pin_mosi = (byte>>4);
    DO_SCK_HIGH();
    DO_SCK_LOW();
    *pin_mosi = (byte>>3);
    DO_SCK_HIGH();
    DO_SCK_LOW();
    *pin_mosi = (byte>>2);
    DO_SCK_HIGH();
    DO_SCK_LOW();
    *pin_mosi = (byte>>1);
    DO_SCK_HIGH();
    DO_SCK_LOW();
    *pin_mosi = (byte&0x01);
    DO_SCK_HIGH();
    DO_SCK_LOW();
    
    return true;
}


uint8 spi_recive_byte_mode3(uint8 ctrl , const struct spi_bus_resource_t CODE *spi_bus_resource)
{
    register uint32 byte = 0;
    register gpio_port_t *pin_clk = spi_bus_resource->clk->lat_out;
    register gpio_port_t *miso = spi_bus_resource->miso->port_in;
    register uint32 H = 1;
    register uint32 L = 0;
    

    DO_SCK_HIGH();
    byte += (DO_MISO_RD() << 7);
    DO_SCK_LOW();
 
    DO_SCK_HIGH();
    byte += (DO_MISO_RD() << 6);
    DO_SCK_LOW();

    DO_SCK_HIGH();
    byte += (DO_MISO_RD() << 5);
    DO_SCK_LOW();
 
    DO_SCK_HIGH();
    byte += (DO_MISO_RD() << 4);
    DO_SCK_LOW();

    DO_SCK_HIGH();
    byte += (DO_MISO_RD() << 3);
    DO_SCK_LOW();
 
    DO_SCK_HIGH();
    byte += (DO_MISO_RD() << 2);
    DO_SCK_LOW();

    DO_SCK_HIGH();
    byte += (DO_MISO_RD() << 1);
    DO_SCK_LOW();
 
    DO_SCK_HIGH();
    byte += DO_MISO_RD();
    DO_SCK_LOW();
    
    return (uint8)byte;
}








void spi_start(const struct spi_bus_resource_t CODE *spi_bus_resource)
{
    gpio_port_t *pin_clk = spi_bus_resource->clk->lat_out;
    register uint32 L = 0;
    
    spi_bus_resource->mosi->out(spi_bus_resource->mosi->direct , spi_bus_resource->mosi->pin_bit);
    spi_bus_resource->clk->out(spi_bus_resource->clk->direct , spi_bus_resource->clk->pin_bit);
    
    DO_SCK_LOW();
}

void spi_stop(const struct spi_bus_resource_t CODE *spi_bus_resource)
{    
    spi_bus_resource->mosi->in(spi_bus_resource->mosi->direct , spi_bus_resource->mosi->pin_bit);
    spi_bus_resource->clk->in(spi_bus_resource->clk->direct , spi_bus_resource->clk->pin_bit);
}


const struct spi_bus_ops_t CODE spi_mode3_bus_driver =
{
    spi_bus_init,
    spi_start,
    spi_stop,
    spi_send_byte_mode3,
    spi_recive_byte_mode3,
};


/** @} */