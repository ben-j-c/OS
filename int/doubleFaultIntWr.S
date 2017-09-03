.intel_syntax

.globl _doubleFaultIntWr
.align 4

.text

_doubleFaultIntWr:
pushad
cld
call _doubleFaultInt
popad
iret
