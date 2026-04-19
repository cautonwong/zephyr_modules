/**
 * @ingroup    drivers_i2c_bus
 * @brief      i2c 总线驱动
 *
 * @{
 * @file
 *
 */
#include "hfp_system.h"
#include "rn831x_rn861x_mcu.h"

#define SDA_INPUT()     {iic_bus_resource->sda->in(iic_bus_resource->sda->direct , iic_bus_resource->sda->pin_bit);GPIO->PIEA &= ~BIT28;}
#define SDA_OUTPUT()    {iic_bus_resource->sda->out(iic_bus_resource->sda->direct , iic_bus_resource->sda->pin_bit);GPIO->PIEA |= BIT28;}
#define SCL_OUTPUT()    {iic_bus_resource->scl->out(iic_bus_resource->scl->direct , iic_bus_resource->scl->pin_bit);}
#define SCL_INPUT()     {iic_bus_resource->scl->in(iic_bus_resource->scl->direct , iic_bus_resource->scl->pin_bit);}

#ifdef  BIT_BAND_EN
#define SCL_GET_DIN()   ((*(iic_bus_resource->scl->port_in)))
#define SDA_GET_DIN()   ((*(iic_bus_resource->sda->port_in)))
#define SCL_DOUT_1()    {*(iic_bus_resource->scl->lat_out) = 1;}
#define SCL_DOUT_0()    {*(iic_bus_resource->scl->lat_out) = L;}
#define SDA_DOUT_1()    {*(iic_bus_resource->sda->lat_out) = 1;}
#define SDA_DOUT_0()    {*(iic_bus_resource->sda->lat_out) = 0;}
#define SCL_OUT_1()    {*(scl) = 1;}
#define SCL_OUT_0()    {*(scl) = L;}

#define SCL_OUT_1()    {*(scl) = 1;}
#define SCL_OUT_0()    {*(scl) = L;}

#define SDA_OUT_1()    {*(sda) = 1;}
#define SDA_OUT_0()    {*(sda) = 0;}
#define SDA_IN()       (*sda_in)
#else
#define SCL_GET_DIN()   ((*(iic_bus_resource->scl->port_in)) & iic_bus_resource->scl->pin_bit)
#define SDA_GET_DIN()   ((*(iic_bus_resource->sda->port_in)) & iic_bus_resource->sda->pin_bit)
#define SCL_DOUT_1()    {*(iic_bus_resource->scl->lat_out) |= iic_bus_resource->scl->pin_bit;}
#define SCL_DOUT_0()    {*(iic_bus_resource->scl->lat_out) &= ~iic_bus_resource->scl->pin_bit;}
#define SDA_DOUT_1()    {*(iic_bus_resource->sda->lat_out) |= iic_bus_resource->sda->pin_bit;}
#define SDA_DOUT_0()    {*(iic_bus_resource->sda->lat_out) &= ~iic_bus_resource->sda->pin_bit;}
#define SCL_OUT_1()     {*(scl) |= iic_bus_resource->scl->pin_bit;}
#define SCL_OUT_0()     {*(scl) &= ~iic_bus_resource->scl->pin_bit;}
#define SDA_OUT_1()     {*(sda) |= iic_bus_resource->sda->pin_bit;}
#define SDA_OUT_0()     {*(sda) &= ~iic_bus_resource->sda->pin_bit;}
#define SDA_IN()        (*sda_in & iic_bus_resource->sda->pin_bit)
#endif

#define IIC_DELAY()     {__NOP();}

uint8 iic_bus_init(const struct iic_bus_resource_t CODE *iic_bus_resource)
{
    
    SDA_OUTPUT();
    SDA_DOUT_1();
    IIC_DELAY();
    SCL_DOUT_1();
    SCL_OUTPUT();
    IIC_DELAY();
    
    /*for (i = 0; i < 8; i++)
    {
        IIC_DELAY();
        if (SCL_GET_DIN() != 0)
        {
            break;
        }
    }
    
    if (i >= 8)
    {
        SCL_OUTPUT();
        hardware_platform.mcu_delay_us(1);
        return 0;   //Slave busy failed
    }   */
    
    
    return true;
}



void iic_start(const struct iic_bus_resource_t CODE *iic_bus_resource)
{
    /* Insert another delay */
    uint32 L = 0;
  
    IIC_DELAY();
    SDA_DOUT_1();
    SDA_OUTPUT();
    IIC_DELAY();
    SCL_DOUT_1();
    SCL_OUTPUT();
    IIC_DELAY();
    SDA_DOUT_0();
    IIC_DELAY();
    SCL_DOUT_0();
    IIC_DELAY();
}



void iic_stop(const struct iic_bus_resource_t CODE *iic_bus_resource)
{
    SDA_DOUT_0();
    SDA_OUTPUT();
    IIC_DELAY();
    SCL_DOUT_1();
    SCL_OUTPUT();
    IIC_DELAY();
    SDA_DOUT_1();
    IIC_DELAY();
}


/********************************************************************************
* Function Name: HAL_I2C_Ack
* Description  : HAL I2C bus Ack
* Arguments    :
*                Enable: = true: Ack
*                        = false: NoAck
* Return       : none
********************************************************************************/
void iic_ack(uint8 Enable , const struct iic_bus_resource_t CODE *iic_bus_resource)
{
    uint32 L = 0;
  
    if (Enable == true)
    {
        SDA_DOUT_0();
    }
    else
    {
        SDA_DOUT_1();
    }
    
    SDA_OUTPUT();
    
#if 0
    hardware_platform.mcu_delay_us(5);
#endif
    IIC_DELAY();
    
    SCL_DOUT_1();
    SCL_OUTPUT();
    SCL_DOUT_0();
}



uint8 iic_send_byte(uint8 Data , const struct iic_bus_resource_t CODE *iic_bus_resource)
{
    uint16 i;

 
    register gpio_port_t *scl = iic_bus_resource->scl->lat_out;
    register uint32 byte = Data;
    register uint32 bit;
    register uint32 H = 1;
    register uint32 L = 0;
    
    gpio_port_t *sda = iic_bus_resource->sda->lat_out;
    
    *scl = 0;
    
    SDA_OUTPUT();
    
    IIC_DELAY();
    
    bit = byte>>7;

    *sda = bit;

    *scl = H;
    IIC_DELAY();
    bit = byte>>6;
    *scl = L;
    IIC_DELAY();
    *sda = bit;

    *scl = H;
    IIC_DELAY();
    bit = byte>>5;
    *scl = L;
    IIC_DELAY();
    *sda = bit;

    *scl = H;
    IIC_DELAY();
    bit = byte>>4;
    *scl = L;
    IIC_DELAY();
    *sda = bit;

    *scl = H;
    IIC_DELAY();
    bit = byte>>3;
    *scl = L;
    IIC_DELAY();
    *sda = bit;

    *scl = H;
    IIC_DELAY();
    bit = byte>>2;
    *scl = L;
    IIC_DELAY();
    *sda = bit;

    *scl = H;
    IIC_DELAY();
    bit = byte>>1;
    *scl = L;
    IIC_DELAY();
    *sda = bit;

    *scl = H;
    IIC_DELAY();
    bit = byte&0x01;
    *scl = L;
    IIC_DELAY();
    *sda = bit;

    *scl = 1;
    IIC_DELAY();
    *scl = L;
    IIC_DELAY();
    /* 等待应答 */
    SDA_INPUT();
    i = 0;
    *scl = 1;
    IIC_DELAY();
    
    while (SDA_GET_DIN() != 0)
    {
        if (++i >= 1200)
        {
            *scl = 0;
            return false;
        }
    }
    
    *scl = 0;
    return true;
}




uint8 iic_recive_byte(uint8 AckEnable , const struct iic_bus_resource_t CODE *iic_bus_resource)
{
    register uint32 val;
    register uint32 H = 1;
    register uint32 L = 0;
    register uint32 bit;
    register gpio_port_t *scl = iic_bus_resource->scl->lat_out;
    gpio_port_t *sda_in = iic_bus_resource->sda->port_in;
    

        *scl = 0;
        
        val = 0;
        SDA_INPUT();
        IIC_DELAY();
        SCL_OUTPUT();
        
        *scl = H;
        bit = (SDA_IN() << 7);
        *scl = L;
        val += bit;

        *scl = H;
        bit = (SDA_IN() << 6);
        *scl = L;
        val += bit;

        *scl = H;
        bit = (SDA_IN() << 5);
        *scl = L;
        val += bit;

        *scl = H;
        bit = (SDA_IN() << 4);
        *scl = L;
        val += bit;

        *scl = H;
        bit = (SDA_IN() << 3);
        *scl = L;
        val += bit;

        *scl = H;
        bit = (SDA_IN() << 2);
        *scl = L;
        val += bit;

        *scl = H;
        bit = (SDA_IN() << 1);
        *scl = L;
        val += bit;

        *scl = H;
        bit = SDA_IN();
        *scl = L;
        val += bit;
    
    
    iic_ack(AckEnable , iic_bus_resource);
    
    return val;
}

const struct iic_bus_ops_t CODE iic_bus_driver =
{
    iic_bus_init,
    iic_start,
    iic_stop,
    iic_send_byte,
    iic_recive_byte,
};
/** @} */