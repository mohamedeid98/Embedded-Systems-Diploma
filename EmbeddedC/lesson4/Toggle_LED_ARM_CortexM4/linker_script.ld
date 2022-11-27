/* linker_script CortexM3
Eng. Mohamed Eid
*/

MEMORY
{
	flash(RX) : ORIGIN = 0x00000000, LENGTH = 512M
	sram(RWX) : ORIGIN = 0x20000000, LENGTH = 512M
}

SECTIONS
{
	.text : {
		*(.vectors*)
		*(.text*)
		*(.rodata)
		_E_TEXT = .;
	} > flash
	
	.data : {
		_S_DATA = .;
		*(.data)
		_E_DATA = .;
	} > sram AT> flash
	.bss : {
		_S_BSS = .;
		*(.bss)
		. = ALIGN(4);
		_E_BSS = .;
	} > sram
}