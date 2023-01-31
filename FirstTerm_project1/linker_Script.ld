/* linker script for cortex-m3
    @Author Eng. Mohamed Eid */

MEMORY
{
    flash(RX) : ORIGIN = 0x08000000, LENGTH = 128K
    sram(RWX) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .text : {
        *(.vectors)
        *(.text)
        _E_TEXT = .;
    } > flash
    
    .rodata : {
        *(.rodata)
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

    . = . + 0x1000;
    _STACK_TOP = .;
}