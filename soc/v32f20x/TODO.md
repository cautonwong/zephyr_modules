# Zephyr Porting TODO for V32F20X

## 1. Analysis & Preparation
- [x] Create module structure (zephyr/module.yml, Kconfig, CMakeLists.txt).
- [x] Analyze `target.h` and SVD:
    - [x] Memory Layout (Flash, SRAM base/size).
    - [x] Peripheral Base Addresses (UART, GPIO, SPI, I2C, etc.).
    - [x] Interrupt Vector Table (IRQ numbers).
- [x] Determine Core Type:
    - **Decision:** Use **Cortex-M33** as the primary target for the SoC adaptation.

## 2. Device Tree (DTS)
- [x] Update `dts/v32f20x.dtsi`:
    - [x] Set `flash0` and `sram0` base addresses and sizes.
    - [x] Define `cpus` node (ARM Cortex-M33).
    - [x] Define `soc` node with all 20 UARTs, 14 SPIs, 15 I2Cs, etc.
    - [x] Configure GPIO interrupts (16 EXTI lines shared across ports).

## 3. SoC Source Code (`soc/arm/vango/v32f20x`)
- [ ] Implement `soc.c`:
    - [ ] `v32f20x_init()`: Call HAL `SystemInit()`.
    - [ ] Clock configuration logic.
- [x] Implement `soc.h`:
    - [x] Include HAL headers (`target.h`, `system_target_cm33.h`).
- [x] Create `Kconfig.soc`:
    - [x] Define `SOC_V32F20X_M33` and select `CPU_CORTEX_M33`.

## 4. Drivers
- [x] **GPIO Driver** (`drivers/gpio/gpio_v32f20x.c`):
    - [x] Implement `gpio_driver_api`.
    - [x] Support 16 EXTI interrupt lines.
- [x] **UART Driver** (`drivers/serial/uart_v32f20x.c`):
    - [x] Implement `uart_driver_api` (poll and interrupt-driven).
- [x] **Clock Control Driver**:
    - [x] Implement basic `clock_control_api`.
- [x] **Reset Controller Driver**:
    - [x] Implement `reset_driver_api`.
- [ ] **SPI/I2C/DMA Drivers**:
    - [ ] High priority for communication.

## 5. Board Support (`boards/vango/v32f20x_demo`)
- [ ] Update `v32f20x_demo.dts`:
    - [ ] Enable console and basic peripherals.

## 6. Testing
- [ ] Build `samples/hello_world`.
- [ ] Test GPIO interrupts (button) and UART IRQ.
