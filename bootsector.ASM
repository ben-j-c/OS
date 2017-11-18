; A boot sector that boots a C kernel in 32 - bit protected mode
org 0x7c00
KERNEL_OFFSET equ 0x7E00;after the bootsector the kernel is loaded
mov [ BOOT_DRIVE ], dl ; BIOS stores the boot drive in dl
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


mov ebx, [ 0x500 ]; at 0x500 is the length of the memory description
imul ebx, 20; 20 bytes per descriptor
add ebx, 0x504; point to the next 4 bytes
mov al, [ BOOT_DRIVE ]
mov [ ebx ], bl ;store the boot drive

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
jmp $ ; Hang (which will never happen)

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
