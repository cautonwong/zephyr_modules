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
                DCD     I2C0_IRQHandler           ;  1:  I2C0
                DCD     DMA0_IRQHandler           ;  2:  DMA
                DCD     UART0_IRQHandler          ;  3:  UART0
                DCD     UART1_IRQHandler          ;  4:  UART1
                DCD     UART2_IRQHandler          ;  5:  UART2
                DCD     UART3_IRQHandler          ;  6:  UART3
                DCD     UART4_IRQHandler          ;  7:  UART4
                DCD     UART5_IRQHandler          ;  8:  UART5
                DCD     ISO78160_IRQHandler       ;  9:  ISO7816 0
                DCD     ISO78161_IRQHandler       ; 10:  ISO7816 1
                DCD     MEM_ECC_IRQHandler        ; 11:  Memory ECC
                DCD     BTMR0_1_IRQHandler        ; 12:  BTMR0 and BTMR1
                DCD     BTMR2_IRQHandler          ; 13:  BTMR2
                DCD     BTMR3_IRQHandler          ; 14:  BTMR3
                DCD     BPWM0_IRQHandler          ; 15:  BPWM0
                DCD     BPWM1_IRQHandler          ; 16:  BPWM1
                DCD     BPWM2_IRQHandler          ; 17:  BPWM2
                DCD     BPWM3_IRQHandler          ; 18:  BPWM3
                DCD     HFM_COP_IRQHandler        ; 19:  HFM
                DCD     SPI0_IRQHandler           ; 20:  SPI0
                DCD     SPI1_IRQHandler           ; 21:  SPI1
                DCD     SPI2_IRQHandler           ; 22:  SPI2
                DCD     SPI3_IRQHandler           ; 23:  SPI3
                DCD     SPI4_IRQHandler           ; 24:  SPI4
                DCD     SPI5_IRQHandler           ; 25:  SPI5
                DCD     FLASH0_IRQHandler         ; 26:  FLASH0
                DCD     RTC_RTCALM_IRQHandler     ; 27:  RTC and RTC_ALM
                DCD     MAILBOX_IRQHandler        ; 28:  Mailbox CM0
                DCD     GPIO_IRQHandler           ; 29:  IO
                DCD     SYSCON_LP_ANA_CMP_IRQHandler ; 30:  SYSCON_LP_ANA_CMP
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
                EXPORT  I2C0_IRQHandler          [WEAK]
                EXPORT  DMA0_IRQHandler          [WEAK]
                EXPORT  UART0_IRQHandler         [WEAK]
                EXPORT  UART1_IRQHandler         [WEAK]
                EXPORT  UART2_IRQHandler         [WEAK]
                EXPORT  UART3_IRQHandler         [WEAK]
                EXPORT  UART4_IRQHandler         [WEAK]
                EXPORT  UART5_IRQHandler         [WEAK]
                EXPORT  ISO78160_IRQHandler      [WEAK]
                EXPORT  ISO78161_IRQHandler      [WEAK]
                EXPORT  MEM_ECC_IRQHandler       [WEAK]
                EXPORT  BTMR0_1_IRQHandler       [WEAK]
                EXPORT  BTMR2_IRQHandler         [WEAK]
                EXPORT  BTMR3_IRQHandler         [WEAK]
                EXPORT  BPWM0_IRQHandler         [WEAK]
                EXPORT  BPWM1_IRQHandler         [WEAK]
                EXPORT  BPWM2_IRQHandler         [WEAK]
                EXPORT  BPWM3_IRQHandler         [WEAK]
                EXPORT  HFM_COP_IRQHandler       [WEAK]
                EXPORT  SPI0_IRQHandler          [WEAK]
                EXPORT  SPI1_IRQHandler          [WEAK]
                EXPORT  SPI2_IRQHandler          [WEAK]
                EXPORT  SPI3_IRQHandler          [WEAK]
                EXPORT  SPI4_IRQHandler          [WEAK]
                EXPORT  SPI5_IRQHandler          [WEAK]
                EXPORT  FLASH0_IRQHandler        [WEAK]
                EXPORT  RTC_RTCALM_IRQHandler    [WEAK]
                EXPORT  MAILBOX_IRQHandler       [WEAK]
                EXPORT  GPIO_IRQHandler          [WEAK]
                EXPORT  SYSCON_LP_ANA_CMP_IRQHandler [WEAK]
                EXPORT  LPBTMR_IRQHandler        [WEAK]
PMU_IRQHandler
I2C0_IRQHandler
DMA0_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
ISO78160_IRQHandler
ISO78161_IRQHandler
MEM_ECC_IRQHandler
BTMR0_1_IRQHandler
BTMR2_IRQHandler
BTMR3_IRQHandler
BPWM0_IRQHandler
BPWM1_IRQHandler
BPWM2_IRQHandler
BPWM3_IRQHandler
HFM_COP_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
SPI3_IRQHandler
SPI4_IRQHandler
SPI5_IRQHandler
FLASH0_IRQHandler
RTC_RTCALM_IRQHandler
MAILBOX_IRQHandler
GPIO_IRQHandler
SYSCON_LP_ANA_CMP_IRQHandler
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
