.intel_syntax

.globl _divideByZeroIntWr
.align 4

.text

_divideByZeroIntWr:
pushad
cld
call _divideByZeroInt
popad
iret
