;/**
;* @file    startup_target_cm0.S
;* @author  Application Team
;* @version V1.0.0
;* @date    2021-09-10
;* @brief   Target Devices vector table.
;******************************************************************************/
;* <<< Use Configuration Wizard in Context Menu >>>
;
; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x000000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000400

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                
                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     PMU_IRQHandler            ;  0:  PMU
                DCD     I2C14_IRQHandler          ;  1:  I2C14
                DCD     BDMA_IRQHandler           ;  2:  BDMA
                DCD     UART14_IRQHandler         ;  3:  UART14
                DCD     UART15_IRQHandler         ;  4:  UART15
                DCD     UART16_IRQHandler         ;  5:  UART16
                DCD     UART17_IRQHandler         ;  6:  UART17
                DCD     UART18_IRQHandler         ;  7:  UART18
                DCD     UART19_IRQHandler         ;  8:  UART19
                DCD     ISO78162_IRQHandler       ;  9:  ISO7816 2
                DCD     ISO78163_IRQHandler       ; 10:  ISO7816 3
                DCD     MEM_ECC_IRQHandler        ; 11:  Memory ECC
                DCD     BTMR4_5_IRQHandler        ; 12:  BTMR4 and BTMR5
                DCD     BTMR6_IRQHandler          ; 13:  BTMR6
                DCD     BTMR7_IRQHandler          ; 14:  BTMR7
                DCD     BPWM4_IRQHandler          ; 15:  BPWM4
                DCD     BPWM5_IRQHandler          ; 16:  BPWM5
                DCD     BPWM6_IRQHandler          ; 17:  BPWM6
                DCD     BPWM7_IRQHandler          ; 18:  BPWM7
                DCD     HFM_COP_IRQHandler        ; 19:  HFM
                DCD     BSPI0_IRQHandler          ; 20:  BSPI0
                DCD     BSPI1_IRQHandler          ; 21:  BSPI1
                DCD     BSPI2_IRQHandler          ; 22:  BSPI2
                DCD     BSPI3_IRQHandler          ; 23:  BSPI3
                DCD     BSPI4_IRQHandler          ; 24:  BSPI4
                DCD     BSPI5_IRQHandler          ; 25:  BSPI5
                DCD     FLASH0_IRQHandler         ; 26:  FLASH0
                DCD     RTC_RTCALM_IRQHandler     ; 27:  RTC and RTC_ALM
                DCD     MAILBOX_IRQHandler        ; 28:  Mailbox CM0
                DCD     GPIO_IRQHandler           ; 29:  IO
                DCD     SYSCFGLP_ANA_CMP_IRQHandler ; 30:  SYSCFGLP_ANA_CMP
                DCD     LPBTMR_IRQHandler          ; 31:  LPBTMR
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset Handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


                AREA    |.text|, CODE, READONLY

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  PMU_IRQHandler           [WEAK]
                EXPORT  I2C14_IRQHandler         [WEAK]
                EXPORT  BDMA_IRQHandler          [WEAK]
                EXPORT  UART14_IRQHandler        [WEAK]
                EXPORT  UART15_IRQHandler        [WEAK]
                EXPORT  UART16_IRQHandler        [WEAK]
                EXPORT  UART17_IRQHandler        [WEAK]
                EXPORT  UART18_IRQHandler        [WEAK]
                EXPORT  UART19_IRQHandler        [WEAK]
                EXPORT  ISO78162_IRQHandler      [WEAK]
                EXPORT  ISO78163_IRQHandler      [WEAK]
                EXPORT  MEM_ECC_IRQHandler       [WEAK]
                EXPORT  BTMR4_5_IRQHandler       [WEAK]
                EXPORT  BTMR6_IRQHandler         [WEAK]
                EXPORT  BTMR7_IRQHandler         [WEAK]
                EXPORT  BPWM4_IRQHandler         [WEAK]
                EXPORT  BPWM5_IRQHandler         [WEAK]
                EXPORT  BPWM6_IRQHandler         [WEAK]
                EXPORT  BPWM7_IRQHandler         [WEAK]
                EXPORT  HFM_COP_IRQHandler       [WEAK]
                EXPORT  BSPI0_IRQHandler         [WEAK]
                EXPORT  BSPI1_IRQHandler         [WEAK]
                EXPORT  BSPI2_IRQHandler         [WEAK]
                EXPORT  BSPI3_IRQHandler         [WEAK]
                EXPORT  BSPI4_IRQHandler         [WEAK]
                EXPORT  BSPI5_IRQHandler         [WEAK]
                EXPORT  FLASH0_IRQHandler        [WEAK]
                EXPORT  RTC_RTCALM_IRQHandler    [WEAK]
                EXPORT  MAILBOX_IRQHandler       [WEAK]
                EXPORT  GPIO_IRQHandler          [WEAK]
                EXPORT  SYSCFGLP_ANA_CMP_IRQHandler [WEAK]
                EXPORT  LPBTMR_IRQHandler        [WEAK]
PMU_IRQHandler
I2C14_IRQHandler
BDMA_IRQHandler
UART14_IRQHandler
UART15_IRQHandler
UART16_IRQHandler
UART17_IRQHandler
UART18_IRQHandler
UART19_IRQHandler
ISO78162_IRQHandler
ISO78163_IRQHandler
MEM_ECC_IRQHandler
BTMR4_5_IRQHandler
BTMR6_IRQHandler
BTMR7_IRQHandler
BPWM4_IRQHandler
BPWM5_IRQHandler
BPWM6_IRQHandler
BPWM7_IRQHandler
HFM_COP_IRQHandler
BSPI0_IRQHandler
BSPI1_IRQHandler
BSPI2_IRQHandler
BSPI3_IRQHandler
BSPI4_IRQHandler
BSPI5_IRQHandler
FLASH0_IRQHandler
RTC_RTCALM_IRQHandler
MAILBOX_IRQHandler
GPIO_IRQHandler
SYSCFGLP_ANA_CMP_IRQHandler
LPBTMR_IRQHandler
                B       .

                ENDP


                ALIGN




; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF

                END

/*********************************** END OF FILE ******************************/
