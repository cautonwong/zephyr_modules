/**
  * @file    std_def.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   std_def.
******************************************************************************/

#ifndef __STD_DEF_H
#define __STD_DEF_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
#include <arm_cmse.h>
#endif

#include <stddef.h>
#include <stdint.h>

/* Exported macros -----------------------------------------------------------*/

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
  #ifndef __weak
    #define __weak  __attribute__((weak))
  #endif
  #ifndef __packed
    #define __packed  __attribute__((packed))
  #endif
#elif defined (__GNUC__) /* GNU Compiler */
  #ifndef __weak
    #define __weak  __attribute__((weak))
  #endif /* __weak */
  #ifndef __packed
    #define __packed  __attribute__((__packed__))
  #endif /* __packed */
#endif /* __GNUC__ */

/* Macro to get variable aligned on 4-bytes, for __ICCARM__ the directive "#pragma data_alignment=4" must be used instead */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
  #ifndef __ALIGN_BEGIN
    #define __ALIGN_BEGIN
  #endif
  #ifndef __ALIGN_END
    #define __ALIGN_END  __attribute__((aligned (4)))
  #endif
#elif defined (__GNUC__) /* GNU Compiler */
  #ifndef __ALIGN_END
    #define __ALIGN_END  __attribute__((aligned (4)))
  #endif /* __ALIGN_END */
  #ifndef __ALIGN_BEGIN
    #define __ALIGN_BEGIN
  #endif /* __ALIGN_BEGIN */
#else
  #ifndef __ALIGN_END
    #define __ALIGN_END
  #endif /* __ALIGN_END */
  #ifndef __ALIGN_BEGIN
    #if defined (__ICCARM__)    /* IAR Compiler */
      #define __ALIGN_BEGIN
    #endif /* __ICCARM__ */
  #endif /* __ALIGN_BEGIN */
#endif /* __GNUC__ */

/**
  * @brief  __RAM_FUNC definition
  */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
/* ARM Compiler V6
   ---------------
   RAM functions are defined using the toolchain options.
   Functions that are executed in RAM should reside in a separate source module.
   Using the 'Options for File' dialog you can simply change the 'Code / Const'
   area of a module to a memory space in physical RAM.
   Available memory areas are declared in the 'Target' tab of the 'Options for Target'
   dialog.
*/
#define __RAM_FUNC __attribute((used))

#elif defined (__ICCARM__)
/* ICCARM Compiler
   ---------------
   RAM functions are defined using a specific toolchain keyword "__ramfunc".
*/
#define __RAM_FUNC  __ramfunc

#elif defined (__GNUC__)
/* GNU Compiler
   ------------
  RAM functions are defined using a specific toolchain attribute
   "__attribute__((section(".RamFunc")))".
*/
#define __RAM_FUNC  __attribute__((section(".RamFunc")))

#endif

/**
  * @brief  __NOINLINE definition
  */
#if (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || defined (__GNUC__)
/* ARM V6 & GNU Compiler
   ---------------------
*/
#define __NOINLINE __attribute__((noinline))

#elif defined (__ICCARM__)
/* ICCARM Compiler
   ---------------
*/
#define __NOINLINE _Pragma("optimize = no_inline")

#endif

#define BIT0        0x00000001
#define BIT1        0x00000002
#define BIT2        0x00000004
#define BIT3        0x00000008
#define BIT4        0x00000010
#define BIT5        0x00000020
#define BIT6        0x00000040
#define BIT7        0x00000080
#define BIT8        0x00000100
#define BIT9        0x00000200
#define BIT10       0x00000400
#define BIT11       0x00000800
#define BIT12       0x00001000
#define BIT13       0x00002000
#define BIT14       0x00004000
#define BIT15       0x00008000
#define BIT16       0x00010000
#define BIT17       0x00020000
#define BIT18       0x00040000
#define BIT19       0x00080000
#define BIT20       0x00100000
#define BIT21       0x00200000
#define BIT22       0x00400000
#define BIT23       0x00800000
#define BIT24       0x01000000
#define BIT25       0x02000000
#define BIT26       0x04000000
#define BIT27       0x08000000
#define BIT28       0x10000000
#define BIT29       0x20000000
#define BIT30       0x40000000
#define BIT31       0x80000000

#define UNUSED(X)             (void)X      /* To avoid gcc/g++ warnings */

#define REG_BIT_NOT(x)        (~(x))
#define IS_BIT_SET(REG, BIT)  (((REG) & (BIT)) == (BIT))
#define IS_BIT_CLR(REG, BIT)  (((REG) & (BIT)) == 0U)
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define NOR_BIT(REG, BIT)     ((REG) ^= (BIT))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define WRITE_MEM32(MEM, VAL) ((*(__IO uint32_t *)(MEM)) = (VAL))
#define WRITE_MEM16(MEM, VAL) ((*(__IO uint16_t *)(MEM)) = (VAL))
#define WRITE_MEM8(MEM, VAL)  ((*(__IO uint8_t *)(MEM)) = (VAL))

#define READ_MEM32(MEM)       (*(__IO uint32_t *)(MEM))
#define READ_MEM16(MEM)       (*(__IO uint16_t *)(MEM))
#define READ_MEM8(MEM)        (*(__IO uint8_t *)(MEM))

typedef enum {RESET = 0, SET = !RESET} BitAction, FlagStatus, ITStatus,INTStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))
#define IS_BIT_ACTION(ACTION) (((ACTION) == RESET) || ((ACTION) == SET))

/**
  * @brief  STD Status structures definition
  */
typedef enum
{
  STD_OK       = 0x00,
  STD_ERROR    = 0x01,
  STD_BUSY     = 0x02,
  STD_TIMEOUT  = 0x03
} STD_StatusType;

/** 
  * @brief  STD Lock structures definition  
  */
typedef enum 
{
  STD_UNLOCKED = 0x00U,
  STD_LOCKED   = 0x01U  
} STD_LockType;

#if (USE_RTOS == 1U)
  /* Reserved for future use */
  #error "USE_RTOS should be 0 in the current STD release"
#else
  #define __STD_LOCK(__HANDLE__)                                           \
                                do{                                        \
                                    if((__HANDLE__)->Lock == STD_LOCKED)   \
                                    {                                      \
                                       return STD_BUSY;                    \
                                    }                                      \
                                    else                                   \
                                    {                                      \
                                       (__HANDLE__)->Lock = STD_LOCKED;    \
                                    }                                      \
                                  }while (0U)

  #define __STD_UNLOCK(__HANDLE__)                                          \
                                  do{                                       \
                                      (__HANDLE__)->Lock = STD_UNLOCKED;    \
                                    }while (0U)
#endif /* USE_RTOS */


#ifdef __cplusplus
}
#endif     

#endif /* __STD_DEF_H */

/*********************************** END OF FILE ******************************/