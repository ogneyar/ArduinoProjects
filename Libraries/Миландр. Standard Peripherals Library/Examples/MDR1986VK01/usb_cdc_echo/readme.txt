  /**
  @addtogroup usb_cdc_echo
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2022 Milandr *******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    07/04/2022
  * @brief   Description of the usb_cdc_echo Example.
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

This example shows how to use USB CDC (Communication Device Class) device as
Virtual COM port implementing "echo" mode (data received from host is sent back to host).

@par Directory contains:

  - main.c                                Main program
  - MDR1986VK01_usb_CDC.c                  USB Communication Device Class source file
  - MDR1986VK01_usb_CDC.h                  USB Communication Device Class header file
  - MDR1986VK01_usb_default_handlers.h     USB default handlers file
  - MDR1986VK01_usb_device.c               USB Library device source file
  - MDR1986VK01_usb_device.h               USB Library device header file

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VK01 demo board with MDR1986VK01
  microcontroller.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR1986VK01_port.h
        MDR1986VK01_clk.h
        MDR1986VK01_delay.h
        MDR1986VK01_usb.h
        adc.h
        
  - Edit the MDR1986VK01_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2022 Milandr</center></h3>
 */


