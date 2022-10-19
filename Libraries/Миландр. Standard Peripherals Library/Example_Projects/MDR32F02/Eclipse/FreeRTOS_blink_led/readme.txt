  /**
  @page FreeRTOS_blink_led example readme for MDR32F02 demo board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2021 Milandr ****************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.0.2
  * @date    27/01/2022
  * @brief   Description of the FreeRTOS_blink_led Example.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  @endverbatim
  @endlatexonly

@par Example Description

This example shows, how to configure and build FreeRTOS for MLDR187.
And then, run two simple asynchronous tasks.

@par Directory contains:

    - MLDR187_SPL							SPL library v0.29
    - FreeRTOS								https://github.com/FreeRTOS/FreeRTOS-Kernel
    										only needed files are kept
 	- src/FreeRTOSConfig.h					FreeRTOS application-dependent configuration
 	- src/freertos_riscv_chip_specific_extensions.h		FreeRTOS RISC-V application-dependent configuration
 	- src/hooks.c							some system event handlers for FreeRTOS
 	- src/init.c							common peripherals init
 	- src/init.h
    - src/main.c							Main program
    - src/startup_MLDR187.S					default bootloader
    - src/syscalls.c						syscalls wrappers
    - src/link_Flash.ld						linker script for building program to be stored in flash
    - src/link_RAM.ld						linker script for debugging in RAM
    - MLDR187-ft2232hl.cfg					OpenOCD script to connect to ft2232hl (interface 0) USB-UART bridge tied to JTAG on demo board
    - MLDR187-jlink.cfg						OpenOCD script to connect to Jlink probe attached to JTAG socket on demo board
    - svd/MLDR187_rev1.svd					Peripherals memory-mapped registers definitions for MCU rev. 1
    - svd/MLDR187_rev2.svd					Peripherals memory-mapped registers definitions for MCU rev. 2


@par Hardware and Software environment:

    - This example is intended to run on MLDR187B_Ver2 demo board with MDR32F02 microcontroller.


@par How to use.

To launch the example, you must do the following: 
    - Configure Eclipse IDE with RISC-V toolchain
    - Import this project: File -> Import... -> Existing Projects into Workspace
    - Edit FreeRTOSConfig.h to set the appropriate microcontroller revision (MCU_REVx macro)
    - Create launch configuration
    - Build and Run the example
    - Look at LEDs

 * <h3><center>&copy; COPYRIGHT 2021 Milandr</center></h3>
 */

