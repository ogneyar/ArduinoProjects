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
#include "MDR32FxQI_usb_handlers.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_eeprom.h"
#include "MDR32FxQI_bkp.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
 * @{
 */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
 * @{
 */

/** @addtogroup  USB_Virtual_COM_Port_Echo_MDR32F1QI USB Virtual COM Port Echo
 * @{
 */

/* Private define ------------------------------------------------------------*/
#define BUFFER_LENGTH                        100

/* Private variables ---------------------------------------------------------*/
USB_Clock_TypeDef USB_Clock_InitStruct;
USB_DeviceBUSParam_TypeDef USB_DeviceBUSParam;

static uint8_t Buffer[BUFFER_LENGTH];

#ifdef USB_CDC_LINE_CODING_SUPPORTED
    static USB_CDC_LineCoding_TypeDef LineCoding;
#endif /* USB_CDC_LINE_CODING_SUPPORTED */

#ifdef USB_VCOM_SYNC
    volatile uint32_t PendingDataLength = 0;
#endif /* USB_VCOM_SYNC */

/* USB protocol debugging */
#ifdef USB_DEBUG_PROTO

    #define USB_DEBUG_NUM_PACKETS   100

    typedef struct
    {
        USB_SetupPacket_TypeDef packet;
        uint32_t address;
    } TDebugInfo;

    static TDebugInfo SetupPackets[USB_DEBUG_NUM_PACKETS];
    static uint32_t SPIndex;
    static uint32_t ReceivedByteCount, SentByteCount, SkippedByteCount;

#endif /* USB_DEBUG_PROTO */

/* Private function prototypes -----------------------------------------------*/
static void Setup_CPU_Clock ( void );
static void Setup_USB ( void );
static void VCom_Configuration ( void );

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program - initialization and empty infinite loop
  * @param  None
  * @retval None
  */
int main(void)
{
    VCom_Configuration();

    /* CDC layer initialization */
    USB_CDC_Init(Buffer, 1, SET);

    Setup_CPU_Clock();
    Setup_USB();

    /* Main loop */
    while (1)
    {
    }
}

/**
  * @brief  Frequencies setup
  * @param  None
  * @retval None
  */
void Setup_CPU_Clock ( void )
{
    /* Reset the clock system settings */
    RST_CLK_DeInit();
    
    /* Enable HSE (High Speed External) clock */
    RST_CLK_HSEconfig(RST_CLK_HSE_ON);
    if(RST_CLK_HSEstatus() != SUCCESS)
    {
        while (1);
    }
    
    /* Configures the CPU_PLL clock source (CPU_CLK = HSE_CLK * 16 = 8 MHz * 16 = 128 MHz) */
    RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul16);
    /* Enables the CPU_PLL */
    RST_CLK_CPU_PLLcmd(ENABLE);
    if(RST_CLK_CPU_PLLstatus() == ERROR)
    {
        while (1);
    }
    
    /* Select the CPU_PLL output as input for CPU_C2_SEL */
    RST_CLK_CPU_PLLuse(ENABLE);
    /* Set CPUClk Prescaler (CPU_C3_SEL = CPU_C2) */
    RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
    
    /* Enables the RST_CLK_PCLK_EEPROM */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);
    /* Sets the code latency value (CPU_CLK up to 144 MHz) */
    EEPROM_SetLatency(EEPROM_Latency_5);
    /* Disables the RST_CLK_PCLK_EEPROM */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, DISABLE);
    
    /* Enables the RST_CLK_PCLK_BKP */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_BKP, ENABLE);
    /* Setting the parameters of the voltage regulator SelectRI and LOW in the BKP controller (CPU_CLK = 128 MHz) */
    BKP_DUccMode(BKP_DUcc_over_80MHz);

    /* Select the CPU clock source */
    RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
}

/**
  * @brief  USB Device layer setup and powering on
  * @param  None
  * @retval None
  */
void Setup_USB(void)
{
    /* Enables the CPU_CLK clock on USB */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_USB, ENABLE);

    /* Device layer initialization */
    USB_Clock_InitStruct.USB_USBC1_Source = USB_C1HSEdiv1;
    USB_Clock_InitStruct.USB_PLLUSBMUL = USB_PLLUSBMUL6;

    USB_DeviceBUSParam.MODE = USB_SC_SCFSP_Full;
    USB_DeviceBUSParam.SPEED = USB_SC_SCFSR_12Mb;
    USB_DeviceBUSParam.PULL = USB_HSCR_DP_PULLUP_Set;

    USB_DeviceInit(&USB_Clock_InitStruct, &USB_DeviceBUSParam);

    /* Enable all USB interrupts */
    USB_SetSIM(USB_SIS_Msk);

    USB_DevicePowerOn();

    /* Enable interrupt on USB */
#ifdef USB_INT_HANDLE_REQUIRED
    NVIC_EnableIRQ(USB_IRQn);
#endif /* USB_INT_HANDLE_REQUIRED */

    USB_DEVICE_HANDLE_RESET;
}

/**
  * @brief  Example-relating data initialization
  * @param  None
  * @retval None
  */
static void VCom_Configuration ( void )
{
#ifdef USB_CDC_LINE_CODING_SUPPORTED
    LineCoding.dwDTERate = 115200;
    LineCoding.bCharFormat = 0;
    LineCoding.bParityType = 0;
    LineCoding.bDataBits = 8;
#endif /* USB_CDC_LINE_CODING_SUPPORTED */
}

/**
  * @brief  USB_CDC_HANDLE_DATA_RECEIVE implementation - data echoing
  * @param  Buffer: Pointer to the user's buffer with received data
  * @param  Length: Length of data
  * @retval @ref USB_Result.
  */
USB_Result USB_CDC_RecieveData ( uint8_t* Buffer, uint32_t Length )
{
    USB_Result result;

#ifdef USB_DEBUG_PROTO
    ReceivedByteCount += Length;
#endif /* USB_DEBUG_PROTO */

    /* Send back received data portion */
    result = USB_CDC_SendData(Buffer, Length);

#ifdef USB_DEBUG_PROTO
    if (result == USB_SUCCESS) {
        SentByteCount += Length;
    }
#ifndef USB_VCOM_SYNC
    else
    {
        SkippedByteCount += Length;
    }
#endif /* !USB_VCOM_SYNC */
#endif /* USB_DEBUG_PROTO */

#ifdef USB_VCOM_SYNC
    if (result != USB_SUCCESS) {
        /* If data cannot be sent now, it will await nearest possibility
         * (see USB_CDC_DataSent) */
        PendingDataLength = Length;
    }
    return result;
#else
    return USB_SUCCESS;
#endif /* USB_VCOM_SYNC */
}

#ifdef USB_VCOM_SYNC

/**
  * @brief  USB_CDC_HANDLE_DATA_SENT implementation - sending of pending data
  * @param  None
  * @retval @ref USB_Result.
  */
USB_Result USB_CDC_DataSent ( void )
{
    USB_Result result = USB_SUCCESS;

    if (PendingDataLength)
    {
        result = USB_CDC_SendData(Buffer, PendingDataLength);
#ifdef USB_DEBUG_PROTO
        if (result == USB_SUCCESS)
        {
            SentByteCount += PendingDataLength;
        }
        else
        {
            SkippedByteCount += PendingDataLength;
        }
#endif /* USB_DEBUG_PROTO */
        PendingDataLength = 0;
        USB_CDC_ReceiveStart();
    }
    return USB_SUCCESS;
}

#endif /* USB_VCOM_SYNC */

#ifdef USB_CDC_LINE_CODING_SUPPORTED

/**
  * @brief  USB_CDC_HANDLE_GET_LINE_CODING implementation example
  * @param  wINDEX: Request value 2nd word (wIndex)
  * @param  DATA: Pointer to the USB_CDC Line Coding Structure
  * @retval @ref USB_Result.
  */
USB_Result USB_CDC_GetLineCoding ( uint16_t wINDEX,
        USB_CDC_LineCoding_TypeDef* DATA )
{
    assert_param(DATA);
    if (wINDEX != 0)
    {
        /* Invalid interface */
        return USB_ERR_INV_REQ;
    }

    /* Just store received settings */
    *DATA = LineCoding;
    return USB_SUCCESS;
}

/**
  * @brief  USB_CDC_HANDLE_SET_LINE_CODING implementation example
  * @param  wINDEX: Request value 2nd word (wIndex)
  * @param  DATA: Pointer to the USB_CDC Line Coding Structure
  * @retval @ref USB_Result.
  */
USB_Result USB_CDC_SetLineCoding ( uint16_t wINDEX,
        const USB_CDC_LineCoding_TypeDef* DATA )
{
    assert_param(DATA);
    if (wINDEX != 0)
    {
        /* Invalid interface */
        return USB_ERR_INV_REQ;
    }

    /* Just send back settings stored earlier */
    LineCoding = *DATA;
    return USB_SUCCESS;
}

#endif /* USB_CDC_LINE_CODING_SUPPORTED */

#ifdef USB_DEBUG_PROTO

/**
  * @brief  Overwritten USB_DEVICE_HANDLE_SETUP default handler - to dump received setup packets
  * @param  EPx: USB Control EndPoint (EP0) number
  * @param  USB_SetupPacket: Pointer to a USB_SetupPacket_TypeDef structure
  *         that contains received setup packet contents (on success)
  * @retval @ref USB_Result.
  */
USB_Result USB_DeviceSetupPacket_Debug ( USB_EP_TypeDef EPx,
        const USB_SetupPacket_TypeDef* USB_SetupPacket )
{

#ifdef USB_DEBUG_PROTO
    SetupPackets[SPIndex].packet = *USB_SetupPacket;
    SetupPackets[SPIndex].address = USB_GetSA();
    SPIndex = (SPIndex < USB_DEBUG_NUM_PACKETS ? SPIndex + 1 : 0);
#endif /* USB_DEBUG_PROTO */

    return USB_DeviceSetupPacket(EPx, USB_SetupPacket);
}

#endif /* USB_DEBUG_PROTO */

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

/** @} *//* End of group USB_Virtual_COM_Port_Echo_MDR32F1QI */

/** @} *//* End of group __MDR32F1QI_EVAL */

/** @} *//* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
 *
 * END OF FILE main.c */


