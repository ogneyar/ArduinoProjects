  /**
  @page SPI_DMA example readme for MDR32F02 demo board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2021 Milandr ****************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    14/07/2021
  * @brief   Description of the SPI Example.
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

This example shows, how to use DMA with SPI.

The program performs a single SPI exchange asynchronously with DMA.
It sends a command to read device ID and receives the response.
At the end of transfer it sets a flag to tell the main loop that transfer is done.
Alternatively, you can initiate another SPI exchange in the interrupt handler in a same way.


@par Directory contains:

    - MLDR187_SPL							SPL library v0.29
    - src/main.c							Main program
    - src/startup_MLDR187.S					default bootloader
    - src/syscalls.c						syscalls wrappers needed for printf to send data to UART
    - src/link_Flash.ld						linker script for building program to be stored in flash
    - src/link_RAM.ld						linker script for debugging in RAM
    - MLDR187-ft2232hl.cfg					OpenOCD script to connect to ft2232hl (interface 0) USB-UART bridge tied to JTAG on demo board
    - MLDR187-jlink.cfg						OpenOCD script to connect to Jlink probe attached to JTAG socket on demo board
    - src/									Peripherals memory-mapped registers definitions


@par Hardware and Software environment:

    - This example is intended to run on MLDR187B_Ver2 demo board with MDR32F02 microcontroller.
    - This example is tested with XM25QH32B SPI flash memory chip as a slave device


@par How to use.

To launch the example, you must do the following:
    - Connect pins (Vcc, GND, CLK, CS, MOSI, MISO) of SPI slave device to SPI2 of MLDR187
    - Connect serial terminal to COM port, associated with ft2232hl (Interface 1) device
    - Configure Eclipse IDE with RISC-V toolchain
    - Import this project: File -> Import... -> Existing Projects into Workspace
    - Create launch configuration
    - Build and Run the example.
    - Check serial port output

 * <h3><center>&copy; COPYRIGHT 2021 Milandr</center></h3>
 */

