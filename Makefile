TOOLPREFIX := aarch64-none-elf-

CC	= $(TOOLPREFIX)gcc
AS	= $(TOOLPREFIX)as
LD	= $(TOOLPREFIX)ld

CFLAGS = -Iinclude \
		 -Ilib/include \
		 -Iarch/aarch64 \
		 -Iarch/aarch64/boards/raspberry-pi/include \
		 -nostdlib \
		 -mgeneral-regs-only \
		 -ffreestanding \
		 -nostartfiles

AFLAGS = -D__ASSEMBLY__

LINKER_SCRIPT  = ./arch/aarch64/boards/raspberry-pi/kernel.ld

SRC_DIR = ./arch/aarch64 \
		  ./arch/aarch64/boards/raspberry-pi \
		  ./lib \
		  ./init \
		  ./mm

BUILD_DIR := ./build

BUILD_TARGET = vmbison.bin

QEMU = qemu-system-aarch64

QEMU_FLAGS = -machine raspi3b \
			 -serial null -serial mon:stdio \
			 -nographic

OBJS_C += $(patsubst %.c,%.o,$(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.c)))
OBJS_S += $(patsubst %.S,%.o,$(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.S)))

$(OBJS_C) : %.o : %.c
	$(CC) -c $< $(CFLAGS)

$(OBJS_S) : %.o : %.S
	$(CC) -c $< $(CFLAGS) $(AFLAGS)

$(BUILD_DIR)/*.o: $(OBJS_C) $(OBJS_S)
	mkdir -p $(BUILD_DIR)
	mv *.o $(BUILD_DIR)/

$(BUILD_TARGET): $(BUILD_DIR)/*.o
	$(LD) $< -T $(LINKER_SCRIPT) -o $@

run: $(BUILD_TARGET)
	$(QEMU) $(QEMU_FLAGS) -kernel $<

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BUILD_TARGET)