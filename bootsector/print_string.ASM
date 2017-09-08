;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

print_string:
pusha
mov ah , 0x0e
print_string_loop:
mov al, [bx]
add al, 0
jz print_string_return

int 0x10

inc bx
mov al, [bx]
add al, 0
jnz print_string_loop

print_string_return:
popa
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

print_hex:
pusha
mov ch, 0     ; counter
mov cl, 12    ; shift count

print_hex_loop:
cmp ch, 4
jz print_hex_done
	;Extract digit
	mov bx, [MASK]
	shl bx, cl
	and bx, dx
	shr bx, cl

	;Use numerical value of digit to lookuptable the hex char
	add bx, ASCIITABLE
	mov al, [bx]

	;Place the value in the decoded section
	movzx bx, ch
	add bx, DECODED_HEX
	mov [bx], al

inc ch
sub cl, 4
jmp print_hex_loop
print_hex_done:

mov bx, DECODED_HEX_FINAL
call print_string
popa
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
DECODED_HEX_FINAL:
db '0x'
DECODED_HEX:
db '0000',0
ASCIITABLE:
db '0123456789ABCDEF',0
MASK:
dw 0x000f

