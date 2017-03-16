;print_pm.asm
;Prints null terminated strings w/out BIOS interrupts
[bits 32]
;Constants
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f
YELLOW_ON_BLACK equ 0x0e

;Print null terminated string @ EDX
print_string_pm:
	pusha
	mov edx, VIDEO_MEMORY; set EDX to start of video memory

print_string_pm_loop:
	mov al, [ebx] ; store char @ EBX to AL
	mov ah, YELLOW_ON_BLACK ; set attribute

	cmp al, 0 ; if (al==0) we hit null, so return
	je print_string_pm_done

	mov [edx], ax ;Store char & attribute in character cell

	add ebx, 1
	add edx, 2

	jmp print_string_pm_loop

print_string_pm_done:
	popa
	ret
