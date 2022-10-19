  /**
  @addtogroup PORT_Joystick_LEDs_MDR32F9Q2I PORT_Joystick_LEDs for MDR32F9Q2I evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2022 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    27/07/2021
  * @brief   Description of the PORT_Joystick_LEDs Example.
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

This example shows how to use input/output ports.
PORTB is configured for input. Its 6 pin are connected to the joystick button.
PORTE is configured for input. Its 3 pin are connected to the joystick button.
PORTC is configured for output. Its 0..1 pins control LED indicators.


@par Directory contains:

    - main.c          Main program


@par Hardware and Software environment:

    - This example is intended to run on MDR32F9Q2I eval board with MDR32F9Q2I microcontroller.
    - "LEFT" and "RIGHT" joystick buttons are connected to PE.3, PB.6 pins, respectively.
    - VD3, VD4 LEDs are connected to PC.0, PC.1 pins, respectively.


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.

 * <h3><center>&copy; COPYRIGHT 2022 Milandr</center></h3>
 */


