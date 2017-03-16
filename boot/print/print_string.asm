;print.asm
;Printing Functions

; Uses the BIOS print interrupt to display a null-terminated string to the screen
; not available in 32-bit protected mode
; Argument passed to bx
print_string:
	mov ah, 0x0e ; setup the teletype
	loop: ;printing loop
		mov cl, [bx] ; grab the next byte of the string
		cmp cl, 0 ; check if null
		je end ; quit if null
		mov al, cl ; otherwise, move to the al
		int 0x10 ; & call the print interrupt
		add bx, 1 ; add one to the pointer
		jmp loop ; move on

	end:
		ret; return
