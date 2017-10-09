static void startPaging()
{
	unsigned int* pageDirectory = 0;
	int largestIdx = 0;
	for(int i = 1;i < *memoryRegions;i++)
	{
		if(memoryRegionDesc[largestIdx].length < memoryRegionDesc[i].length)
			largestIdx = i;
	}
	
	pageDirectory = (unsigned int*) memoryRegionDesc[largestIdx].baseAddress;
	print("The largest memory region is: ");
	printI32(largestIdx);
	print("\n");
	
	//The page diretory will be a series of consecutive entries pointing to consecutive tables
	for(int i = 0 ; i < 1024 ; i++)
	{
		unsigned int* tableAdr = pageDirectory + (i << 12) + 4096;
		pageDirectory[i] =  (unsigned int) tableAdr | 0b0000011;
		
		for(int j = 0 ; j < 1024 ; j++)
		{
			//Map the linear address space to the physical address space: Linear_Address = Physical_Address
			tableAdr[j] = (j << 12) | (i << 22) |  0b100000011;
			/*
			 * Physical address:
			 * 31:22 = i (10-bit)
			 * 21:12 = j (10-bit)
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
	"or eax, 0x80000001;"
	"mov cr0, eax;"
	".att_syntax"
	:
	:
	);
	
	
}
