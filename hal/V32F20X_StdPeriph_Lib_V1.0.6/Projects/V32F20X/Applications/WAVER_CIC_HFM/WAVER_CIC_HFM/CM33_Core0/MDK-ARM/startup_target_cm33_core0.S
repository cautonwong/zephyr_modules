;* ---------------------------------------------------------------------------------------
;* @file:    startup_target_cm33_core0.s
;* @purpose: CMSIS Cortex-M33 Core0 Device Startup File
;* @version: 1.0.0
;* @date:    2021-09-10
;* ---------------------------------------------------------------------------------------*/
;* <<< Use Configuration Wizard in Context Menu >>>
;
; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00004000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00004000

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
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     SecureFault_Handler       ; Secure Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; Cortex-M33 External Interrupts (#0~97)
                DCD     CM33_MAILBOX_IRQHandler   ; CM33_MAILBOX global interrupts         
                DCD     CM0_MAILBOX_IRQHandler    ; CM0_MAILBOX global interrupts
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     I2S0_IRQHandle            ; I2S0
                DCD     I2S1_IRQHandler           ; I2S1
                DCD     USB_HS_IRQHandler         ; USB HS
                DCD     USB_FS_IRQHandler         ; USB FS
                DCD     SSI0_IRQHandler           ; SSI0
                DCD     SSI1_IRQHandler           ; SSI1
                DCD     FLASHA_IRQHandler         ; FLASHA
                DCD     FLASHB_IRQHandler         ; FLASHB
                DCD     ISO7816_0_1_IRQHandler    ; ISO7816 0/1
                DCD     MEM_ECC_IRQHandler        ; Memory ECC global interrupts
                DCD     BTMR0_IRQHandler          ; BTMR0
                DCD     BTMR1_IRQHandler          ; BTMR1
                DCD     BTMR2_IRQHandler          ; BTMR2
                DCD     BTMR3_IRQHandler          ; BTMR3
                DCD     BPWM0_IRQHandler          ; BPWM0
                DCD     BPWM1_IRQHandler          ; BPWM1
                DCD     BPWM2_IRQHandler          ; BPWM2
                DCD     BPWM3_IRQHandler          ; BPWM3
                DCD     SDIO0_IRQHandler          ; SDIO0
                DCD     SDIO1_IRQHandler          ; SDIO1
                DCD     RNG_IRQHandler            ; RNG
                DCD     EADC_IRQHandler           ; EADC
                DCD     SCR_IRQHandler            ; SCR global interrupts
                DCD     CAN0_IRQHandler           ; CAN0
                DCD     CAN1_IRQHandler           ; CAN1
                DCD     TMR1_UP_IRQHandler        ; TMR1 Update
                DCD     TMR1_BRK_IRQHandler       ; TMR1 Break
                DCD     TMR1_CC_IRQHandler        ; TMR1 Capture Compare
                DCD     TMR1_TRG_COM_IRQHandler   ; TMR1 Trigger and Commutation
                DCD     TMR2_UP_IRQHandler        ; TMR2 Update
                DCD     TMR2_BRK_IRQHandler       ; TMR2 Break
                DCD     TMR2_CC_IRQHandler        ; TMR2 Capture Compare
                DCD     TMR2_TRG_COM_IRQHandler   ; TMR2 Trigger and Commutation
                DCD     TMR3_IRQHandler           ; TMR3
                DCD     TMR4_IRQHandler           ; TMR4
                DCD     TMR5_IRQHandler           ; TMR5
                DCD     TMR6_IRQHandler           ; TMR6
                DCD     DMA0_CH0_IRQHandler       ; DMA0 Channel 0
                DCD     DMA0_CH1_IRQHandler       ; DMA0 Channel 1
                DCD     DMA0_CH2_IRQHandler       ; DMA0 Channel 2
                DCD     DMA0_CH3_IRQHandler       ; DMA0 Channel 3
                DCD     DMA0_CH4_IRQHandler       ; DMA0 Channel 4
                DCD     DMA0_CH5_IRQHandler       ; DMA0 Channel 5
                DCD     DMA0_CH6_IRQHandler       ; DMA0 Channel 6
                DCD     DMA0_CH7_IRQHandler       ; DMA0 Channel 7
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     ADC0_IRQHandler           ; ADC1
                DCD     ADC1_IRQHandler           ; ADC2
                DCD     ENCENG_IRQHandler         ; ENCENG
                DCD     MAC0_SBD_IRQHandler       ; MAC0 SBD
                DCD     MAC0_PMT_IRQHandler       ; MAC0 PMT
                DCD     MAC1_SBD_IRQHandler       ; MAC1 SBD
                DCD     MAC1_PMT_IRQHandler       ; MAC1 PMT
                DCD     DCMI_IRQHandler           ; DCMI
                DCD     CDMA_ADC_IRQHandler         ; DSMADC 
                DCD     FLEXCOMM0_IRQHandler      ; FLEXCOMM0
                DCD     FLEXCOMM1_IRQHandler      ; FLEXCOMM1
                DCD     FLEXCOMM2_IRQHandler      ; FLEXCOMM2
                DCD     FLEXCOMM3_IRQHandler      ; FLEXCOMM3
                DCD     FLEXCOMM4_IRQHandler      ; FLEXCOMM4
                DCD     FLEXCOMM5_IRQHandler      ; FLEXCOMM5
                DCD     FLEXCOMM6_IRQHandler      ; FLEXCOMM6
                DCD     FLEXCOMM7_IRQHandler      ; FLEXCOMM7
                DCD     FLEXCOMM8_IRQHandler      ; FLEXCOMM8
                DCD     FLEXCOMM9_IRQHandler      ; FLEXCOMM9
                DCD     FLEXCOMM10_IRQHandler     ; FLEXCOMM10
                DCD     FLEXCOMM11_IRQHandler     ; FLEXCOMM11
                DCD     FLEXCOMM12_IRQHandler     ; FLEXCOMM12
                DCD     FLEXCOMM13_IRQHandler     ; FLEXCOMM13
                DCD     DMA1_CH0_IRQHandler       ; DMA1 Channel 0
                DCD     DMA1_CH1_IRQHandler       ; DMA1 Channel 1
                DCD     DMA1_CH2_IRQHandler       ; DMA1 Channel 2
                DCD     DMA1_CH3_IRQHandler       ; DMA1 Channel 3
                DCD     DMA1_CH4_IRQHandler       ; DMA1 Channel 4
                DCD     DMA1_CH5_IRQHandler       ; DMA1 Channel 5
                DCD     DMA1_CH6_IRQHandler       ; DMA1 Channel 6
                DCD     DMA1_CH7_IRQHandler       ; DMA1 Channel 7
                DCD     EXTI0_IRQHandler          ; EXTI Line0
                DCD     EXTI1_IRQHandler          ; EXTI Line1
                DCD     EXTI2_IRQHandler          ; EXTI Line2
                DCD     EXTI3_IRQHandler          ; EXTI Line3
                DCD     EXTI4_IRQHandler          ; EXTI Line4
                DCD     EXTI5_IRQHandler          ; EXTI Line5
                DCD     EXTI6_IRQHandler          ; EXTI Line6
                DCD     EXTI7_IRQHandler          ; EXTI Line7
                DCD     EXTI8_IRQHandler          ; EXTI Line8
                DCD     EXTI9_IRQHandler          ; EXTI Line9
                DCD     EXTI10_IRQHandler         ; EXTI Line10
                DCD     EXTI11_IRQHandler         ; EXTI Line11
                DCD     EXTI12_IRQHandler         ; EXTI Line12
                DCD     EXTI13_IRQHandler         ; EXTI Line13
                DCD     EXTI14_IRQHandler         ; EXTI Line14
                DCD     EXTI15_IRQHandler         ; EXTI Line15
                DCD     I2C0_CM0_IRQHandler       ; I2C0 
                DCD     DMA_CM0_IRQHandler        ; DMA
                DCD     UART0_CM0_IRQHandler      ; UART0
                DCD     UART1_CM0_IRQHandler      ; UART1
                DCD     UART2_CM0_IRQHandler      ; UART2
                DCD     UART3_CM0_IRQHandler      ; UART3
                DCD     UART4_CM0_IRQHandler      ; UART4
                DCD     UART5_CM0_IRQHandler      ; UART5
                DCD     ISO78160_CM0_IRQHandler   ; ISO78160
                DCD     ISO78161_CM0_IRQHandler   ; ISO78161
                DCD     BTMR0_CM0_IRQHandler      ; BTMR0
                DCD     BTMR1_CM0_IRQHandler      ; BTMR1
                DCD     BTMR2_CM0_IRQHandler      ; BTMR2
                DCD     BTMR3_CM0_IRQHandler      ; BTMR3
                DCD     BPWM0_CM0_IRQHandler      ; BPWM0
                DCD     BPWM1_CM0_IRQHandler      ; BPWM1
                DCD     BPWM2_CM0_IRQHandler      ; BPWM2
                DCD     BPWM3_CM0_IRQHandler      ; BPWM3
                DCD     FLASH0_IRQHandler         ; FLASH0
                DCD     SPI0_CM0_IRQHandler       ; SPI0
                DCD     SPI1_CM0_IRQHandler       ; SPI1
                DCD     SPI2_CM0_IRQHandler       ; SPI2
                DCD     SPI3_CM0_IRQHandler       ; SPI3
                DCD     SPI4_CM0_IRQHandler       ; SPI4
                DCD     SPI5_CM0_IRQHandler       ; SPI05
                DCD     HFM_COP_IRQHandler        ; HFM & COP
                DCD     RTC_IRQHandler            ; RTC global interrupts
                DCD     PMU_IRQHandler            ; PMU global interrupts
                DCD     RTC_ALM_IRQHandler        ; RTC Alarm
                DCD     SYSCON_LP_ANA_IRQHandler  ; SYSCON_LP & Analog global interrupts 
                DCD     LPBTMR_IRQHandler         ; LPBTMR
                DCD     0                         ; Reserved
                DCD     COMP_IRQHandler           ; Comparator
                
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler\
                PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SecureFault_Handler\
                PROC
                EXPORT  SecureFault_Handler       [WEAK]
                B       .
                ENDP
SVC_Handler\
                PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT     CM33_MAILBOX_IRQHandler   [WEAK]
                EXPORT     CM0_MAILBOX_IRQHandler    [WEAK]
                EXPORT     I2S0_IRQHandle            [WEAK]
                EXPORT     I2S1_IRQHandler           [WEAK]
                EXPORT     USB_HS_IRQHandler         [WEAK]
                EXPORT     USB_FS_IRQHandler         [WEAK]
                EXPORT     SSI0_IRQHandler           [WEAK]
                EXPORT     SSI1_IRQHandler           [WEAK]
                EXPORT     FLASHA_IRQHandler         [WEAK]
                EXPORT     FLASHB_IRQHandler         [WEAK]
                EXPORT     ISO7816_0_1_IRQHandler    [WEAK]
                EXPORT     MEM_ECC_IRQHandler        [WEAK]
                EXPORT     BTMR0_IRQHandler          [WEAK]
                EXPORT     BTMR1_IRQHandler          [WEAK]
                EXPORT     BTMR2_IRQHandler          [WEAK]
                EXPORT     BTMR3_IRQHandler          [WEAK]
                EXPORT     BPWM0_IRQHandler          [WEAK]
                EXPORT     BPWM1_IRQHandler          [WEAK]
                EXPORT     BPWM2_IRQHandler          [WEAK]
                EXPORT     BPWM3_IRQHandler          [WEAK]
                EXPORT     SDIO0_IRQHandler          [WEAK]
                EXPORT     SDIO1_IRQHandler          [WEAK]
                EXPORT     RNG_IRQHandler            [WEAK]
                EXPORT     EADC_IRQHandler           [WEAK]
                EXPORT     SCR_IRQHandler            [WEAK]
                EXPORT     CAN0_IRQHandler           [WEAK]
                EXPORT     CAN1_IRQHandler           [WEAK]
                EXPORT     TMR1_UP_IRQHandler        [WEAK]
                EXPORT     TMR1_BRK_IRQHandler       [WEAK]
                EXPORT     TMR1_CC_IRQHandler        [WEAK]
                EXPORT     TMR1_TRG_COM_IRQHandler   [WEAK]
                EXPORT     TMR2_UP_IRQHandler        [WEAK]
                EXPORT     TMR2_BRK_IRQHandler       [WEAK]
                EXPORT     TMR2_CC_IRQHandler        [WEAK]
                EXPORT     TMR2_TRG_COM_IRQHandler   [WEAK]
                EXPORT     TMR3_IRQHandler           [WEAK]
                EXPORT     TMR4_IRQHandler           [WEAK]
                EXPORT     TMR5_IRQHandler           [WEAK]
                EXPORT     TMR6_IRQHandler           [WEAK]
                EXPORT     DMA0_CH0_IRQHandler       [WEAK]
                EXPORT     DMA0_CH1_IRQHandler       [WEAK]
                EXPORT     DMA0_CH2_IRQHandler       [WEAK]
                EXPORT     DMA0_CH3_IRQHandler       [WEAK]
                EXPORT     DMA0_CH4_IRQHandler       [WEAK]
                EXPORT     DMA0_CH5_IRQHandler       [WEAK]
                EXPORT     DMA0_CH6_IRQHandler       [WEAK]
                EXPORT     DMA0_CH7_IRQHandler       [WEAK]
                EXPORT     ADC0_IRQHandler           [WEAK]
                EXPORT     ADC1_IRQHandler           [WEAK]
                EXPORT     ENCENG_IRQHandler         [WEAK]
                EXPORT     MAC0_SBD_IRQHandler       [WEAK]
                EXPORT     MAC0_PMT_IRQHandler       [WEAK]
                EXPORT     MAC1_SBD_IRQHandler       [WEAK]
                EXPORT     MAC1_PMT_IRQHandler       [WEAK]
                EXPORT     DCMI_IRQHandler           [WEAK]
                EXPORT     CDMA_ADC_IRQHandler       [WEAK]
                EXPORT     FLEXCOMM0_IRQHandler      [WEAK]
                EXPORT     FLEXCOMM1_IRQHandler      [WEAK]
                EXPORT     FLEXCOMM2_IRQHandler      [WEAK]
                EXPORT     FLEXCOMM3_IRQHandler      [WEAK]
                EXPORT     FLEXCOMM4_IRQHandler      [WEAK]
                EXPORT     FLEXCOMM5_IRQHandler      [WEAK]
                EXPORT     FLEXCOMM6_IRQHandler      [WEAK]
                EXPORT     FLEXCOMM7_IRQHandler      [WEAK]
                EXPORT     FLEXCOMM8_IRQHandler      [WEAK]
                EXPORT     FLEXCOMM9_IRQHandler      [WEAK]
                EXPORT     FLEXCOMM10_IRQHandler     [WEAK]
                EXPORT     FLEXCOMM11_IRQHandler     [WEAK]
                EXPORT     FLEXCOMM12_IRQHandler     [WEAK]
                EXPORT     FLEXCOMM13_IRQHandler     [WEAK]
                EXPORT     DMA1_CH0_IRQHandler       [WEAK]
                EXPORT     DMA1_CH1_IRQHandler       [WEAK]
                EXPORT     DMA1_CH2_IRQHandler       [WEAK]
                EXPORT     DMA1_CH3_IRQHandler       [WEAK]
                EXPORT     DMA1_CH4_IRQHandler       [WEAK]
                EXPORT     DMA1_CH5_IRQHandler       [WEAK]
                EXPORT     DMA1_CH6_IRQHandler       [WEAK]
                EXPORT     DMA1_CH7_IRQHandler       [WEAK]
                EXPORT     EXTI0_IRQHandler          [WEAK]
                EXPORT     EXTI1_IRQHandler          [WEAK]
                EXPORT     EXTI2_IRQHandler          [WEAK]
                EXPORT     EXTI3_IRQHandler          [WEAK]
                EXPORT     EXTI4_IRQHandler          [WEAK]
                EXPORT     EXTI5_IRQHandler          [WEAK]
                EXPORT     EXTI6_IRQHandler          [WEAK]
                EXPORT     EXTI7_IRQHandler          [WEAK]
                EXPORT     EXTI8_IRQHandler          [WEAK]
                EXPORT     EXTI9_IRQHandler          [WEAK]
                EXPORT     EXTI10_IRQHandler         [WEAK]
                EXPORT     EXTI11_IRQHandler         [WEAK]
                EXPORT     EXTI12_IRQHandler         [WEAK]
                EXPORT     EXTI13_IRQHandler         [WEAK]
                EXPORT     EXTI14_IRQHandler         [WEAK]
                EXPORT     EXTI15_IRQHandler         [WEAK]
                EXPORT     I2C0_CM0_IRQHandler       [WEAK]
                EXPORT     DMA_CM0_IRQHandler        [WEAK]
                EXPORT     UART0_CM0_IRQHandler      [WEAK]
                EXPORT     UART1_CM0_IRQHandler      [WEAK]
                EXPORT     UART2_CM0_IRQHandler      [WEAK]
                EXPORT     UART3_CM0_IRQHandler      [WEAK]
                EXPORT     UART4_CM0_IRQHandler      [WEAK]
                EXPORT     UART5_CM0_IRQHandler      [WEAK]
                EXPORT     ISO78160_CM0_IRQHandler   [WEAK]
                EXPORT     ISO78161_CM0_IRQHandler   [WEAK]
                EXPORT     BTMR0_CM0_IRQHandler      [WEAK]
                EXPORT     BTMR1_CM0_IRQHandler      [WEAK]
                EXPORT     BTMR2_CM0_IRQHandler      [WEAK]
                EXPORT     BTMR3_CM0_IRQHandler      [WEAK]
                EXPORT     BPWM0_CM0_IRQHandler      [WEAK]
                EXPORT     BPWM1_CM0_IRQHandler      [WEAK]
                EXPORT     BPWM2_CM0_IRQHandler      [WEAK]
                EXPORT     BPWM3_CM0_IRQHandler      [WEAK]
                EXPORT     FLASH0_IRQHandler         [WEAK]
                EXPORT     SPI0_CM0_IRQHandler       [WEAK]
                EXPORT     SPI1_CM0_IRQHandler       [WEAK]
                EXPORT     SPI2_CM0_IRQHandler       [WEAK]
                EXPORT     SPI3_CM0_IRQHandler       [WEAK]
                EXPORT     SPI4_CM0_IRQHandler       [WEAK]
                EXPORT     SPI5_CM0_IRQHandler       [WEAK]
                EXPORT     HFM_COP_IRQHandler        [WEAK]
                EXPORT     RTC_IRQHandler            [WEAK]
                EXPORT     PMU_IRQHandler            [WEAK]
                EXPORT     RTC_ALM_IRQHandler        [WEAK]
                EXPORT     SYSCON_LP_ANA_IRQHandler  [WEAK]
                EXPORT     LPBTMR_IRQHandler         [WEAK]
                EXPORT     COMP_IRQHandler           [WEAK]
CM33_MAILBOX_IRQHandler
CM0_MAILBOX_IRQHandler
I2S0_IRQHandle
I2S1_IRQHandler
USB_HS_IRQHandler
USB_FS_IRQHandler
SSI0_IRQHandler
SSI1_IRQHandler
FLASHA_IRQHandler
FLASHB_IRQHandler
ISO7816_0_1_IRQHandler
MEM_ECC_IRQHandler
BTMR0_IRQHandler
BTMR1_IRQHandler
BTMR2_IRQHandler
BTMR3_IRQHandler
BPWM0_IRQHandler
BPWM1_IRQHandler
BPWM2_IRQHandler
BPWM3_IRQHandler
SDIO0_IRQHandler
SDIO1_IRQHandler
RNG_IRQHandler
EADC_IRQHandler
SCR_IRQHandler
CAN0_IRQHandler
CAN1_IRQHandler
TMR1_UP_IRQHandler
TMR1_BRK_IRQHandler
TMR1_CC_IRQHandler
TMR1_TRG_COM_IRQHandler
TMR2_UP_IRQHandler
TMR2_BRK_IRQHandler
TMR2_CC_IRQHandler
TMR2_TRG_COM_IRQHandler
TMR3_IRQHandler
TMR4_IRQHandler
TMR5_IRQHandler
TMR6_IRQHandler
DMA0_CH0_IRQHandler
DMA0_CH1_IRQHandler
DMA0_CH2_IRQHandler
DMA0_CH3_IRQHandler
DMA0_CH4_IRQHandler
DMA0_CH5_IRQHandler
DMA0_CH6_IRQHandler
DMA0_CH7_IRQHandler
ADC0_IRQHandler
ADC1_IRQHandler
ENCENG_IRQHandler
MAC0_SBD_IRQHandler
MAC0_PMT_IRQHandler
MAC1_SBD_IRQHandler
MAC1_PMT_IRQHandler
DCMI_IRQHandler
CDMA_ADC_IRQHandler
FLEXCOMM0_IRQHandler
FLEXCOMM1_IRQHandler
FLEXCOMM2_IRQHandler
FLEXCOMM3_IRQHandler
FLEXCOMM4_IRQHandler
FLEXCOMM5_IRQHandler
FLEXCOMM6_IRQHandler
FLEXCOMM7_IRQHandler
FLEXCOMM8_IRQHandler
FLEXCOMM9_IRQHandler
FLEXCOMM10_IRQHandler
FLEXCOMM11_IRQHandler
FLEXCOMM12_IRQHandler
FLEXCOMM13_IRQHandler
DMA1_CH0_IRQHandler
DMA1_CH1_IRQHandler
DMA1_CH2_IRQHandler
DMA1_CH3_IRQHandler
DMA1_CH4_IRQHandler
DMA1_CH5_IRQHandler
DMA1_CH6_IRQHandler
DMA1_CH7_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
EXTI5_IRQHandler
EXTI6_IRQHandler
EXTI7_IRQHandler
EXTI8_IRQHandler
EXTI9_IRQHandler
EXTI10_IRQHandler
EXTI11_IRQHandler
EXTI12_IRQHandler
EXTI13_IRQHandler
EXTI14_IRQHandler
EXTI15_IRQHandler
I2C0_CM0_IRQHandler
DMA_CM0_IRQHandler
UART0_CM0_IRQHandler
UART1_CM0_IRQHandler
UART2_CM0_IRQHandler
UART3_CM0_IRQHandler
UART4_CM0_IRQHandler
UART5_CM0_IRQHandler
ISO78160_CM0_IRQHandler
ISO78161_CM0_IRQHandler
BTMR0_CM0_IRQHandler
BTMR1_CM0_IRQHandler
BTMR2_CM0_IRQHandler
BTMR3_CM0_IRQHandler
BPWM0_CM0_IRQHandler
BPWM1_CM0_IRQHandler
BPWM2_CM0_IRQHandler
BPWM3_CM0_IRQHandler
FLASH0_IRQHandler
SPI0_CM0_IRQHandler
SPI1_CM0_IRQHandler
SPI2_CM0_IRQHandler
SPI3_CM0_IRQHandler
SPI4_CM0_IRQHandler
SPI5_CM0_IRQHandler
HFM_COP_IRQHandler
RTC_IRQHandler
PMU_IRQHandler
RTC_ALM_IRQHandler
SYSCON_LP_ANA_IRQHandler
LPBTMR_IRQHandler
COMP_IRQHandler
                B       .

                ENDP


                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
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
