;gdt.asm

;Global Descriptor Table

gdt_start:
	

gdt_null: ; null descriptor
	dd 0x0 ;double word (4b)
	dd 0x0

gdt_code: ; code segment
	;base=0x0, limit=0xfffff
	;1st flags: (present)1 (priviledge)00 (descriptor type)1->1001b
	;type flags: (code)1 (conforming)0 (readable)1 (accessed)0->1010b
	;2nd flags: (granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0->1100b

dw 0xffff ; Limit (bits 0-15)
dw 0x0; base (bits 0-15)
db 0x0; base (bits 16-23)
db 10011010b; 1st flags, type flags
db 11001111b; second flags, limit (bits 16-19)
db 0x0 ; base (bits 23-31)

gdt_data: ;data segment descriptor
	;Same as code segment except for type flags
	;base=0x0, limit=0xfffff
	;1st flags: (present)1 (priviledge)00 (descriptor type)1->1001b
	;type flags: (code)0 (expand down)0 (writable)1 (accessed)0->0010b
	;2nd flags: (granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0->1100b

dw 0xffff ; Limit (bits 0-15)
dw 0x0; base (bits 0-15)
db 0x0; base (bits 16-23)
db 10010010b; 1st flags, type flags
db 11001111b; second flags, limit (bits 16-19)
db 0x0 ; base (bits 23-31)

gdt_end: ; label here so the assembler can calculate GDT size for GDTD


; GDT descriptor
gdt_descriptor:
	dw gdt_end - gdt_start -1 ; size of gdt.

	dd gdt_start ; start address of GDT

; Define constants for the GDT segment ofsets
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
