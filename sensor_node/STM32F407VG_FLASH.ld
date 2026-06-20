ENTRY(Reset_Handler)

MEMORY
{
    flash (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
    sram (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(sram) + LENGTH(sram);

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    }> flash

    _sidata = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    }> sram AT> flash

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    }> sram
}
