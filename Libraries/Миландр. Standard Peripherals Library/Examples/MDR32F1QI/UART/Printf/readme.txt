  /**
  @addtogroup UART_Printf UART_Printf for MDR32F1QI evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2022 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    16/07/2021
  * @brief   Description of the UART_Printf Example.
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

This example shows how to redirect the printf and scanf functions of the C library to the UART.
Configure UART1 on an exchange with 115200 Baud rate, 8 bit data size, 1 stop-bit and no parity check.
Configure PORTC line 3 as UART_TXD1.
Configure PORTC line 4 as UART_RXD1.


@par Directory contains:

    - main.c                       Main program
    - retarget_uart.c              Retarget the C library printf and scanf function to the UART
    - retarget_uart.h              Functions prototypes for configuring UART


@par Hardware and Software environment:

    - This example is intended to run on MDR32F1QI evaluation board with MDR32F1QI microcontroller.
    - UART_TXD1 and UART_RXD1 lines of MCU must be connected to the RS-232 transceiver using jumpers according to specification for evaluation board.
    - Connect USB-RS232 cable between PC and evaluation board (DB9 connector for RS-232) to display data on a terminal (for example PuTTY).


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - For the IAR EW in the project settings "General options -> Library Configuration -> Library" you must set the "Full" parameter.
    - Add main.c file.
    - Add retarget_uart.c and retarget_uart.h files.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_bkp.c
        MDR32FxQI_eeprom.c
        MDR32FxQI_uart.c
    - Be sure to uncomment _USE_DEBUG_UART_ macro defined in MDR32FxQI_config.h.
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.

 * <h3><center>&copy; COPYRIGHT 2022 Milandr</center></h3>
 */


