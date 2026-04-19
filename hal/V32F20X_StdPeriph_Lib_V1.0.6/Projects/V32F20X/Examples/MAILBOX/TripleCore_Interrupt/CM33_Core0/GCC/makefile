# Project name
TARGET = template

COMPILE = /home/zhouyf/toolchain/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-

CC    = $(COMPILE)gcc
OBJCP = $(COMPILE)objcopy
SIZE  = $(COMPILE)size

# Path
vpath %.S	./
vpath %.c	../Src 					\
		../../../../../../../Libraries/Drivers/Src 		\
		../../../../../../../Libraries/CMSIS/cm33/core0 \
		../../../../../../../BSP
vpath %.h 	../Inc					\
		../../../../../../../Libraries/CMSIS/cm33/core0 \
		../../../../../../../Libraries/CMSIS/Include \
		../../../../../../../Libraries/Drivers/Inc \
		../../../../../../../Libraries/include \
		../../../../../../../BSP


DEFS += -D_USE_TARGET_DRIVER
DEFS += -DV32F20XXX_CM33_CORE0
INCS += -I../Inc 					\
		-I../../../../../../../Libraries/CMSIS/cm33/core0 \
		-I../../../../../../../Libraries/CMSIS/Include \
		-I../../../../../../../Libraries/Drivers/Inc \
		-I../../../../../../../Libraries/include \
		-I../../../../../../../BSP

# All source files
OBJS += ./startup_target_cm33_core0.o
OBJS += ../../../../../../../Libraries/CMSIS/cm33/core0/system_target_cm33_core0.o
OBJS += ../../../../../../../BSP/board.o

DRV_SRC0 = $(wildcard ../Src/*.c)
OBJS += $(patsubst %.c, %.o, $(DRV_SRC0))

DRV_SRC1 = $(wildcard ../../../../../../../Libraries/Drivers/Src/*.c)
OBJS += $(patsubst %.c, %.o, $(DRV_SRC1))

RM_OBJS = $(patsubst %.o, %.su, $(OBJS)) 
		
# Options
CFLAGS += -mcpu=cortex-m33 -mthumb -Wall
CFLAGS += -mfloat-abi=soft -static -Wl,--start-group -lm -Wl,--end-group
CFLAGS += -Os
#CFLAGS += -ffunction-sections -fdata-sections
# Warning -> Error, for batch test
CFLAGS += -Werror

CFLAGS = -mcpu=cortex-m33 -mfloat-abi=soft -mthumb -std=gnu11 -g3 \
		 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage

LFLAGS += -mcpu=cortex-m33 -mthumb
LFLAGS += -Wl,--gc-sections 
LFLAGS += -Xlinker --gc-sections
LFLAGS += --specs=nosys.specs

# Generates .bin
all:$(TARGET).bin

$(TARGET).bin:$(TARGET).elf
	$(OBJCP) -O binary -S $< $@
    
$(TARGET).elf:$(OBJS) $(OBJ_FLASH)
	$(CC) $(LFLAGS) $^ -T./Target_FLASH.ld -o $@
	$(SIZE) $@

%.o:%.S
	$(CC) $(CFLAGS) -c $< -o $@
%.o:%.c
	$(CC) $(CFLAGS) $(DEFS) $(INCS) -c $< -o $@

# Clean project
.PHONY:clean
clean:
	@rm -f $(OBJS) $(OBJ_FLASH) $(OBJ_SRAM)  
	@rm -f $(TARGET).bin $(TARGET).elf $(TARGET).bin $(TARGET).elf
	@rm -f $(RM_OBJS)

