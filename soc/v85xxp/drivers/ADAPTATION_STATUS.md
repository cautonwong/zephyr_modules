# V85XXP Zephyr Driver Adaptation Status

## Implemented Zephyr-facing drivers

- serial: `uart_v85xxp.c` (compatible: `v85xxp,uart`)
- gpio: `gpio_v85xxp.c` (compatible: `v85xxp,gpio`)
- i2c: `i2c_v85xxp.c` (compatible: `v85xxp,i2c`)
- spi: `spi_v85xxp.c` (compatible: `v85xxp,spi`)
- pwm: `pwm_v85xxp.c` (compatible: `v85xxp,pwm`)
- watchdog: `wdt_v85xxp.c` (compatible: `v85xxp,wdt`)
- counter: `counter_v85xxp_tmr.c` (compatible: `v85xxp,tmr-counter`)
- adc: `adc_v85xxp.c` (compatible: `v85xxp,adc`)
- rtc: `rtc_v85xxp.c` (compatible: `v85xxp,rtc`)
- flash: `flash_v85xxp.c` (compatible: `v85xxp,flash-controller`)
- dma: `dma_v85xxp.c` (compatible: `v85xxp,dma`)

## Added devicetree bindings

- `dts/bindings/serial/v85xxp,uart.yaml`
- `dts/bindings/gpio/v85xxp,gpio.yaml`
- `dts/bindings/i2c/v85xxp,i2c.yaml`
- `dts/bindings/spi/v85xxp,spi.yaml`
- `dts/bindings/pwm/v85xxp,pwm.yaml`
- `dts/bindings/watchdog/v85xxp,wdt.yaml`
- `dts/bindings/counter/v85xxp,tmr-counter.yaml`
- `dts/bindings/adc/v85xxp,adc.yaml`
- `dts/bindings/rtc/v85xxp,rtc.yaml`
- `dts/bindings/flash/v85xxp,flash-controller.yaml`
- `dts/bindings/dma/v85xxp,dma.yaml`

## Added SoC dtsi nodes

`dts/arm/v85xxp/v85xxp.dtsi` now describes:

- UART0..UART5
- GPIOB..GPIOF
- I2C0
- SPI1..SPI3
- PWM0..PWM3
- TMR0..TMR3 (counter)
- WDT0
- ADC0
- RTC0
- FLASH controller
- DMA0

## HAL modules that still need dedicated Zephyr subsystem adapters

The following HAL blocks exist in `V85XXP_Lib_V2.5` but are not yet exposed as first-class Zephyr subsystem drivers in this module:

- iso7816 (`lib_iso7816.c`)
- crypt (`lib_crypt.c`)
- cmp (`lib_cmp.c`)
- lcd (`lib_lcd.c`)
- u32k (`lib_u32k.c`)
- pmu (`lib_pmu.c`)
- ana/clk/misc/version helpers (`lib_ana.c`, `lib_clk.c`, `lib_misc.c`, `lib_version.c`)

These require either Zephyr subsystem mapping (where available) or a dedicated driver model decision.
