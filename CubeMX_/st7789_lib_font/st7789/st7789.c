#include "stm32f0xx_hal.h"
#include <st7789.h>
#include "font5x7.h"
#include "font7x11.h"
#include <gpio.h>
#include <stdlib.h>
#include <string.h>

uint8_t ST7789_Width, ST7789_Height;

void ST7789_Init(uint8_t Width, uint8_t Height)
{
  ST7789_Width = Width;
  ST7789_Height = Height;
  
  ST7789_HardReset(); 
  ST7789_SoftReset();
  ST7789_SleepModeExit();

  ST7789_ColorModeSet(ST7789_ColorMode_65K | ST7789_ColorMode_16bit);
  HAL_Delay(10);
  ST7789_MemAccessModeSet(4, 1, 1, 0);
  HAL_Delay(10);
  ST7789_InversionMode(1);
  HAL_Delay(10);
  ST7789_FillScreen(0);
  ST7789_SetBL(10);
  ST7789_DisplayPower(1);
  HAL_Delay(100);
}

void ST7789_HardReset(void)
{
	HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
  HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET);
  HAL_Delay(150);
}

void ST7789_SoftReset(void)
{
  ST7789_SendCmd(ST7789_Cmd_SWRESET);
  HAL_Delay(130);
}

void ST7789_SendCmd(uint8_t Cmd)
{
  HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
  //HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
	if (READ_BIT(SPI1->CR1, SPI_CR1_SPE) != (SPI_CR1_SPE)) SET_BIT(SPI1->CR1, SPI_CR1_SPE);
	*((__IO uint8_t *)&SPI1->DR) = Cmd;
  //HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

void ST7789_SendData(uint8_t Data)
{
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
  //HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
  if (READ_BIT(SPI1->CR1, SPI_CR1_SPE) != (SPI_CR1_SPE)) SET_BIT(SPI1->CR1, SPI_CR1_SPE);
	*((__IO uint8_t *)&SPI1->DR) = Data;
  //HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

void ST7789_SleepModeEnter( void )
{
	ST7789_SendCmd(ST7789_Cmd_SLPIN);
  HAL_Delay(500);
}

void ST7789_SleepModeExit( void )
{
	ST7789_SendCmd(ST7789_Cmd_SLPOUT);
  HAL_Delay(500);
}


void ST7789_ColorModeSet(uint8_t ColorMode)
{
  ST7789_SendCmd(ST7789_Cmd_COLMOD);
  ST7789_SendData(ColorMode & 0x77);  
}

void ST7789_MemAccessModeSet(uint8_t Rotation, uint8_t VertMirror, uint8_t HorizMirror, uint8_t IsBGR)
{
  uint8_t Value;
  Rotation &= 7; 

  ST7789_SendCmd(ST7789_Cmd_MADCTL);
  
  switch (Rotation)
  {
  case 0:
    Value = 0;
    break;
  case 1:
    Value = ST7789_MADCTL_MX;
    break;
  case 2:
    Value = ST7789_MADCTL_MY;
    break;
  case 3:
    Value = ST7789_MADCTL_MX | ST7789_MADCTL_MY;
    break;
  case 4:
    Value = ST7789_MADCTL_MV;
    break;
  case 5:
    Value = ST7789_MADCTL_MV | ST7789_MADCTL_MX;
    break;
  case 6:
    Value = ST7789_MADCTL_MV | ST7789_MADCTL_MY;
    break;
  case 7:
    Value = ST7789_MADCTL_MV | ST7789_MADCTL_MX | ST7789_MADCTL_MY;
    break;
  }
  
  if (VertMirror)
    Value = ST7789_MADCTL_ML;
  if (HorizMirror)
    Value = ST7789_MADCTL_MH;
  
  if (IsBGR)
    Value |= ST7789_MADCTL_BGR;
  
  ST7789_SendData(Value);
}

void ST7789_InversionMode(uint8_t Mode)
{
  if (Mode)
    ST7789_SendCmd(ST7789_Cmd_INVON);
  else
    ST7789_SendCmd(ST7789_Cmd_INVOFF);
}

void ST7789_FillScreen(uint16_t color)
{
  ST7789_FillRect(0, 0,  ST7789_Width, ST7789_Height, color);
}

void ST7789_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  if ((x >= ST7789_Width) || (y >= ST7789_Height)) return;
  if ((x + w) > ST7789_Width) w = ST7789_Width - x;
  if ((y + h) > ST7789_Height) h = ST7789_Height - y;
  ST7789_SetWindow(x, y, x + w - 1, y + h - 1);
  for (uint32_t i = 0; i < (h * w); i++) ST7789_RamWrite(&color, 1);
}

void ST7789_SetWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  ST7789_ColumnSet(x0, x1);
  ST7789_RowSet(y0, y1);
  ST7789_SendCmd(ST7789_Cmd_RAMWR);
}

void ST7789_RamWrite(uint16_t *pBuff, uint16_t Len)
{
  while (Len--)
  {
    ST7789_SendData(*pBuff >> 8);  
    ST7789_SendData(*pBuff & 0xFF);
  }  
}

static void ST7789_ColumnSet(uint16_t ColumnStart, uint16_t ColumnEnd)
{
  if (ColumnStart > ColumnEnd)
    return;
  if (ColumnEnd > ST7789_Width)
    return;
  
  ColumnStart += ST7789_X_Start;
  ColumnEnd += ST7789_X_Start;
  
  ST7789_SendCmd(ST7789_Cmd_CASET);
  ST7789_SendData(ColumnStart >> 8);  
  ST7789_SendData(ColumnStart & 0xFF);  
  ST7789_SendData(ColumnEnd >> 8);  
  ST7789_SendData(ColumnEnd & 0xFF);  
}

static void ST7789_RowSet(uint16_t RowStart, uint16_t RowEnd)
{
  if (RowStart > RowEnd)
    return;
  if (RowEnd > ST7789_Height)
    return;
  
  RowStart += ST7789_Y_Start;
  RowEnd += ST7789_Y_Start;
  
  ST7789_SendCmd(ST7789_Cmd_RASET);
  ST7789_SendData(RowStart >> 8);  
  ST7789_SendData(RowStart & 0xFF);  
  ST7789_SendData(RowEnd >> 8);  
  ST7789_SendData(RowEnd & 0xFF);  
}

void ST7789_SetBL(uint8_t Value)
{
  if (Value > 100)
    Value = 100;
  
#if (ST77xx_BLK_PWM_Used)
  //tmr2_PWM_set(ST77xx_PWM_TMR2_Chan, Value);
#else
  if (Value)
		HAL_GPIO_WritePin(BLK_GPIO_Port, BLK_Pin, GPIO_PIN_SET);
  else
		HAL_GPIO_WritePin(BLK_GPIO_Port, BLK_Pin, GPIO_PIN_RESET);
#endif
}

void ST7789_DisplayPower(uint8_t On)
{
  if (On)
    ST7789_SendCmd(ST7789_Cmd_DISPON);
  else
    ST7789_SendCmd(ST7789_Cmd_DISPOFF);
}

void ST7789_DrawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) 
{
  ST7789_DrawLine(x1, y1, x1, y2, color);
  ST7789_DrawLine(x2, y1, x2, y2, color);
  ST7789_DrawLine(x1, y1, x2, y1, color);
  ST7789_DrawLine(x1, y2, x2, y2, color);
}

void ST7789_DrawRectangleFilled(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t fillcolor) 
{
  if (x1 > x2)
    SwapInt16Values(&x1, &x2);
  if (y1 > y2)
    SwapInt16Values(&y1, &y2);
	ST7789_FillRect(x1, y1, x2 - x1, y2 - y1, fillcolor);
}

void ST7789_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) 
{
  // Вертикальная линия
  if (x1 == x2)
  {
    // Отрисовываем линию быстрым методом
    if (y1 > y2)
      ST7789_FillRect(x1, y2, 1, y1 - y2 + 1, color);
    else
      ST7789_FillRect(x1, y1, 1, y2 - y1 + 1, color);
    return;
  }
  
  // Горизонтальная линия
  if (y1 == y2)
  {
    // Отрисовываем линию быстрым методом
    if (x1 > x2)
      ST7789_FillRect(x2, y1, x1 - x2 + 1, 1, color);
    else
      ST7789_FillRect(x1, y1, x2 - x1 + 1, 1, color);
    return;
  }
  
  ST7789_DrawLine_Slow(x1, y1, x2, y2, color);
}

static void SwapInt16Values(int16_t *pValue1, int16_t *pValue2)
{
  int16_t TempValue = *pValue1;
  *pValue1 = *pValue2;
  *pValue2 = TempValue;
}

static void ST7789_DrawLine_Slow(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) 
{
  const int16_t deltaX = abs(x2 - x1);
  const int16_t deltaY = abs(y2 - y1);
  const int16_t signX = x1 < x2 ? 1 : -1;
  const int16_t signY = y1 < y2 ? 1 : -1;

  int16_t error = deltaX - deltaY;

  ST7789_DrawPixel(x2, y2, color);

  while (x1 != x2 || y1 != y2) 
  {
    ST7789_DrawPixel(x1, y1, color);
    const int16_t error2 = error * 2;
 
    if (error2 > -deltaY) 
    {
      error -= deltaY;
      x1 += signX;
    }
    if (error2 < deltaX)
    {
      error += deltaX;
      y1 += signY;
    }
  }
}

void ST7789_DrawPixel(int16_t x, int16_t y, uint16_t color)
{
  if ((x < 0) ||(x >= ST7789_Width) || (y < 0) || (y >= ST7789_Height))
    return;

  ST7789_SetWindow(x, y, x, y);
  ST7789_RamWrite(&color, 1);
}

void ST7789_DrawCircleFilled(int16_t x0, int16_t y0, int16_t radius, uint16_t fillcolor) 
{
  int x = 0;
  int y = radius;
  int delta = 1 - 2 * radius;
  int error = 0;

  while (y >= 0)
  {
    ST7789_DrawLine(x0 + x, y0 - y, x0 + x, y0 + y, fillcolor);
    ST7789_DrawLine(x0 - x, y0 - y, x0 - x, y0 + y, fillcolor);
    error = 2 * (delta + y) - 1;

    if (delta < 0 && error <= 0) 
    {
      ++x;
      delta += 2 * x + 1;
      continue;
    }
	
    error = 2 * (delta - x) - 1;
		
    if (delta > 0 && error > 0) 
    {
      --y;
      delta += 1 - 2 * y;
      continue;
    }
	
    ++x;
    delta += 2 * (x - y);
    --y;
  }
}

void ST7789_DrawCircle(int16_t x0, int16_t y0, int16_t radius, uint16_t color) 
{
  int x = 0;
  int y = radius;
  int delta = 1 - 2 * radius;
  int error = 0;

  while (y >= 0)
  {
    ST7789_DrawPixel(x0 + x, y0 + y, color);
    ST7789_DrawPixel(x0 + x, y0 - y, color);
    ST7789_DrawPixel(x0 - x, y0 + y, color);
    ST7789_DrawPixel(x0 - x, y0 - y, color);
    error = 2 * (delta + y) - 1;

    if (delta < 0 && error <= 0) 
    {
      ++x;
      delta += 2 * x + 1;
      continue;
    }
	
    error = 2 * (delta - x) - 1;
		
    if (delta > 0 && error > 0) 
    {
      --y;
      delta += 1 - 2 * y;
      continue;
    }
	
    ++x;
    delta += 2 * (x - y);
    --y;
  }
}

void ST7789_DrawChar_5x8(uint16_t x, uint16_t y, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg, unsigned char c) 
{
  if((x >= 240) || (y >= 240) || ((x + 4) < 0) || ((y + 7) < 0)) return;
  if(c<128)            c = c-32;
  if(c>=144 && c<=175) c = c-48;
  if(c>=128 && c<=143) c = c+16;
  if(c>=176 && c<=191) c = c-48;
  if(c>191)  return;
  for (uint8_t i=0; i<6; i++ ) 
	{
		uint8_t line;
    if (i == 5) line = 0x00;
    else line = font[(c*5)+i];
		for (uint8_t j = 0; j<8; j++)
		{
			if (line & 0x01) ST7789_DrawPixel(x + i, y + j, TextColor);
			else if (!TransparentBg) ST7789_DrawPixel(x + i, y + j, BgColor);
			line >>= 1;
		}
	}
}

void ST7789_DrawChar_7x11(uint16_t x, uint16_t y, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg, unsigned char c) 
{
	uint8_t i,j;
  uint8_t buffer[11];
	
  if((x >= 240) || (y >= 240) || ((x + 4) < 0) || ((y + 7) < 0)) return;
	
	// Copy selected simbol to buffer
	memcpy(buffer,&font7x11[(c-32)*11],11);
	for(j=0;j<11;j++)
	{
		for(i=0;i<7;i++)
		{
			if ((buffer[j] & (1<<i)) == 0) 
			{
				if (!TransparentBg) ST7789_DrawPixel(x + i, y + j, BgColor);
			}
			else ST7789_DrawPixel(x + i, y + j, TextColor);
		}			
	}
}

void ST7789_print_5x8(uint16_t x, uint16_t y, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg, char *str) 
{
  unsigned char type = *str;
  if (type>=128) x = x - 3;
  while (*str)
	{		
		ST7789_DrawChar_5x8(x, y, TextColor, BgColor, TransparentBg, *str++); 
    unsigned char type = *str;
    if (type>=128) x=x+3;
    else x=x+6;
  }
}

void ST7789_print_7x11(uint16_t x, uint16_t y, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg, char *str) 
{
  unsigned char type = *str;
  if (type>=128) x = x - 3;
  while (*str)
	{		
		ST7789_DrawChar_7x11(x, y, TextColor, BgColor, TransparentBg, *str++); 
    unsigned char type = *str;
    if (type>=128) x=x+8;
    else x=x+8;
  }
}
