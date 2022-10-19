/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.2
  * @date    21/09/2021
  * @brief   Main program body.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32FxQI_config.h"
#include "MDR32FxQI_ssp.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_port.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
 * @{
 */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
 * @{
 */

/** @addtogroup SPI_FullDuplex_MDR32F1QI SPI_FullDuplex
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
    FAILED = 0, PASSED = !FAILED
} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BufferSize         32

/* Private variables ---------------------------------------------------------*/
SSP_InitTypeDef sSSP;
PORT_InitTypeDef PORT_InitStructure;

uint16_t SrcBuf1[BufferSize];
uint16_t SrcBuf2[BufferSize];
uint16_t DstBuf1[BufferSize];
uint16_t DstBuf2[BufferSize];

uint8_t TxIdx = 0, RxIdx = 0;

volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

/* Private function prototypes -----------------------------------------------*/
void Init_RAM ( uint16_t *addr, uint32_t size );
uint32_t ps_rand ( uint32_t addr );
void Zero_RAM ( uint16_t *addr, uint32_t size );
TestStatus Verif_mem ( uint32_t BufSize, uint16_t *pBuffer1, uint16_t *pBuffer2 );

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main ( void )
{
    RST_CLK_DeInit();
    RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSIdiv2, 0);
    /* Enable peripheral clocks */
    RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_SSP1 | RST_CLK_PCLK_SSP2
                    | RST_CLK_PCLK_DMA), ENABLE);
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD), ENABLE);

    /* Disable all DMA request */MDR_DMA ->CHNL_REQ_MASK_CLR = 0xFFFFFFFF;
    MDR_DMA ->CHNL_USEBURST_CLR = 0xFFFFFFFF;

    /* Reset PORTB settings */
    PORT_DeInit(MDR_PORTC);
    /* Reset PORTD settings */
    PORT_DeInit(MDR_PORTD);

    /*Init structure*/
    PORT_StructInit (&PORT_InitStructure);

    /* Configure SSP2 pins: FSS, CLK, RXD, TXD */
    /* Configure PORTF pins 8, 9, 10, 7 */
    PORT_InitStructure.PORT_Pin = (PORT_Pin_8 | PORT_Pin_9 | PORT_Pin_10);
    PORT_InitStructure.PORT_OE = PORT_OE_IN;
    PORT_InitStructure.PORT_FUNC = PORT_FUNC_MAIN;
    PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_PD = PORT_PD_DRIVER;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;
    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    PORT_InitStructure.PORT_Pin = PORT_Pin_7;
    PORT_InitStructure.PORT_OE = PORT_OE_OUT;
    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    /* Configure SSP1 pins: FSS, CLK, RXD, TXD */
    /* Configure PORTD pins 5, 7, 8, 6 */
    PORT_InitStructure.PORT_Pin = PORT_Pin_5 | PORT_Pin_7 | PORT_Pin_8;
    PORT_InitStructure.PORT_OE = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC = PORT_FUNC_ALTER;
    PORT_Init(MDR_PORTC, &PORT_InitStructure);

    PORT_InitStructure.PORT_Pin = PORT_Pin_6;
    PORT_InitStructure.PORT_OE = PORT_OE_IN;
    PORT_Init(MDR_PORTC, &PORT_InitStructure);

    /* Init RAM */
    Zero_RAM(DstBuf1, BufferSize);
    Init_RAM(SrcBuf1, BufferSize);
    Zero_RAM(DstBuf2, BufferSize);
    Init_RAM(SrcBuf2, BufferSize);

    /* Reset all SSP settings */
    SSP_DeInit(MDR_SSP1 );
    SSP_DeInit(MDR_SSP2 );

    SSP_BRGInit(MDR_SSP1, SSP_HCLKdiv16 );
    SSP_BRGInit(MDR_SSP2, SSP_HCLKdiv16 );

    /* SSP1 MASTER configuration */
    SSP_StructInit(&sSSP);

    sSSP.SSP_SCR = 0x10;
    sSSP.SSP_CPSDVSR = 2;
    sSSP.SSP_Mode = SSP_ModeMaster;
    sSSP.SSP_WordLength = SSP_WordLength16b;
    sSSP.SSP_SPH = SSP_SPH_1Edge;
    sSSP.SSP_SPO = SSP_SPO_Low;
    sSSP.SSP_FRF = SSP_FRF_SPI_Motorola;
    sSSP.SSP_HardwareFlowControl = SSP_HardwareFlowControl_SSE;
    SSP_Init(MDR_SSP1, &sSSP);

    /* SSP2 SLAVE configuration */
    sSSP.SSP_SPH = SSP_SPH_1Edge;
    sSSP.SSP_SPO = SSP_SPO_Low;
    sSSP.SSP_CPSDVSR = 12;
    sSSP.SSP_Mode = SSP_ModeSlave;
    SSP_Init(MDR_SSP2, &sSSP);

    /* Enable SSP1 */
    SSP_Cmd(MDR_SSP1, ENABLE);
    /* Enable SSP2 */
    SSP_Cmd(MDR_SSP2, ENABLE);

    /* Transfer procedure */
    while (TxIdx < BufferSize)
    {
        /* Wait for SPI1 Tx buffer empty */
        while (SSP_GetFlagStatus(MDR_SSP1, SSP_FLAG_TFE ) == RESET);

        /* Send SPI1 data */
        SSP_SendData(MDR_SSP1, SrcBuf1[TxIdx]);
        /* Send SPI2 data */
        SSP_SendData(MDR_SSP2, SrcBuf2[TxIdx++]);
        /* Wait for SPI1 data reception */
        while (SSP_GetFlagStatus(MDR_SSP1, SSP_FLAG_RNE ) == RESET);

        /* Read SPI1 received data */
        DstBuf1[RxIdx] = SSP_ReceiveData(MDR_SSP1 );
        /* Wait for SPI2 data reception */
        while (SSP_GetFlagStatus(MDR_SSP2, SSP_FLAG_RNE ) == RESET);

        /* Read SPI2 received data */
        DstBuf2[RxIdx++] = SSP_ReceiveData(MDR_SSP2 );
    }

    /* Check the corectness of written dada */
    TransferStatus1 = Verif_mem((BufferSize), SrcBuf1, DstBuf2);
    TransferStatus2 = Verif_mem((BufferSize), SrcBuf2, DstBuf1);
    /* TransferStatus1, TransferStatus2 = PASSED, if the data transmitted and received
     are correct */
    /* TransferStatus1, TransferStatus2 = FAILED, if the data transmitted and received
     are different */

    while (1);
}

/**
 * @brief  Initialisation memory pseudo random value
 * @param  addr - memory address
 * @param  size - memory size
 * @retval None
 */
void Init_RAM ( uint16_t *addr, uint32_t size )
{
    uint32_t i;

    for (i = 0; i < size; i++) {
        *addr = ps_rand((uint32_t)addr + i*4);
        addr++;
    }
}

/**
 * @brief    Zeroing function memory.
 * @param  addr - memory address
 * @param  size - memory size
 * @retval None
 */
void Zero_RAM ( uint16_t *addr, uint32_t size )
{
    uint32_t i;
    for (i = 0; i < size; i++) {
        addr[i] = 0;
    }
}

/**
 * @brief  Generation random values
 * @param  addr:
 * @retval random value
 */
uint32_t ps_rand ( uint32_t addr )
{
    uint32_t hash = 0;
    uint32_t i;
    char *key = (char *) &addr;

    for (i = 0; i < 4; i++) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    for (i = 0; i < 256; i++) {
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer1, pBuffer2: buffers to be compared.
 * @param  BufSize: buffer's size
 * @retval PASSED: pBuffer1 identical to pBuffer2
 *         FAILED: pBuffer1 differs from pBuffer2
 */
TestStatus Verif_mem ( uint32_t BufSize, uint16_t *pBuffer1, uint16_t *pBuffer2 )
{
    uint32_t i;

    for (i = 0; i < BufSize; i++) {
        if (*pBuffer1++ != *pBuffer2++) {
            return (FAILED);
        }
    }

    return (PASSED);
}

/**
 * @brief  Reports the source file name, the source line number
 *         and expression text (if USE_ASSERT_INFO == 2) where
 *         the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @param  expr:
 * @retval None
 */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the source file name and line number.
     Ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr)
{
    /* User can add his own implementation to report the source file name, line number and
     expression text.
     Ex: printf("Wrong parameters value (%s): file %s on line %d\r\n", expr, file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif /* USE_ASSERT_INFO */

/** @} *//* End of group SPI_FullDuplex_MDR32F1QI */

/** @} *//* End of group __MDR32F1QI_EVAL */

/** @} *//* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *******************************/

/* END OF FILE main.c */


