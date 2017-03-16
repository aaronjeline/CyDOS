nasm "$1.asm" -f bin -o $1
qemu-system-i386 $1
