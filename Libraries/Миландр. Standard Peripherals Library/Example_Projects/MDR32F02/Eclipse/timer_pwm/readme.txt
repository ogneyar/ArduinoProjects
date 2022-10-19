  /**
  @page timer_pwm_periodic_task example readme for MDR32F02 demo board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2021 Milandr ****************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    14/07/2021
  * @brief   Description of the timer_pwm_periodic_task Example.
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

This example shows, how to use timer's PWM feature to control power of LED in time.
Also it shows how to implement periodic task scheduler using timers.

@par Directory contains:

    - MLDR187_SPL							SPL library v0.29
    - src/init.c							CPU clock init
    - src/init.h							
    - src/wait.c							Real-time wait and periodic task scheduler
    - src/wait.h							
    - src/pwm.c								timers configuration to setup PWM
    - src/pwm.h								
    - src/main.c							Main program
    - src/startup_MLDR187.S					default bootloader
    - src/syscalls.c						syscalls wrappers
    - src/link_Flash.ld						linker script for building program to be stored in flash
    - src/link_RAM.ld						linker script for debugging in RAM
    - MLDR187-ft2232hl.cfg					OpenOCD script to connect to ft2232hl (interface 0) USB-UART bridge tied to JTAG on demo board
    - MLDR187-jlink.cfg						OpenOCD script to connect to Jlink probe attached to JTAG socket on demo board
    - src/									Peripherals memory-mapped registers definitions


@par Hardware and Software environment:

    - This example is intended to run on MLDR187B_Ver2 demo board with MDR32F02 microcontroller.


@par How to use.

To launch the example, you must do the following: 
    - Configure Eclipse IDE with RISC-V toolchain
    - Import this project: File -> Import... -> Existing Projects into Workspace
    - Create launch configuration
    - Connect I\O ports with PWM output to LED ports:
    	PA0 -- PD0
    	PA2 -- PD1
    	PA4 -- PD2
    	PA6 -- PD3
    - Build and Run the example
    - Look at LEDs

 * <h3><center>&copy; COPYRIGHT 2021 Milandr</center></h3>
 */

