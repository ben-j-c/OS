; A boot sector that boots a C kernel in 32 - bit protected mode
org 0x7c00
KERNEL_OFFSET equ 0x7E00 ; This is the memory offset to which we will load our kernel
mov [ BOOT_DRIVE ], dl ; BIOS stores our boot drive in DL , so it ’s
; best to remember this for later.
mov bp, 0x7C00 - 0x0010 ; Set -up the stack.
mov sp, bp
mov ax, 0
mov es, ax
mov dx, ax

call load_kernel ; Load our kernel

mov bx, MSG_PROT_MODE_LOAD
call print_string
call switch_to_pm ; Switch to protected mode , from which

jmp $

include "bootsector/print_string.ASM"
include "bootsector/disk_load.asm"
include "bootsector/gdt.asm"
include "bootsector/print_string_pm.asm"
include "bootsector/switch_to_pm.asm"



use16
; load_kernel
load_kernel :
	    mov bx , MSG_LOAD_KERNEL ; Print a message to say we are loading the kernel
	    call print_string

	    mov bx , KERNEL_OFFSET
	    mov dh , 127 ;load 2^7 - 1 sectors
	    mov cl, 0x02; starting from the 2nd sector
	    mov dl , [ BOOT_DRIVE ]
	    call disk_load

	    ;mov bx , KERNEL_OFFSET + 48*512
	    ;mov dh , 48 ;load 48 sectors
	    ;mov cl, 0x49; starting from the 49th sector
	    ;mov dl , [ BOOT_DRIVE ]
	    ;call disk_load

	    ;mov bx , KERNEL_OFFSET + 96*512
	    ;mov dh , 32 ;load 32 sectors
	    ;mov cl, 0x97; starting from the 97th sector
	    ;mov dl , [ BOOT_DRIVE ]
	    ;call disk_load
ret

use32

BEGIN_PM :
	 fldcw [FPU_CONTROL]
	 call SSE_SUPPORT
	 mov ebx , MSG_PROT_MODE ; Use our 32 - bit print routine to
	 call print_string_pm ; announce we are in protected mode
	 call KERNEL_OFFSET ; Now jump to the address of our loaded kernel
jmp $ ; Hang.

;Add support for SSE instructions
SSE_SUPPORT:
	push eax
	mov eax, cr0
	and ax, 0xFFFB		;clear coprocessor emulation CR0.EM
	or ax, 0x2		;set coprocessor monitoring  CR0.MP
	mov cr0, eax
	mov eax, cr4
	or ax, 0x600		;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
	mov cr4, eax
	pop eax
ret

; Global variables
BOOT_DRIVE db 0
MSG_REAL_MODE db "16 bit mode", 10, 13 , 0
MSG_PROT_MODE_LOAD db "Loading 32- bit mode", 0
MSG_PROT_MODE db "landed in 32 bit mode", 0
MSG_LOAD_KERNEL db "Loading kernel", 10, 13 , 0

FPU_CONTROL:
	dw 0x007f

; Bootsector padding
times 510 -( $ - $$ ) db 0
dw 0xaa55
use32
file "kernel.BIN"
jp $
times 512*128 - ($ - $$) db 0
