#define PCD 0
#define PWT 0

static void startPaging()
{
	unsigned int* pageDirectory = 0;
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
	if((memoryRegionDesc[largestIdx].baseAddress&0xFFF) == 0)
		pageDirectory = (unsigned int*)  memoryRegionDesc[largestIdx].baseAddress;
	else
		pageDirectory = (unsigned int*) ((memoryRegionDesc[largestIdx].baseAddress&0xFFFFF000) + 0x1000);
	
	//Proprerties
	pageDirectory = (unsigned int*) ((unsigned int) pageDirectory | (PCD << 4) | ( PWT << 3));
	
	
	//The page diretory will be a series of consecutive entries pointing to consecutive tables
	for(int i = 0 ; i < 1024 ; i++)
	{
		unsigned int* tableAdr = pageDirectory + (i << 12) + 4096;
		//Set the table address and properties
		pageDirectory[i] =  (unsigned int) tableAdr | 0b0000011;
		/* 
		 * Properties (intel x86 dev manual table 4-5) from LSB to MSB:
		 * Present
		 * R/W access
		 * Supervisor only
		 * No PWT
		 * PCD not disabled
		 * Not accessed
		 * Ignored bit
		 * Not 4MB page
		 */
		for(int j = 0 ; j < 1024 ; j++)
		{
			//Map the linear address space to the physical address space: Linear_Address = Physical_Address
			tableAdr[j] = (j << 12) | (i << 22) |  0b100000011;
			/*
			 * Physical address:
			 * [31:22] = i (10-bit)
			 * [21:12] = j (10-bit)
			 * 
			 * Properties (intel x86 dev manual table 4-6):
			 * Present
			 * R/W access
			 * Supervisor only
			 * No PWT
			 * PCD not disabled
			 * Not accessed
			 * Not dirty
			 * PAT disabled
			 * This is a global translation
			 */
		}
	}
	

	
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
