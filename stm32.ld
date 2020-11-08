SECTIONS
{
	. = 0x00000000;

	.text :
	{
		*(vectors)
		*(.text)
	}
	.rodata :
	{
		*(.rodata)
	}
	_DATA_ROM_START = .;
	
	. = 0x20000000;

	_DATA_RAM_START = .;
	.data : AT(_DATA_ROM_START)
	{
		*(.data)
	}
	_DATA_RAM_END = .;

	_BSS_START = .;
	.bss :
	{
		*(bss)
	}
	_BSS_END = .;
}
