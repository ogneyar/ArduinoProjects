  /**
  @addtogroup USB_Virtual_COM_Port_Echo_MDR32F1QI USB Virtual COM Port Echo for MDR32F1QI evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2022 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    11/05/2021
  * @brief   Description of the USB Example.
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


@par Library and example configure

For configuring both library and example, MDR32FxQI_config.h file is used.
USB Library is configured with USB configuration parameters section, while the example
is configured with VCOM Echo example flags section. In particular, the following macros
are introduced for example configuring:
    - USB_VCOM_SYNC - if this symbol is defined, application guarantees that all incoming data
      is sent to server successfully (EP3 may answer NAK to server if there is delay with sent
      data acceptance). Otherwise, the data is received at the maximum rate and some of it
      may be dropped. The macro is not defined by default.
    - USB_DEBUG_PROTO - if this symbol is defined, auxiliary ring buffer for received setup
      packets by EP0 and sent/received byte counters for EP1/EP3 are introduced in main.c.
      This data structures may be used for JTAG-debugging.


@par Using USB Library handlers

To override default USB Library handlers the MDR32FxQI_usb_handlers.h file is used.
The current example shows the following default USB Library handlers overriding:
    - USB_CDC_HANDLE_DATA_RECEIVE
    - USB_CDC_HANDLE_DATA_SENT       - if USB_VCOM_SYNC is defined
    - USB_CDC_HANDLE_GET_LINE_CODING - if USB_CDC_LINE_CODING_SUPPORTED is defined
    - USB_CDC_HANDLE_SET_LINE_CODING - if USB_CDC_LINE_CODING_SUPPORTED is defined
    - USB_DEVICE_HANDLE_SETUP        - if USB_DEBUG_PROTO is defined


@par Directory contains:

    - inc\MDR32FxQI_usb_handlers.h   USB Library user-defined handlers definition file.
    - src\main.c                     Main program.
    - USB_CDC_DRIVER                 Folder with Virtual COM port driver.


@par Hardware and Software environment:

    - This example is intended to run on MDR32F1QI eval board with MDR32F1QI microcontroller.


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_usb.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_eeprom.c
        MDR32FxQI_bkp.c
        MDR32FxQI_usb_device.c
        MDR32FxQI_usb_CDC.c
    - Edit the MDR32FxQI_config.h to adjust example running mode and to set appropriate
      run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.
    - Setup Virtual COM port driver from USB_CDC_DRIVER folder (on the first run).


 * <h3><center>&copy; COPYRIGHT 2022 Milandr</center></h3>
 */


