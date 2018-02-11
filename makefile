DRIVER_FILES = 	$(wildcard C/drivers/*.c)
ASM_FILES = 	$(wildcard int/*.S)
INT_FILES = 	$(wildcard C/int/*.c)
UTIL_FILES = 	$(wildcard C/util/*.c)
KERNEL_FILES = 	$(wildcard C/*.c)

OBJS_DRIVERS =  $(addprefix C/drivers/obj/,$(notdir $(DRIVER_FILES:.c=.o)))
OBJS_ASM = 		$(addprefix int/obj/,$(notdir $(ASM_FILES:.S=.o)))
OBJS_INT = 		$(addprefix C/int/obj/,$(notdir $(INT_FILES:.c=.o)))
OBJS_UTIL = 	$(addprefix C/util/obj/,$(notdir $(UTIL_FILES:.c=.o)))

CC = gcc
CFLAGS = -IC -ffreestanding -nostdlib -std=c99 -m32 -O0 -c -ggdb -mno-ms-bitfields
LINKER = ld
LFLAGS = -T linkscript.ld -m i386pe
OCOPY = objcopy
OFLAGS = -O binary 




kernel.BIN: obj/kernel.tmp
	$(OCOPY) $(OFLAGS) obj/kernel.tmp kernel.BIN
	
obj/kernel.tmp: obj/kernel.o $(OBJS_DRIVERS) $(OBJS_ASM) $(OBJS_INT) $(OBJS_UTIL)
	$(LINKER) $(LFLAGS) -o obj/kernel.tmp obj/kernel.o $(OBJS_DRIVERS) $(OBJS_ASM) $(OBJS_INT) $(OBJS_UTIL)
	
obj/kernel.o: $(DRIVER_FILES) $(ASM_FILES) $(INT_FILES) $(UTIL_FILES) $(KERNEL_FILES)
	$(CC) $(CFLAGS) -o obj/kernel.o C/kernel.c




C/drivers/obj/%.o: C/drivers/%.c
	$(CC) $(CFLAGS) -o $@ $<

int/obj/%.o: int/%.S
	$(CC) $(CFLAGS) -o $@ $<

C/int/obj/%.o: C/int/%.c
	$(CC) $(CFLAGS) -o $@ $<
	
C/util/obj/%.o: C/util/%.c
	$(CC) $(CFLAGS) -o $@ $<



clean:
	rm obj/* *.BIN int/obj/*.o C/int/obj/* C/drivers/obj/*
