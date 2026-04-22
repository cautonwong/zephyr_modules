/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_uart

#include <lib_uart.h> /* Correctly included for Vango HAL */
#include <soc.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/drivers/reset.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/irq.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(v32f20x_uart, CONFIG_UART_LOG_LEVEL);

struct uart_v32f20x_config {
  UART_Type *regs;
  const struct device *clock_dev;
  clock_control_subsys_t clock_subsys;
  const struct reset_dt_spec reset;
  const struct pinctrl_dev_config *pincfg;
  uint32_t baud_rate;
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
  void (*irq_config_func)(const struct device *dev);
#endif
};

struct uart_v32f20x_data {
  struct uart_config uart_cfg;
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
  uart_irq_callback_user_data_t callback;
  void *cb_data;
#endif
};

static int uart_v32f20x_poll_in(const struct device *dev,
                                unsigned char *p_char) {
  const struct uart_v32f20x_config *config = dev->config;

  if (UART_GetFlag(config->regs, UART_FLAG_RX) == RESET) {
    return -1;
  }

  *p_char = UART_ReceiveData(config->regs);
  return 0;
}

static void uart_v32f20x_poll_out(const struct device *dev,
                                  unsigned char out_char) {
  const struct uart_v32f20x_config *config = dev->config;

  while (UART_GetFlag(config->regs, UART_FLAG_TXE) == RESET) {
    /* Wait for TX Empty */
  }

  UART_SendData(config->regs, out_char);
}

static int uart_v32f20x_err_check(const struct device *dev) {
  const struct uart_v32f20x_config *config = dev->config;
  uint32_t lsr = config->regs->LSR;
  int err = 0;

  if (lsr & UART_LSR_OE)
    err |= UART_ERROR_OVERRUN;
  if (lsr & UART_LSR_PE)
    err |= UART_ERROR_PARITY;
  /* Corrected: Use UART_LSR_FE for Framing Error. UART_LSR_BI is not defined in
   * HAL. */
  if (lsr & UART_LSR_FE)
    err |= UART_ERROR_FRAMING;
  /* Removed check for UART_LSR_BI as it's not available in HAL */

  return err;
}

static int uart_v32f20x_configure(const struct device *dev,
                                  const struct uart_config *cfg) {
  const struct uart_v32f20x_config *config = dev->config;
  struct uart_v32f20x_data *data = dev->data;
  UART_InitType init_struct;
  uint32_t clock_rate;

  if (clock_control_get_rate(config->clock_dev, config->clock_subsys,
                             &clock_rate) != 0) {
    LOG_ERR("Failed to get clock rate for %s", dev->name);
    return -EIO;
  }

  UART_StructInit(&init_struct);
  init_struct.Baudrate = cfg->baudrate;
  init_struct.SerialClock = clock_rate;

  switch (cfg->parity) {
  case UART_CFG_PARITY_NONE:
    init_struct.Parity = UART_PARITY_NONE;
    break;
  case UART_CFG_PARITY_ODD:
    init_struct.Parity = UART_PARITY_ODD;
    break;
  case UART_CFG_PARITY_EVEN:
    init_struct.Parity = UART_PARITY_EVEN;
    break;
  default:
    LOG_ERR("Unsupported parity");
    return -ENOTSUP;
  }

  switch (cfg->stop_bits) {
  case UART_CFG_STOP_BITS_1:
    init_struct.StopBit = UART_STOPBIT_1;
    break;
  case UART_CFG_STOP_BITS_2:
    init_struct.StopBit = UART_STOPBIT_2;
    break;
  case UART_CFG_STOP_BITS_1_5:
    init_struct.StopBit = UART_STOPBIT_1_5;
    break;
  default:
    LOG_ERR("Unsupported stop bits");
    return -ENOTSUP;
  }

  switch (cfg->data_bits) {
  case UART_CFG_DATA_BITS_5:
    init_struct.DataLength = UART_DATALEN_5B;
    break;
  case UART_CFG_DATA_BITS_6:
    init_struct.DataLength = UART_DATALEN_6B;
    break;
  case UART_CFG_DATA_BITS_7:
    init_struct.DataLength = UART_DATALEN_7B;
    break;
  case UART_CFG_DATA_BITS_8:
    init_struct.DataLength = UART_DATALEN_8B;
    break;
  default:
    LOG_ERR("Unsupported data bits");
    return -ENOTSUP;
  }

  UART_Init(config->regs, &init_struct);

  /* Professional Polish: Configure FIFO using direct register access */
  /* Enable FIFO, set RX trigger level to 1/8 full, reset FIFOs */
  config->regs->FCR |= UART_FCR_FIFOEN;
  config->regs->FCR &= ~UART_FCR_RT_MASK; /* Clear current RX trigger level */
  config->regs->FCR |= UART_FIFOLEVEL_8;  /* Set RX trigger level to 1/8 full */
  config->regs->FCR |=
      (UART_FCR_RXFIFORESET | UART_FCR_TXFIFORESET); /* Reset FIFOs */

  data->uart_cfg = *cfg;
  LOG_INF("%s: Baudrate set to %u", dev->name, cfg->baudrate);
  return 0;
}

static int uart_v32f20x_config_get(const struct device *dev,
                                   struct uart_config *cfg) {
  struct uart_v32f20x_data *data = dev->data;
  *cfg = data->uart_cfg;
  return 0;
}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static int uart_v32f20x_fifo_fill(const struct device *dev,
                                  const uint8_t *tx_data, int len) {
  const struct uart_v32f20x_config *config = dev->config;
  int num_tx = 0;

  while ((len - num_tx > 0) &&
         (UART_GetFlag(config->regs, UART_FLAG_TXE) != RESET)) {
    UART_SendData(config->regs, tx_data[num_tx++]);
  }
  return num_tx;
}

static int uart_v32f20x_fifo_read(const struct device *dev, uint8_t *rx_data,
                                  const int len) {
  const struct uart_v32f20x_config *config = dev->config;
  int num_rx = 0;

  while ((len - num_rx > 0) &&
         (UART_GetFlag(config->regs, UART_FLAG_RX) != RESET)) {
    rx_data[num_rx++] = UART_ReceiveData(config->regs);
  }
  return num_rx;
}

static void uart_v32f20x_irq_tx_enable(const struct device *dev) {
  const struct uart_v32f20x_config *config = dev->config;
  UART_INTConfig(config->regs, UART_INT_TXE, ENABLE);
}

static void uart_v32f20x_irq_tx_disable(const struct device *dev) {
  const struct uart_v32f20x_config *config = dev->config;
  UART_INTConfig(config->regs, UART_INT_TXE, DISABLE);
}

static int uart_v32f20x_irq_tx_ready(const struct device *dev) {
  const struct uart_v32f20x_config *config = dev->config;
  return (UART_GetFlag(config->regs, UART_FLAG_TXE) != RESET) &&
         (config->regs->IER & UART_INT_TXE);
}

static void uart_v32f20x_irq_rx_enable(const struct device *dev) {
  const struct uart_v32f20x_config *config = dev->config;
  UART_INTConfig(config->regs, UART_INT_RX | UART_INT_RXERR, ENABLE);
}

static void uart_v32f20x_irq_rx_disable(const struct device *dev) {
  const struct uart_v32f20x_config *config = dev->config;
  UART_INTConfig(config->regs, UART_INT_RX | UART_INT_RXERR, DISABLE);
}

static int uart_v32f20x_irq_tx_complete(const struct device *dev) {
  const struct uart_v32f20x_config *config = dev->config;
  return (config->regs->LSR & UART_LSR_TEMT) ? 1 : 0;
}

static int uart_v32f20x_irq_rx_ready(const struct device *dev) {
  const struct uart_v32f20x_config *config = dev->config;
  return (UART_GetFlag(config->regs, UART_FLAG_RX) != RESET) &&
         (config->regs->IER & UART_INT_RX);
}

static void uart_v32f20x_irq_err_enable(const struct device *dev) {
  const struct uart_v32f20x_config *config = dev->config;
  UART_INTConfig(config->regs, UART_INT_RXERR, ENABLE);
}

static void uart_v32f20x_irq_err_disable(const struct device *dev) {
  const struct uart_v32f20x_config *config = dev->config;
  UART_INTConfig(config->regs, UART_INT_RXERR, DISABLE);
}

static int uart_v32f20x_irq_is_pending(const struct device *dev) {
  const struct uart_v32f20x_config *config = dev->config;
  /* IIR bit 0 is 0 if an interrupt is pending */
  return !(config->regs->IIR & 0x1);
}

static int uart_v32f20x_irq_update(const struct device *dev) {
  ARG_UNUSED(dev);
  return 1;
}

static void uart_v32f20x_irq_callback_set(const struct device *dev,
                                          uart_irq_callback_user_data_t cb,
                                          void *cb_data) {
  struct uart_v32f20x_data *data = dev->data;
  data->callback = cb;
  data->cb_data = cb_data;
}

static void uart_v32f20x_isr(const struct device *dev) {
  struct uart_v32f20x_data *data = dev->data;

  if (data->callback) {
    data->callback(dev, data->cb_data);
  }
}
#endif /* CONFIG_UART_INTERRUPT_DRIVEN */

static int uart_v32f20x_init(const struct device *dev) {
  const struct uart_v32f20x_config *config = dev->config;
  int ret;

  /* Multi-core Barrier: CPU0 can only access Standalone UARTs (>= 0x41000000)
   */
#if defined(CONFIG_SOC_V32F20XXX_CM0_CORE) /* Check if CM0 core */
  if ((uint32_t)config->regs < 0x41000000) {
    LOG_ERR("CPU0 cannot access FLEXCOMM UART %p", config->regs);
    return -EACCES;
  }
#endif

  ret = pinctrl_apply_state(config->pincfg, PINCTRL_STATE_DEFAULT);
  if (ret < 0) {
    LOG_ERR("Failed to apply pinctrl for %s", dev->name);
    return ret;
  }

  if (config->reset.dev != NULL) {
    reset_line_toggle(config->reset.dev, config->reset.id);
  }

  ret = clock_control_on(config->clock_dev, config->clock_subsys);
  if (ret < 0) {
    LOG_ERR("Failed to enable clock for %s", dev->name);
    return ret;
  }

  struct uart_config uart_cfg = {
      .baudrate = config->baud_rate,
      .parity = UART_CFG_PARITY_NONE,
      .stop_bits = UART_CFG_STOP_BITS_1,
      .data_bits = UART_CFG_DATA_BITS_8,
      .flow_ctrl = UART_CFG_FLOW_CTRL_NONE,
  };

  ret = uart_v32f20x_configure(dev, &uart_cfg);
  if (ret < 0)
    return ret;

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
  config->irq_config_func(dev);
#endif

  return 0;
}

static const struct uart_driver_api uart_v32f20x_driver_api = {
    .poll_in = uart_v32f20x_poll_in,
    .poll_out = uart_v32f20x_poll_out,
    .err_check = uart_v32f20x_err_check,
    .configure = uart_v32f20x_configure,
    .config_get = uart_v32f20x_config_get,
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
    .fifo_fill = uart_v32f20x_fifo_fill,
    .fifo_read = uart_v32f20x_fifo_read,
    .irq_tx_enable = uart_v32f20x_irq_tx_enable,
    .irq_tx_disable = uart_v32f20x_irq_tx_disable,
    .irq_tx_ready = uart_v32f20x_irq_tx_ready,
    .irq_rx_enable = uart_v32f20x_irq_rx_enable,
    .irq_rx_disable = uart_v32f20x_irq_rx_disable,
    .irq_tx_complete = uart_v32f20x_irq_tx_complete,
    .irq_rx_ready = uart_v32f20x_irq_rx_ready,
    .irq_err_enable = uart_v32f20x_irq_err_enable,
    .irq_err_disable = uart_v32f20x_irq_err_disable,
    .irq_is_pending = uart_v32f20x_irq_is_pending,
    .irq_update = uart_v32f20x_irq_update,
    .irq_callback_set = uart_v32f20x_irq_callback_set,
#endif
};

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
#define UART_V32F20X_CONFIG_FUNC(n)                                            \
  static void uart_v32f20x_irq_config_##n(const struct device *dev) {          \
    IRQ_CONNECT(DT_INST_IRQN(n), DT_INST_IRQ(n, priority), uart_v32f20x_isr,   \
                DEVICE_DT_INST_GET(n), 0);                                     \
    irq_enable(DT_INST_IRQN(n));                                               \
  }
#define UART_V32F20X_IRQ_CFG_FUNC_INIT(n)                                      \
  .irq_config_func = uart_v32f20x_irq_config_##n,
#else
#define UART_V32F20X_CONFIG_FUNC(n)
#define UART_V32F20X_IRQ_CFG_FUNC_INIT(n)
#endif

#define UART_V32F20X_INIT(n)                                                   \
  PINCTRL_DT_INST_DEFINE(n);                                                   \
  UART_V32F20X_CONFIG_FUNC(n)                                                  \
  static const struct uart_v32f20x_config uart_v32f20x_config_##n = {          \
      .regs = (UART_Type *)DT_INST_REG_ADDR(n),                                \
      .clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)),                      \
      .clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, id),      \
      .reset = RESET_DT_SPEC_INST_GET_OR(n, {0}),                              \
      .pincfg = PINCTRL_DT_INST_DEV_CONFIG_GET(n),                             \
      .baud_rate = DT_INST_PROP(n, current_speed),                             \
      UART_V32F20X_IRQ_CFG_FUNC_INIT(n)};                                      \
  static struct uart_v32f20x_data uart_v32f20x_data_##n;                       \
  DEVICE_DT_INST_DEFINE(n, uart_v32f20x_init, NULL, &uart_v32f20x_data_##n,    \
                        &uart_v32f20x_config_##n, PRE_KERNEL_1,                \
                        CONFIG_SERIAL_INIT_PRIORITY,                           \
                        &uart_v32f20x_driver_api);

DT_INST_FOREACH_STATUS_OKAY(UART_V32F20X_INIT)
