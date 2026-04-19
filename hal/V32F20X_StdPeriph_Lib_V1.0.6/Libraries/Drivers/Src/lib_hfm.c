/**
  ******************************************************************************
  * @file    lib_hfm.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   HFM library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_hfm.h"

/* WAVER registers' reset value */
#define WAVER_CFG_RSTVAL               (0UL)
#define WAVER_MODE_RSTVAL              (0UL)

/* HFM registers' reset value */
#define HFM_CFG_RSTVAL                 (0UL)
#define HFM_EXCHADDR_RSTVAL            (0UL)
#define HFM_WAVEADDR_RSTVAL            (0UL)
#define HFM_DSPINSTRADDR_RSTVAL        (0UL)
#define HFM_DSPEXCHADDR_RSTVAL         (0UL)
#define HFM_CMD_RSTVAL                 (0UL)
#define HFM_EGYCONST0_RSTVAL           (0UL)
#define HFM_EGYCONST1_RSTVAL           (0UL)
#define HFM_EGYCONST2_RSTVAL           (0UL)
#define HFM_DSPCFG_RSTVAL              (0UL)
#define HFM_EGYCFG_RSTVAL              (0UL)
#define HFM_EGYPRCTH_RSTVAL            (0UL)
#define HFM_EGYPWRTH0_RSTVAL           (0UL)
#define HFM_EGYPWRTH1_RSTVAL           (0UL)
#define HFM_EGYCFDIVTH_RSTVAL          (0UL)
#define HFM_EGYCLKDIV_RSTVAL           (0UL)
#define HFM_PWROVTHH_RSTVAL            (0UL)
#define HFM_PWROVTHL_RSTVAL            (0UL)
#define HFM_DSPCALICFGADDR_RSTVAL      (0UL)

/* WAVER_CFG register masks */
#define WAVER_CFG_CLEAR_MASK           (0x000001FFUL)
/* WAVER_MODE register mask */
#define WAVER_MODE_CLEAR_MASK          (0x00000003UL)
/* WAVER PD mask */
#define WAVER_PD_EN                    (0x80000000UL)
#define WAVER_PD_EN_CLR                REG_BIT_NOT(WAVER_PD_EN)
/* HFM CMD mask */
#define HFM_CMD_T2F                    (0x00000001UL)
#define HFM_CMD_DSP                    (0x00000002UL)
/* HFM CFG mask */
#define HFM_MODE_MASK                 (0x03UL)
#define HFM_MODE_CLR                  REG_BIT_NOT(HFM_MODE_MASK)
#define HFM_HARMNUM_MASK              (0x1FUL)
#define HFM_HARMNUM_CLR               REG_BIT_NOT(HFM_HARMNUM_MASK)
/* HFM_EGYCFG0 register masks */
#define HFM_EGYCFG0_CLEAR_MASK        (0x000003F7UL)
#define HFM_EGYCFG0_OFFSETADDR        (10)
#define HFM_EGYCFG0_EGYMODE0_POS      (0)
#define HFM_EGYCFG0_EGYSOURCE_POS     (1)
#define HFM_EGYCFG0_EGYTYPESEL_POS    (4)
#define HFM_EGYCFG0_EGYPWRMODE_POS    (5)
#define HFM_EGYCFG0_CHANNEL_POS       (7)
/* HFM_DSPCFG register mask */
#define HFM_DSPCFG_CLEAR_MASK         (0x000008F0UL)
#define HFM_DSPCFG_CLEAR_CLR          REG_BIT_NOT(HFM_DSPCFG_CLEAR_MASK)
#define HFM_DSPCFG_CRP_EN             (1<<0)
#define HFM_DSPCFG_CRP_EN_CLR         REG_BIT_NOT(HFM_DSPCFG_CRP_EN)
#define HFM_DSPCFG_EGY0_EN            (1<<1)
#define HFM_DSPCFG_EGY0_EN_CLR        REG_BIT_NOT(HFM_DSPCFG_EGY0_EN)
#define HFM_DSPCFG_EGY1_EN            (1<<2)
#define HFM_DSPCFG_EGY1_EN_CLR        REG_BIT_NOT(HFM_DSPCFG_EGY1_EN)
#define HFM_DSPCFG_EGY2_EN            (1<<3)
#define HFM_DSPCFG_EGY2_EN_CLR        REG_BIT_NOT(HFM_DSPCFG_EGY2_EN)
#define HFM_DSPCFG_FAST_POS           (4)
#define HFM_DSPCFG_PULSE_POS          (6)
#define HFM_DSPCFG_OUTEN_MASK         (1<<8)
#define HFM_DSPCFG_OUTEN_CLR          REG_BIT_NOT(HFM_DSPCFG_OUTEN_MASK)
#define HFM_DSPCFG_OUTEN_POS          (8)
#define HFM_DSPCFG_POLARITY_MASK      (1<<11)
#define HFM_DSPCFG_POLARITY_CLR       REG_BIT_NOT(HFM_DSPCFG_POLARITY_MASK)
#define HFM_DSPCFG_POLARITY_POS       (11)
#define HFM_DSPCFG_SOURCE_MASK        (3<<14)
#define HFM_DSPCFG_SOURCE_CLR         REG_BIT_NOT(HFM_DSPCFG_SOURCE_MASK)
#define HFM_DSPCFG_SOURCE_POS         (14)
#define HFM_DSPCFG_PWRTHSEL_MASK      (1<<20)
#define HFM_DSPCFG_PWRTHSEL_CLR       REG_BIT_NOT(HFM_DSPCFG_PWRTHSEL_MASK)
#define HFM_DSPCFG_PWRTHSEL_POS       (20)
#define HFM_DSPCFG_PWRCRP_EN          (1<<23)
#define HFM_DSPCFG_PWRCRP_EN_CLR      REG_BIT_NOT(HFM_DSPCFG_PWRCRP_EN)

const unsigned int __attribute__ ((aligned (0x4000))) CMDBUF[]=
{
0x04F01,
0x05806,
0x06006,
0x14002,
0x05800,
0x06000,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80C,
0x10000,
0x05806,
0x06009,
0x14002,
0x05800,
0x06003,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80D,
0x0957A,
0x05E00,
0x0657A,
0x14000,
0x24000,
0x0C80C,
0x0C180,
0x09400,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D7A,
0x05E15,
0x0657A,
0x14002,
0x0C80C,
0x05F00,
0x0657A,
0x0C180,
0x0958D,
0x05809,
0x06009,
0x14002,
0x05803,
0x06003,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80C,
0x10000,
0x05800,
0x06009,
0x14002,
0x05806,
0x06003,
0x14000,
0x0C380,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80D,
0x0957A,
0x05E00,
0x0657A,
0x14000,
0x24000,
0x0C80C,
0x0C180,
0x09415,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D7A,
0x05E15,
0x0657A,
0x14002,
0x0C80C,
0x05F00,
0x0657A,
0x0C180,
0x0958E,
0x06F03,
0x20073,
0x05C00,
0x09B00,
0x05C15,
0x09B09,
0x05D8E,
0x09B12,
0x06F04,
0x2007B,
0x05C00,
0x09B03,
0x05C15,
0x09B0C,
0x05D8E,
0x09B15,
0x06F05,
0x20083,
0x05C00,
0x09B06,
0x05C15,
0x09B0F,
0x05D8E,
0x09B18,
0x04F00,
0x08D7B,
0x08D7C,
0x08D7D,
0x08D7E,
0x08D7F,
0x08D80,
0x04F01,
0x08F01,
0x05806,
0x06006,
0x14002,
0x05800,
0x06000,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80C,
0x10000,
0x05806,
0x06009,
0x14002,
0x05800,
0x06003,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80D,
0x0957A,
0x05E00,
0x0657A,
0x14000,
0x24000,
0x0C80C,
0x0C180,
0x09400,
0x05F00,
0x0657B,
0x0C180,
0x0957B,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D7A,
0x05E15,
0x0657A,
0x14002,
0x0C80C,
0x05F00,
0x0657A,
0x0C180,
0x0947E,
0x0658D,
0x2C000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x2C001,
0x08CFC,
0x08D7A,
0x05D7A,
0x0657A,
0x14002,
0x05D7D,
0x0657E,
0x0C180,
0x08D7D,
0x0957E,
0x05809,
0x06009,
0x14002,
0x05803,
0x06003,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80C,
0x10000,
0x05800,
0x06009,
0x14002,
0x05806,
0x06003,
0x14000,
0x0C380,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80D,
0x0957A,
0x05E00,
0x0657A,
0x14000,
0x24000,
0x0C80C,
0x0C180,
0x09415,
0x05F00,
0x0657C,
0x0C180,
0x0957C,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D7A,
0x05E15,
0x0657A,
0x14002,
0x0C80C,
0x05F00,
0x0657A,
0x0C180,
0x09493,
0x0658E,
0x2C000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x2C001,
0x08D11,
0x08D7A,
0x05D7A,
0x0657A,
0x14002,
0x05D7F,
0x06580,
0x0C180,
0x08D7F,
0x09580,
0x06F03,
0x20158,
0x05C00,
0x09B00,
0x05C15,
0x09B09,
0x05C93,
0x09B12,
0x06F04,
0x20160,
0x05C00,
0x09B03,
0x05C15,
0x09B0C,
0x05C93,
0x09B15,
0x06F05,
0x20168,
0x05C00,
0x09B06,
0x05C15,
0x09B0F,
0x05C93,
0x09B18,
0x06F02,
0x2016B,
0x1C08B,
0x04D7D,
0x0557E,
0x0C80C,
0x10000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D81,
0x04D7F,
0x05580,
0x0C80C,
0x10000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D82,
0x04D7B,
0x08D87,
0x04D7C,
0x08D88,
0x08F01,
0x06F03,
0x201C2,
0x05D87,
0x09B00,
0x05D88,
0x09B09,
0x06F04,
0x201C6,
0x05D87,
0x09B03,
0x06F05,
0x201CA,
0x05D87,
0x09B06,
0x06F06,
0x20562,
0x04F01,
0x05807,
0x06007,
0x14002,
0x05801,
0x06001,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80C,
0x10000,
0x05807,
0x0600A,
0x14002,
0x05801,
0x06004,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80D,
0x0957A,
0x05E00,
0x0657A,
0x14000,
0x24000,
0x0C80C,
0x0C180,
0x0942A,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D7A,
0x05E15,
0x0657A,
0x14002,
0x0C80C,
0x05F00,
0x0657A,
0x0C180,
0x0958F,
0x0580A,
0x0600A,
0x14002,
0x05804,
0x06004,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80C,
0x10000,
0x05801,
0x0600A,
0x14002,
0x05807,
0x06004,
0x14000,
0x0C380,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80D,
0x0957A,
0x05E00,
0x0657A,
0x14000,
0x24000,
0x0C80C,
0x0C180,
0x0943F,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D7A,
0x05E15,
0x0657A,
0x14002,
0x0C80C,
0x05F00,
0x0657A,
0x0C180,
0x09590,
0x06F03,
0x2023F,
0x05C2A,
0x09B01,
0x05C3F,
0x09B0A,
0x05D90,
0x09B13,
0x06F04,
0x20247,
0x05C2A,
0x09B04,
0x05C3F,
0x09B0D,
0x05D90,
0x09B16,
0x06F05,
0x2024F,
0x05C2A,
0x09B07,
0x05C3F,
0x09B10,
0x05D90,
0x09B19,
0x04F00,
0x08D7B,
0x08D7C,
0x08D7D,
0x08D7E,
0x08D7F,
0x08D80,
0x04F01,
0x08F01,
0x05807,
0x06007,
0x14002,
0x05801,
0x06001,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80C,
0x10000,
0x05807,
0x0600A,
0x14002,
0x05801,
0x06004,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80D,
0x0957A,
0x05E00,
0x0657A,
0x14000,
0x24000,
0x0C80C,
0x0C180,
0x0942A,
0x05F00,
0x0657B,
0x0C180,
0x0957B,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D7A,
0x05E15,
0x0657A,
0x14002,
0x0C80C,
0x05F00,
0x0657A,
0x0C180,
0x094A8,
0x0658F,
0x2C000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x2C001,
0x08D26,
0x08D7A,
0x05D7A,
0x0657A,
0x14002,
0x05D7D,
0x0657E,
0x0C180,
0x08D7D,
0x0957E,
0x0580A,
0x0600A,
0x14002,
0x05804,
0x06004,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80C,
0x10000,
0x05801,
0x0600A,
0x14002,
0x05807,
0x06004,
0x14000,
0x0C380,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80D,
0x0957A,
0x05E00,
0x0657A,
0x14000,
0x24000,
0x0C80C,
0x0C180,
0x0943F,
0x05F00,
0x0657C,
0x0C180,
0x0957C,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D7A,
0x05E15,
0x0657A,
0x14002,
0x0C80C,
0x05F00,
0x0657A,
0x0C180,
0x094BD,
0x06590,
0x2C000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x2C001,
0x08D3B,
0x08D7A,
0x05D7A,
0x0657A,
0x14002,
0x05D7F,
0x06580,
0x0C180,
0x08D7F,
0x09580,
0x06F03,
0x20324,
0x05C2A,
0x09B01,
0x05C3F,
0x09B0A,
0x05CBD,
0x09B13,
0x06F04,
0x2032C,
0x05C2A,
0x09B04,
0x05C3F,
0x09B0D,
0x05CBD,
0x09B16,
0x06F05,
0x20334,
0x05C2A,
0x09B07,
0x05C3F,
0x09B10,
0x05CBD,
0x09B19,
0x06F02,
0x20337,
0x1C257,
0x04D7D,
0x0557E,
0x0C80C,
0x10000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D83,
0x04D7F,
0x05580,
0x0C80C,
0x10000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D84,
0x04D7B,
0x08D89,
0x04D7C,
0x08D8A,
0x08F01,
0x06F03,
0x2038E,
0x05D89,
0x09B01,
0x05D8A,
0x09B0A,
0x06F04,
0x20392,
0x05D89,
0x09B04,
0x06F05,
0x20396,
0x05D89,
0x09B07,
0x06F07,
0x20562,
0x04F01,
0x05808,
0x06008,
0x14002,
0x05802,
0x06002,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80C,
0x10000,
0x05808,
0x0600B,
0x14002,
0x05802,
0x06005,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80D,
0x0957A,
0x05E00,
0x0657A,
0x14000,
0x24000,
0x0C80C,
0x0C180,
0x09454,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D7A,
0x05E15,
0x0657A,
0x14002,
0x0C80C,
0x05F00,
0x0657A,
0x0C180,
0x09591,
0x0580B,
0x0600B,
0x14002,
0x05805,
0x06005,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80C,
0x10000,
0x05802,
0x0600B,
0x14002,
0x05808,
0x06005,
0x14000,
0x0C380,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80D,
0x0957A,
0x05E00,
0x0657A,
0x14000,
0x24000,
0x0C80C,
0x0C180,
0x09469,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D7A,
0x05E15,
0x0657A,
0x14002,
0x0C80C,
0x05F00,
0x0657A,
0x0C180,
0x09592,
0x06F03,
0x2040B,
0x05C54,
0x09B02,
0x05C69,
0x09B0B,
0x05D92,
0x09B14,
0x06F04,
0x20413,
0x05C54,
0x09B05,
0x05C69,
0x09B0E,
0x05D92,
0x09B17,
0x06F05,
0x2041B,
0x05C54,
0x09B08,
0x05C69,
0x09B11,
0x05D92,
0x09B1A,
0x04F00,
0x08D7B,
0x08D7C,
0x08D7D,
0x08D7E,
0x08D7F,
0x08D80,
0x04F01,
0x08F01,
0x05808,
0x06008,
0x14002,
0x05802,
0x06002,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80C,
0x10000,
0x05808,
0x0600B,
0x14002,
0x05802,
0x06005,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80D,
0x0957A,
0x05E00,
0x0657A,
0x14000,
0x24000,
0x0C80C,
0x0C180,
0x09454,
0x05F00,
0x0657B,
0x0C180,
0x0957B,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D7A,
0x05E15,
0x0657A,
0x14002,
0x0C80C,
0x05F00,
0x0657A,
0x0C180,
0x094D2,
0x06591,
0x2C000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x2C001,
0x08D50,
0x08D7A,
0x05D7A,
0x0657A,
0x14002,
0x05D7D,
0x0657E,
0x0C180,
0x08D7D,
0x0957E,
0x0580B,
0x0600B,
0x14002,
0x05805,
0x06005,
0x14000,
0x0C180,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80C,
0x10000,
0x05802,
0x0600B,
0x14002,
0x05808,
0x06005,
0x14000,
0x0C380,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80F,
0x0C80D,
0x0957A,
0x05E00,
0x0657A,
0x14000,
0x24000,
0x0C80C,
0x0C180,
0x09469,
0x05F00,
0x0657C,
0x0C180,
0x0957C,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D7A,
0x05E15,
0x0657A,
0x14002,
0x0C80C,
0x05F00,
0x0657A,
0x0C180,
0x094E7,
0x06592,
0x2C000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x2C001,
0x08D65,
0x08D7A,
0x05D7A,
0x0657A,
0x14002,
0x05D7F,
0x06580,
0x0C180,
0x08D7F,
0x09580,
0x06F03,
0x204F0,
0x05C54,
0x09B02,
0x05C69,
0x09B0B,
0x05CE7,
0x09B14,
0x06F04,
0x204F8,
0x05C54,
0x09B05,
0x05C69,
0x09B0E,
0x05CE7,
0x09B17,
0x06F05,
0x20500,
0x05C54,
0x09B08,
0x05C69,
0x09B11,
0x05CE7,
0x09B1A,
0x06F02,
0x20503,
0x1C423,
0x04D7D,
0x0557E,
0x0C80C,
0x10000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D85,
0x04D7F,
0x05580,
0x0C80C,
0x10000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x00000,
0x10001,
0x08D86,
0x04D7B,
0x08D8B,
0x04D7C,
0x08D8C,
0x08F01,
0x06F03,
0x2055A,
0x05D8B,
0x09B02,
0x05D8C,
0x09B0B,
0x06F04,
0x2055E,
0x05D8B,
0x09B05,
0x06F05,
0x20562,
0x05D8B,
0x09B08,
0x1CFFF,
0x00000,
};

/**
  * @brief  Initializes the WAVER0 peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void WAVER_DeInit(void)
{
  WAVER0->CFG = WAVER_CFG_RSTVAL;
  WAVER0->MODE = WAVER_MODE_RSTVAL;
}

/**
  * @brief  Fills each WAVER_InitStruct member with its default value.
  * @param  WAVER_InitStruct: pointer to an WAVER_InitType structure which will be initialized.
  * @retval None
  */
void WAVER_StructInit(WAVER_InitType *WAVER_InitStruct)
{ 
  WAVER_InitStruct->Mode = WAVER_MODE_U_IA;
  WAVER_InitStruct->SampleLength = WAVER_SAMPLELEN_256;
  WAVER_InitStruct->CICRateSEL = WAVER_CIC_DISABLE;
  WAVER_InitStruct->COMPSEL = WAVER_COMP_DISABLE;
  WAVER_InitStruct->UploadSEL = WAVER_UPLOAD_DISABLE;
  WAVER_InitStruct->UploadEndianSEL = WAVER_UPLOAD_LITTLE_ENDIAN;
  WAVER_InitStruct->BackupSEL = WAVER_BACKUP_DISABLE;
}

/**
  * @brief  WAVER initialization.
  * @param  WAVER_InitStruct:WAVER configuration.
  *          Mode:
  *               WAVER_MODE_U_IA
  *               WAVER_MODE_U_IA_IB
  *               WAVER_MODE_3U_IA_IB_IC
  *          SampleLength:
  *               WAVER_SAMPLELEN_256
  *               WAVER_SAMPLELEN_128
  *          CICRateSEL:
  *               WAVER_CIC_DISABLE
  *               WAVER_CIC_128
  *               WAVER_CIC_64
  *          COMPSEL:
  *               WAVER_COMP_DISABLE
  *               WAVER_COMP_ENABLE
  *          UploadSEL:
  *               WAVER_UPLOAD_DISABLE
  *               WAVER_UPLOAD_SPI
  *               WAVER_UPLOAD_M33
  *               WAVER_UPLOAD_SPI_M33
  *          UploadEndianSEL:
  *               WAVER_UPLOAD_LITTLE_ENDIAN
  *               WAVER_UPLOAD_BIG_ENDIAN
  *          BackupSEL:
  *               WAVER_BACKUP_DISABLE
  *               WAVER_BACKUP_ENABLE
  * @retval None
  */
void WAVER_Init(WAVER_InitType *WAVER_InitStruct)
{
  uint32_t tmpreg;

  /* Check parameters */
  assert_parameters(IS_WAVER_MODE(WAVER_InitStruct->Mode));
  assert_parameters(IS_WAVER_SAMPLELEN(WAVER_InitStruct->SampleLength));
  assert_parameters(IS_WAVER_CIC(WAVER_InitStruct->CICRateSEL));
  assert_parameters(IS_WAVER_COMP(WAVER_InitStruct->COMPSEL));
  assert_parameters(IS_WAVER_UPLOAD(WAVER_InitStruct->UploadSEL));
  assert_parameters(IS_WAVER_UPLOADENDIAN(WAVER_InitStruct->UploadEndianSEL));
  assert_parameters(IS_WAVER_BACKUP(WAVER_InitStruct->BackupSEL));
  
  /*---------------------------- WAVER CFG Configuration ------------------------*/
  tmpreg = WAVER0->CFG;
  tmpreg &= ~WAVER_CFG_CLEAR_MASK;
  tmpreg |= (WAVER_InitStruct->SampleLength          |
             WAVER_InitStruct->CICRateSEL      |
             WAVER_InitStruct->COMPSEL         |
             WAVER_InitStruct->UploadSEL       | 
             WAVER_InitStruct->UploadEndianSEL |
             WAVER_InitStruct->BackupSEL);
  WAVER0->CFG = tmpreg;
  
  /*---------------------------- WAVER MODE Configuration ------------------------*/
  tmpreg = WAVER0->MODE;
  tmpreg &= ~WAVER_MODE_CLEAR_MASK;
  tmpreg |= (WAVER_InitStruct->Mode);
  WAVER0->MODE |= tmpreg;
}

/**
  * @brief  Enables or disables WAVER function.
  * @param  NewState: new state of the specified WAVER function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WAVER_Cmd(uint32_t NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    WAVER0->CFG |= WAVER_PD_EN;
  }
  else
  {
    WAVER0->CFG &= WAVER_PD_EN_CLR;
  }
}

/**
  * @brief  Initializes the HFM peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void HFM_DeInit(void)
{
  HFM->CFG = HFM_CFG_RSTVAL;
  HFM->EXCH_BADDR = HFM_EXCHADDR_RSTVAL;
  HFM->WAVE_BADDR = HFM_WAVEADDR_RSTVAL;
  HFM->DSPINSTR_BADDR = HFM_DSPINSTRADDR_RSTVAL;
  HFM->DSPEXCH_BADDR = HFM_DSPEXCHADDR_RSTVAL;
  HFM->EGY_CONST0 = HFM_EGYCONST0_RSTVAL;
  HFM->EGY_CONST1 = HFM_EGYCONST1_RSTVAL;
  HFM->EGY_CONST2 = HFM_EGYCONST2_RSTVAL;
  HFM->DSP_CFG = HFM_DSPCFG_RSTVAL;
  HFM->EGY_CFG = HFM_EGYCFG_RSTVAL;
  HFM->EGY_PROCTH = HFM_EGYPRCTH_RSTVAL;
  HFM->EGY_PWRTH0 = HFM_EGYPWRTH0_RSTVAL;
  HFM->EGY_PWRTH1 = HFM_EGYPWRTH1_RSTVAL;
  HFM->EGY_CFDIVTH = HFM_EGYCFDIVTH_RSTVAL;
  HFM->EGY_CLKDIV = HFM_EGYCLKDIV_RSTVAL;
  HFM->PWROVTHH = HFM_PWROVTHH_RSTVAL;
  HFM->PWROVTHL = HFM_PWROVTHL_RSTVAL;
  HFM->DSPCALICFGADDR = HFM_DSPCALICFGADDR_RSTVAL;
}

/**
  * @brief  Fills each HFM_InitType member with its default value.
  * @param  HFM_InitStruct: pointer to an HFM_InitType structure which will be initialized.
  * @retval None
  */
void HFM_StructInit(HFM_InitType *HFM_InitStruct)
{
  HFM_InitStruct->Mode = HFM_MODE_U_IA;
  HFM_InitStruct->ExchAddr = 0;
  HFM_InitStruct->WaveBaseAddr = 0;
  HFM_InitStruct->DSPInstrAddr = 0;
  HFM_InitStruct->DSPExchAddr = 0;
}

/**
  * @brief  HFM initialization.
  * @param  HFM_InitStruct:HFM configuration.
  *          Mode:
  *               HFM_MODE_U_IA
  *               HFM_MODE_U_IA_IB
  *               HFM_MODE_3U_IA_IB_IC
  *          ExchAddr: FFT calculation exchange buffer base address.
  *          WaveBaseAddr: The source waveform & FFT Result buffer base address.
  *          DSPInstrAddr: The DSP instruction buffer base address.
  *          DSPExchAddr:The DSP power value and exchange buffer base address.
  * @retval None
  */
void HFM_Init(HFM_InitType *HFM_InitStruct)
{
  uint32_t tmpreg;

  /* Check the parameters */
  assert_parameters(IS_HFM_MODE(HFM_InitStruct->Mode));

  tmpreg = HFM->CFG;
  tmpreg &= HFM_MODE_CLR;
  tmpreg |= HFM_InitStruct->Mode;
  HFM->CFG = tmpreg;
  HFM->EXCH_BADDR = HFM_InitStruct->ExchAddr;
  HFM->WAVE_BADDR = HFM_InitStruct->WaveBaseAddr;
  HFM->DSPINSTR_BADDR = HFM_InitStruct->DSPInstrAddr;
  HFM->DSPEXCH_BADDR = HFM_InitStruct->DSPExchAddr;
}

/**
  * @brief  Enables or disables HFM specified interrupt.
  * @param  INTMask: specifies the HFM interrupt source to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *                 HFM_INT_T2FDONE
  *                 HFM_INT_DSPDONE
  *                 HFM_INT_EGY0SPILL
  *                 HFM_INT_EGY1SPILL
  *                 HFM_INT_EGY2SPILL
  * @param  NewState: new state of the specified HFM interrupt function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void HFM_INTConfig(uint32_t INTMask, uint32_t NewState)
{
  /* Check the parameters */
  assert_parameters(IS_HFM_INTC(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    HFM->INTEN |= INTMask;
  }
  else
  {
    HFM->INTEN &= ~INTMask;
  }
}

/**
  * @brief  Gets HFM interrupt status.
  * @param  INTMask: specifies the HFM interrupt source to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *                 HFM_INT_T2FDONE
  *                 HFM_INT_DSPDONE
  *                 HFM_INT_EGY0SPILL
  *                 HFM_INT_EGY1SPILL
  *                 HFM_INT_EGY2SPILL
  * @retval The new state of HFM specified interrupt status (SET or RESET).
  */
ITStatus HFM_GetINTStatus(uint32_t INTMask)
{
  /* Check the parameters */
  assert_parameters(IS_HFM_INTR(INTMask));
  
  if (HFM->INTSTS & INTMask)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clears HFM specified interrupt status.
  * @param  INTMask: specifies the HFM interrupt source to clear.
  *         This parameter can be any combination of the following values:
  *                 HFM_INT_T2FDONE
  *                 HFM_INT_DSPDONE
  *                 HFM_INT_EGY0SPILL
  *                 HFM_INT_EGY1SPILL
  *                 HFM_INT_EGY2SPILL
  * @retval None
  */
void HFM_ClearINTStatus(uint32_t INTMask)
{
  /* Check the parameters */
  assert_parameters(IS_HFM_INTC(INTMask));
  
  HFM->INTSTS = INTMask;
}

/**
  * @brief  Gets HFM specified flag status.
  * @param  FlagMask: specifies the HFM flag status to check.
  *         This parameter can be one of the following values: 
  *             HFM_FLAG_T2FDONE
  *             HFM_FLAG_DSPDONE
  * @retval  The new state of HFM specified flag status (SET or RESET).
  */
FlagStatus HFM_GetFlag(uint32_t FlagMask)
{
  /* Check the parameters */
  assert_parameters(IS_HFM_FLAG(FlagMask));
  if (HFM->CMD & FlagMask)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Start T2F calculate.
  * @param  None
  * @retval  None
  */
void HFM_T2F_StartManual(void)
{
  HFM->CMD |= HFM_CMD_T2F;
}

/**
  * @brief  Start DSP calculate.
  * @param  None
  * @retval  None
  */
void HFM_DSP_StartManual(void)
{
  HFM->CMD |= HFM_CMD_DSP;
}

/**
  * @brief  Wait for the T2F calculation to complete.
  * @param  None
  * @retval  None
  */
void HFM_T2F_WaitForManual(void)
{
  while (HFM->CMD & BIT0)
  {
  }
}

/**
  * @brief  Wait for the DSP calculation to complete.
  * @param  None
  * @retval  None
  */
void HFM_DSP_WaitForManual(void)
{
  while (HFM->CMD & BIT1)
  {
  }
}
/**
  * @brief  Fills each EGY_InitType member with its default value.
  * @param  EGY_InitStruct: pointer to an EGY_InitType structure which will be initialized.
  * @retval None
  */
void EGY_StructInit(EGY_InitType *EGY_InitStruct)
{
  EGY_InitStruct->Channel= 0;
  EGY_InitStruct->HARMNum = 0;
  EGY_InitStruct->AddSource = EGY_ACCSOURCE_POWER;
  EGY_InitStruct->AddEGYMode = EGY_ACCEGYMODE_ORIGINAL;
  EGY_InitStruct->AddTypeSel = EGY_ACCTYPE_ACTIVEPOWER;
  EGY_InitStruct->AddPWRMode = EGY_ACCPOWERTYPE_POSITIVE;
}

/**
  * @brief  EGY initialization.
  * @param  EGY :EGY0~EGY2.
  * @param  EGY_InitStruct:EGY configuration.
  *          Channel:This parameter can be any combination of the following values:
  *               EGY_CHANNEL_A
  *               EGY_CHANNEL_B
  *               EGY_CHANNEL_C
  *          HARMNum: 0~20
  *          AddSource:
  *               EGY_ACCSOURCE_POWER
  *               EGY_ACCSOURCE_CURRENT
  *               EGY_ACCSOURCE_CONSTANT
  *          AddEGYMode:
  *               EGY_ACCEGYMODE_ORIGINAL
  *               EGY_ACCEGYMODE_ABSOLUTE
  *          AddTypeSel:
  *               EGY_ACCTYPE_ACTIVEPOWER
  *               EGY_ACCTYPE_REACTIVEPOWER
  *          AddPWRMode:
  *               EGY_ACCPOWERTYPE_POSITIVE
  *               EGY_ACCPOWERTYPE_NEGATIVE
  *               EGY_ACCPOWERTYPE_ORGINAL
  *               EGY_ACCPOWERTYPE_ABSOLUTE
  *          PowerThresholdSEL:
  *               EGY_POWRTHRESHOLD_PWRTH0
  *               EGY_POWRTHRESHOLD_PWRTH1
  * @retval None
  */
void EGY_Init(uint8_t EGY, EGY_InitType *EGY_InitStruct)
{
  uint32_t tmpreg;
  
  /* Check the parameters */
  assert_parameters(IS_EGY(EGY));
  assert_parameters(IS_EGY_CF_HARM_NUM(EGY_InitStruct->HARMNum));
  assert_parameters(IS_EGY_ACCSOURCE(EGY_InitStruct->AddSource));
  assert_parameters(IS_EGY_ACCEGYMODE(EGY_InitStruct->AddEGYMode));
  if ((EGY_InitStruct->AddSource == EGY_ACCSOURCE_POWER) || (EGY_InitStruct->AddSource == EGY_ACCSOURCE_CURRENT))
  {
    assert_parameters(IS_EGY_ACCPOWRERSOURCE(EGY_InitStruct->AddTypeSel));
    assert_parameters(IS_EGY_CHANNEL(EGY_InitStruct->Channel));
  }
  else if (EGY_InitStruct->AddSource == EGY_ACCSOURCE_POWER)
  {
    assert_parameters(IS_EGY_ACCPOWRERTYPE(EGY_InitStruct->AddPWRMode));
  }
  assert_parameters(IS_POWRTHRESHOLD_PWRTH(EGY_InitStruct->PowerThresholdSEL));
  
  /*---------------------------- EGY_CFG Configuration ------------------------*/
  tmpreg = HFM->EGY_CFG;
  tmpreg &= ~(HFM_EGYCFG0_CLEAR_MASK << (EGY * HFM_EGYCFG0_OFFSETADDR));
  tmpreg |= (EGY_InitStruct->AddEGYMode << HFM_EGYCFG0_EGYMODE0_POS << (EGY * HFM_EGYCFG0_OFFSETADDR)) |\
            (EGY_InitStruct->AddSource << HFM_EGYCFG0_EGYSOURCE_POS << (EGY * HFM_EGYCFG0_OFFSETADDR));
  if((EGY_InitStruct->AddSource == EGY_ACCSOURCE_POWER) || (EGY_InitStruct->AddSource == EGY_ACCSOURCE_CURRENT))
  {
    tmpreg |= (EGY_InitStruct->AddTypeSel << HFM_EGYCFG0_EGYTYPESEL_POS << (EGY * HFM_EGYCFG0_OFFSETADDR)) |\
              (EGY_InitStruct->Channel << HFM_EGYCFG0_CHANNEL_POS << (EGY * HFM_EGYCFG0_OFFSETADDR)) ;
  }
  if(EGY_InitStruct->AddSource == EGY_ACCSOURCE_POWER)
  {
    tmpreg |= (EGY_InitStruct->AddPWRMode << HFM_EGYCFG0_EGYPWRMODE_POS << (EGY * HFM_EGYCFG0_OFFSETADDR));
  }
  HFM->EGY_CFG = tmpreg;
  
  /*---------------------------- CFG Configuration ------------------------*/
  tmpreg = HFM->CFG;
  if (EGY == EGY0)
  {
    tmpreg &= HFM_HARMNUM_CLR << 24;
    tmpreg |= EGY_InitStruct->HARMNum << 24;
  }
  else if (EGY == EGY1)
  {
    tmpreg &= HFM_HARMNUM_CLR << 16;
    tmpreg |= EGY_InitStruct->HARMNum << 16;
  }
  else
  {
    tmpreg &= HFM_HARMNUM_CLR << 8;
    tmpreg |= EGY_InitStruct->HARMNum << 8;
  }
  HFM->CFG = tmpreg;
  
  /*---------------------------- DSPCFG Configuration ------------------------*/
  tmpreg = HFM->DSP_CFG;
  tmpreg &= HFM_DSPCFG_PWRTHSEL_CLR;
  tmpreg |= EGY_InitStruct->PowerThresholdSEL << HFM_DSPCFG_PWRTHSEL_POS << EGY;
  HFM->DSP_CFG = tmpreg;
}

/**
  * @brief  Fills each CF_InitStruct member with its default value.
  * @param  InitStruct: pointer to an CF_InitType structure which will be initialized.
  * @retval None
  */
void CF_StructInit(CF_InitType *CF_InitStruct)
{
  CF_InitStruct->ConstValue = 0;
  CF_InitStruct->CF_Source = CF_SOURCE_EGY0;
  CF_InitStruct->CF_Polarity= CF_ORGINAL;
  CF_InitStruct->CF_PulsePeriod = CF_PERIOD_80MS;
  CF_InitStruct->CF_Fast = CF_FAST_X1;
  CF_InitStruct->CF_Division = 0;
}

/**
  * @brief  CF initialization.
  * @param  EGY :EGY0~EGY2.
  * @param  CF_InitStruct:CF configuration.
  *          ConstValue:0~0xFFFFFFFF
  *          CF_Source: 
  *               CF_SOURCE_EGY0
  *               CF_SOURCE_EGY1
  *               CF_SOURCE_EGY2
  *               CF_SOURCE_0
  *          CF_Polarity:
  *               CF_ORGINAL
  *               CF_OPPOSITE
  *          CF_PulsePeriod:
  *               CF_PERIOD_80MS
  *               CF_PERIOD_40MS
  *               CF_PERIOD_20MS
  *               CF_PERIOD_10MS
  *          CF_Fast:
  *               CF_FAST_X1
  *               CF_FAST_X4
  *               CF_FAST_X8
  *               CF_FAST_X16
  *          CF_Division:0~0xFFFF
  * @retval None
  */
void CF_Init(uint8_t EGY, CF_InitType *CF_InitStruct)
{
  uint32_t tmpreg;
  __IO uint32_t *addr;
  
  /* Check the parameters */
  assert_parameters(IS_EGY(EGY));
  assert_parameters(IS_EGY_CF_DIV(CF_InitStruct->CF_Division));
  assert_parameters(IS_EGY_CF_SOURCE(CF_InitStruct->CF_Source));
  assert_parameters(IS_EGY_CF_POLARITY(CF_InitStruct->CF_Polarity));
  assert_parameters(IS_EGY_CF_PERIOD(CF_InitStruct->CF_PulsePeriod));
  assert_parameters(IS_EGY_CF_FAST(CF_InitStruct->CF_Fast));
  
  /*---------------------------- DSPCFG Configuration ------------------------*/
  tmpreg = HFM->DSP_CFG;
  tmpreg &= ~0xF0;
  tmpreg &= HFM_DSPCFG_POLARITY_CLR << EGY;
  tmpreg &= HFM_DSPCFG_SOURCE_CLR << (EGY * 2);

  tmpreg |= (CF_InitStruct->CF_Fast << HFM_DSPCFG_FAST_POS) |\
            (CF_InitStruct->CF_PulsePeriod << HFM_DSPCFG_PULSE_POS) |\
            (CF_InitStruct->CF_Polarity << HFM_DSPCFG_POLARITY_POS << EGY) |\
            (CF_InitStruct->CF_Source << HFM_DSPCFG_SOURCE_POS << (EGY * 2));
  HFM->DSP_CFG = tmpreg;
  
  HFM->EGY_CLKDIV = CF_InitStruct->CF_Division;
  addr = &HFM->EGY_CONST0 + EGY;
  *addr = CF_InitStruct->ConstValue;
}

/**
  * @brief  Enables or disables CFfunction.
  * @param  CF :CF0~CF2.
  * @param  NewState: new state of the specified CF function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CF_Cmd(uint8_t CF, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_EGY(CF));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    HFM->DSP_CFG |= (HFM_DSPCFG_OUTEN_MASK << CF);
  }
  else
  {
    HFM->DSP_CFG &= (HFM_DSPCFG_OUTEN_CLR << CF);
  }
}

/**
  * @brief  Enables or disables power creeping function.
  * @param  NewState: new state of the specified HFM power creeping function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EGY_PWRCRP_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    HFM->DSP_CFG |= HFM_DSPCFG_PWRCRP_EN;
  }
  else
  {
    HFM->DSP_CFG &= HFM_DSPCFG_PWRCRP_EN_CLR;
  }
}

/**
  * @brief  Enables or disables energy creeping function.
  * @param  NewState: new state of the specified energy creeping function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EGY_CRP_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    HFM->DSP_CFG |= HFM_DSPCFG_CRP_EN;
  }
  else
  {
    HFM->DSP_CFG &= HFM_DSPCFG_CRP_EN_CLR;
  }
}

/**
  * @brief  Enables or disables EGY function.
  * @param  EGY :EGY0~EGY2.
  * @param  NewState: new state of the specified EGY function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EGY_Cmd(uint8_t EGY, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_EGY(EGY));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    HFM->DSP_CFG |= (HFM_DSPCFG_EGY0_EN << EGY);
  }
  else
  {
    HFM->DSP_CFG &= (HFM_DSPCFG_EGY0_EN_CLR << EGY);
  }
}

/**
  * @brief  Set power creep over high and low threshold.
  * @param  HighThreshold :0~0xFFFFFFFF
  * @param  LowThreshold: 0~0xFFFFFFFF
  * @retval None
  */
void EGY_PWRCRPThresholdConfig(uint32_t HighThreshold, uint32_t LowThreshold)
{
  /* Check the parameters */
  assert_parameters(IS_EGY_PWRCRP_THRESHOLD(HighThreshold));
  assert_parameters(IS_EGY_PWRCRP_THRESHOLD(LowThreshold));
  
  /* Set the power creep over high threshold */
  HFM->PWROVTHH = HighThreshold;
  /* Set the power creep over low threshold */
  HFM->PWROVTHL = LowThreshold;
}

/**
  * @brief  Set power 0 threshold.
  * @param  Threshold: 0~0xFFFFFFFF.
  * @retval None
  */
void EGY_PWR0ThresholdConfig(uint32_t Threshold)
{
  /* Check the parameters */
  assert_parameters(IS_EGY_PWR_THRESHOLD(Threshold));

  /* Set the power0 threshold */
  HFM->EGY_PWRTH0 = Threshold;
}

/**
  * @brief  Set power 1 threshold.
  * @param  Threshold: 0~0xFFFFFFFF.
  * @retval None
  */
void EGY_PWR1ThresholdConfig(uint32_t Threshold)
{
  /* Check the parameters */
  assert_parameters(IS_EGY_PWR_THRESHOLD(Threshold));

  /* Set the power0 threshold */
  HFM->EGY_PWRTH1 = Threshold;
}

/**
  * @brief  Set EGY threshold.
  * @param  Threshold: 0~0xFFFFFFFF.
  * @retval None
  */
void EGY_PRCThresholdConfig(uint32_t Threshold)
{
  /* Check the parameters */
  assert_parameters(IS_EGY_PWR_THRESHOLD(Threshold));

  /* Set the prevent creeping threshold */
  HFM->EGY_PROCTH = Threshold;
}

/**
  * @brief  Clear EGY count or cumulative energy value.
  * @param  Threshold: 0~0xFFFFFFFF.
  * @retval None
  */
void EGY_Clear(uint8_t Mask)
{
  /* Check the parameters */
  assert_parameters(IS_EGY_CLEARC(Mask));

  HFM->EGY_CLR = Mask;
}
/*********************************** END OF FILE ******************************/
