;pm.asm
;Executes switch to protected mode
[bits 16]
switch_to_pm:

	cli	;Stop CPU interrupts until we rebuild 
		;The interrupt vector table for 32-bit mode

	lgdt [gdt_descriptor]	; Load the GDTD

	mov eax, cr0	;Load the control register into eax
	or eax, 0x1	;Set the first bit of the control register to signify
	mov cr0, eax	;switch to 32-bit mode-then save eax back to CR0

	jmp CODE_SEG:init_pm	; Make a far jump to force the CPU to
				; flush the pipeline


[bits 32]
;Initialize registers & stack for 32-bit mode
init_pm:

	mov ax, DATA_SEG 	;Old segments are meaningless, update from GDT
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000 	;Update stack pointer
	mov esp, ebp

	call BEGIN_PM		;Call out
