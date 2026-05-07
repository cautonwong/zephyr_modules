# V85XXP Zephyr Driver Adaptation Status

## Implemented Zephyr-facing drivers

### Communication & IO
- serial: `uart_v85xxp.c` (compatible: `v85xxp,uart`)
- gpio: `gpio_v85xxp.c` (compatible: `v85xxp,gpio`)
- i2c: `i2c_v85xxp.c` (compatible: `v85xxp,i2c`)
- spi: `spi_v85xxp.c` (compatible: `v85xxp,spi`)
- iso7816: `iso7816_v85xxp.c` (compatible: `v85xxp,iso7816`)

### Analog & Timers
- pwm: `pwm_v85xxp.c` (compatible: `v85xxp,pwm`)
- watchdog: `wdt_v85xxp.c` (compatible: `v85xxp,wdt`)
- counter: `counter_v85xxp_tmr.c` (compatible: `v85xxp,tmr-counter`)
- adc: `adc_v85xxp.c` (compatible: `v85xxp,adc`)
- rtc: `rtc_v85xxp.c` (compatible: `v85xxp,rtc`)
- analog: `analog_v85xxp.c` (compatible: `v85xxp,analog`)

### System
- flash: `flash_v85xxp.c` (compatible: `v85xxp,flash-controller`)
- dma: `dma_v85xxp.c` (compatible: `v85xxp,dma`)
- clock_control: `clock_control_v85xxp.c` (compatible: `v85xxp,clock`)
- pinctrl: `pinctrl_v85xxp.c` (compatible: `v85xxp,pinctrl`)
- crypt: `crypt_v85xxp.c` (compatible: `v85xxp,crypt`)
- lcd: `lcd_v85xxp.c` (compatible: `v85xxp,lcd`) — segment LCD with custom API
- pmu: `pmu_v85xxp.c` (compatible: `v85xxp,pmu`) — power management with custom API

## Devicetree bindings

All drivers have corresponding YAML bindings under `dts/bindings/`.

## SoC DTS nodes

`dts/arm/v85xxp/v85xxp.dtsi` describes:
- UART0..UART5, GPIOA..GPIOF, I2C0, SPI1..SPI3
- PWM0..PWM3, TMR0..TMR3 (counter), WDT0, ADC0, RTC0
- FLASH controller, DMA0, CRYPT0, LCD0, ISO7816-0/1
- ANA0 (analog), PMU0 (power management)
- CLOCK, PINCTRL

All peripheral nodes default to `status = "disabled"`.

## HAL modules awaiting Zephyr subsystem adapters

- cmp (`lib_cmp.c`) — comparator; no standard Zephyr subsystem exists
- u32k (`lib_u32k.c`) — 32 kHz timer; could map to counter or custom API

## HAL build quality

- HAL CMakeLists.txt uses conditional `zephyr_library_sources_ifdef` per module
- Each driver Kconfig `select`s the corresponding `VANGO_V85XXP_HAL_XXX` option
- Core HAL files (clk, misc, version, CMSIS device) are always compiled
