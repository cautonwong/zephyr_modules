# V32F20X Drivers Implementation TODO

## Phase 1: Core Infrastructure (Highest Priority)
- [ ] **Interrupt Controller (INTC)**
    - Zephyr already supports NVIC for Cortex-M.
    - [ ] Ensure `NUM_IRQS` and priority levels are correctly configured in `Kconfig.defconfig`.
- [ ] **Clock Control Driver** (`drivers/clock_control/clock_v32f20x.c`)
    - [ ] Implement `clock_control_api`.
    - [ ] Support enabling/disabling peripheral clocks using `lib_clk.h`.
    - [ ] Add DTS clock-controller node.
- [ ] **Reset Controller Driver** (`drivers/reset/reset_v32f20x.c`)
    - [ ] Implement `reset_driver_api`.
    - [ ] Support peripheral reset using `SYSCFG0_PeriphReset` from `lib_syscfg.h`.
- [ ] **Pinctrl Driver** (`drivers/pinctrl/pinctrl_v32f20x.c`)
    - [ ] Implement `pinctrl_driver_api`.
    - [ ] Map DTS pin configurations to `GPIO_PinAFConfig` or equivalent.

## Phase 2: Fundamental I/O
- [x] **GPIO Driver** (Basic version done, needs refinement)
    - [ ] Integrate with Clock Control (enable GPIO clock in `init`).
    - [ ] Add interrupt support (`gpio_v32f20x_manage_callback`).
- [ ] **DMA Driver** (`drivers/dma/dma_v32f20x.c`)
    - [ ] Implement `dma_driver_api`.
    - [ ] Support CM0 `BDMA` and/or standard `DMA0/1`.

## Phase 3: Communication & Timers
- [x] **UART Driver** (Poll-mode done)
    - [ ] Add Interrupt-driven mode (using `lib_uart.h` IRQ helpers).
    - [ ] Integrate with Clock Control.
- [ ] **I2C Driver**
- [ ] **SPI Driver**
- [ ] **Timer/Counter (PWM)**

## Phase 4: Analog & Others
- [ ] **ADC Driver**
- [ ] **DAC Driver**
- [ ] **Watchdog Driver**
- [ ] **RTC Driver**
