/*****************************************************************************
*
* @file    src/link_Flash.ld
* @author  Milandr Application Team
* @version V1.0.2
* @date    01/06/2021
* @brief   Linker Script.
*
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/

/* It defines following symbols, which code can use without definition:
 *   __data_load_start
 *   __data_start
 *   __sdata_start
 *   __data_end
 *   __bss_start
 *   __bss_end
 *   __global_pointer$
 *   __end
 *   __ahbram_data_load_start
 *   __ahbram_data_start
 *   __ahbram_data_end
 *   __ahbram_bss_start
 *   __ahbram_bss_end
 *   __ramfunc_load_start
 *   __ramfunc_start
 *   __ramfunc_end
 *   __stack_top
 *   __stack_size
 *   __stack_limit
 *   __heap_top
 *   __heap_min_size
 *   __heap_size
 *   __heap_limit
 */

OUTPUT_ARCH( "riscv" )
ENTRY(_start)

/* __stack_size - total stack size */
__stack_size    	= 0x1000;
/* __heap_min_size - minimum heap size, used to check if space can be allocated. The total heap size (__heap_size) takes up all space from end of the .bss to beginning of .stack */
__heap_min_size     = 0x1000;

/* Specify the memory areas */
MEMORY
{
	FLASH     (rx)      : ORIGIN = 0x10000000, LENGTH = 256K
	OTP       (rx)      : ORIGIN = 0x00020000, LENGTH = 16K
	TCMA_RAM  (xrw)     : ORIGIN = 0x80000000, LENGTH = 64K
	TCMB_RAM  (xrw)     : ORIGIN = 0x80010000, LENGTH = 32K
	AHB_RAM   (xrw)     : ORIGIN = 0x20000000, LENGTH = 16K
}

/* Description of regions:
- REGION_LOAD     - region where the program is stored
- REGION_DATA     - region where initialized and uninitialized data, stack and heap are located
- REGION_RAMFUNC  - the region of RAM where the code is stored                 */

/* RUN IN FLASH */
  REGION_ALIAS("REGION_LOAD",    FLASH);
  REGION_ALIAS("REGION_DATA",    TCMA_RAM);
  REGION_ALIAS("REGION_RAMFUNC", TCMB_RAM);

/* RUN IN RAM */
/*REGION_ALIAS("REGION_LOAD",    TCMB_RAM);
  REGION_ALIAS("REGION_DATA",    TCMA_RAM);
  REGION_ALIAS("REGION_RAMFUNC", TCMB_RAM);*/

/* Define output sections */
/* ">vma_region" - VMA (virtual memory address), 
   "AT>lma_region" - LMA (load memory address) */

SECTIONS
{
  /* The startup code goes first into REGION_LOAD */
  .text.init :
  {
	*(.text.init)
  } >REGION_LOAD
  
  /* The program code goes into REGION_LOAD */
  .text :
  {
	. = ALIGN(4);
	*(.text*)
  } >REGION_LOAD

  /* Read-only data goes into REGION_LOAD */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata*)
  	*(.srodata*)
  } >REGION_LOAD
  
  /* Alignment of the following section .data */  
  .dalign :
  {
    . = ALIGN(4);
  } >REGION_LOAD
  
  /* Initialized data section goes into REGION_DATA, load from REGION_LOAD */
  __data_load_start = LOADADDR(.data);
  .data :
  {
    . = ALIGN(4);
	__data_start = .;
	*(.data*)
	. = ALIGN(8);
	__sdata_start = .;
	*(.sdata*)
  } >REGION_DATA AT>REGION_LOAD
  
  . = ALIGN(4);
  __data_end = .;
  
  /* Uninitialized data section goes into REGION_DATA*/
  .bss :
  {
	. = ALIGN(8);
    __bss_start = .; 
    *(.sbss*)
	*(.scommon)
	*(.bss*)
    *(COMMON)
	. = ALIGN(8);
	__bss_end = .;
	/* The linker uses the __global_pointer$ symbol definition to compare the memory addresses and,
	   if within range, it replaces absolute/pc-relative addressing with gp-relative addressing,
	   which makes the code more efficient. */
	__global_pointer$ = MIN(__sdata_start + 0x800, MAX(__data_start + 0x800, __bss_end - 0x800));
  } >REGION_DATA AT>REGION_DATA
  
  . = ALIGN(8);
  __end = .;
  
  /* Alignment of the following section .ahbram */
  .aalign :
  {
    . = ALIGN(4);
  } >REGION_LOAD
  
  /* AHB_RAM section */
  /* Initialized ahbram_data section goes into AHB_RAM, load from REGION_LOAD */
  __ahbram_data_load_start = LOADADDR(.ahbram_data);
  .ahbram_data :
  {
    . = ALIGN(4);
    __ahbram_data_start = .;
    *(.ahbram_data)
    . = ALIGN(4);
    __ahbram_data_end = .;
  } >AHB_RAM AT>REGION_LOAD
  
  .ahbram_bss :
  {
    . = ALIGN(4);
    __ahbram_bss_start = .;
    *(.ahbram_bss)
    . = ALIGN(4);
    __ahbram_bss_end = .;
  } >AHB_RAM AT>AHB_RAM
  
  /* Alignment of the following section .ramfunc */
  .ralign :
  {
    . = ALIGN(4);
  } >REGION_LOAD
  
  /* RAM functions goes into REGION_RAMFUNC, loaded from REGION_LOAD */
  __ramfunc_load_start = LOADADDR(.ramfunc);
  .ramfunc :
  {
    . = ALIGN(4);
	__ramfunc_start = .;
	*(.ramfunc*)
  } >REGION_RAMFUNC AT>REGION_LOAD
  
  . = ALIGN(4);   
  __ramfunc_end = .;
  
  /* Stack and Heap symbol definitions */
  __stack_top = ORIGIN(REGION_DATA) + LENGTH(REGION_DATA);
  __stack_limit = __stack_top - __stack_size;
  __heap_top = __end;
  __heap_size = __stack_limit - __heap_top;
  __heap_limit = __heap_top + __heap_size;
  
  /* Check allocation for heap of size __heap_min_size */
  ASSERT(__heap_size >= __heap_min_size, "Unable to allocate __heap_min_size for heap!")
   
  /* .heap section doesn't contains any symbols. 
     It is only used for linker to calculate size of heap sections, and assign values to heap symbols */
  .heap __heap_top :
  {
	. += __heap_size;
  } >REGION_DATA

  /* .stack section doesn't contains any symbols. 
     It is only used for linker to calculate size of stack sections, and assign values to stack symbols */
  .stack __stack_limit :
  {
	. += __stack_size;
  } >REGION_DATA
}