;This function loads the memory map for the system by using int 0x15 & EAX= 0xE820
use16
loadSMAP:
	pushad
	mov ebx, 0x0000
	mov eax, 0x504
	mov di, ax
	mov edx, 0x534d4150 ;Dumb magic word needed to get the memory map
	loadSMAP_loop:
		mov eax, 0xE820
		mov ecx, 20
		int 0x15

		jc SMAPError
		cmp cx, 20
		jne SMAPError

		push eax
		mov eax, [0x500]
		add eax, 1
		mov [0x500], eax
		pop eax

		cmp ebx, 0
		je loadSMAP_done
		mov edx, eax
		mov ax, di
		add ax, 24
		mov di, ax
		jmp loadSMAP_loop

	loadSMAP_done:
	popad
	ret

SMAPError:
	mov bx, ERROR_MSG
	call print_string
	jmp $

ERROR_MSG:
db "SMAP error", 13, 0