  /**
  @addtogroup Ethernet_IT Ethernet for MDR32F1QI evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2022 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    15/06/2021
  * @brief   Description of the Ethernet Example.
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

This example contain:
  - the example of ICMP echo server.
  - the example of TELNET echo server.


@par Directory contains:

    - src/main.c                Main program.
    - src/MDR32F1QI_IT.c      Main Interrupt Service Routines.
    - src/tcpip.c               Functions for processing ethernet frames.
    - src/hash.c                Functions for HASH calculations.
    - inc/MDR32F1QI_IT.h      Functions prototypes for the interrupt.
    - inc/tcpip.h               Functions prototypes for the TCPIP.
    - inc/hash.h                Functions prototypes for HASH calculations.


@par Hardware and Software environment:

  - This example is intended to run on MDR32F1QI eval board with MDR32F1QI microcontroller.

@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_eth.c
        MDR32FxQI_timer.c
        MDR32FxQI_eeprom.c
        MDR32FxQI_uart.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Place EEPROM functions in RAM by defining section "EXECUTABLE_MEMORY_SECTION" as RAM section.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.
If used FIFO mode, config scatter file to DMA enable.


 * <h3><center>&copy; COPYRIGHT 2022 Milandr</center></h3>
 */


