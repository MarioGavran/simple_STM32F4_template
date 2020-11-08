extern unsigned int _DATA_ROM_START;
extern unsigned int _DATA_RAM_START;
extern unsigned int _DATA_RAM_END;
extern unsigned int _BSS_START;
extern unsigned int _BSS_END;

#define STACK_TOP 0x20040000
void startup();

unsigned int * vectortable[2]
__attribute__ ((section("vectors")))= {
	(unsigned int *) STACK_TOP,
	(unsigned int *) startup
};

void main();

void startup()
{
	unsigned int * data_rom_start_p = &_DATA_ROM_START;
	unsigned int * data_ram_start_p = &_DATA_RAM_START;
	unsigned int * data_ram_end_p = &_DATA_RAM_END;

	while(data_ram_start_p != data_ram_end_p)
	{
		*data_ram_start_p = *data_rom_start_p;
		data_rom_start_p++;
		data_ram_start_p++;
	}

	unsigned int * bss_start_p = &_BSS_START;
	unsigned int * bss_end_p = &_BSS_END;

	while(bss_start_p != bss_end_p)
	{
		*bss_start_p = 0;
		bss_start_p++;
	}

	main();
}


