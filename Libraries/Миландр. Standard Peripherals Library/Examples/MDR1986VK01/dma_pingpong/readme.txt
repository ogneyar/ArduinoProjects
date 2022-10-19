  /**
  \addtogroup dma_pingpong readme
  @{
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2022 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.0.2
  * @date    28/01/2021
  * @brief   Description of the dma_pingpong Example.
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

This example shows, how to use DMA.
In this demo there are DMA, DAC and Timer initialisation functions and DMA done interrupt handler function. 
DMA works in ping pong mode, changing two structures with different data portions outputs to DAC channel.
User can watch signal using oscilloscope and XW5 on demo board.

@par Directory contains:

  - main.c                 Main program
  - MDR1986VK01_it.c        Main Interrupt Service Routines
  - MDR1986VK01_it.h        Functions prototypes for the interrupt

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VK01 demo board with MDR1986VK01 
  microcontroller.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR1986VK01_port.h
        MDR1986VK01_timer.h
        MDR1986VK01_dma.h
        MDR1986VK01_clk.h
        demoboard.h
        dac.h
        adc.h
        
  - Edit the MDR1986VK01_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2022 Milandr</center></h3>
 */


