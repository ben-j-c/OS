#include "interruptInit.h"

typedef struct {
   unsigned short offset_1; // offset bits 0..15
   unsigned short selector; // a code segment selector in GDT or LDT
   unsigned char zero;      // unused, set to 0
   unsigned char type_attr; // type and attributes, see below
   unsigned short offset_2; // offset bits 16..31
} __attribute__((packed)) IDTDescr;

volatile IDTDescr idtTable[256];
volatile unsigned char IDT[6];
 
/*
 * This was taken from OSDev wiki
 * 
 * 
arguments:
	offset1 - vector offset for master PIC vectors on the master become offset1..offset1+7
	offset2 - same for slave PIC: offset2..offset2+7
*/
void PIC_remap(int offset1, int offset2)
{
	unsigned char a1, a2;
 
	a1 = portInB(PIC1_DATA);                        // save masks
	a2 = portInB(PIC2_DATA);
 
	portOutB(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	portOutB(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	io_wait();
	portOutB(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	portOutB(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	portOutB(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	portOutB(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	portOutB(PIC1_DATA, ICW4_8086);
	io_wait();
	portOutB(PIC2_DATA, ICW4_8086);
	io_wait();
 
	portOutB(PIC1_DATA, a1);   // restore saved masks.
	portOutB(PIC2_DATA, a2);
}

void NMI_enable(void)
{
	portOutB(0x70, portInB(0x70)&0x7F);
}
 
void NMI_disable(void)
{
	portOutB(0x70, portInB(0x70)|0x80);
}

void PIC_sendEOI_MASTER()
{
	portOutB(0x20,0x20);
}

void PIC_sendEOI_SLAVE()
{
	portOutB(0xA0,0x20);
}

void interruptInit()
{
	print("interruptInit: ");
	printX32((unsigned int) interruptInit);
	print("\n");
	printX32(sizeof(IDT));
	print("\n");
	
	*(unsigned short*)(IDT) = sizeof(IDTDescr)*256 - 1;
	IDT[5] = (0xff000000 & (unsigned int) idtTable) >> 24;
	IDT[4] = (0xff0000 & (unsigned int) idtTable) >> 16;
	IDT[3] = (0xff00 & (unsigned int) idtTable) >> 8;
	IDT[2] = (0xff & (unsigned int) idtTable);
	
	//here is where we set the values in the interrupt table
	idtTable[0x0].offset_1 = (0xffff & (unsigned int) divideByZeroIntWr);
	idtTable[0x0].offset_2 = (0xffff0000 & (unsigned int) divideByZeroInt) >> 16;
	idtTable[0x0].type_attr = 0x8E;
	idtTable[0x0].selector = 0b0000000000001000;
	
	idtTable[0x8].offset_1 = (0xffff & (unsigned int) doubleFaultIntWr);
	idtTable[0x8].offset_2 = (0xffff0000 & (unsigned int) doubleFaultInt) >> 16;
	idtTable[0x8].type_attr = 0x8E;
	idtTable[0x8].selector = 0b0000000000001000;
	
	idtTable[0x20].offset_1 = (0xffff & (unsigned int) pitIntWr);
	idtTable[0x20].offset_2 = (0xffff0000 & (unsigned int) pitIntWr) >> 16;
	idtTable[0x20].type_attr = 0x8E;
	idtTable[0x20].selector = 0b0000000000001000;
	
	idtTable[0x21].offset_1 = (0xffff & (unsigned int) keyboardIntWr);
	idtTable[0x21].offset_2 = (0xffff0000 & (unsigned int) keyboardIntWr) >> 16;
	idtTable[0x21].type_attr = 0x8E;
	idtTable[0x21].selector = 0b0000000000001000;
	
	print("\nIDT Length: ");
	printX32(*(unsigned short*)(IDT));
	print("\nIDT start: ");
	printX32(*(unsigned int*)(IDT+ 2));
	print("\nidtTable: ");
	printX32((unsigned int)idtTable);
	print("\n");
	
	
	__asm__("lidt %0" :: "m"(IDT));
	
	PIC_remap(0x20, 0x30);
	PIC_sendEOI_MASTER();
	PIC_sendEOI_SLAVE();
	portOutB(0x21,0x00);
	portOutB(0xa1,0x00);
	
	NMI_enable();
	
	
	__asm__("sti");
	
}
