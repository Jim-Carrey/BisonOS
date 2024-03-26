# default architecture is arm64
# you can give the parameter like 'make MACHINE=risc-v' for building whichever cpu target you want
MACHINE := arm64

AARCH64_OBJS = \
	arch/aarch64/mm.o \
	arch/aarch64/head.o \
	arch/aarch64/boards/raspberry-pi/pl_uart.o \
	lib/printk.o \
	lib/string.o \
	init/main.o

RISC-V_OBJS = \
  arch/riscv/boards/qemu-virt/entry.o \
  arch/riscv/boards/qemu-virt/uart.o \
  arch/riscv/boot/start.o

SUPPORT_TARGET :
ifeq ($(MACHINE),arm64)
    TOOLPREFIX := aarch64-linux-gnu-
    LINKER_SCRIPT 	:= ./arch/aarch64/boards/raspberry-pi/kernel.ld
    BUILD_OBJS := $(AARCH64_OBJS)
    QEMU	:= qemu-system-aarch64
    QEMUOPTS += -machine raspi3 -serial null -serial mon:stdio -nographic -kernel vmbison
    CFLAGS = -Iinclude -nostdlib -mgeneral-regs-only -ffreestanding -nostartfiles
    ifeq ($(wildcard ./build),)
    $(shell mkdir -p ./build)
    endif
else ifeq ($(MACHINE),risc-v)
    TOOLPREFIX := riscv64-unknown-elf-
    LINKER_SCRIPT 	:= ./arch/riscv/boards/qemu-virt/kernel.ld
    BUILD_OBJS := $(RISC-V_OBJS)
    QEMU	:= qemu-system-riscv64
    QEMUOPTS += -M virt -bios none -m 128M -nographic -kernel vmbison
    CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb -gdwarf-2
    CFLAGS += -MD
    CFLAGS += -mcmodel=medany
    CFLAGS += -ffreestanding -fno-common -nostdlib -mno-relax
    CFLAGS += -I.
    ifeq ($(wildcard ./build),)
    $(shell mkdir -p ./build)
    endif
else
	@echo "Unsupported Architecture: $(MACHINE)"
	@echo "Currently Supported Architecture: \n MACHINE=arm64 \n MACHINE=risc-v"
	@exit 1
endif

BUILD_DIR := build

CC	= $(TOOLPREFIX)gcc
LD	= $(TOOLPREFIX)ld
AS	= $(TOOLPREFIX)as

# 查找并移动所有的.o文件
$(BUILD_DIR)/%.o : $(BUILD_OBJS)
	@find . -name "*.o" ! -path "./build/*" -exec mv {} ./build/ \;

$(BUILD_DIR)/vmbison : $(BUILD_DIR)/%.o
	$(LD) $(BUILD_DIR)/*.o -T $(LINKER_SCRIPT) -o vmbison

qemu: SUPPORT_TARGET $(BUILD_DIR)/vmbison
	$(QEMU) $(QEMUOPTS)

clean:
	rm -rf build/
	$(shell test -f vmbison && rm -rf vmbison)
	@echo -e Clean Finished