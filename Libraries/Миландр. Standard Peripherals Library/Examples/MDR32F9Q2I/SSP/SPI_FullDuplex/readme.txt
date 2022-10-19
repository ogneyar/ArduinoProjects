  /**
  @addtogroup SPI_FullDuplex_MDR32F9Q2I SPI_FullDuplex for MDR32F9Q2I evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2022 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    27/07/2021
  * @brief   Description of the SPI_FullDuplex Example.
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

This example provides a description of how to set a communication between SPI1 and SPI2 in full-duplex mode and performs a
transfer from Master to Slave.
Both SPIs are configured with 16bit data frame and a 7Kbit/s communication speed.
The master SPI1 starts the SrcBuf1 transfer while the slave SPI1 transmit SrcBuf2. Once the transfer is
completed a comparison is done and TransferStatus1 and TransferStatus2 gives the data transfer status for each data transfer
direction where it is PASSED if transmitted and received data are the same otherwise it is FAILED.


@par Directory contains:

    - main.c     Main program


@par Hardware and Software environment:

    - This example is intended to run on MDR32F9Q2I eval board with MDR32F9Q2I microcontroller.
    - Connect SSP1 FSS pin (X26.1. 8) to SSP2 FSS pin (X27.1.21).
    - Connect SSP1 CLK pin (X26.1.10) to SSP2 CLK pin (X27.1.20).
    - Connect SSP1 RXD pin (X26.1. 7) to SSP2 TXD pin (X27.1.19).
    - Connect SSP1 TXD pin (X26.1.11) to SSP2 RXD pin (X27.1.22).


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_ssp.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.

 * <h3><center>&copy; COPYRIGHT 2022 Milandr</center></h3>
 */


