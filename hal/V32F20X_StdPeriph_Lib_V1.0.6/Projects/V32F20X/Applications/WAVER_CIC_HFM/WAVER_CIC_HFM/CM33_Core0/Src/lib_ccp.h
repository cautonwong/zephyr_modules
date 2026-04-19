/**
  ******************************************************************************
  * @file    lib_ccp.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief  
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef _LIB_CCP_H_
#define _LIB_CCP_H_

#include "arm_acle.h"
#include "target.h"

#define CASPER_BASE                                CRYPTO_BASE
#define CASPER                                     (0x200F0000)
#define PRINTF printf

/*! @file */
/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*!
 * @addtogroup casper_driver
 * @{
 */

/*! @name Driver version */
/*@{*/
/*! @brief CASPER driver version. Version 2.0.10.
 *
 * Current version: 2.0.10
 *
 * Change log:
 * - Version 2.0.0
 *   - Initial version
 * - Version 2.0.1
 *   - Bug fix KPSDK-24531 double_scalar_multiplication() result may be all zeroes for some specific input
 * - Version 2.0.2
 *   - Bug fix KPSDK-25015 CASPER_MEMCPY hard-fault on LPC55xx when both source and destination buffers are outside of
 * CASPER_RAM
 * - Version 2.0.3
 *   - Bug fix KPSDK-28107 RSUB, FILL and ZERO operations not implemented in enum _casper_operation.
 * - Version 2.0.4
 *   - For GCC compiler, enforce O1 optimize level, specifically to remove strict-aliasing option.
 *     This driver is very specific and requires -fno-strict-aliasing.
 * - Version 2.0.5
 *   - Fix sign-compare warning.
 * - Version 2.0.6
 *   - Fix IAR Pa082 warning.
 * - Version 2.0.7
 *   - Fix MISRA-C 2012 issue.
 * - Version 2.0.8
 *   - Add feature macro for CASPER_RAM_OFFSET.
 * - Version 2.0.9
 *   - Remove unused function Jac_oncurve().
 *   - Fix ECC384 build.
 * - Version 2.0.10
 *   - Fix MISRA-C 2012 issue.
 */
#define FSL_CASPER_DRIVER_VERSION (MAKE_VERSION(2, 0, 10))
/*@}*/

/** CASPER - Register Layout Typedef */
typedef struct {
  __IO uint32_t CFG;                               /**< Contains the offsets of AB and CD in the RAM., offset: 0x0 */
  __IO uint32_t CTRL;                             /**< Contains the opcode mode, iteration count, and result offset (in RAM) and also launches the accelerator. Note: with CP version: CTRL0 and CRTL1 can be written in one go with MCRR., offset: 0x4 */
  __IO uint32_t CIC_CFG;                           /**< CIC Config 0x08 */
  __IO uint32_t STATUS;                            /**< Indicates operational status and would contain the carry bit if used., offset: 0xC */
  __IO uint32_t INTENSET;                          /**< Sets interrupts, offset: 0x10 */
  __IO uint32_t INTENCLR;                          /**< Clears interrupts, offset: 0x14 */
  __I  uint32_t INTSTAT;                           /**< Interrupt status bits (mask of INTENSET and STATUS), offset: 0x18 */
  __IO uint32_t SRAMBADDR;                         /**< SRAM Base Address, offset: 0x1C */
} CASPER_Type;

/*! @brief CASPER operation
 *
 */
typedef enum _casper_operation
{
    kCASPER_OpMul6464NoSum = 0x01, /*! Walking 1 or more of J loop, doing r=a*b using 64x64=128*/
    kCASPER_OpMul6464Sum = 0x02, /*! Walking 1 or more of J loop, doing c,r=r+a*b using 64x64=128, but assume inner j loop*/
    kCASPER_OpMul6464FullSum = 0x03, /*! Walking 1 or more of J loop, doing c,r=r+a*b using 64x64=128, but sum all of w. */
    kCASPER_OpAdd64       = 0x08, /*! Walking add with off_AB, and in/out off_RES doing c,r=r+a+c using 64+64=65*/
    kCASPER_OpSub64       = 0x09, /*! Walking subtract with off_AB, and in/out off_RES doing r=r-a using 64-64=64, with last
                               borrow implicit if any*/
    kCASPER_OpCopy        = 0x14,  /*! Copy from ABoff to resoff, 64b at a time*/
    kCASPER_CIC_Integrate = 0xF0, /*! CIC Integrate */
    kCASPER_CIC_Comb      = 0xF1, /*! CIC Comb */
} casper_operation_t;

/*! @brief Algorithm used for CASPER operation */
typedef enum _casper_algo_t
{
    kCASPER_ECC_P256 = 0x01, /*!< ECC_P256*/
    kCASPER_ECC_P384 = 0x02, /*!< ECC_P384 */
    kCASPER_ECC_P521 = 0x03, /*!< ECC_P521 */
} casper_algo_t;

#define CASPER_CP           1
#define CASPER_CP_CFG       (0x0)
#define CASPER_CP_CTRL      (0x4)
#define CASPER_CP_CIC_CFG   (0x8)
#define CASPER_CP_STATUS    (0xC)
#define CASPER_CP_INTENSET  (0x10)
#define CASPER_CP_INTENCLR  (0x14)
#define CASPER_CP_INTSTAT   (0x18)
#define CASPER_CP_SRAMBADDR (0x1C)

/* ----------------------------------------------------------------------------
   -- CASPER Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CASPER_Register_Masks CASPER Register Masks
 * @{
 */

/*! ABBPAIR - Which bank-pair the offset ABOFF is within. This must be 0 if only 2-up
 *  0b0..Bank-pair 0 (1st)
 *  0b1..Bank-pair 1 (2nd)
 */
#define CASPER_CFG_ABOFF_MASK                  (0xFFFFU)
#define CASPER_CFG_ABOFF_SHIFT                 (0U)
/*! ABOFF - Word or DWord Offset of AB values, with B at [2]=0 and A at [2]=1 as far as the code
 *    sees (normally will be an interleaved bank so only sequential to AHB). Word offset only allowed
 *    if 32 bit operation. Ideally not in the same RAM as the CD values if 4-up
 */
#define CASPER_CFG_ABOFF(x)                    (((uint32_t)(((uint32_t)(x)) << CASPER_CFG_ABOFF_SHIFT)) & CASPER_CFG_ABOFF_MASK)

#define CASPER_CFG_CDOFF_MASK                  (0xFFFF0000U)
#define CASPER_CFG_CDOFF_SHIFT                 (16U)
/*! CDOFF - Word or DWord Offset of CD, with D at [2]=0 and C at [2]=1 as far as the code sees
 *    (normally will be an interleaved bank so only sequential to AHB). Word offset only allowed if 32
 *    bit operation. Ideally not in the same RAM as the AB values
 */
#define CASPER_CFG_CDOFF(x)                    (((uint32_t)(((uint32_t)(x)) << CASPER_CFG_CDOFF_SHIFT)) & CASPER_CFG_CDOFF_MASK)
/*! @} */

/*! @name CTRL - Contains the opcode mode, iteration count, and result offset (in RAM) and also launches the accelerator. Note: with CP version: CTRL0 and CRTL1 can be written in one go with MCRR. */
/*!  FOR MarsPlus it's "LOOP" 2021/6/1 */
/*! @{ */
#define CASPER_CTRL_ITER_MASK                   (0xFFU)
#define CASPER_CTRL_ITER_SHIFT                  (0U)
/*! ITER - Iteration counter. Is number_cycles - 1. write 0 means Does one cycle - does not iterate.
 */
#define CASPER_CTRL_ITER(x)                     (((uint32_t)(((uint32_t)(x)) << CASPER_CTRL_ITER_SHIFT)) & CASPER_CTRL_ITER_MASK)
#define CASPER_CTRL_MODE_MASK                   (0xFF00U)
#define CASPER_CTRL_MODE_SHIFT                  (8U)
/*! MODE - Operation mode to perform. write 0 means Accelerator is inactive. write others means accelerator is active.
 */
#define CASPER_CTRL_MODE(x)                     (((uint32_t)(((uint32_t)(x)) << CASPER_CTRL_MODE_SHIFT)) & CASPER_CTRL_MODE_MASK)
/*! RESBPAIR - Which bank-pair the offset RESOFF is within. This must be 0 if only 2-up. Ideally
 *    this is not the same bank as ABBPAIR (when 4-up supported)
 *  0b0..Bank-pair 0 (1st)
 *  0b1..Bank-pair 1 (2nd)
 */
#define CASPER_CTRL_RESOFF_MASK                 (0xFFFF0000U)
#define CASPER_CTRL_RESOFF_SHIFT                (16U)
/*! RESOFF - Word or DWord Offset of result. Word offset only allowed if 32 bit operation. Ideally
 *    not in the same RAM as the AB and CD values
 */
#define CASPER_CTRL_RESOFF(x)                   (((uint32_t)(((uint32_t)(x)) << CASPER_CTRL_RESOFF_SHIFT)) & CASPER_CTRL_RESOFF_MASK)

/*! @name STATUS - Indicates operational status and would contain the carry bit if used. */
/*! @{ */
#define CASPER_STATUS_DONE_MASK                  (0x1U)
#define CASPER_STATUS_DONE_SHIFT                 (0U)
/*! DONE - Indicates if the accelerator has finished an operation. Write 1 to clear, or write CTRL to clear.
 *  0b0..Busy or just cleared
 *  0b1..Completed last operation
 */
#define CASPER_STATUS_DONE(x)                    (((uint32_t)(((uint32_t)(x)) << CASPER_STATUS_DONE_SHIFT)) & CASPER_STATUS_DONE_MASK)
#define CASPER_STATUS_CARRY_MASK                 (0x10U)
#define CASPER_STATUS_CARRY_SHIFT                (4U)
/*! CARRY - Last carry value if operation produced a carry bit
 *  0b0..Carry was 0 or no carry
 *  0b1..Carry was 1
 */
#define CASPER_STATUS_CARRY(x)                   (((uint32_t)(((uint32_t)(x)) << CASPER_STATUS_CARRY_SHIFT)) & CASPER_STATUS_CARRY_MASK)
#define CASPER_STATUS_BUSY_MASK                  (0x20U)
#define CASPER_STATUS_BUSY_SHIFT                 (5U)
/*! BUSY - Indicates if the accelerator is busy performing an operation
 *  0b0..Not busy - is idle
 *  0b1..Is busy
 */
#define CASPER_STATUS_BUSY(x)                    (((uint32_t)(((uint32_t)(x)) << CASPER_STATUS_BUSY_SHIFT)) & CASPER_STATUS_BUSY_MASK)
/*! @} */

/*! @name INTENSET - Sets interrupts */
/*! @{ */
#define CASPER_INTENSET_DONE_MASK                (0x1U)
#define CASPER_INTENSET_DONE_SHIFT               (0U)
/*! DONE - Set if the accelerator should interrupt when done.
 *  0b0..Do not interrupt when done
 *  0b1..Interrupt when done
 */
#define CASPER_INTENSET_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << CASPER_INTENSET_DONE_SHIFT)) & CASPER_INTENSET_DONE_MASK)
/*! @} */

/*! @name INTENCLR - Clears interrupts */
/*! @{ */
#define CASPER_INTENCLR_DONE_MASK                (0x1U)
#define CASPER_INTENCLR_DONE_SHIFT               (0U)
/*! DONE - Written to clear an interrupt set with INTENSET.
 *  0b0..If written 0, ignored
 *  0b1..If written 1, do not Interrupt when done
 */
#define CASPER_INTENCLR_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << CASPER_INTENCLR_DONE_SHIFT)) & CASPER_INTENCLR_DONE_MASK)
/*! @} */

/*! @name INTSTAT - Interrupt status bits (mask of INTENSET and STATUS) */
/*! @{ */
#define CASPER_INTSTAT_DONE_MASK                 (0x1U)
#define CASPER_INTSTAT_DONE_SHIFT                (0U)
/*! DONE - If set, interrupt is caused by accelerator being done.
 *  0b0..Not caused by accelerator being done
 *  0b1..Caused by accelerator being done
 */
#define CASPER_INTSTAT_DONE(x)                   (((uint32_t)(((uint32_t)(x)) << CASPER_INTSTAT_DONE_SHIFT)) & CASPER_INTSTAT_DONE_MASK)

/*! @ CIC_Channel_Num - Just for 1bit input type of cic intergrate.It determines where to get the 32*1 bits from SRAM to calculate the integration.
 * If Channel_Num is x
 * the first  32 inputs is at CDOFFSET+0*4(x+1)
 * the second 32 inputs is at CDOFFSET+1*4(x+1)
 * the third  32 inputs is at CDOFFSET+2*4(x+1),etc
 */
#define CIC_CHANNEL_NUM(x)                    (((uint32_t)(((uint32_t)(x)) << CIC_CHANNEL_NUM_SHIFT)) & CIC_CHANNEL_NUM_MASK)
#define CIC_CHANNEL_NUM_MASK                      (0x38000000U)
#define CIC_CHANNEL_NUM_SHIFT                     (27U)

/*! @ CIC_Result_Length - the length of result(1,2,3,4......)
 * for integrate: input length = result length * decimation_rate
 */
#define CIC_RESULT_LENGTH(x)                    (((uint32_t)(((uint32_t)(x)) << CIC_RESULT_LENGTH_SHIFT)) & CIC_RESULT_LENGTH_MASK)
#define CIC_RESULT_LENGTH_MASK                      (0x7FE0000U)
#define CIC_RESULT_LENGTH_SHIFT                     (17U)

/*! @ Integrate_Type
 * 0 :1bit
 * 1 :32bit
 */
#define CIC_INTEGRATE_TYPE(x)                    (((uint32_t)(((uint32_t)(x)) << CIC_INTEGRATE_TYPE_SHIFT)) & CIC_INTEGRATE_TYPE_MASK)
#define CIC_INTEGRATE_TYPE_MASK                      (0x10000U)
#define CIC_INTEGRATE_TYPE_SHIFT                     (16U)

/*! @ Decimation_Offset
 * decimation_offset of integrate instruction
 * its value should be less than the decimation rate
 */
#define CIC_DECIMATION_OFFSET(x)                    (((uint32_t)(((uint32_t)(x)) << CIC_DECIMATION_OFFSET_SHIFT)) & CIC_DECIMATION_OFFSET_MASK)
#define CIC_DECIMATION_OFFSET_MASK                      (0xFFC0U)
#define CIC_DECIMATION_OFFSET_SHIFT                     (2U)

/*! @ Decimation_Rate
 * decimation rate of integrate instruction
 * x:decimation rate is power(2,x)
 * 0:mininum decimation rate is 1
 * 10: maxium decimation rate is 1024
 */
#define CIC_DECIMATION_RATE(x)                    (((uint32_t)(((uint32_t)(x)) << CIC_DECIMATION_RATE_SHIFT)) & CIC_DECIMATION_RATE_MASK)
#define CIC_DECIMATION_RATE_MASK                      (0x3CU)
#define CIC_DECIMATION_RATE_SHIFT                     (2U)

/*! @ CIC_Order
 * decimation rate of integrate instruction
 * x:decimation rate is power(2,x)
 * 0:mininum decimation rate is 1
 * 10: maxium decimation rate is 1024
 */
#define CIC_ORDER(x)                              (((uint32_t)(((uint32_t)(x)) << CIC_ORDER_SHIFT)) & CIC_ORDER_MASK)
#define CIC_ORDER_MASK                              (0x3U)
#define CIC_ORDER_SHIFT                             (0U)


/*! @} */
/*!
 * @}
 */ /* end of group CASPER_Register_Masks */
 
/* mcr (cp,  opc1, value, CRn, CRm, opc2) */
#define CASPER_Wr32b(value, off) __arm_mcr(CASPER_CP, 0, value, ((off >> 4)), (off), 0)
/* mrc(coproc, opc1, CRn, CRm, opc2) */
#define CASPER_Rd32b(off) __arm_mrc(CASPER_CP, 0, ((off >> 4)), (off), 0)


/*  The model for this algo is that it can be implemented for a fixed size RSA key */
/*  for max speed. If this is made into a variable (to allow varying size), then */
/*  it will be slower by a bit. */
/*  The file is compiled with N_bitlen passed in as number of bits of the RSA key */
/*  #define N_bitlen 2048 */
#define N_wordlen_max (4096U / 32U)

/* CASPER driver allows usage of 256 or 384 ECC, not both at once */
#define CASPER_ECC_P256 1
#define CASPER_ECC_P384 0

#if CASPER_ECC_P256
#define N_bitlen 256U
#endif /* CASPER_ECC_P256 */

#if CASPER_ECC_P384
#define N_bitlen 384U
#endif /* CASPER_ECC_P256 */

#define NUM_LIMBS (N_bitlen / 32U)

enum
{
    kCASPER_RamOffset_Result   = 0x0u,
    kCASPER_RamOffset_Base     = (N_wordlen_max + 8u),
    kCASPER_RamOffset_TempBase = (2u * N_wordlen_max + 16u),
    kCASPER_RamOffset_Modulus  = (kCASPER_RamOffset_TempBase + N_wordlen_max + 4u),
    kCASPER_RamOffset_M64      = 1022U,
};

typedef enum
{
    CIC_Integrate_1bit  = 0x00, /*!< integrate input date type is 1bit */
    CIC_Integrate_32bit = 0x01, /*!< integrate input date type is 32bit */
}CICIntegrate_TypeDef;

typedef enum
{
    CIC_Order_2 = 0x00, /*!< stage 2 */
    CIC_Order_3 = 0x01, /*!< stage 3 */
    CIC_Order_4 = 0x02, /*!< stage 4 */
    CIC_Order_5 = 0x03, /*!< stage 5 of the integrate or comb */
}CICOrder_TypeDef;

typedef struct 
{
    uint8_t ChannelNum;      /* 0~7 */
    uint32_t ResultLenth;      /* 0~1023 */
    CICIntegrate_TypeDef IntegrateType;    /* 1bit/32bit */
    uint32_t DecimationOffset; /* less than rate */
    uint32_t DecimationRate;  /*  */
    CICOrder_TypeDef Order;            /* 0~3  */
}CIC_InitType;

/*! @} */

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @addtogroup casper_driver
 * @{
 */

/*!
 * @brief Enables clock and disables reset for CASPER peripheral.
 *
 * Enable clock and disable reset for CASPER.
 *
 * @param base CASPER base address
 */
//void CASPER_Init(CASPER_Type *base);
void CASPER_Init(uint32_t base);

/*!
 * @brief Disables clock for CASPER peripheral.
 *
 * Disable clock and enable reset.
 *
 * @param base CASPER base address
 */
void CASPER_Deinit(CASPER_Type *base);

/*!
 *@}
 */ /* end of casper_driver */

/*******************************************************************************
 * PKHA API
 ******************************************************************************/

/*!
 * @addtogroup casper_driver_pkha
 * @{
 */

/*!
 * @brief Performs modular exponentiation - (A^E) mod N.
 *
 * This function performs modular exponentiation.
 *
 * @param base CASPER base address
 * @param signature first addend (in little endian format)
 * @param pubN modulus (in little endian format)
 * @param wordLen Size of pubN in bytes
 * @param pubE exponent
 * @param[out] plaintext Output array to store result of operation (in little endian format)
 */
void CASPER_ModExp(CASPER_Type *base, 
                   const uint8_t *signature, 
                   size_t signatureWordLen, 
                   const uint8_t *pubN, 
                   size_t wordLen, 
                   const uint8_t * pubE, 
                   size_t pubELen, 
                   uint8_t *plaintext);

/*!
 * @brief Initialize prime modulus mod in Casper memory .
 *
 * Set the prime modulus mod in Casper memory and set N_wordlen
 * according to selected algorithm.
 *
 * @param curve elliptic curve algoritm
 */
void CASPER_ecc_init(casper_algo_t curve);

/*!
 * @brief Performs ECC secp256r1 point single scalar multiplication
 *
 * This function performs ECC secp256r1 point single scalar multiplication
 * [resX; resY] = scalar * [X; Y]
 * Coordinates are affine in normal form, little endian.
 * Scalars are little endian.
 * All arrays are little endian byte arrays, uint32_t type is used
 * only to enforce the 32-bit alignment (0-mod-4 address).
 *
 * @param base CASPER base address
 * @param[out] resX Output X affine coordinate in normal form, little endian.
 * @param[out] resY Output Y affine coordinate in normal form, little endian.
 * @param X Input X affine coordinate in normal form, little endian.
 * @param Y Input Y affine coordinate in normal form, little endian.
 * @param scalar Input scalar integer, in normal form, little endian.
 */
void CASPER_ECC_SECP256R1_Mul(
    CASPER_Type *base, uint32_t resX[8], uint32_t resY[8], uint32_t X[8], uint32_t Y[8], uint32_t scalar[8]);

/*!
 * @brief Performs ECC secp256r1 point double scalar multiplication
 *
 * This function performs ECC secp256r1 point double scalar multiplication
 * [resX; resY] = scalar1 * [X1; Y1] + scalar2 * [X2; Y2]
 * Coordinates are affine in normal form, little endian.
 * Scalars are little endian.
 * All arrays are little endian byte arrays, uint32_t type is used
 * only to enforce the 32-bit alignment (0-mod-4 address).
 *
 * @param base CASPER base address
 * @param[out] resX Output X affine coordinate.
 * @param[out] resY Output Y affine coordinate.
 * @param X1 Input X1 affine coordinate.
 * @param Y1 Input Y1 affine coordinate.
 * @param scalar1 Input scalar1 integer.
 * @param X2 Input X2 affine coordinate.
 * @param Y2 Input Y2 affine coordinate.
 * @param scalar2 Input scalar2 integer.
 */
void CASPER_ECC_SECP256R1_MulAdd(CASPER_Type *base,
                                 uint32_t resX[8],
                                 uint32_t resY[8],
                                 uint32_t X1[8],
                                 uint32_t Y1[8],
                                 uint32_t scalar1[8],
                                 uint32_t X2[8],
                                 uint32_t Y2[8],
                                 uint32_t scalar2[8]);

/*!
 * @brief Performs ECC secp384r1 point single scalar multiplication
 *
 * This function performs ECC secp384r1 point single scalar multiplication
 * [resX; resY] = scalar * [X; Y]
 * Coordinates are affine in normal form, little endian.
 * Scalars are little endian.
 * All arrays are little endian byte arrays, uint32_t type is used
 * only to enforce the 32-bit alignment (0-mod-4 address).
 *
 * @param base CASPER base address
 * @param[out] resX Output X affine coordinate in normal form, little endian.
 * @param[out] resY Output Y affine coordinate in normal form, little endian.
 * @param X Input X affine coordinate in normal form, little endian.
 * @param Y Input Y affine coordinate in normal form, little endian.
 * @param scalar Input scalar integer, in normal form, little endian.
 */
void CASPER_ECC_SECP384R1_Mul(
    CASPER_Type *base, uint32_t resX[12], uint32_t resY[12], uint32_t X[12], uint32_t Y[12], uint32_t scalar[12]);

/*!
 * @brief Performs ECC secp384r1 point double scalar multiplication
 *
 * This function performs ECC secp384r1 point double scalar multiplication
 * [resX; resY] = scalar1 * [X1; Y1] + scalar2 * [X2; Y2]
 * Coordinates are affine in normal form, little endian.
 * Scalars are little endian.
 * All arrays are little endian byte arrays, uint32_t type is used
 * only to enforce the 32-bit alignment (0-mod-4 address).
 *
 * @param base CASPER base address
 * @param[out] resX Output X affine coordinate.
 * @param[out] resY Output Y affine coordinate.
 * @param X1 Input X1 affine coordinate.
 * @param Y1 Input Y1 affine coordinate.
 * @param scalar1 Input scalar1 integer.
 * @param X2 Input X2 affine coordinate.
 * @param Y2 Input Y2 affine coordinate.
 * @param scalar2 Input scalar2 integer.
 */
void CASPER_ECC_SECP384R1_MulAdd(CASPER_Type *base,
                                 uint32_t resX[12],
                                 uint32_t resY[12],
                                 uint32_t X1[12],
                                 uint32_t Y1[12],
                                 uint32_t scalar1[12],
                                 uint32_t X2[12],
                                 uint32_t Y2[12],
                                 uint32_t scalar2[12]);

void CASPER_ECC_SECP521R1_MulAdd(CASPER_Type *base,
                                 uint32_t resX[18],
                                 uint32_t resY[18],
                                 uint32_t X1[18],
                                 uint32_t Y1[18],
                                 uint32_t scalar1[18],
                                 uint32_t X2[18],
                                 uint32_t Y2[18],
                                 uint32_t scalar2[18]);

void CASPER_ECC_SECP521R1_Mul(CASPER_Type *base, 
                              uint32_t resX[18], 
                              uint32_t resY[18], 
                              uint32_t X[18], 
                              uint32_t Y[18], 
                              uint32_t scalar[18]);

void CASPER_ECC_equal(int *res, uint32_t *op1, uint32_t *op2);
void CASPER_ECC_equal_to_zero(int *res, uint32_t *op1);
uint32_t CA_MK_OFF(const void *addr);
uint32_t Accel_IterOpcodeResaddr(uint32_t iter, uint32_t opcode, uint32_t resAddr);
uint32_t Accel_CIC_Config(CIC_InitType* CIC_InitStruct);

int CASPER_ModSub1(uint8_t *A, uint32_t sizeA, uint8_t *B, uint32_t sizeB, uint8_t *C);
int CASPER_ModMul(uint8_t *A, uint32_t sizeA, uint8_t *B, uint32_t sizeB, uint8_t *C);
int CASPER_ModAdd(uint8_t *A, uint32_t sizeA, uint8_t *B, uint32_t sizeB, uint8_t *C);
/*!
 *@}
 */ /* end of casper_driver_pkha */

#if defined(__cplusplus)
}
#endif

#endif /* _LIB_CCP_H_ */
