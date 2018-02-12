.intel_syntax

.globl _pageFaultIntWr
.align 4

.text

_pageFaultIntWr:
pushad
cld
call _pageFaultInt
popad
iret
