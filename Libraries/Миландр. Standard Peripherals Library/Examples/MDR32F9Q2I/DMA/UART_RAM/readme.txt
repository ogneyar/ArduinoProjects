  /**
  @addtogroup DMA_UART_RAM_MDR32F9Q2I DMA_UART_RAM for MDR32F9Q2I evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2022 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    27/07/2021
  * @brief   Description of the DMA_UART_RAM Example.
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

This example provides a basic communication between UART1 and UART2 using DMA capability.
First, the DMA transfers data from SrcBuf1 buffer to UART1 Transmit data register,
then this data is sent to UART2.
Data received by USART2 is transferred by DMA and stored in DstBuf2 then compared with
the send ones and the result of this comparison is stored in the "TransferStatus2" variable.

In the same time, the DMA transfers data from SrcBuf2 buffer to UART2 Transmit data register,
then this data is sent to UART1. Data received by UART1 is transferred by DMA and stored in
DstBuf1 then compared with the send ones and the result of this comparison is stored in the
"TransferStatus1" variable.

UART1 and UART2 configured as follow:

    - BaudRate = 1200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - FIFO enable
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled


@par Directory contains:

    - main.c           Main program


@par Hardware and Software environment:

    - This example is intended to run on MDR32F9Q2I eval board with MDR32F9Q2I microcontroller.
    - Connect UART1 RXD pin (X26.1.19) to UART2 TXD pin (X27.1.20).
    - Connect UART1 TXD pin (X26.1.18) to UART2 RXD pin (X27.1.19).

@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_uart.c
        MDR32FxQI_dma.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.

 * <h3><center>&copy; COPYRIGHT 2022 Milandr</center></h3>
 */


