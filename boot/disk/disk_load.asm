;Load DH sectors to ES:BX from drive DL
disk_load:
	push dx

	mov ah, 0x02 ; BIOS Read-Sectors Function
	mov al, dh ; #Sectors
	mov ch, 0x00 ; Cylindar#
	mov dh, 0x00 ; Head$
	mov cl, 0x02 ; Start @ second sectors (after boot sector)

	int 0x13 ;Call function

	jc disk_error 

	pop dx
	cmp dh, al
	jne sector_error
	ret

disk_error:
	mov bx, DISK_ERROR_MSG
	call print_string
	jmp $

sector_error:
	mov bx, INVALID_SECTOR_MSG
	call print_string
	jmp $

DRIVER_MSG: db "Enterred disk_load.asm",0
DISK_ERROR_MSG:	db "Disk Read Error!",0
INVALID_SECTOR_MSG: db "Bad Sector Read!",0
GOOD_MSG: db "No Disc Error!",0
