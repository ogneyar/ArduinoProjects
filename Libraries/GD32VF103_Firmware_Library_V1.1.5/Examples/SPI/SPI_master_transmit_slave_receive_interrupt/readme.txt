/*!
    \file    readme.txt
    \brief   description of the master transmit and slave receive using interrupt mode

    \version 2019-06-05, V1.0.0, firmware for GD32VF103
    \version 2020-08-04, V1.1.0, firmware for GD32VF103
    \version 2022-05-18, V1.1.1, firmware for GD32VF103
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

  This example is based on the GD32V103V-EVAL-V1.0 board, it shows master sends data
and slave receives data using interrupt mode.

  1.Modify files: examlple/SPI/SPI_master_transmit_slave_receive_interrupt/main.h, choose
to disable CRC function.
  #define SPI_CRC_ENABLE       0
  After the communication is completed, if the data received equal to the data sent, LED2
turn on, and if not, LED2 turn off.

  2.Modify files: examlple/SPI/SPI_master_transmit_slave_receive_interrupt/main.h, choose
to enable CRC function.
  #define SPI_CRC_ENABLE       1
  After the communication is completed, if the CRC checking is passed, LED2 turn on,
and if not, LED2 turn off.

  Connect SPI0 SCK  PIN(PA5) to SPI2 SCK  PIN(PC10).
  Connect SPI0 MOSI PIN(PA7) to SPI2 MISO PIN(PC11).