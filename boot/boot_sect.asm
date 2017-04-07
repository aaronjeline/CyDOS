;Boot sector the loads/boots a C kernel in 32-bit PM
[org 0x7c00]
KERNEL_OFFSET equ 0x1000

	mov [BOOT_DRIVE], dl

	mov bp, 0x9000; setup the stack
	mov sp, bp

	mov bx, MSG_REAL_MODE ; Announce that we are starting
	call print_string     ; booting from 16-bit real mode
	mov ah, 0 ; Waiting for key press
	int 0x16

	call load_kernel      ; Load kernel from disk
	call switch_to_pm     ; Switch to PM

	%include "boot/print/print_string.asm"
	%include "boot/disk/disk_load.asm"
	%include "boot/pm/gdt.asm"
	%include "boot/pm/print_string_pm.asm"
	%include "boot/pm/switch_to_pm.asm"

[bits 16]

;load kernel
load_kernel:
	mov bx, MSG_LOAD_KERNEL ; print message
	call print_string
	mov bx, KERNEL_OFFSET ; load parameters for disk_load
	mov dh, 30
	mov dl, [BOOT_DRIVE]
	call disk_load

	ret

[bits 32]
;32-bit protected mode starts here
BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm

	call KERNEL_OFFSET

	jmp $

;Global variables
BOOT_DRIVE	db 0
MSG_REAL_MODE	db "Welcome to the CYDOS BootLoader, press any key to continue...",0
MSG_PROT_MODE	db "Successfully landed in 32-bit Protected Mode",0
MSG_LOAD_KERNEL	db "Loading kernel into memory",0

;Bootsector padding
times 510-($-$$) db 0
dw 0xaa55
