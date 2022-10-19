  /**
  @addtogroup DAC_DMA_SineWave_MDR32F1QI DAC_DMA_SineWave for MDR32F1QI evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2022 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    11/06/2021
  * @brief   Description of the DAC DMA_SineWave Example.
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

This example describes how to use DAC with DMA to generate sine waves on DAC channel output.
Configure PORTE line 9 as DAC1_OUT .
DMA channel10 is configured to transfer ping-pong mode, word by word, a 32-word
buffer to DAC register DAC1_DATA. The transfered 32 buffer is made to have 
a sine wave generation on DAC channel output. DAC channel1 is enabled.
Once TIM1 is enabled, each TIM1 CNT_ARR_EVENT generate a DMA request which 
transfer data to the  DAC DATA register and DAC conversion is started. 
The sine waves can be visualized by connecting DAC_OUT jack to an oscilloscope.

@par Directory contains:

    - main.c               Main program
    - MDR32F1QI_IT.      Main Interrupt Service Routines
    - MDR32F1QI_IT.      Functions prototypes for the interrupt


@par Hardware and Software environment:

    - This example is intended to run on MDR32F1QI eval board with MDR32F1QI microcontroller.
    -  XP33 jamper must be switched into a state SMA.


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add MDR32F1QI_IT.c and MDR32F1QI_IT.h files.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_dac.c
        MDR32FxQI_timer.c
        MDR32FxQI_dma.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.


 * <h3><center>&copy; COPYRIGHT 2022 Milandr</center></h3>
 */


