#define PCD 0
#define PWT 0

typedef union
{
	unsigned int word;
	struct PageDirectoryFields
	{
		unsigned char present : 1;
		unsigned char writeEnable : 1;
		unsigned char userPermission : 1;
		unsigned char pageLevelWriteThrough : 1;
		unsigned char pageLevelCacheDisable : 1;
		unsigned char accessed : 1;
		unsigned char ignored1 : 1;
		unsigned char pageSize : 1;
		unsigned char ignored2 : 4;
		unsigned int  tableAddress : 20;
	};

}PageDirectory;

typedef union
{
	unsigned int word;
	struct PageTableFields
	{
		unsigned char present : 1;
		unsigned char writeEnable : 1;
		unsigned char userPermission : 1;
		unsigned char pageLevelWriteThrough : 1;
		unsigned char pageLevelCacheDisable : 1;
		unsigned char accessed : 1;
		unsigned char dirty : 1;
		unsigned char pat : 1;
		unsigned char global : 1;
		unsigned char ignored2 : 3;
		unsigned int  pageAddress : 20;
	};
	
} PageTable;

static void startPaging()
{
	PageDirectory * pageDirectory = 0;
	PageTable* tableAdr = 0;

	int largestIdx = 0;
	for(int i = 1;i < *memoryRegions;i++)
	{
		if(memoryRegionDesc[largestIdx].length < memoryRegionDesc[i].length)
			largestIdx = i;
	}
	
	print("The largest memory region is: ");
	printI32(largestIdx);
	print("\n");
	

	//Directory alignment
	//if the largest region didnt land at a 4k aligned block, shift over to the next
	if((memoryRegionDesc[largestIdx].baseAddress&0xFFF) == 0)
		pageDirectory = (PageDirectory*)  memoryRegionDesc[largestIdx].baseAddress;
	else
		pageDirectory = (PageDirectory*) ((memoryRegionDesc[largestIdx].baseAddress&0xFFFFF000) + 0x1000);
	
	//The page diretory will be a series of consecutive entries pointing to consecutive tables
	for(int i = 0 ; i < 1024 ; i++)
	{
		//The ith page table is after the page directory (pageDirectory + 4096) and after the i-1th
		tableAdr = (PageTable*) ((unsigned int) pageDirectory + (i << 12) + 4096);
		//Set the table address and properties
		//pageDirectory[i].word =  (unsigned int) tableAdr | 0b0000011;
		
		pageDirectory[i].present = 1;
		pageDirectory[i].writeEnable = 1;
		pageDirectory[i].tableAddress = (unsigned int)tableAdr >> 12;
		for(int j = 0 ; j < 1024 ; j++)
		{
			//Map the linear address space to the physical address space: Linear_Address = Physical_Address
			//tableAdr[j].word = (j << 12) | (i << 22) |  0b100000011;
			
			tableAdr[j].present = 1;
			tableAdr[j].writeEnable = 1;
			tableAdr[j].global = 1;
			tableAdr[j].pageAddress = j | (i << 10);
		}
	}
	
	//Proprerties
	pageDirectory = (PageDirectory*)((unsigned int)pageDirectory | (PCD << 4) | (PWT << 3));
	

	__asm__(
	".intel_syntax;"
	"mov cr3, %0;"
	".att_syntax"
	:
	: "r" (pageDirectory)
	);
	
	__asm__(
	".intel_syntax;"
	"mov eax, cr0;"
	"or eax, 0x80000001;" // protected mode and paging enable
	"mov cr0, eax;"
	".att_syntax"
	:
	:
	);
	
	
}
