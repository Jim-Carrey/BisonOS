QEMU	:= qemu-system-aarch64
CROSS	:= aarch64-none-linux-gnu-

CC	= $(CROSS)gcc
LD	= $(CROSS)ld
AS	= $(CROSS)as

LINKER_SCRIPT 	:= ./arch/aarch64/boards/qemu-virt/kernel.ld

vmbison :
ifeq ($(wildcard ./build),)
	$(shell mkdir -p ./build)
endif
	$(CC) -c arch/aarch64/boards/qemu-virt/entry.S -o build/entry.o
	$(CC) -c init/main.c -o build/main.o
	$(LD) build/entry.o build/main.o -T $(LINKER_SCRIPT) -o vmbison	

run: vmbison
	$(QEMU) -M virt -cpu cortex-a53 -m 128M -nographic -kernel vmbison

clean:
	rm -rf build/
	$(shell test -f vmbison && rm -rf vmbison)
	@echo -e '\n'Clean Finished
