/* STM32F446RE: 512 kB Flash, 128 kB RAM */

ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    .text :
    {
        *(.text*)
    } > FLASH

    .rodata :
    {
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    .data :
    {
        . = ALIGN(4);
        _sdata = .;    /* RAM begin of .data */
        *(.data*)
        . = ALIGN(4);
        _edata = .;    /* RAM end of data */
    } > RAM AT > FLASH

    /* FLASH */
    _sidata = LOADADDR(.data);

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;      /* RAM begin of .bss */
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;      /* RAM end of .bss */
    } > RAM
}