  /**
  @addtogroup BKP_RTC_MDR32F1QI BKP_RTC for MDR32F1QI evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2022 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    11/05/2021
  * @brief   Description of the BKP_RTC Example.
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

This example shows how to use BKP module functions.
That action includes the following steps:
    - Configure PORTD line 10,11 as output LED;
    - Configure RTC clock source;
    - Enable RTC interrupts;
    - Set RTC counter,prescaller and alarm values;
    - Enable RTC;
    - Switch On\Off LED1 when SECF Flag is set;
    - Switch On LED2 when ALRF is set.


@par Directory contains:

    - main.c                     Main program
    - MDR32F1QI_IT.c           Main Interrupt Service Routines
    - MDR32F1QI_IT.h           Functions prototypes for the interrupt


@par Hardware and Software environment:

    - This example is intended to run on MDR32F1QI eval board with MDR32F1QI microcontroller.
    - VD7 (LED1), VD8 (LED2) are connected to PD.10, PD.11 pins, respectively.
    - If using LSE, then jumper XP5, XP6 should be set to OSC_IN32 and OS_OUT32.  


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add MDR32F1QI_IT.c and MDR32F1QI_IT.h files.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_bkp.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.


 * <h3><center>&copy; COPYRIGHT 2022 Milandr</center></h3>
 */


