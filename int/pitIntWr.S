.intel_syntax

.globl _pitIntWr
.align 4

.text

_pitIntWr:
pushad
cld
call _pitInt
popad
iret
