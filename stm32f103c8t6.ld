MEMORY{
    RAM (RWX) : ORIGIN = 0x20000000, LENGTH = 20K
    FLASH (RX) : ORIGIN = 0x08000000, LENGTH = 64K
}

_estack = ORIGIN(RAM)+LENGTH(RAM);

SECTIONS{
    .text : {
        . = ALIGN(4);
        *(.isr_vector*)
        *(.text*)
        _etext = .;
    } > FLASH

    .bss : {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        _ebss = .;
    } >RAM

    .data : {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        _edata = .;
        _sidata = LOADADDR(.data);
   } > RAM AT> FLASH

    .rodata : {
        *(.rodata*)
    } > FLASH
}

