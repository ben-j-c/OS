print_hex:

mov ch, 0     ; counter
mov cl, 12    ; shift count

print_hex_loop:
cmp ch, 4
jz print_hex_done
	;Extract digit
	mov bx, [MASK]
	and bx, dx
	shl bx, cl

	;Use numerical value of digit to lookuptable the hex char
	add bx, ASCIITABLE
	mov al, [bx]
	mov ah, 0x0e
	int 0x10

	;Place the value in the decoded section
	movzx bx, ch
	add bx, DECODED_HEX
	mov [bx], al

inc ch
sub cl, 4

print_hex_done:

mov bx, DECODED_HEX_FINAL
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
