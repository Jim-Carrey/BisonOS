BisonOS:
ifeq ($(wildcard ./build),)
	$(shell mkdir -p ./build)
endif
	arm-linux-gnueabi-gcc -c arch/$(ARCH)/boards/$(BOARD)/entry.S -o build/kernel.o
	arm-linux-gnueabi-ld build/kernel.o -T arch/$(ARCH)/boards/$(BOARD)/kernel.ld -o build/kernel

run: BisonOS
	qemu-system-arm -M virt -m 128M -nographic -kernel build/kernel

clean:
	rm -rf build/
