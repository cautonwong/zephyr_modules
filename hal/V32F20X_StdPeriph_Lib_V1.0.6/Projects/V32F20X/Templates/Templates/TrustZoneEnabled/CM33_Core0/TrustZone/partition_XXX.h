
#ifndef __PARTITION_XXX_H
#define __PARTITION_XXX_H

/*
// SYSCFG0_CLK_EN2
*/
#define TZ_SYSCFG0_CLK_EN2_SCR          (1UL << 25)
#define TZ_SCR_BUSY_BUSY                 (1UL << 0)
#define TZ_SYSCFG0_KEY                  (0xBEEFBEEFUL)

/* Enable SCR clock */
#define TZ_SCR_CLOCK_ENABLE()             SYSCFG0->SYSCON_PASSWD = TZ_SYSCFG0_KEY; \
                                          SYSCFG0->CLK_EN2 |= TZ_SYSCFG0_CLK_EN2_SCR
/* Wait until SCR configuration done */
#define TZ_SCR_WAIT_IDLE()                while (SCR33->BUSY & TZ_SCR_BUSY_BUSY)


/*
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
*/

/*
// <e>Initialize Security Attribution Unit (SAU) CTRL register
*/
#define SAU_INIT_CTRL          1

/*
//   <q> Enable SAU
//   <i> Value for SAU->CTRL register bit ENABLE
*/
#define SAU_INIT_CTRL_ENABLE   1

/*
//   <o> When SAU is disabled
//     <0=> All Memory is Secure
//     <1=> All Memory is Non-Secure
//   <i> Value for SAU->CTRL register bit ALLNS
//   <i> When all Memory is Non-Secure (ALLNS is 1), IDAU can override memory map configuration.
*/
#define SAU_INIT_CTRL_ALLNS  0

/*
// </e>
*/

/*
// <h>Initialize Security Attribution Unit (SAU) Address Regions
// <i>SAU configuration specifies regions to be one of:
// <i> - Secure and Non-Secure Callable
// <i> - Non-Secure
// <i>Note: All memory regions not configured by SAU are Secure
*/
#define SAU_REGIONS_MAX   8                 /* Max. number of SAU regions */

/*
//   <e>Initialize SAU Region 0
//   <i> Setup SAU Region 0 memory attributes
*/
#define SAU_INIT_REGION0    1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START0     0x0007E000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END0       0x0007FFFF      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC0       1
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 1
//   <i> Setup SAU Region 1 memory attributes
*/
#define SAU_INIT_REGION1    1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START1     0x00080000      /* start address of SAU region 1 */
/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END1       0x000FFFFF      /* end address of SAU region 1 */
/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC1       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 2
//   <i> Setup SAU Region 2 memory attributes
*/
#define SAU_INIT_REGION2    1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START2     0x20040000      /* start address of SAU region 2 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END2       0xFFFFFFFF      /* end address of SAU region 2 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC2       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 3
//   <i> Setup SAU Region 3 memory attributes
*/
#define SAU_INIT_REGION3    1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START3     0x00100000      /* start address of SAU region 3 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END3       0x001FFFFF      /* end address of SAU region 3 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC3       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 4
//   <i> Setup SAU Region 4 memory attributes
*/
#define SAU_INIT_REGION4    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START4     0x00000000      /* start address of SAU region 4 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END4       0x00000000      /* end address of SAU region 4 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC4       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 5
//   <i> Setup SAU Region 5 memory attributes
*/
#define SAU_INIT_REGION5    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START5     0x00000000      /* start address of SAU region 5 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END5       0x00000000      /* end address of SAU region 5 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC5       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 6
//   <i> Setup SAU Region 6 memory attributes
*/
#define SAU_INIT_REGION6    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START6     0x00000000      /* start address of SAU region 6 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END6       0x00000000      /* end address of SAU region 6 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC6       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 7
//   <i> Setup SAU Region 7 memory attributes
*/
#define SAU_INIT_REGION7    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START7     0x00000000      /* start address of SAU region 7 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END7       0x00000000      /* end address of SAU region 7 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC7       0
/*
//   </e>
*/

/*
// </h>
*/

/*
// <h>Initialize Internal MPC configuations
// <i> 0 - Secure
// <i> 1 - Non-Secure
*/

/*
//   <e>Initialize FLASHA MPC
//   <i> Setup FLASH Bank A MPC attributes
//   <i> Every bit unit in 8K-size
*/
#define FLASHA_MPC_INIT     1
/*
//     <o>CONFIG0
*/
#define FLASHA_MPC_CFG0     0x00000000
/*
//     <o>CONFIG1
*/
#define FLASHA_MPC_CFG1     0x00000000
/*
//     <o>CONFIG2
*/
#define FLASHA_MPC_CFG2     0xFFFFFFFF
/*
//     <o>CONFIG3
*/
#define FLASHA_MPC_CFG3     0xFFFFFFFF
/*
//   </e>
*/
/*

//   <e>Initialize FLASHB MPC
//   <i> Setup FLASH Bank B MPC attributes
//   <i> Every bit unit in 8K-size
*/
#define FLASHB_MPC_INIT     1
/*
//     <o>CONFIG0
*/
#define FLASHB_MPC_CFG0     0xFFFFFFFF
/*
//     <o>CONFIG1
*/
#define FLASHB_MPC_CFG1     0xFFFFFFFF
/*
//     <o>CONFIG2
*/
#define FLASHB_MPC_CFG2     0xFFFFFFFF
/*
//     <o>CONFIG3
*/
#define FLASHB_MPC_CFG3     0xFFFFFFFF
/*
//   </e>
*/

/*
//   <e>Initialize CM33 SRAM0 MPC
//   <i> Setup CM33 SRAM0 MPC attributes
*/
#define SRAM0_MPC_INIT     1

/*
//      <o>CONFIG0
*/     
#define SRAM0_MPC_CFG0       0x00000000
/*
//      <o>CONFIG1
*/     
#define SRAM0_MPC_CFG1       0x00000000
/*
//      <o>CONFIG2
*/     
#define SRAM0_MPC_CFG2       0x00000000
/*
//      <o>CONFIG3
*/     
#define SRAM0_MPC_CFG3       0x00000000
/*
//      <o>CONFIG4
*/     
#define SRAM0_MPC_CFG4       0x00000000
/*
//      <o>CONFIG5
*/     
#define SRAM0_MPC_CFG5       0x00000000
/*
//      <o>CONFIG6
*/     
#define SRAM0_MPC_CFG6       0x00000000
/*
//      <o>CONFIG7
*/     
#define SRAM0_MPC_CFG7       0x00000000
/*
//      <o>CONFIG8
*/     
#define SRAM0_MPC_CFG8       0x00000000
/*
//      <o>CONFIG9
*/     
#define SRAM0_MPC_CFG9       0x00000000
/*
//      <o>CONFIG10
*/     
#define SRAM0_MPC_CFG10       0x00000000
/*
//      <o>CONFIG11
*/     
#define SRAM0_MPC_CFG11       0x00000000
/*
//      <o>CONFIG12
*/     
#define SRAM0_MPC_CFG12       0x00000000
/*
//      <o>CONFIG13
*/     
#define SRAM0_MPC_CFG13       0x00000000
/*
//      <o>CONFIG14
*/     
#define SRAM0_MPC_CFG14       0x00000000
/*
//      <o>CONFIG15
*/     
#define SRAM0_MPC_CFG15       0x00000000
/*
//      <o>CONFIG16
*/     
#define SRAM0_MPC_CFG16       0x00000000
/*
//      <o>CONFIG17
*/     
#define SRAM0_MPC_CFG17       0x00000000
/*
//      <o>CONFIG18
*/     
#define SRAM0_MPC_CFG18       0x00000000
/*
//      <o>CONFIG19
*/     
#define SRAM0_MPC_CFG19       0x00000000
/*
//      <o>CONFIG20
*/     
#define SRAM0_MPC_CFG20       0x00000000
/*
//      <o>CONFIG21
*/     
#define SRAM0_MPC_CFG21       0x00000000
/*
//      <o>CONFIG22
*/     
#define SRAM0_MPC_CFG22       0x00000000
/*
//      <o>CONFIG23
*/     
#define SRAM0_MPC_CFG23       0x00000000
/*
//      <o>CONFIG24
*/     
#define SRAM0_MPC_CFG24       0x00000000
/*
//      <o>CONFIG25
*/     
#define SRAM0_MPC_CFG25       0x00000000
/*
//      <o>CONFIG26
*/     
#define SRAM0_MPC_CFG26       0x00000000
/*
//      <o>CONFIG27
*/     
#define SRAM0_MPC_CFG27       0x00000000
/*
//      <o>CONFIG28
*/     
#define SRAM0_MPC_CFG28       0x00000000
/*
//      <o>CONFIG29
*/     
#define SRAM0_MPC_CFG29       0x00000000
/*
//      <o>CONFIG30
*/     
#define SRAM0_MPC_CFG30       0x00000000
/*
//      <o>CONFIG31
*/     
#define SRAM0_MPC_CFG31       0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize CM33 SRAM1 MPC
//   <i> Setup CM33 SRAM1 MPC attributes
*/
#define SRAM1_MPC_INIT     1

/*
//      <o>CONFIG0
*/     
#define SRAM1_MPC_CFG0       0xFFFFFFFF
/*
//      <o>CONFIG1
*/     
#define SRAM1_MPC_CFG1       0xFFFFFFFF
/*
//      <o>CONFIG2
*/     
#define SRAM1_MPC_CFG2       0xFFFFFFFF
/*
//      <o>CONFIG3
*/     
#define SRAM1_MPC_CFG3       0xFFFFFFFF
/*
//      <o>CONFIG4
*/     
#define SRAM1_MPC_CFG4       0xFFFFFFFF
/*
//      <o>CONFIG5
*/     
#define SRAM1_MPC_CFG5       0xFFFFFFFF
/*
//      <o>CONFIG6
*/     
#define SRAM1_MPC_CFG6       0xFFFFFFFF
/*
//      <o>CONFIG7
*/     
#define SRAM1_MPC_CFG7       0xFFFFFFFF
/*
//      <o>CONFIG8
*/     
#define SRAM1_MPC_CFG8       0xFFFFFFFF
/*
//      <o>CONFIG9
*/     
#define SRAM1_MPC_CFG9       0xFFFFFFFF
/*
//      <o>CONFIG10
*/     
#define SRAM1_MPC_CFG10       0xFFFFFFFF
/*
//      <o>CONFIG11
*/     
#define SRAM1_MPC_CFG11       0xFFFFFFFF
/*
//      <o>CONFIG12
*/     
#define SRAM1_MPC_CFG12       0xFFFFFFFF
/*
//      <o>CONFIG13
*/     
#define SRAM1_MPC_CFG13       0xFFFFFFFF
/*
//      <o>CONFIG14
*/     
#define SRAM1_MPC_CFG14       0xFFFFFFFF
/*
//      <o>CONFIG15
*/     
#define SRAM1_MPC_CFG15       0xFFFFFFFF
/*
//      <o>CONFIG16
*/     
#define SRAM1_MPC_CFG16       0xFFFFFFFF
/*
//      <o>CONFIG17
*/     
#define SRAM1_MPC_CFG17       0xFFFFFFFF
/*
//      <o>CONFIG18
*/     
#define SRAM1_MPC_CFG18       0xFFFFFFFF
/*
//      <o>CONFIG19
*/     
#define SRAM1_MPC_CFG19       0xFFFFFFFF
/*
//      <o>CONFIG20
*/     
#define SRAM1_MPC_CFG20       0xFFFFFFFF
/*
//      <o>CONFIG21
*/     
#define SRAM1_MPC_CFG21       0xFFFFFFFF
/*
//      <o>CONFIG22
*/     
#define SRAM1_MPC_CFG22       0xFFFFFFFF
/*
//      <o>CONFIG23
*/     
#define SRAM1_MPC_CFG23       0xFFFFFFFF
/*
//      <o>CONFIG24
*/     
#define SRAM1_MPC_CFG24       0xFFFFFFFF
/*
//      <o>CONFIG25
*/     
#define SRAM1_MPC_CFG25       0xFFFFFFFF
/*
//      <o>CONFIG26
*/     
#define SRAM1_MPC_CFG26       0xFFFFFFFF
/*
//      <o>CONFIG27
*/     
#define SRAM1_MPC_CFG27       0xFFFFFFFF
/*
//      <o>CONFIG28
*/     
#define SRAM1_MPC_CFG28       0xFFFFFFFF
/*
//      <o>CONFIG29
*/     
#define SRAM1_MPC_CFG29       0xFFFFFFFF
/*
//      <o>CONFIG30
*/     
#define SRAM1_MPC_CFG30       0xFFFFFFFF
/*
//      <o>CONFIG31
*/     
#define SRAM1_MPC_CFG31       0xFFFFFFFF
/*
//   </e>
*/

/*
//   <e>Initialize CM33 SRAM2 MPC
//   <i> Setup CM33 SRAM2 MPC attributes
*/
#define SRAM2_MPC_INIT     1

/*
//      <o>CONFIG0
*/     
#define SRAM2_MPC_CFG0       0xFFFFFFFF
/*
//      <o>CONFIG1
*/     
#define SRAM2_MPC_CFG1       0xFFFFFFFF
/*
//      <o>CONFIG2
*/     
#define SRAM2_MPC_CFG2       0xFFFFFFFF
/*
//      <o>CONFIG3
*/     
#define SRAM2_MPC_CFG3       0xFFFFFFFF
/*
//      <o>CONFIG4
*/     
#define SRAM2_MPC_CFG4       0xFFFFFFFF
/*
//      <o>CONFIG5
*/     
#define SRAM2_MPC_CFG5       0xFFFFFFFF
/*
//      <o>CONFIG6
*/     
#define SRAM2_MPC_CFG6       0xFFFFFFFF
/*
//      <o>CONFIG7
*/     
#define SRAM2_MPC_CFG7       0xFFFFFFFF
/*
//      <o>CONFIG8
*/     
#define SRAM2_MPC_CFG8       0xFFFFFFFF
/*
//      <o>CONFIG9
*/     
#define SRAM2_MPC_CFG9       0xFFFFFFFF
/*
//      <o>CONFIG10
*/     
#define SRAM2_MPC_CFG10       0xFFFFFFFF
/*
//      <o>CONFIG11
*/     
#define SRAM2_MPC_CFG11       0xFFFFFFFF
/*
//      <o>CONFIG12
*/     
#define SRAM2_MPC_CFG12       0xFFFFFFFF
/*
//      <o>CONFIG13
*/     
#define SRAM2_MPC_CFG13       0xFFFFFFFF
/*
//      <o>CONFIG14
*/     
#define SRAM2_MPC_CFG14       0xFFFFFFFF
/*
//      <o>CONFIG15
*/     
#define SRAM2_MPC_CFG15       0xFFFFFFFF
/*
//      <o>CONFIG16
*/     
#define SRAM2_MPC_CFG16       0xFFFFFFFF
/*
//      <o>CONFIG17
*/     
#define SRAM2_MPC_CFG17       0xFFFFFFFF
/*
//      <o>CONFIG18
*/     
#define SRAM2_MPC_CFG18       0xFFFFFFFF
/*
//      <o>CONFIG19
*/     
#define SRAM2_MPC_CFG19       0xFFFFFFFF
/*
//      <o>CONFIG20
*/     
#define SRAM2_MPC_CFG20       0xFFFFFFFF
/*
//      <o>CONFIG21
*/     
#define SRAM2_MPC_CFG21       0xFFFFFFFF
/*
//      <o>CONFIG22
*/     
#define SRAM2_MPC_CFG22       0xFFFFFFFF
/*
//      <o>CONFIG23
*/     
#define SRAM2_MPC_CFG23       0xFFFFFFFF
/*
//      <o>CONFIG24
*/     
#define SRAM2_MPC_CFG24       0xFFFFFFFF
/*
//      <o>CONFIG25
*/     
#define SRAM2_MPC_CFG25       0xFFFFFFFF
/*
//      <o>CONFIG26
*/     
#define SRAM2_MPC_CFG26       0xFFFFFFFF
/*
//      <o>CONFIG27
*/     
#define SRAM2_MPC_CFG27       0xFFFFFFFF
/*
//      <o>CONFIG28
*/     
#define SRAM2_MPC_CFG28       0xFFFFFFFF
/*
//      <o>CONFIG29
*/     
#define SRAM2_MPC_CFG29       0xFFFFFFFF
/*
//      <o>CONFIG30
*/     
#define SRAM2_MPC_CFG30       0xFFFFFFFF
/*
//      <o>CONFIG31
*/     
#define SRAM2_MPC_CFG31       0xFFFFFFFF
/*
//   </e>
*/

/*
//   <e>Initialize CM33 SRAM3 MPC
//   <i> Setup CM33 SRAM3 MPC attributes
*/
#define SRAM3_MPC_INIT     1

/*
//      <o>CONFIG0
*/     
#define SRAM3_MPC_CFG0       0xFFFFFFFF
/*
//      <o>CONFIG1
*/     
#define SRAM3_MPC_CFG1       0xFFFFFFFF
/*
//      <o>CONFIG2
*/     
#define SRAM3_MPC_CFG2       0xFFFFFFFF
/*
//      <o>CONFIG3
*/     
#define SRAM3_MPC_CFG3       0xFFFFFFFF
/*
//      <o>CONFIG4
*/     
#define SRAM3_MPC_CFG4       0xFFFFFFFF
/*
//      <o>CONFIG5
*/     
#define SRAM3_MPC_CFG5       0xFFFFFFFF
/*
//      <o>CONFIG6
*/     
#define SRAM3_MPC_CFG6       0xFFFFFFFF
/*
//      <o>CONFIG7
*/     
#define SRAM3_MPC_CFG7       0xFFFFFFFF
/*
//      <o>CONFIG8
*/     
#define SRAM3_MPC_CFG8       0xFFFFFFFF
/*
//      <o>CONFIG9
*/     
#define SRAM3_MPC_CFG9       0xFFFFFFFF
/*
//      <o>CONFIG10
*/     
#define SRAM3_MPC_CFG10       0xFFFFFFFF
/*
//      <o>CONFIG11
*/     
#define SRAM3_MPC_CFG11       0xFFFFFFFF
/*
//      <o>CONFIG12
*/     
#define SRAM3_MPC_CFG12       0xFFFFFFFF
/*
//      <o>CONFIG13
*/     
#define SRAM3_MPC_CFG13       0xFFFFFFFF
/*
//      <o>CONFIG14
*/     
#define SRAM3_MPC_CFG14       0xFFFFFFFF
/*
//      <o>CONFIG15
*/     
#define SRAM3_MPC_CFG15       0xFFFFFFFF
/*
//      <o>CONFIG16
*/     
#define SRAM3_MPC_CFG16       0xFFFFFFFF
/*
//      <o>CONFIG17
*/     
#define SRAM3_MPC_CFG17       0xFFFFFFFF
/*
//      <o>CONFIG18
*/     
#define SRAM3_MPC_CFG18       0xFFFFFFFF
/*
//      <o>CONFIG19
*/     
#define SRAM3_MPC_CFG19       0xFFFFFFFF
/*
//      <o>CONFIG20
*/     
#define SRAM3_MPC_CFG20       0xFFFFFFFF
/*
//      <o>CONFIG21
*/     
#define SRAM3_MPC_CFG21       0xFFFFFFFF
/*
//      <o>CONFIG22
*/     
#define SRAM3_MPC_CFG22       0xFFFFFFFF
/*
//      <o>CONFIG23
*/     
#define SRAM3_MPC_CFG23       0xFFFFFFFF
/*
//      <o>CONFIG24
*/     
#define SRAM3_MPC_CFG24       0xFFFFFFFF
/*
//      <o>CONFIG25
*/     
#define SRAM3_MPC_CFG25       0xFFFFFFFF
/*
//      <o>CONFIG26
*/     
#define SRAM3_MPC_CFG26       0xFFFFFFFF
/*
//      <o>CONFIG27
*/     
#define SRAM3_MPC_CFG27       0xFFFFFFFF
/*
//      <o>CONFIG28
*/     
#define SRAM3_MPC_CFG28       0xFFFFFFFF
/*
//      <o>CONFIG29
*/     
#define SRAM3_MPC_CFG29       0xFFFFFFFF
/*
//      <o>CONFIG30
*/     
#define SRAM3_MPC_CFG30       0xFFFFFFFF
/*
//      <o>CONFIG31
*/     
#define SRAM3_MPC_CFG31       0xFFFFFFFF
/*
//   </e>
*/

/*
// </h>
*/

/*
// <h>Setup SCR PPC configurations
*/
/*
//   <e>Initialize CM33 APB
*/
#define SCR_APBPPC_INIT    1
/*
// Error Response
//   <o.0>  ErrorResponse    <0=> RAZ/WI <1=> Bus Error
*/
#define SCR_APBPPC_RESP_CFG      0x00000000
/*
//   <e>Secure/NonSecure 0
*/
#define SCR_APBPPC_NSEC_INIT0    1
/*
// Secure/NonSecure 0
//   <o.0>  DAC    <0=> Secure state <1=> Non-Secure state
//   <o.1>  FC0    <0=> Secure state <1=> Non-Secure state
//   <o.2>  FC1    <0=> Secure state <1=> Non-Secure state
//   <o.3>  FC2    <0=> Secure state <1=> Non-Secure state
//   <o.4>  FC3    <0=> Secure state <1=> Non-Secure state
//   <o.5>  FC4    <0=> Secure state <1=> Non-Secure state
//   <o.6>  FC5    <0=> Secure state <1=> Non-Secure state
//   <o.7>  FC6    <0=> Secure state <1=> Non-Secure state
//   <o.8>  FC7    <0=> Secure state <1=> Non-Secure state
//   <o.9>  FC8    <0=> Secure state <1=> Non-Secure state
//   <o.10>  FC9     <0=> Secure state <1=> Non-Secure state
//   <o.11>  FC10    <0=> Secure state <1=> Non-Secure state
//   <o.12>  FC11    <0=> Secure state <1=> Non-Secure state
//   <o.13>  FC12    <0=> Secure state <1=> Non-Secure state
//   <o.14>  FC13    <0=> Secure state <1=> Non-Secure state
//   <o.15>  ISO7816 <0=> Secure state <1=> Non-Secure state
//   <o.16>  BTMR0_3   <0=> Secure state <1=> Non-Secure state
//   <o.17>  RNG     <0=> Secure state <1=> Non-Secure state
//   <o.19>  CAN0    <0=> Secure state <1=> Non-Secure state
//   <o.20>  CAN1    <0=> Secure state <1=> Non-Secure state
//   <o.20>  CAN1    <0=> Secure state <1=> Non-Secure state
//   <o.21>  RESERVED   <0=> Secure state <1=> Non-Secure state
//   <o.22>  I2S0       <0=> Secure state <1=> Non-Secure state
//   <o.23>  SDIO0      <0=> Secure state <1=> Non-Secure state
//   <o.24>  SDIO1      <0=> Secure state <1=> Non-Secure state
//   <o.25>  WDT0       <0=> Secure state <1=> Non-Secure state
//   <o.26>  WDT1       <0=> Secure state <1=> Non-Secure state
//   <o.28>  ETMR0       <0=> Secure state <1=> Non-Secure state
//   <o.29>  ETMR1       <0=> Secure state <1=> Non-Secure state
//   <o.30>  GTMR0       <0=> Secure state <1=> Non-Secure state
//   <o.31>  GTMR1       <0=> Secure state <1=> Non-Secure state
*/
#define SCR_APBPPC_NSEC_CFG0      0x00000000
/*
//   </e>
*/
/*
//   <e>Secure/NonSecure 1
*/
#define SCR_APBPPC_NSEC_INIT1    1
/*
// Secure/NonSecure 1
//   <o.0>  GTMR2    <0=> Secure state <1=> Non-Secure state
//   <o.1>  GTMR3    <0=> Secure state <1=> Non-Secure state
//   <o.2>  EADC    <0=> Secure state <1=> Non-Secure state
//   <o.3>  I2S1    <0=> Secure state <1=> Non-Secure state
*/
#define SCR_APBPPC_NSEC_CFG1      0x00000000
/*
//   </e>
*/
/*
//   <e>PrivOnly/UnPriv 0
*/
#define SCR_APBPPC_AP_INIT0    1
/*
// PrivOnly/UnPriv configuration 0
//   <o.0>  DAC    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.1>  FC0    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.2>  FC1    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.3>  FC2    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.4>  FC3    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.5>  FC4    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.6>  FC5    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.7>  FC6    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.8>  FC7    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.9>  FC8    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.10>  FC9     <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.11>  FC10    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.12>  FC11    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.13>  FC12    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.14>  FC13    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.15>  ISO7816 <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.16>  BTMR0~3    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.17>  RNG     <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.19>  CAN0    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.20>  CAN1    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.20>  CAN1    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.21>  RESERVED    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.22>  I2S0       <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.23>  SDIO0      <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.24>  SDIO1      <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.25>  WDT0       <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.26>  WDT1       <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.28>  ETMR0       <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.29>  ETMR1       <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.30>  GTMR0       <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.31>  GTMR1       <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_APBPPC_AP_CFG0      0x00000000
/*
//   </e>
*/
/*
//   <e>PrivOnly/UnPriv 1
*/
#define SCR_APBPPC_AP_INIT1    1
/*
// PrivOnly/UnPriv 1
//   <o.0>  GTMR2    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.1>  GTMR3    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.2>  EADC    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.3>  I2S1    <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_APBPPC_AP_CFG1      0x00000000
/*
//   </e>
*/
/*
//   </e>
*/

/*
//   <e>Initialize CM33 SYNC APB
*/
#define SCR_APBPPC_SYNC_INIT    1
/*
// Error Response
//   <o.0>  ErrorResponse    <0=> RAZ/WI <1=> Bus Error
*/
#define SCR_APBPPC_SYNC_RESP_CFG      0x00000000
/*
//   <e>Secure/NonSecure
*/
#define SCR_APBPPC_SYNC_NSEC_INIT    1
/*
// Secure/NonSecure
//   <o.0>  SYSCFG0  <0=> Secure state <1=> Non-Secure state
//   <o.1>  GPIO      <0=> Secure state <1=> Non-Secure state
//   <o.2>  FLASHA    <0=> Secure state <1=> Non-Secure state
//   <o.3>  FLASHB    <0=> Secure state <1=> Non-Secure state
//   <o.4>  MAC0      <0=> Secure state <1=> Non-Secure state
//   <o.5>  MAC1      <0=> Secure state <1=> Non-Secure state
//   <o.7>  ENCENG    <0=> Secure state <1=> Non-Secure state
*/
#define SCR_APBPPC_SYNC_NSEC_CFG      0x00000000
/*
//   </e>
*/
/*
//   <e>PrivOnly/UnPriv
*/
#define SCR_APBPPC_SYNC_AP_INIT    1
/*
// PrivOnly/UnPriv
//   <o.0>  SYSCFG0    <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.1>  GPIO        <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.2>  FLASHA      <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.3>  FLASHB      <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.4>  MAC0        <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.5>  MAC1        <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.7>  ENCENG      <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_APBPPC_SYNC_AP_CFG      0x00000000
/*
//   </e>
*/
/*
//   </e>
*/

/*
//   <e>Initialize CM33 DMA0
*/
#define SCR_DMA0_INIT    1
/*
//   <e>Secure/NonSecure
*/
#define SCR_DMA0_NSEC_INIT    1
/*
// Secure/NonSecure
//   <o.0>  Channel0  <0=> Secure state <1=> Non-Secure state
//   <o.1>  Channel1  <0=> Secure state <1=> Non-Secure state
//   <o.2>  Channel2  <0=> Secure state <1=> Non-Secure state
//   <o.3>  Channel3  <0=> Secure state <1=> Non-Secure state
//   <o.4>  Channel4  <0=> Secure state <1=> Non-Secure state
//   <o.5>  Channel5  <0=> Secure state <1=> Non-Secure state
//   <o.6>  Channel6  <0=> Secure state <1=> Non-Secure state
//   <o.7>  Channel7  <0=> Secure state <1=> Non-Secure state
//   <o.8>  Common Registers  <0=> Secure state <1=> Non-Secure state
*/
#define SCR_DMA0_NSEC_CFG      0x00000000
/*
//   </e>
*/
/*
//   <e>PrivOnly/UnPriv
*/
#define SCR_DMA0_AP_INIT    1
/*
// PrivOnly/UnPriv
//   <o.0>  Channel0  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.1>  Channel1  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.2>  Channel2  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.3>  Channel3  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.4>  Channel4  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.5>  Channel5  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.5>  Channel6  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.7>  Channel7  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.8>  Common Registers  <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_DMA0_AP_CFG      0x00000000
/*
//   </e>
*/
/*
//   </e>
*/

/*
//   <e>Initialize CM33 DMA1
*/
#define SCR_DMA1_INIT    1
/*
//   <e>Secure/NonSecure
*/
#define SCR_DMA1_NSEC_INIT    1
/*
// Secure/NonSecure
//   <o.0>  Channel0  <0=> Secure state <1=> Non-Secure state
//   <o.1>  Channel1  <0=> Secure state <1=> Non-Secure state
//   <o.2>  Channel2  <0=> Secure state <1=> Non-Secure state
//   <o.3>  Channel3  <0=> Secure state <1=> Non-Secure state
//   <o.4>  Channel4  <0=> Secure state <1=> Non-Secure state
//   <o.5>  Channel5  <0=> Secure state <1=> Non-Secure state
//   <o.6>  Channel6  <0=> Secure state <1=> Non-Secure state
//   <o.7>  Channel7  <0=> Secure state <1=> Non-Secure state
//   <o.8>  Common Registers  <0=> Secure state <1=> Non-Secure state
*/
#define SCR_DMA1_NSEC_CFG      0x00000000
/*
//   </e>
*/
/*
//   <e>PrivOnly/UnPriv
*/
#define SCR_DMA1_AP_INIT    1
/*
// PrivOnly/UnPriv
//   <o.0>  Channel0  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.1>  Channel1  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.2>  Channel2  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.3>  Channel3  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.4>  Channel4  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.5>  Channel5  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.5>  Channel6  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.7>  Channel7  <0=> Privilage Only <1=> Privilage & Unprivilage 
//   <o.8>  Common Registers  <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_DMA1_AP_CFG      0x00000000
/*
//   </e>
*/
/*
//   </e>
*/

/*
//   <e>Initialize CM33 MAC0 Master
*/
#define SCR_MAC0_MSC_INIT    1
/*
// Master Secure/NonSecure
//   <o.0>  MAC0 Security  <0=> Secure state <1=> Non-Secure state
*/
#define SCR_MAC0_MSC_NSEC_CFG      0x00000000
/*
// Master PrivOnly/UnPriv
//   <o.0>  MAC0 AP  <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_MAC0_MSC_AP_CFG      0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize CM33 MAC1 Master
*/
#define SCR_MAC1_MSC_INIT    1
/*
// Master Secure/NonSecure
//   <o.0>  MAC1 Security  <0=> Secure state <1=> Non-Secure state
*/
#define SCR_MAC1_MSC_NSEC_CFG      0x00000000
/*
// Master PrivOnly/UnPriv
//   <o.0>  MAC1 AP  <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_MAC1_MSC_AP_CFG      0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize CM33 ENCENG Master
*/
#define SCR_ENCENG_MSC_INIT    1
/*
// Master Secure/NonSecure
//   <o.0>  ENCENG Security  <0=> Secure state <1=> Non-Secure state
*/
#define SCR_ENCENG_MSC_NSEC_CFG      0x00000000
/*
// Master PrivOnly/UnPriv
//   <o.0>  ENCENG AP  <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_ENCENG_MSC_AP_CFG      0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize CM33 SDIO0 Master
*/
#define SCR_SDIO0_MSC_INIT    1
/*
// Master Secure/NonSecure
//   <o.0>  SDIO0 Security  <0=> Secure state <1=> Non-Secure state
*/
#define SCR_SDIO0_MSC_NSEC_CFG      0x00000000
/*
// Master PrivOnly/UnPriv
//   <o.0>  SDIO0 AP  <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_SDIO0_MSC_AP_CFG      0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize CM33 SDIO1 Master
*/
#define SCR_SDIO1_MSC_INIT    1
/*
// Master Secure/NonSecure
//   <o.0>  SDIO1 Security  <0=> Secure state <1=> Non-Secure state
*/
#define SCR_SDIO1_MSC_NSEC_CFG      0x00000000
/*
// Master PrivOnly/UnPriv
//   <o.0>  SDIO1 AP  <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_SDIO1_MSC_AP_CFG      0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize CM33 OSPI0 Master
*/
#define SCR_OSPI0_MSC_INIT    1
/*
// Master Error Response
//   <o.16>  ErrorResponse    <0=> RAZ/WI <1=> Bus Error
*/
#define SCR_OSPI0_MSC_RESP_CFG      0x00000000
/*
// Master Secure/NonSecure
//   <o.16>  OSPI0 Security  <0=> Secure state <1=> Non-Secure state
*/
#define SCR_OSPI0_MSC_NSEC_CFG      0x00000000
/*
// Master PrivOnly/UnPriv
//   <o.16>  OSPI0 AP  <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_OSPI0_MSC_AP_CFG      0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize CM33 OSPI1 Master
*/
#define SCR_OSPI1_MSC_INIT    1
/*
// Master Error Response
//   <o.16>  ErrorResponse    <0=> RAZ/WI <1=> Bus Error
*/
#define SCR_OSPI1_MSC_RESP_CFG      0x00000000
/*
// Master Secure/NonSecure
//   <o.16>  OSPI1 Security  <0=> Secure state <1=> Non-Secure state
*/
#define SCR_OSPI1_MSC_NSEC_CFG      0x00000000
/*
// Master PrivOnly/UnPriv
//   <o.16>  OSPI1 AP  <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_OSPI1_MSC_AP_CFG      0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize CM33 HS USB Master
*/
#define SCR_USB_HS_MSC_INIT    1
/*
// Master Error Response
//   <o.16>  ErrorResponse    <0=> RAZ/WI <1=> Bus Error
*/
#define SCR_USB_HS_MSC_RESP_CFG      0x00000000
/*
// Master Secure/NonSecure
//   <o.16>  USB_HS Security  <0=> Secure state <1=> Non-Secure state
*/
#define SCR_USB_HS_MSC_NSEC_CFG      0x00000000
/*
// Master PrivOnly/UnPriv
//   <o.16>  USB_HS AP  <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_USB_HS_MSC_AP_CFG      0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize CM33 FS USB Master
*/
#define SCR_USB_FS_MSC_INIT    1
/*
// Master Error Response
//   <o.16>  ErrorResponse    <0=> RAZ/WI <1=> Bus Error
*/
#define SCR_USB_FS_MSC_RESP_CFG      0x00000000
/*
// Master Secure/NonSecure
//   <o.16>  USB_FS Security  <0=> Secure state <1=> Non-Secure state
*/
#define SCR_USB_FS_MSC_NSEC_CFG      0x00000000
/*
// Master PrivOnly/UnPriv
//   <o.16>  USB_FS AP  <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_USB_FS_MSC_AP_CFG      0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize CM0 Bridge Master
*/
#define SCR_CM0_BRIDGE_MSC_INIT    1
/*
// Master Error Response
//   <o.16>  ErrorResponse    <0=> RAZ/WI <1=> Bus Error
*/
#define SCR_CM0_BRIDGE_MSC_RESP_CFG      0x00000000
/*
// Master Secure/NonSecure
//   <o.16>  CM0_BRIDGE Security  <0=> Secure state <1=> Non-Secure state
*/
#define SCR_CM0_BRIDGE_MSC_NSEC_CFG      0x00000000
/*
// Master PrivOnly/UnPriv
//   <o.16>  CM0_BRIDGE AP  <0=> Privilage Only <1=> Privilage & Unprivilage 
*/
#define SCR_CM0_BRIDGE_MSC_AP_CFG      0x00000000
/*
//   </e>
*/

/*
// </h>
*/
////////////////////////////////////////////////////////////////

/*
// <e>Setup behaviour of Sleep and Exception Handling
*/
#define SCB_CSR_AIRCR_INIT  1

/*
//   <o> Deep Sleep can be enabled by
//     <0=>Secure and Non-Secure state
//     <1=>Secure state only
//   <i> Value for SCB->CSR register bit DEEPSLEEPS
*/
#define SCB_CSR_DEEPSLEEPS_VAL  0

/*
//   <o>System reset request accessible from
//     <0=> Secure and Non-Secure state
//     <1=> Secure state only
//   <i> Value for SCB->AIRCR register bit SYSRESETREQS
*/
#define SCB_AIRCR_SYSRESETREQS_VAL  0
/*
//   <o>Priority of Non-Secure exceptions is
//     <0=> Not altered
//     <1=> Lowered to 0x04-0x07
//   <i> Value for SCB->AIRCR register bit PRIS
*/
#define SCB_AIRCR_PRIS_VAL      0

/*
//   <o>BusFault, HardFault, and NMI target
//     <0=> Secure state
//     <1=> Non-Secure state
//   <i> Value for SCB->AIRCR register bit BFHFNMINS
*/
#define SCB_AIRCR_BFHFNMINS_VAL 0

/*
// </e>
*/
/*
// <e>Setup behaviour of Floating Point Unit
*/
#define TZ_FPU_NS_USAGE 1

/*
// <o>Floating Point Unit usage
//     <0=> Secure state only
//     <3=> Secure and Non-Secure state
//   <i> Value for SCB->NSACR register bits CP10, CP11
*/
#define SCB_NSACR_CP10_11_VAL       3

/*
// <o>Treat floating-point registers as Secure
//     <0=> Disabled
//     <1=> Enabled
//   <i> Value for FPU->FPCCR register bit TS
*/
#define FPU_FPCCR_TS_VAL            0

/*
// <o>Clear on return (CLRONRET) accessibility
//     <0=> Secure and Non-Secure state
//     <1=> Secure state only
//   <i> Value for FPU->FPCCR register bit CLRONRETS
*/
#define FPU_FPCCR_CLRONRETS_VAL     0

/*
// <o>Clear floating-point caller saved registers on exception return
//     <0=> Disabled
//     <1=> Enabled
//   <i> Value for FPU->FPCCR register bit CLRONRET
*/
#define FPU_FPCCR_CLRONRET_VAL      1

/*
// </e>
*/
/*
// <h>Setup Interrupt Target
*/

/*
//   <e>Initialize ITNS 0 (Interrupts 0..31)
*/
#define NVIC_INIT_ITNS0    1
/*
// Interrupts 0..31
//   <o.0>  CM33_MAILBOX_IRQn    <0=> Secure state <1=> Non-Secure state
//   <o.1>  CM0_MAILBOX_IRQn     <0=> Secure state <1=> Non-Secure state
//   <o.4>  I2S0_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.5>  I2S1_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.6>  USB_HS_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.7>  USB_FS_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.8>  OSPI0_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.9>  OSPI1_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.10>  FLASHA_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.11>  FLASHB_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.12>  ISO78163_IRQn    <0=> Secure state <1=> Non-Secure state
//   <o.13>  MEM_ECC_IRQn        <0=> Secure state <1=> Non-Secure state
//   <o.14>  BTMR0_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.15>  BTMR1_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.16>  BTMR2_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.17>  BTMR3_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.18>  BPWM0_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.19>  BPWM1_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.20>  BPWM2_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.21>  BPWM3_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.22>  SDIO0_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.23>  SDIO1_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.24>  RNG_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.25>  EADC_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.26>  SCR_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.27>  CAN0_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.28>  CAN1_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.29>  ETMR0_UP_IRQn        <0=> Secure state <1=> Non-Secure state
//   <o.30>  ETMR0_BRK_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.31>  ETMR0_CC_IRQn        <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS0_VAL      0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize ITNS 1 (Interrupts 32..63)
*/
#define NVIC_INIT_ITNS1    1
/*
// Interrupts 32..63
//   <o.0>  ETMR0_TRG_COM_IRQn    <0=> Secure state <1=> Non-Secure state
//   <o.1>  ETMR1_UP_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.2>  ETMR1_BRK_IRQn        <0=> Secure state <1=> Non-Secure state
//   <o.3>  ETMR1_CC_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.4>  ETMR1_TRG_COM_IRQn    <0=> Secure state <1=> Non-Secure state
//   <o.5>  GTMR0_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.6>  GTMR1_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.7>  GTMR2_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.8>  GTMR3_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.9>  DMA0_CH0_IRQn        <0=> Secure state <1=> Non-Secure state
//   <o.10>  DMA0_CH1_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.11>  DMA0_CH2_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.12>  DMA0_CH3_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.13>  DMA0_CH4_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.14>  DMA0_CH5_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.15>  DMA0_CH6_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.16>  DMA0_CH7_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.19>  ADC0_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.20>  ADC1_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.21>  ENCENG_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.22>  MAC0_SBD_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.23>  MAC0_PMT_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.24>  MAC1_SBD_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.25>  MAC1_PMT_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.26>  DCMI_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.27>  CDMA_ADC_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.28>  FLEXCOMM0_IRQn      <0=> Secure state <1=> Non-Secure state
//   <o.29>  FLEXCOMM1_IRQn      <0=> Secure state <1=> Non-Secure state
//   <o.30>  FLEXCOMM2_IRQn      <0=> Secure state <1=> Non-Secure state
//   <o.31>  FLEXCOMM3_IRQn      <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS1_VAL      0x00000000
/*
//   </e>
*/


/*
//   <e>Initialize ITNS 2 (Interrupts 64..95)
*/
#define NVIC_INIT_ITNS2    1
/*
// Interrupts 64..95
//   <o.0>  FLEXCOMM4_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.1>  FLEXCOMM5_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.2>  FLEXCOMM6_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.3>  FLEXCOMM7_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.4>  FLEXCOMM8_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.5>  FLEXCOMM9_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.6>  FLEXCOMM10_IRQn      <0=> Secure state <1=> Non-Secure state
//   <o.7>  FLEXCOMM11_IRQn      <0=> Secure state <1=> Non-Secure state
//   <o.8>  FLEXCOMM12_IRQn      <0=> Secure state <1=> Non-Secure state
//   <o.9>  FLEXCOMM13_IRQn      <0=> Secure state <1=> Non-Secure state
//   <o.10>  DMA1_CH0_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.11>  DMA1_CH1_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.12>  DMA1_CH2_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.13>  DMA1_CH3_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.14>  DMA1_CH4_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.15>  DMA1_CH5_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.16>  DMA1_CH6_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.17>  DMA1_CH7_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.18>  EXTI0_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.19>  EXTI1_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.20>  EXTI2_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.21>  EXTI3_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.22>  EXTI4_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.23>  EXTI5_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.24>  EXTI6_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.25>  EXTI7_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.26>  EXTI8_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.27>  EXTI9_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.28>  EXTI10_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.29>  EXTI11_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.30>  EXTI12_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.31>  EXTI13_IRQn         <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS2_VAL      0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize ITNS 3 (Interrupts 96..127)
*/
#define NVIC_INIT_ITNS3    1
/*
// Interrupts 96..127
//   <o.0>  EXTI14_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.1>  EXTI15_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.2>  I2C14_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.3>  BDMA_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.4>  UART14_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.5>  UART15_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.6>  UART16_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.7>  UART17_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.8>  UART18_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.9>  UART19_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.10>  ISO78162_IRQn   <0=> Secure state <1=> Non-Secure state
//   <o.11>  ISO78163_IRQn   <0=> Secure state <1=> Non-Secure state
//   <o.12>  BTMR4_IRQn      <0=> Secure state <1=> Non-Secure state
//   <o.13>  BTMR5_IRQn      <0=> Secure state <1=> Non-Secure state
//   <o.14>  BTMR6_IRQn      <0=> Secure state <1=> Non-Secure state
//   <o.15>  BTMR7_IRQn      <0=> Secure state <1=> Non-Secure state
//   <o.16>  BPWM4_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.17>  BPWM5_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.18>  BPWM6_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.19>  BPWM7_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.20>  FLASH0_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.21>  BSPI0_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.22>  BSPI1_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.23>  BSPI2_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.24>  BSPI3_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.25>  BSPI4_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.26>  BSPI5_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.27>  HFM_COP_IRQn        <0=> Secure state <1=> Non-Secure state
//   <o.28>  RTC_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.29>  PMU_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.30>  RTC_ALM_IRQn        <0=> Secure state <1=> Non-Secure state
//   <o.31>  SYSCFGLP_ANA_IRQn  <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS3_VAL      0x00000000
/*
//   </e>
*/

/*
//   <e>Initialize ITNS 4 (Interrupts 128..130)
*/
#define NVIC_INIT_ITNS4    1
/*
// Interrupts 128..130
//   <o.0>  LPBTMR_IRQn          <0=> Secure state <125=> Non-Secure state
//   <o.2>  MPMU_COMP_IRQn       <0=> Secure state <126=> Non-Secure state
*/
#define NVIC_INIT_ITNS4_VAL      0x00000000
/*
//   </e>
*/

/*
// </h>
*/

/*
    max 8 SAU regions.
    SAU regions are defined in partition.h
 */

#define SAU_INIT_REGION(n) \
    SAU->RNR  =  (n                                     & SAU_RNR_REGION_Msk); \
    SAU->RBAR =  (SAU_INIT_START##n                     & SAU_RBAR_BADDR_Msk); \
    SAU->RLAR =  (SAU_INIT_END##n                       & SAU_RLAR_LADDR_Msk) | \
                ((SAU_INIT_NSC##n << SAU_RLAR_NSC_Pos)  & SAU_RLAR_NSC_Msk)   | 1U

#define FLASH_MPC_INIT(n) \
    MPC_FLASH##n->CTRL = 0x00000100UL; \
    MPC_FLASH##n->BLK_IDX = 0UL; \
    MPC_FLASH##n->BLK_LUT = FLASH##n##_MPC_CFG0; \
    MPC_FLASH##n->BLK_LUT = FLASH##n##_MPC_CFG1; \
    MPC_FLASH##n->BLK_LUT = FLASH##n##_MPC_CFG2; \
    MPC_FLASH##n->BLK_LUT = FLASH##n##_MPC_CFG3

#define SRAM_MPC_INIT(n) \
    MPC_SRAM33_##n->CTRL = 0x00000100UL; \
    MPC_SRAM33_##n->BLK_IDX = 0UL; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG0; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG1; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG2; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG3; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG4; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG5; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG6; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG7; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG8; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG9; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG10; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG11; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG12; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG13; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG14; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG15; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG16; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG17; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG18; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG19; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG20; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG21; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG22; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG23; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG24; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG25; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG26; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG27; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG28; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG29; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG30; \
    MPC_SRAM33_##n->BLK_LUT = SRAM##n##_MPC_CFG31

__STATIC_INLINE void TZ_SCR_PPC_Master_Init(void)
{
  /*- CM33 APB PPC configuration --------------------------------------*/
#if defined (SCR_APBPPC_INIT) && (SCR_APBPPC_INIT == 1U)
  
  SCR33->APB0PPC_RESP = SCR_APBPPC_RESP_CFG;
  
#if defined (SCR_APBPPC_NSEC_INIT0) && (SCR_APBPPC_NSEC_INIT0 == 1U)
  SCR33->APB0PPC_SEC = SCR_APBPPC_NSEC_CFG0;
#endif /* (SCR_APBPPC_NSEC_INIT0) && (SCR_APBPPC_NSEC_INIT0 == 1U) */
  
#if defined (SCR_APBPPC_NSEC_INIT1) && (SCR_APBPPC_NSEC_INIT1 == 1U)
  SCR33->APB0PPC_SEC1 = SCR_APBPPC_NSEC_CFG1;
#endif /* (SCR_APBPPC_NSEC_INIT1) && (SCR_APBPPC_NSEC_INIT1 == 1U) */
  
#if defined (SCR_APBPPC_AP_INIT0) && (SCR_APBPPC_AP_INIT0 == 1U)
  SCR33->APB0PPC_AP = SCR_APBPPC_AP_CFG0;
#endif /* (SCR_APBPPC_AP_INIT0) && (SCR_APBPPC_AP_INIT0 == 1U) */

#if defined (SCR_APBPPC_AP_INIT1) && (SCR_APBPPC_AP_INIT1 == 1U)
  SCR33->APB0PPC_AP1 = SCR_APBPPC_AP_CFG1;
#endif /* (SCR_APBPPC_AP_INIT1) && (SCR_APBPPC_AP_INIT1 == 1U) */

#endif /* (SCR_APBPPC_INIT) && (SCR_APBPPC_INIT == 1U) */

  /*- CM33 SYNC APB PPC configuration -----------------------------------*/
#if defined (SCR_APBPPC_SYNC_INIT) && (SCR_APBPPC_SYNC_INIT == 1U)

  SCR33->APB0PPC_SYNC_RESP = SCR_APBPPC_SYNC_RESP_CFG;
  
#if defined (SCR_APBPPC_SYNC_NSEC_INIT) && (SCR_APBPPC_SYNC_NSEC_INIT == 1U)
  SCR33->APB0PPC_SYNC_SEC = SCR_APBPPC_SYNC_NSEC_CFG;
#endif /* SCR_APBPPC_SYNC_NSEC_INIT) && (SCR_APBPPC_SYNC_NSEC_INIT == 1U) */

#if defined (SCR_APBPPC_SYNC_AP_INIT) && (SCR_APBPPC_SYNC_AP_INIT == 1U)
  SCR33->APB0PPC_SYNC_AP = SCR_APBPPC_SYNC_AP_CFG;
#endif /* SCR_APBPPC_SYNC_AP_INIT) && (SCR_APBPPC_SYNC_AP_INIT == 1U) */

#endif /* (SCR_APBPPC_SYNC_INIT) && (SCR_APBPPC_SYNC_INIT == 1U) */

  /*- CM33 DMA0 configuration -------------------------------------------*/
#if defined (SCR_DMA0_INIT) && (SCR_DMA0_INIT == 1U)

#if defined (SCR_DMA0_NSEC_INIT) && (SCR_DMA0_NSEC_INIT == 1U)
  SCR33->DMA0_SEC = SCR_DMA0_NSEC_CFG;
#endif /* SCR_DMA0_NSEC_INIT) && (SCR_DMA0_NSEC_INIT == 1U) */

#if defined (SCR_DMA0_AP_INIT) && (SCR_DMA0_AP_INIT == 1U)
  SCR33->DMA0_AP = SCR_DMA0_AP_CFG;
#endif /* SCR_DMA0_AP_INIT) && (SCR_DMA0_AP_INIT == 1U) */

#endif /* (SCR_DMA0_INIT) && (SCR_DMA0_INIT == 1U) */

  /*- CM33 DMA1 configuration -------------------------------------------*/
#if defined (SCR_DMA1_INIT) && (SCR_DMA1_INIT == 1U)

#if defined (SCR_DMA1_NSEC_INIT) && (SCR_DMA1_NSEC_INIT == 1U)
  SCR33->DMA1_SEC = SCR_DMA1_NSEC_CFG;
#endif /* SCR_DMA1_NSEC_INIT) && (SCR_DMA1_NSEC_INIT == 1U) */

#if defined (SCR_DMA1_AP_INIT) && (SCR_DMA1_AP_INIT == 1U)
  SCR33->DMA1_AP = SCR_DMA1_AP_CFG;
#endif /* SCR_DMA1_AP_INIT) && (SCR_DMA1_AP_INIT == 1U) */

#endif /* (SCR_DMA1_INIT) && (SCR_DMA1_INIT == 1U) */

  /*- CM33 MAC0 Master configuration -------------------------------------------*/
#if defined (SCR_MAC0_MSC_INIT) && (SCR_MAC0_MSC_INIT == 1U)
  SCR33->ETH0_SEC = SCR_MAC0_MSC_NSEC_CFG;
  SCR33->ETH0_AP = SCR_MAC0_MSC_AP_CFG;
#endif /* (SCR_MAC0_MSC_INIT) && (SCR_MAC0_MSC_INIT == 1U) */

  /*- CM33 MAC1 Master configuration -------------------------------------------*/
#if defined (SCR_MAC1_MSC_INIT) && (SCR_MAC1_MSC_INIT == 1U)
  SCR33->ETH1_SEC = SCR_MAC1_MSC_NSEC_CFG;
  SCR33->ETH1_AP = SCR_MAC1_MSC_AP_CFG;
#endif /* (SCR_MAC1_MSC_INIT) && (SCR_MAC1_MSC_INIT == 1U) */

  /*- CM33 ENCENG Master configuration -----------------------------------------*/
#if defined (SCR_ENCENG_MSC_INIT) && (SCR_ENCENG_MSC_INIT == 1U)
  SCR33->ENCENG_SEC = SCR_ENCENG_MSC_NSEC_CFG;
  SCR33->ENCENG_AP = SCR_ENCENG_MSC_AP_CFG;
#endif /* (SCR_ENCENG_MSC_INIT) && (SCR_ENCENG_MSC_INIT == 1U) */

  /*- CM33 SDIO0 Master configuration -----------------------------------------*/
#if defined (SCR_SDIO0_MSC_INIT) && (SCR_SDIO0_MSC_INIT == 1U)
  SCR33->SDIO0_SEC = SCR_SDIO0_MSC_NSEC_CFG;
  SCR33->SDIO0_AP = SCR_SDIO0_MSC_AP_CFG;
#endif /* (SCR_SDIO0_MSC_INIT) && (SCR_SDIO0_MSC_INIT == 1U) */

  /*- CM33 SDIO1 Master configuration -----------------------------------------*/
#if defined (SCR_SDIO1_MSC_INIT) && (SCR_SDIO1_MSC_INIT == 1U)
  SCR33->SDIO1_SEC = SCR_SDIO1_MSC_NSEC_CFG;
  SCR33->SDIO1_AP = SCR_SDIO1_MSC_AP_CFG;
#endif /* (SCR_SDIO1_MSC_INIT) && (SCR_SDIO1_MSC_INIT == 1U) */

  /*- CM33 OSPI0 Master configuration -----------------------------------------*/
#if defined (SCR_OSPI0_MSC_INIT) && (SCR_OSPI0_MSC_INIT == 1U)
  SCR33->OSPI0_RESP = SCR_OSPI0_MSC_RESP_CFG;
  SCR33->OSPI0_SEC = SCR_OSPI0_MSC_NSEC_CFG;
  SCR33->OSPI0_AP = SCR_OSPI0_MSC_AP_CFG;
#endif /* (SCR_OSPI0_MSC_INIT) && (SCR_OSPI0_MSC_INIT == 1U) */

  /*- CM33 OSPI1 Master configuration -----------------------------------------*/
#if defined (SCR_OSPI1_MSC_INIT) && (SCR_OSPI1_MSC_INIT == 1U)
  SCR33->OSPI1_RESP = SCR_OSPI1_MSC_RESP_CFG;
  SCR33->OSPI1_SEC = SCR_OSPI1_MSC_NSEC_CFG;
  SCR33->OSPI1_AP = SCR_OSPI1_MSC_AP_CFG;
#endif /* (SCR_OSPI1_MSC_INIT) && (SCR_OSPI1_MSC_INIT == 1U) */

  /*- CM33 HS USB Master configuration ---------------------------------------*/
#if defined (SCR_USB_HS_MSC_INIT) && (SCR_USB_HS_MSC_INIT == 1U)
  SCR33->USBHS_RESP = SCR_USB_HS_MSC_RESP_CFG;
  SCR33->USBHS_SEC = SCR_USB_HS_MSC_NSEC_CFG;
  SCR33->USBHS_AP = SCR_USB_HS_MSC_AP_CFG;
#endif /* (SCR_USB_HS_MSC_INIT) && (SCR_USB_HS_MSC_INIT == 1U) */

  /*- CM33 FS USB Master configuration ---------------------------------------*/
#if defined (SCR_USB_FS_MSC_INIT) && (SCR_USB_FS_MSC_INIT == 1U)
  SCR33->USBFS_RESP = SCR_USB_FS_MSC_RESP_CFG;
  SCR33->USBFS_SEC = SCR_USB_FS_MSC_NSEC_CFG;
  SCR33->USBFS_AP = SCR_USB_FS_MSC_AP_CFG;
#endif /* (SCR_USB_FS_MSC_INIT) && (SCR_USB_FS_MSC_INIT == 1U) */

  /*- CM0 Bridge Master configuration ---------------------------------------*/
#if defined (SCR_CM0_BRIDGE_MSC_INIT) && (SCR_CM0_BRIDGE_MSC_INIT == 1U)
  SCR33->M0BRIDGE_RESP = SCR_CM0_BRIDGE_MSC_RESP_CFG;
  SCR33->M0BRIDGE_SEC = SCR_CM0_BRIDGE_MSC_NSEC_CFG;
  SCR33->M0BRIDGE_AP = SCR_CM0_BRIDGE_MSC_AP_CFG;
#endif /* (SCR_CM0_BRIDGE_MSC_INIT) && (SCR_CM0_BRIDGE_MSC_INIT == 1U) */
  
  TZ_SCR_WAIT_IDLE();
}

/**
  \brief   Setup a SAU Region
  \details Writes the region information contained in SAU_Region to the
           registers SAU_RNR, SAU_RBAR, and SAU_RLAR
 */
__STATIC_INLINE void TZ_SAU_SCR_Init (void)
{

#if defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U)
  
  #if defined (SAU_INIT_REGION0) && (SAU_INIT_REGION0 == 1U)
    SAU_INIT_REGION(0);
  #endif

  #if defined (SAU_INIT_REGION1) && (SAU_INIT_REGION1 == 1U)
    SAU_INIT_REGION(1);
  #endif

  #if defined (SAU_INIT_REGION2) && (SAU_INIT_REGION2 == 1U)
    SAU_INIT_REGION(2);
  #endif

  #if defined (SAU_INIT_REGION3) && (SAU_INIT_REGION3 == 1U)
    SAU_INIT_REGION(3);
  #endif

  #if defined (SAU_INIT_REGION4) && (SAU_INIT_REGION4 == 1U)
    SAU_INIT_REGION(4);
  #endif

  #if defined (SAU_INIT_REGION5) && (SAU_INIT_REGION5 == 1U)
    SAU_INIT_REGION(5);
  #endif

  #if defined (SAU_INIT_REGION6) && (SAU_INIT_REGION6 == 1U)
    SAU_INIT_REGION(6);
  #endif

  #if defined (SAU_INIT_REGION7) && (SAU_INIT_REGION7 == 1U)
    SAU_INIT_REGION(7);
  #endif

  /* repeat this for all possible SAU regions */

#endif /* defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U) */

  #if defined (SAU_INIT_CTRL) && (SAU_INIT_CTRL == 1U)
    SAU->CTRL = ((SAU_INIT_CTRL_ENABLE << SAU_CTRL_ENABLE_Pos) & SAU_CTRL_ENABLE_Msk) |
                ((SAU_INIT_CTRL_ALLNS  << SAU_CTRL_ALLNS_Pos)  & SAU_CTRL_ALLNS_Msk)   ;
  #endif

  #if defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U)
    SCB->SCR   = (SCB->SCR   & ~(SCB_SCR_SLEEPDEEPS_Msk    )) |
                   ((SCB_CSR_DEEPSLEEPS_VAL     << SCB_SCR_SLEEPDEEPS_Pos)     & SCB_SCR_SLEEPDEEPS_Msk);

    SCB->AIRCR = (SCB->AIRCR & ~(SCB_AIRCR_VECTKEY_Msk   | SCB_AIRCR_SYSRESETREQS_Msk |
                                 SCB_AIRCR_BFHFNMINS_Msk | SCB_AIRCR_PRIS_Msk)        )                     |
                   ((0x05FAU                    << SCB_AIRCR_VECTKEY_Pos)      & SCB_AIRCR_VECTKEY_Msk)      |
                   ((SCB_AIRCR_SYSRESETREQS_VAL << SCB_AIRCR_SYSRESETREQS_Pos) & SCB_AIRCR_SYSRESETREQS_Msk) |
                   ((SCB_AIRCR_PRIS_VAL         << SCB_AIRCR_PRIS_Pos)         & SCB_AIRCR_PRIS_Msk)         |
                   ((SCB_AIRCR_BFHFNMINS_VAL    << SCB_AIRCR_BFHFNMINS_Pos)    & SCB_AIRCR_BFHFNMINS_Msk);
  #endif /* defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U) */
  
  /* Enable SCR clock */
  TZ_SCR_CLOCK_ENABLE();
  
#if defined (FLASHA_MPC_INIT) && (FLASHA_MPC_INIT == 1U)
  FLASH_MPC_INIT(A);
#endif /* defined (FLASHA_MPC_INIT) && (FLASHA_MPC_INIT == 1U) */
  
#if defined (FLASHB_MPC_INIT) && (FLASHB_MPC_INIT == 1U)
  FLASH_MPC_INIT(B);
#endif /* defined (FLASHB_MPC_INIT) && (FLASHB_MPC_INIT == 1U) */

#if defined (SRAM0_MPC_INIT) && (SRAM0_MPC_INIT == 1U)
  SRAM_MPC_INIT(0);
#endif /* defined (SRAM0_MPC_INIT) && (SRAM0_MPC_INIT == 1U) */

#if defined (SRAM1_MPC_INIT) && (SRAM1_MPC_INIT == 1U)
  SRAM_MPC_INIT(1);
#endif /* defined (SRAM1_MPC_INIT) && (SRAM1_MPC_INIT == 1U) */

#if defined (SRAM2_MPC_INIT) && (SRAM2_MPC_INIT == 1U)
  SRAM_MPC_INIT(2);
#endif /* defined (SRAM2_MPC_INIT) && (SRAM2_MPC_INIT == 1U) */

#if defined (SRAM3_MPC_INIT) && (SRAM3_MPC_INIT == 1U)
  SRAM_MPC_INIT(3);
#endif /* defined (SRAM3_MPC_INIT) && (SRAM3_MPC_INIT == 1U) */

  TZ_SCR_PPC_Master_Init();

  #if defined (__FPU_USED) && (__FPU_USED == 1U) && \
      defined (TZ_FPU_NS_USAGE) && (TZ_FPU_NS_USAGE == 1U)

    SCB->NSACR = (SCB->NSACR & ~(SCB_NSACR_CP10_Msk | SCB_NSACR_CP11_Msk)) |
                   ((SCB_NSACR_CP10_11_VAL << SCB_NSACR_CP10_Pos) & (SCB_NSACR_CP10_Msk | SCB_NSACR_CP11_Msk));

    FPU->FPCCR = (FPU->FPCCR & ~(FPU_FPCCR_TS_Msk | FPU_FPCCR_CLRONRETS_Msk | FPU_FPCCR_CLRONRET_Msk)) |
                   ((FPU_FPCCR_TS_VAL        << FPU_FPCCR_TS_Pos       ) & FPU_FPCCR_TS_Msk       ) |
                   ((FPU_FPCCR_CLRONRETS_VAL << FPU_FPCCR_CLRONRETS_Pos) & FPU_FPCCR_CLRONRETS_Msk) |
                   ((FPU_FPCCR_CLRONRET_VAL  << FPU_FPCCR_CLRONRET_Pos ) & FPU_FPCCR_CLRONRET_Msk );
  #endif

  #if defined (NVIC_INIT_ITNS0) && (NVIC_INIT_ITNS0 == 1U)
    NVIC->ITNS[0] = NVIC_INIT_ITNS0_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS1) && (NVIC_INIT_ITNS1 == 1U)
    NVIC->ITNS[1] = NVIC_INIT_ITNS1_VAL;
  #endif
  
  #if defined (NVIC_INIT_ITNS2) && (NVIC_INIT_ITNS2 == 1U)
    NVIC->ITNS[2] = NVIC_INIT_ITNS2_VAL;
  #endif
  
  #if defined (NVIC_INIT_ITNS3) && (NVIC_INIT_ITNS3 == 1U)
    NVIC->ITNS[3] = NVIC_INIT_ITNS3_VAL;
  #endif
  
  #if defined (NVIC_INIT_ITNS4) && (NVIC_INIT_ITNS4 == 1U)
    NVIC->ITNS[4] = NVIC_INIT_ITNS4_VAL;
  #endif
}

#endif /* __PARTITION_XXX_H */
