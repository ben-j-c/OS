; A boot sector that boots a C kernel in 32 - bit protected mode
org 0x7c00
KERNEL_OFFSET equ 0x7E00 ; This is the memory offset to which we will load our kernel
mov [ BOOT_DRIVE ], dl ; BIOS stores our boot drive in DL , so it ’s
; best to remember this for later.
mov bp, 0x7C00; Set -up the stack.
mov sp, bp

mov ax, 0
mov es, ax
mov bx, ax
mov cx, ax
mov dx, ax
mov si, ax

mov bx, TEST_STR
call print_string

call loadSMAP
call load_kernel ; Load our kernel
call switch_to_pm ; Switch to protected mode

jmp $

include "bootsector/print_string.ASM"
include "bootsector/disk_load.asm"
include "bootsector/gdt.asm"
include "bootsector/switch_to_pm.asm"
include "bootsector/loadSMAP.asm"

use16
load_kernel :
	    pusha
	    mov bx , KERNEL_OFFSET
	    mov dh , 127 ;load 2^7 - 1 sectors
	    mov cl, 0x02; starting from the 2nd sector
	    mov dl , [ BOOT_DRIVE ]
	    call disk_load
	    popa
	    ret

use32

BEGIN_PM :
	 ;fldcw [FPU_CONTROL]
	 ;call SSE_SUPPORT
	 call KERNEL_OFFSET ; Execute the kernel
jmp $ ; Hang.

;Add support for SSE instructions
;SSE_SUPPORT:
;	 push eax
;	 mov eax, cr0
;	 and ax, 0xFFFB 	 ;clear coprocessor emulation CR0.EM
;	 or ax, 0x2		 ;set coprocessor monitoring  CR0.MP
;	 mov cr0, eax
;	 mov eax, cr4
;	 or ax, 0x600		 ;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
;	 mov cr4, eax
;	 pop eax
;ret

; Global variables
TEST_STR: db "Hello? Its dark...", 0

BOOT_DRIVE db 0

FPU_CONTROL:
	dw 0x007f

; Bootsector padding
times 510 -( $ - $$ ) db 0
dw 0xaa55
use32
file "kernel.BIN"
jp $
times 512*1024 - ($ - $$) db 0
