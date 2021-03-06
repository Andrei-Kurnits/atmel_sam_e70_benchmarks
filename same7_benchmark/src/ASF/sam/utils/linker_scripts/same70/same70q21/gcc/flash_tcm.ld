/*------------------------------------------------------------------------------
 *      Linker script for running in internal FLASH on the ATSAME70Q21
 *----------------------------------------------------------------------------*/

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
SEARCH_DIR(.)

/* Memory Spaces Definitions */
MEMORY
{
  rom (rx)   : ORIGIN = 0x00400000, LENGTH = 0x00200000
  itcm (rwx) : ORIGIN = 0x00000000, LENGTH = 0x00020000
  dtcm (rw)  : ORIGIN = 0x20000000, LENGTH = 0x00020000
  ram (rwx)  : ORIGIN = 0x20400000, LENGTH = 0x00020000
}

/* The stack size used by the application. NOTE: you need to adjust according to your application. */
STACK_SIZE = DEFINED(STACK_SIZE) ? STACK_SIZE : 0x2000;
__ram_end__ = ORIGIN(ram) + LENGTH(ram) - 4; 

/* The heapsize used by the application. NOTE: you need to adjust according to your application. */
HEAP_SIZE = DEFINED(HEAP_SIZE) ? HEAP_SIZE : 0x1000;


SECTIONS
{
    .code_TCM 0x00000000:
    AT ( _itcm_lma )
    {
		. = ALIGN(4);
        _sitcm = .; 
		*(EXCLUDE_FILE (src/ASF/* src/main.o) .text)
        *(EXCLUDE_FILE (src/ASF/* src/main.o) .text.*)
        *(EXCLUDE_FILE (src/ASF/* src/main.o) .rodata.*)
        *(EXCLUDE_FILE (src/ASF/* src/main.o) .fini*)
        _eitcm = .;
    } > itcm

    .data_TCM 0x20000000:
    {
		. = ALIGN(4);
        _sdtcm = .; 
		*(EXCLUDE_FILE (src/ASF/* src/main.o) .data)
        *(EXCLUDE_FILE (src/ASF/* src/main.o) .bss*)
        *(EXCLUDE_FILE (src/ASF/* src/main.o) COMMON)
        _edtcm = .;
    } > dtcm

    .DTCM_stack :
    {
        . = ALIGN(8);
        _sdtcm_stack = .;
        . += STACK_SIZE;
        _edtcm_stack = .;
    } > dtcm
}



/* Section Definitions */
SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        _sfixed = .;
        KEEP(*(.vectors .vectors.*))
        *(.text .text.* .gnu.linkonce.t.*)
        *(.glue_7t) *(.glue_7)
        *(.rodata .rodata* .gnu.linkonce.r.*)
        *(.ARM.extab* .gnu.linkonce.armextab.*)

        /* Support C constructors, and C destructors in both user code
           and the C library. This also provides support for C++ code. */
        . = ALIGN(4);
        KEEP(*(.init))
        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(.preinit_array))
        __preinit_array_end = .;

        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;

        . = ALIGN(0x4);
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*crtend.o(.ctors))

        . = ALIGN(4);
        KEEP(*(.fini))

        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        __fini_array_end = .;

        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*crtend.o(.dtors))

        . = ALIGN(4);
        _efixed = .;            /* End of text section */
    } > rom

    /* .ARM.exidx is sorted, so has to go in its own output section.  */
    PROVIDE_HIDDEN (__exidx_start = .);
    .ARM.exidx :
    {
      *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > rom
    PROVIDE_HIDDEN (__exidx_end = .);

    . = ALIGN(4);
	_itcm_lma = .;
    .relocate_to_itcm :
    {
        . = ALIGN(8);
        . = . + 0x20000; /*SIZEOF(.code_TCM);*/ 
        . = ALIGN(8);
    } > rom

    _etext = .;

    .relocate : AT (_etext)
    {
        . = ALIGN(4);
        _srelocate = .;
        *(.ramfunc .ramfunc.*);
        *(.data .data.*);
        . = ALIGN(4);
        _erelocate = .;
    } > ram

    /* .bss section which is used for uninitialized data */
    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _sbss = . ;
        _szero = .;
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = . ;
        _ezero = .;
    } > ram

    /* stack section */
    .stack (NOLOAD):
    {
        . = ALIGN(8);
        _sstack = .;
        . = . + STACK_SIZE;
        . = ALIGN(8);
        _estack = .;
    } > ram

    /* heap section */
    .heap (NOLOAD):
    {
        . = ALIGN(8);
         _sheap = .;
        . = . + HEAP_SIZE;
        . = ALIGN(8);
        _eheap = .;
    } > ram

    . = ALIGN(4);
    _end = . ;
    _ram_end_ = ORIGIN(ram) + LENGTH(ram) -1 ;
}

