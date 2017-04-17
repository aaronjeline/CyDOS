#Automatically generate lists of sources using wildcards
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

#TODO: make sources dependant on all header files

# Convert the *.c filenames to *.o for list of files to build
OBJ = ${C_SOURCES:.c=.o}

#Default build target
all: os-image

# Run qemu to simulate code
run: all
	qemu-system-i386 -drive file=os-image,format=raw,index=0,if=floppy 

# Run qemu, open a gdb hook, halt
debug: all
	qemu-system-i386 -drive file=os-image,format=raw,index=0,if=floppy -s -S
	

os-image: boot/boot_sect.bin kernel.bin
	cat $^ > os-image

#Builds the binary of our kernel from two object files:
# - kernel_entry, which jumps to main()
# - compiled c kernel
kernel.bin: kernel/kernel_entry.o ${OBJ}
	ld -o $@ -m elf_i386 -Ttext 0x1000 -g $^ --oformat binary

#Generic rule for compiling C code to an object file
%.o : %.c ${HEADERS}
	gcc -ffreestanding -m32 -c -g $< -o $@

#Assemble the kernel_entry
%.o : %.asm
	nasm $< -f elf -o $@

%.bin : %.asm
	nasm $< -f bin -I '../../16bit/' -o $@

clean:
	rm -fr *.bin *.dis *.o os-image
	rm -fr kernel/*.o boot/*.bin drivers/*.o
