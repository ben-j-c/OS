.intel_syntax

.globl _keyboardIntWr
.align 4

.text

_keyboardIntWr:
pushad
cld
call _keyboardInt
popad
iret
