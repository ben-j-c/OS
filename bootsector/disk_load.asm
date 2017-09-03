; load DH sectors to ES:BX from drive DL
disk_load :
	  mov [MY_DX], dx ; Store DX

	  mov ah , 0x02 ; BIOS read sector function
	  mov al , dh ; Read DH sectors
	  mov ch , 0x00 ; Select cylinder 0
	  mov dh , 0x00 ; Select head 0
	  int 0x13 ; BIOS interrupt

	  jc disk_error ; Jump if error ( i.e. carry flag set )
	  mov dx, [MY_DX] ; Restore DX from the stack
	  cmp dh , al ; if AL ( sectors read ) != DH ( sectors expected )
	  jne disk_error ; display error message
	  ret
disk_error :
	   add ah, 1
	   add al, 1
	   mov [DE_CODE], ah
	   mov [DE_READ], al
	   pusha
	   mov bx , DE_MSG
	   call print_string
	   popa
	   ; Variables
	   MY_DX: dw 0
	   DE_MSG: db " Disk read error ! "
	   db "Disk error code: "
	   DE_CODE: db "0"
	   db ", but "
	   DE_READ: db "0"
	   db " sectors were read", 0
