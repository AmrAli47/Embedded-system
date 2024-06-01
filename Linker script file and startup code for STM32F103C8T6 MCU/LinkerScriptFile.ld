/* end address of RAM */
_estack = ORIGIN(RAM) + LENGTH(RAM); 

Min_Heap_Size  = 0x200;   /* Heap size */
Min_Stack_Size = 0x4000;  /* stack size */

/* Memories definition */
MEMORY
{
FLASH (rx) : ORIGIN = 0x08000000,  LENGTH = 64K
RAM  (rwx) : ORIGIN = 0x20000000,  LENGTH = 20K
}

SECTIONS
{
/* vector table section in flash*/
.isr_vector :
{
. = ALIGN(4);
*(.isr_vector);
*(.isr_vector*)
. = ALIGN(4);
}> FLASH
/* Program code section in flash*/
.text :
{
. = ALIGN(4);
*(.text);
*(.text*)
. = ALIGN(4);
}> FLASH
/* Read only (global constant) data section in flash*/
.rodata :
{
. = ALIGN(4);
*(.rodata);
*(.rodata*)
. = ALIGN(4);
}> FLASH
/* data section in RAM (startup code will copy .data section from Flash into .data section in RAM */
_sidata = LOADADDR(.data);
.data :
{
. = ALIGN(4);
_sdata = .;
*(.data);
*(.data*)
. = ALIGN(4);
_edata = .;

}> RAM AT> FLASH
/* bss data section in RAM (startup code will initialize this section */
.bss :
{
. = ALIGN(4);
_sbss = .;
*(.bss);
*(.bss*)
. = ALIGN(4);
_ebss = .;
}> RAM
}