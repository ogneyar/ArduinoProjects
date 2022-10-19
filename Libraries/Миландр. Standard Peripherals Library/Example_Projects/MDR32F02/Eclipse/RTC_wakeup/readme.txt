  /**
  @page RTC_wakeup example readme for MDR32F02 demo board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2021 Milandr ****************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    14/07/2021
  * @brief   Description of the RTC_wakeup Example.
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

This example shows, how to enter power-save mode and wake up on external event.
When main power supply is turned off and battery domain is powered,
it automatically sets SW pin to 1 when external event (WAKEUP1-3) is triggered.
On MLDR187B demo board, SW pin controls power switch that connects battery power source to main power line

In this example, program can function in 2 modes: normal and power-save.
In normal mode it does some stuff in main loop and handles external event on WAKEUP1
In power-save mode it only handles event on WAKEUP1 and then turns main power off (SW = 0)
It automatically detects if main power supply is present or not and chooses corresponding mode.

@par Directory contains:

    - MLDR187_SPL							SPL library v0.29
    - src/init.c							Common initialisation of used peripherals and LED control functions
    - src/init.h
    - src/main.c							Main program
    - src/startup_MLDR187.S					default bootloader
    - src/syscalls.c						syscalls wrappers
    - src/link_Flash.ld						linker script for building program to be stored in flash
    - src/link_RAM.ld						linker script for debugging in RAM
    - MLDR187-ft2232hl.cfg					OpenOCD script to connect to ft2232hl (interface 0) USB-UART bridge tied to JTAG on demo board
    - MLDR187-jlink.cfg						OpenOCD script to connect to Jlink probe attached to JTAG socket on demo board
    - src/									Peripherals memory-mapped registers definitions


@par Hardware and Software environment:

    - This example is intended to run on MLDR187B_Ver2 demo board with MDR32F02 microcontroller.


@par How to use.

To launch the example, you must do the following: 
    - Configure Eclipse IDE with RISC-V toolchain
    - Open serial terminal on a COM port, associated with ft2232hl (Interface 1) device
    - Import this project: File -> Import... -> Existing Projects into Workspace
    - Create launch configuration
    - Build and Run the example in Flash
    - Take out and then insert battery into battery slot
    - Disconnect main power supply
	- Connect external 3.3V power supply to BUcc Ext
	- Press Wake1 button and make sure the LED2 is blinking

 * <h3><center>&copy; COPYRIGHT 2021 Milandr</center></h3>
 */

