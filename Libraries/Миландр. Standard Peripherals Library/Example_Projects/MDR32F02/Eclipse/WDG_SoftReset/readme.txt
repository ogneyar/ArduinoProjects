  /**
  @page WDT_SoftReset example readme for MDR32F02 eval board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2021 Milandr ****************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    29/12/2021
  * @brief   Description of the WDT_SoftReset Example.
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

This example shows how to use the WWDG and IWDG watchdog timers for a soft reset.

Pressing the UP button performs a soft reset using WWDG. The reset takes place immediately after the counter value is written outside the window.
Pressing the DOWN button performs a soft reset using IWDG. The reset occurs after 2 counter clock cycles (~ 250 μs).

@par Directory contains:

    - MLDR187_SPL							SPL library v0.30
    - src/main.c							Main program
    - src/startup_MLDR187.S					default bootloader
    - src/link_Flash.ld						linker script for building program to be stored in flash
    - src/link_RAM.ld						linker script for debugging in RAM
    - MLDR187-ft2232hl.cfg					OpenOCD script to connect to ft2232hl (interface 0) USB-UART bridge tied to JTAG on demo board
    - MLDR187-jlink.cfg						OpenOCD script to connect to Jlink probe attached to JTAG socket on demo board
    - svd/MLDR187_rev1.svd					Peripherals memory-mapped registers definitions for MCU rev. 1
    - svd/MLDR187_rev2.svd					Peripherals memory-mapped registers definitions for MCU rev. 2


@par Hardware and Software environment:

    - This example is intended to run on MLDR187B_Ver2 eval board with MDR32F02 microcontroller.


@par How to use.

To launch the example, you must do the following: 
    - Configure Eclipse IDE with RISC-V toolchain
    - Import this project: File -> Import... -> Existing Projects into Workspace
    - Create launch configuration
    - Build and Run the example
    - Press UP or DOWN button for soft reset

 * <h3><center>&copy; COPYRIGHT 2021 Milandr</center></h3>
 */

