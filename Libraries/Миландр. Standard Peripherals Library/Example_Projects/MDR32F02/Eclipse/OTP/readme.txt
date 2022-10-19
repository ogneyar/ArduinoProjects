  /**
  @page OTP example readme for MDR32F02 demo board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2021 Milandr ****************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    14/07/2021
  * @brief   Description of the OTP Example.
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

This example shows, how to use One-Time-Programmable memory area.
It covers how to write data to OTP and compile functions for running in OTP

The program is split in two parts:
 
 - program/* -- defines some functions and writes them to OTP at specific address.
 				Every function is stored in separate section. Addresses of these sections are configured in the linker script.
 				
 - src/* -- some program that uses functions from OTP stored at specific address with known signature.
            This example program writes data to flash jumping to OTP to perform flash operations.

!!! WARNING !!!
You can not erase data in OTP, so please examine all source files before running this example.


@par Directory contains:

    - MLDR187_SPL							SPL library v0.29
    
    - src/*									Example program that uses function from OTP
    - src/init.c							Common initialisation of used peripherals
    - src/init.h
    - src/main.c							Main program
    - src/otp.h								Declarations of functions stored in OTP
    - src/startup_MLDR187.S					default bootloader
    - src/syscalls.c						syscalls wrappers
    - src/link_Flash.ld						linker script for building program to be stored in flash
    - src/link_RAM.ld						linker script for debugging in RAM
    
    - program/*								Source files for writing functions to OTP
    - program/init.c						Common initialisation of used peripherals
    - program/init.h
    - program/main.c						Main program
    - program/otp_functions.c				Implementation of functions stored in OTP
    - program/otp_functions.h				
    - program/otp.c							helper functions for working with OTP
    - program/otp.h
    - program/startup_MLDR187.S				default bootloader
    - program/syscalls.c					syscalls wrappers
    - program/link_RAM_OTP.ld				linker script for placing some functions in OTP, and whole program in RAM
    
    - MLDR187-ft2232hl.cfg					OpenOCD script to connect to ft2232hl (interface 0) USB-UART bridge tied to JTAG on demo board
    - MLDR187-jlink.cfg						OpenOCD script to connect to Jlink probe attached to JTAG socket on demo board
    - src/									Peripherals memory-mapped registers definitions


@par Hardware and Software environment:

    - This example is intended to run on MLDR187B_Ver2 demo board with MDR32F02 microcontroller.


@par How to use.

To launch the example, you must do the following:
    - Configure Eclipse IDE with RISC-V toolchain
    - Import this project: File -> Import... -> Existing Projects into Workspace
    - Create launch configurations for OTP and for main program
    - Build and Run Program_OTP and verify that it has exited main() without errors.
    - Build and Run main program.

 * <h3><center>&copy; COPYRIGHT 2021 Milandr</center></h3>
 */

