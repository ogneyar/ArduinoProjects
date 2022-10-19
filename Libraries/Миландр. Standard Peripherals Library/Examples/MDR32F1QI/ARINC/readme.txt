  /**
  @addtogroup ARINC429_MDR32F1QI ARINC for MDR32F1QI evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2022 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    11/05/2021
  * @brief   Description of the ARINC Example.
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

This example provides a description of how to set a communication with the ARINC.
The ARINC transmitter send the data array and the ARINC receiver take the data
in the interrupt on presence of of data in the FIFO.
The received frame is checked and LED1 light up to indicate what the 
communication was successful, else LED2 light up.


@par Directory contains:

    - main.c                Main program
    - MDR32F1QI_IT.c      Main Interrupt Service Routines
    - MDR32F1QI_IT.h      Functions prototypes for the interrupt


@par Hardware and Software environment:

    - This example is intended to run on MDR32F1QI eval board with 
      MDR32F1QI microcontroller.
    - Pin PB0 must be connected to pin PD13.
    - Pin PB1 must be connected to pin PD14.
    - VD6 jamper must be enable.
    - VD7 jamper must be enable.


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_eeprom.h
        MDR32FxQI_arinc429r.c
        MDR32FxQI_arinc429t.c
        MDR32FxQI_uart.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.


 * <h3><center>&copy; COPYRIGHT 2022 Milandr</center></h3>
 */


