/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/12/21
* Description        : CH32F103 IAP 
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "debug.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "iap.h"
#include "usb_istr.h"
#include "usb_desc.h"

/* Global define */


/* Global Variable */    
extern u8 End_Flag;

void IAP_2_APP(void)
{
	USB_Port_Set(DISABLE, DISABLE);	
	printf("jump APP\r\n");
	Delay_Ms(10);
	iap_load_app(0x08000000 + User_APP_Addr_offset);
}
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main(void)
{   
	u8 usbstatus=0;	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init(); 
	
	USART_Printf_Init(115200);  
	printf("SystemClk:%d\r\n",SystemCoreClock);
	 
	printf("IAP Test\r\n");
	
	
  USART3_CFG(57600);	
 	USBD_CFG();
	  
	while(1)
	{
		if(End_Flag)
		{
       Delay_Ms(50);
       IAP_2_APP();
       while(1);
		}
		if(usbstatus!=bDeviceState)
		{
			usbstatus=bDeviceState;
			
			if(usbstatus==CONFIGURED)
			{
			}else
			{			
			}
		}
		
		EP2_RecData_Deal();
		if( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET){
			UART_Rx_Deal();
		}		
		
		IWDG_ReloadCounter();
	}
}







