.intel_syntax

.globl _setCh0
.globl _setCh1
.globl _setCh2
.align 4


_setCh0:
	push ebp
	mov ebp, esp
	sub esp, 0
	push ax
	
	mov al, 0x36
	out 0x43, al
	
	mov ax, [ebp + 8]
	out 0x40, al
	mov al, ah
	out 0x40, al

	pop ax
	mov esp, ebp
	pop ebp
	ret 0



_setCh1:
	push ebp
	mov ebp, esp
	sub esp, 0
	push ax
	
	mov al, 0x30
	out 0x43, al
	
	mov ax, [ebp + 8]
	out 0x40, al
	mov al, ah
	out 0x40, al

	pop ax
	mov esp, ebp
	pop ebp
	ret 0

_setCh2:
	ret 0
