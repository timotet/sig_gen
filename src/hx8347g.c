/*
 * hx8347g.c
 *
 * For driving a HX8347g LCD
 * Hacked from the internet
 *
 * Created on: Apr 11, 2015
 *      Author: timotet
 *
 * Reworked 2/19/19 for sine wave generator project
 */

#include "stm32f0xx.h"
#include "spi.h"
#include "hx8347g.h"
#include "font_5x7.h"
#include "font_11x16.h"
#include "font_8x12.h"
#include "sevenSeg.h"
#include "delay.h"
#include "stdbool.h"
#include "math.h"


#define START_BYTE         0x70
#define SET_INDEX          0x00
#define READ_STATUS        0x01
#define LCD_WRITE_REG      0x02
#define LCD_READ_REG       0x03


// Global variables
bool flipFlag = false; // for clear function
static __IO uint16_t TextColor = 0x0000, BackColor = 0xFFFF;
uint16_t LCDType = 0;

void
LCD_GPIO_Init(void) { // Initialize the GPIO pins needed other than SPI which is in SPI_init

	GPIO_InitTypeDef GPIO_InitStructure;
	// GPIOB Periph clock enable
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	// Configure PB5 and PB4 in output push pull mode
	GPIO_InitStructure.GPIO_Pin = LCD_Reset | LCD_CS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	LCD_Reset_Low;
	LCD_CS_High;
}

void
hx8347g_Init(void) {

	LCD_GPIO_Init();

	LCD_Reset_Low;
	delay(1);
	LCD_Reset_High;
	delay(5);

	// Register settings
	LCD_WriteReg(LCD_REG_234, 0x00);
	LCD_WriteReg(LCD_REG_235, 0x20);
	LCD_WriteReg(LCD_REG_236, 0x0C);
	LCD_WriteReg(LCD_REG_237, 0xC4);
	LCD_WriteReg(LCD_REG_232, 0x40);
	LCD_WriteReg(LCD_REG_233, 0x38);
	LCD_WriteReg(LCD_REG_241, 0x01);
	LCD_WriteReg(LCD_REG_242, 0x10);
	LCD_WriteReg(LCD_REG_39, 0xA3);

	// Adjust the Gamma Curve
	LCD_WriteReg(LCD_REG_64, 0x01);
	LCD_WriteReg(LCD_REG_65, 0x00);
	LCD_WriteReg(LCD_REG_66, 0x00);
	LCD_WriteReg(LCD_REG_67, 0x10);
	LCD_WriteReg(LCD_REG_68, 0x0E);
	LCD_WriteReg(LCD_REG_69, 0x24);
	LCD_WriteReg(LCD_REG_70, 0x04);
	LCD_WriteReg(LCD_REG_71, 0x50);
	LCD_WriteReg(LCD_REG_72, 0x02);
	LCD_WriteReg(LCD_REG_73, 0x13);
	LCD_WriteReg(LCD_REG_74, 0x19);
	LCD_WriteReg(LCD_REG_75, 0x19);
	LCD_WriteReg(LCD_REG_76, 0x16);
	LCD_WriteReg(LCD_REG_80, 0x1B);
	LCD_WriteReg(LCD_REG_81, 0x31);
	LCD_WriteReg(LCD_REG_82, 0x2F);
	LCD_WriteReg(LCD_REG_83, 0x3F);
	LCD_WriteReg(LCD_REG_84, 0x3F);
	LCD_WriteReg(LCD_REG_85, 0x3E);
	LCD_WriteReg(LCD_REG_86, 0x2F);
	LCD_WriteReg(LCD_REG_87, 0x7B);
	LCD_WriteReg(LCD_REG_88, 0x09);
	LCD_WriteReg(LCD_REG_89, 0x06);
	LCD_WriteReg(LCD_REG_90, 0x06);
	LCD_WriteReg(LCD_REG_91, 0x0C);
	LCD_WriteReg(LCD_REG_92, 0x1D);
	LCD_WriteReg(LCD_REG_93, 0xCC);

	// Power voltage setting
	LCD_WriteReg(LCD_REG_27, 0x1B);
	LCD_WriteReg(LCD_REG_26, 0x01);
	LCD_WriteReg(LCD_REG_36, 0x2F);
	LCD_WriteReg(LCD_REG_37, 0x57);
	// VCOM offset
	LCD_WriteReg(LCD_REG_35, 0x86);

	// Power ON
	LCD_WriteReg(LCD_REG_24, 0x36); // Display frame rate = 70Hz RADJ = '0110'
	LCD_WriteReg(LCD_REG_25, 0x01); // OSC_EN = 1
	LCD_WriteReg(LCD_REG_28, 0x06); // AP[2:0] = 111
	LCD_WriteReg(LCD_REG_29, 0x06); // AP[2:0] = 111
	LCD_WriteReg(LCD_REG_31, 0x90); // GAS=1, VOMG=00, PON=1, DK=0, XDK=0, DVDH_TRI=0, STB=0
	LCD_WriteReg(LCD_REG_39, 1);    // REF = 1
	delay(10);

	// 262k/65k color selection
	LCD_WriteReg(LCD_REG_23, 0x05); // default 0x06 262k color,  0x05 65k color

	// SET PANEL
    LCD_WriteReg(LCD_REG_54, 0x09); // SS_PANEL = 1, GS_PANEL = 0,REV_PANEL = 0, BGR_PANEL = 1
	//LCD_WriteReg(LCD_REG_54, 0x0D); // SS_PANEL = 1, GS_PANEL = 1,REV_PANEL = 0, BGR_PANEL = 1
	//LCD_WriteReg(LCD_REG_54, 0x05); // SS_PANEL = 0, GS_PANEL = 1,REV_PANEL = 0, BGR_PANEL = 1

	// Display ON
	LCD_WriteReg(LCD_REG_40, 0x38); // GON=1, DTE=1, D=10
	delay(60);
	LCD_WriteReg(LCD_REG_40, 0x3C); // GON=1, DTE=1, D=11

	// Set Partial Display, Deep Sleep
	LCD_WriteReg(LCD_REG_1, 0x00); // DP_STB = 0, DP_STB_S = 0, SCROLL = 0 PTLON = 0

	// LCD vertical
	LCD_WriteReg(LCD_REG_2, 0x00); // Column address start high byte   Y
	LCD_WriteReg(LCD_REG_3, 0x00); // Column address start low byte
	LCD_WriteReg(LCD_REG_4, 0x00); // Column address end high byte
	LCD_WriteReg(LCD_REG_5, 0xef); // Column address end low byte      240
	LCD_WriteReg(LCD_REG_6, 0x00); // Row address start high byte      X
	LCD_WriteReg(LCD_REG_7, 0x00); // Row address start low byte
	LCD_WriteReg(LCD_REG_8, 0x01); // Row address end high byte
	LCD_WriteReg(LCD_REG_9, 0x3f); // Row address end low byte         320
	LCD_WriteReg(LCD_REG_22, 0x00); // Memory access control: MY = 0, MX = 0, MV = 0, ML = 0

}

// Change the display orientation
// ENABLE for horizontal orientation
// Defaults to vertical
void
LCD_flipOrientation(FunctionalState NewState) {

	if (NewState != DISABLE) {

		flipFlag = true;               // for clear function
		// LCD horizontal
//		LCD_WriteReg(LCD_REG_2, 0x00); // Column address start high byte         Y
//		LCD_WriteReg(LCD_REG_3, 0x00); // Column address start low byte
//		LCD_WriteReg(LCD_REG_4, 0x01); // Column address end high byte
//		LCD_WriteReg(LCD_REG_5, 0x3f); // Column address end low byte            320
//		LCD_WriteReg(LCD_REG_6, 0x00); // Row address start high byte      X
//		LCD_WriteReg(LCD_REG_7, 0x00); // Row address start low byte
//		LCD_WriteReg(LCD_REG_8, 0x00); // Row address end high byte
//		LCD_WriteReg(LCD_REG_9, 0xef); // Row address end low byte         240
		LCD_WriteReg(LCD_REG_22, 0xa0); // Memory access control: MY = 1, MX = 0, MV = 1, ML = 0
	} else {

		flipFlag = false;
		// LCD vertical
//		LCD_WriteReg(LCD_REG_2, 0x00); // Column address start high byte   Y
//		LCD_WriteReg(LCD_REG_3, 0x00); // Column address start low byte
//		LCD_WriteReg(LCD_REG_4, 0x00); // Column address end high byte
//		LCD_WriteReg(LCD_REG_5, 0xef); // Column address end low byte      240
//		LCD_WriteReg(LCD_REG_6, 0x00); // Row address start high byte      X
//		LCD_WriteReg(LCD_REG_7, 0x00); // Row address start low byte
//		LCD_WriteReg(LCD_REG_8, 0x01); // Row address end high byte
//		LCD_WriteReg(LCD_REG_9, 0x3f); // Row address end low byte         320
		LCD_WriteReg(LCD_REG_22, 0x00); // Memory access control: MY = 0, MX = 0, MV = 0, ML = 0
	}
}

// Sets the LCD Text and Background colors.
void
LCD_SetColors(__IO uint16_t _TextColor, __IO uint16_t _BackColor) {
	TextColor = _TextColor;
	BackColor = _BackColor;
}

// Sets the Text color.
// Color: specifies the Text color code RGB(5-6-5).
void
LCD_SetTextColor(__IO uint16_t Color) {
	TextColor = Color;
}

// Sets the Background color.
// Color: specifies the Background color code RGB(5-6-5).
void
LCD_SetBackColor(__IO uint16_t Color) {
	BackColor = Color;
}

// Sets the workable area
// xStart, xEnd: specifies the X position.
// yStart, yEnd: specifies the Y position.
void
setArea(uint16_t yStart, uint16_t xStart, uint16_t yEnd, uint16_t xEnd) {

  LCD_WriteReg(LCD_REG_2, xStart >> 8);
	LCD_WriteReg(LCD_REG_3, xStart & 0xFF);
	LCD_WriteReg(LCD_REG_4, xEnd >> 8);
	LCD_WriteReg(LCD_REG_5, xEnd & 0xFF);
	LCD_WriteReg(LCD_REG_6, yStart >> 8);
	LCD_WriteReg(LCD_REG_7, yStart & 0xFF);
	LCD_WriteReg(LCD_REG_8, yEnd >> 8);
	LCD_WriteReg(LCD_REG_9, yEnd & 0xFF);
}

void
LCD_Clear_Some(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t Color){

	uint16_t index;
	setArea(ys, xs, ye, xe);
	LCD_WriteRAM_Prepare();
	for (index = 0; index < ((ye - ys) * (xe - xs) + 1); index++) {
		LCD_WriteRAM(Color);
	}
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
		;
	LCD_CS_High;
}

// clear the lcd
void
LCD_Clear(uint16_t Color) {

	uint32_t index = 0;

	if (flipFlag) {
		setArea(319,0,0,239);
	} else {
		setArea(0,0,319,239);
	}
	// Prepare to write GRAM
	LCD_WriteRAM_Prepare();

	for (index = 0; index < 320 * 240; index++) {
		LCD_WriteRAM(Color);
	}
	// Wait until a data is sent(not busy), before CS HIGH
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
		;
	LCD_CS_High;
}

// Draw a character at the x and y position
void
drawChar5_7(uint16_t x, uint16_t y, char c) {

	uint8_t col = 0;
	uint8_t row = 0;
	uint8_t bit = 0x01;
	uint8_t oc = c - 0x20;

	setArea(y, x, y+7, x+4);
    LCD_WriteRAM_Prepare();
	while (row < 8) {
		while (col < 5) {
			if (font5_7[oc][col] & bit) {
				//foreground
				LCD_WriteRAM(TextColor);
			} else {
				//background
				LCD_WriteRAM(BackColor);
			}
			col++;
		}
		col = 0;
		bit <<= 1;
		row++;
	}
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET);
	LCD_CS_High;
}

void
drawString5_7(uint16_t x, uint16_t y, char *string) {

	while (*string) {
		drawChar5_7(x, y, *string++);
		x += 6;
	}
}

// 11x16 font - this function draws background pixels
void
drawChar11_16(uint16_t x, uint16_t y, char c) {

	uint8_t col = 0;
	uint8_t row = 0;
	uint16_t bit = 0x1;
	uint8_t oc = c - 0x20;

	setArea(y, x, y + 15, x + 10);
	LCD_WriteRAM_Prepare();

	while (row < 16) {
		while (col < 11) {
			if (font_11x16[oc][col] & bit) {
				//foreground
				LCD_WriteRAM(TextColor);
			}

			else {
				//background
				LCD_WriteRAM(BackColor);
			}
			col++;
		}
		col = 0;
		bit <<= 1;
		row++;
	}
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET);
	LCD_CS_High;
}

void
drawString11_16(uint16_t x, uint16_t y, char *string) {

	while (*string) {
		drawChar11_16(x, y, *string++);
		x += 12;
	}
}

// 8x12 font - this function draws background pixels
void
drawChar8_12(uint16_t x, uint16_t y, char c) {

	uint8_t col = 0;
	uint8_t row = 0;
	uint8_t bit = 0x80;
	uint8_t oc = c - 0x20;

	setArea(y, x, y + 11, x + 7);
	LCD_WriteRAM_Prepare();
	while (row < 12) {
		while (col < 8) {
			if (font_8x12[oc][row] & bit) {
				//foreground
				LCD_WriteRAM(TextColor);
			}

			else {
				//background
				LCD_WriteRAM(BackColor);
			}
			col++;
			bit >>= 1;
		}
		col = 0;
		bit = 0x80;
		row++;
	}
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET);
	LCD_CS_High;
}

void
drawString8_12(uint16_t x, uint16_t y, char *string) {

	while (*string) {
		drawChar8_12(x, y, *string++);
		x += 8;
	}
}

// Draw a sevenSeg number at the x and y position
void
drawSevenSeg(uint16_t x, uint16_t y, char n) {

	uint8_t row, col, byte;
	uint16_t xT = x;
	uint16_t yT = y;
	uint8_t pixel = 0;
	uint8_t bit = 0x01;

	setArea(y, x, y+49, x+31);
	LCD_WriteRAM_Prepare();

	for (row = 0; row < 50; row++) {
		for (col = 0; col < 4; col++) {  // 8*4=32
			for (byte = 0; byte < 8; byte++) {
				if (sevenSeg[n][pixel] & bit) {
					//foreground
					LCD_WriteRAM(TextColor);
				} else {
					//background
					LCD_WriteRAM(BackColor);
				}
				xT++;
				bit <<= 1;
			}
			pixel++;
			bit = 0x01;
		}
		yT++;
		xT = x;
	}
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET);
	LCD_CS_High;
}

// only for numbers
void
drawStringSeven(uint16_t x, uint16_t y, uint8_t len, char *string) {

  uint8_t i;
  for (i = 0; i < len; i++)
    {
      drawSevenSeg (x, y, string[i]);
      x += 33;
    }
}

// Sets a display window
// xStart: specifies the X start row
// xEnd: specifies the Y end row
void
LCD_SetDisplayWindow(uint16_t xStart, uint16_t xEnd) {

	LCD_WriteReg(LCD_REG_1, 0x01);             // PLTON on
	LCD_WriteReg(LCD_REG_10, xStart >> 8);
	LCD_WriteReg(LCD_REG_11, xStart & 0xFF);
	LCD_WriteReg(LCD_REG_12, xEnd >> 8);
	LCD_WriteReg(LCD_REG_13, xEnd & 0xFF);
}

// Disables LCD Window mode.
void
LCD_WindowModeDisable(void) {

	LCD_WriteReg(LCD_REG_1, 0x00);            // PLTON off
}

// Draws a line between two points on the display.
// Xpos, Ypos Absolute pixel coordinates for line origin.
// Length - Absolute pixel coordinates for line length.
void LCD_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length,
		uint8_t Direction) {

	uint32_t i = 0;

	setPixel(Xpos, Ypos, TextColor);

	if (Direction == LCD_DIR_HORIZONTAL) {

		LCD_WriteRAM_Prepare();
		for (i = 0; i < Length; i++) {
			setPixel(Xpos, Ypos, TextColor);
			Xpos++;
		}

		// Wait until a data is sent(not busy)
		while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
			;
		LCD_CS_High;

	} else {

		LCD_WriteRAM_Prepare();
		for (i = 0; i < Length; i++) {
			setPixel(Xpos, Ypos, TextColor);
			Ypos++;
		}

		while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
			;
		LCD_CS_High;
	}
}

// Displays a rectangle.
// x1, y1 - Absolute pixel coordinates for top left corner
// x2, y2 - Absolute pixel coordinates for bottom right corner
void
LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height) {

	LCD_DrawLine(Xpos, Ypos, Width, LCD_DIR_HORIZONTAL);
	LCD_DrawLine(Xpos, (Ypos + Height), Width, LCD_DIR_HORIZONTAL);

	LCD_DrawLine(Xpos, Ypos, Height, LCD_DIR_VERTICAL);
	LCD_DrawLine((Xpos + Width), Ypos, Height, LCD_DIR_VERTICAL);
}

// Displays a full rectangle.
// Xpos: specifies the X position.
// Ypos: specifies the Y position.
// Height: rectangle height.
// Width: rectangle width.
void
LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width,
		uint16_t Height) {

	LCD_DrawRect(Xpos, Ypos, Width, Height);

	Width--;
	Height--;
	Xpos++;

	while (Height--) {
		LCD_DrawLine(Xpos, ++Ypos, Width, LCD_DIR_HORIZONTAL);
	}
}

// Displays a circle.
// Xpos: specifies the X position.
// Ypos: specifies the Y position.
// Radius
void
LCD_DrawCircle(uint16_t Ypos, uint16_t Xpos, uint16_t Radius) {

	int16_t D;     // Decision Variable
	uint16_t CurX; // Current X Value
	uint16_t CurY; // Current Y Value

	D = 3 - (Radius << 1);
	CurX = 0;
	CurY = Radius;

	while (CurX <= CurY) {
		setArea(Xpos + CurX, Ypos + CurY, Xpos + CurX, Ypos + CurY);
		LCD_WriteRAMWord(TextColor);

		setArea(Xpos + CurX, Ypos - CurY, Xpos + CurX, Ypos - CurY);
		LCD_WriteRAMWord(TextColor);

		setArea(Xpos - CurX, Ypos + CurY, Xpos - CurX, Ypos + CurY);
		LCD_WriteRAMWord(TextColor);

		setArea(Xpos - CurX, Ypos - CurY, Xpos - CurX, Ypos - CurY);
		LCD_WriteRAMWord(TextColor);

		setArea(Xpos + CurY, Ypos + CurX, Xpos + CurY, Ypos + CurX);
		LCD_WriteRAMWord(TextColor);

		setArea(Xpos + CurY, Ypos - CurX, Xpos + CurY, Ypos - CurX);
		LCD_WriteRAMWord(TextColor);

		setArea(Xpos - CurY, Ypos + CurX, Xpos - CurY, Ypos + CurX);
		LCD_WriteRAMWord(TextColor);

		setArea(Xpos - CurY, Ypos - CurX, Xpos - CurY, Ypos - CurX);
		LCD_WriteRAMWord(TextColor);

		if (D < 0) {
			D += (CurX << 2) + 6;
		} else {
			D += ((CurX - CurY) << 2) + 10;
			CurY--;
		}
		CurX++;
	}
}

// Displays a full circle. Taken from stackoverflow thanks kmillen
// Xpos: specifies the X position.
// Ypos: specifies the Y position.
// Radius
void
LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius) {

	int r2 = Radius * Radius;
	int area = r2 << 2;
	int rr = Radius << 1;

	for (int i = 0; i < area; i++) {
		int tx = (i % rr) - Radius;
		int ty = (i / rr) - Radius;

		if (tx * tx + ty * ty <= r2)
			setPixel(Xpos + tx, Ypos + ty, TextColor);
	}
}

// Displays a picture.
// Pict: pointer to the picture array.
void
LCD_DrawPict(const uint16_t *Pict, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {

	uint16_t i = 0;
	setArea(y, x, y+w-1, x+h-1);

	LCD_WriteRAM_Prepare(); // Prepare to write GRAM
	for (i = 0; i < w*h; i++){
		LCD_WriteRAM(Pict[i]);
	}
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
		;
	LCD_CS_High;
}

// This works with the DMA
// Size is for number of DMA transfers
//void
//LCD_DrawPict(const uint16_t *Pict, uint16_t size, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
//
//	setArea(x, y, x+w-1, y+h-1);
//
//	spiPutDMA(Pict, size);

// Displays a pixel.
// x: pixel x.
// y: pixel y.
void
setPixel(int16_t x, int16_t y, int16_t color) {

	setArea(y, x, y+1, x+1);

	LCD_WriteRAM_Prepare();             // Prepare to write GRAM
	LCD_WriteRAM(color);
	// Wait until a data is sent(not busy)
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
		;
	LCD_CS_High;
}

// Reset LCD control line(/CS) and Send Start-Byte
// Start_Byte: the Start-Byte to be sent
void
LCD_nCS_StartByte(uint8_t Start_Byte) {

	LCD_CS_Low;
	SPI_SendData8(LCD_SPI, Start_Byte);
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		;
	SPI_ReceiveData8(LCD_SPI);
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_TXE) == RESET)
		;
}

// Writes index to select the LCD register.
// LCD_Reg: address of the selected register.
void
LCD_WriteRegIndex(uint8_t LCD_Reg) {

	LCD_nCS_StartByte(START_BYTE | SET_INDEX);

	// Write 16-bit Reg Index (High Byte is 0)
	SPI_SendData8(LCD_SPI, 0x00);
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_TXE) == RESET)
		;
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		;
	SPI_ReceiveData8(LCD_SPI);

	SPI_SendData8(LCD_SPI, LCD_Reg);
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		;
	SPI_ReceiveData8(LCD_SPI);
	// Wait until a data is sent(not busy), before config /CS HIGH
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
		;
	LCD_CS_High;
}

// Writes to the selected LCD register.
// LCD_Reg: address of the selected register.
// LCD_RegValue: value to write to the selected register.
void
LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue) {

	// Write 16-bit Index then Write Reg
	LCD_WriteRegIndex(LCD_Reg);

	// Write 16-bit Reg
	LCD_nCS_StartByte(START_BYTE | LCD_WRITE_REG);

	SPI_SendData8(LCD_SPI, LCD_RegValue >> 8);
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		;
	SPI_ReceiveData8(LCD_SPI);

	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_TXE) == RESET)
		;
	SPI_SendData8(LCD_SPI, (LCD_RegValue & 0xFF));
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		;
	SPI_ReceiveData8(LCD_SPI);

	// Wait until a data is sent(not busy), before config /CS HIGH
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
		;
	LCD_CS_High;
}

// Reads LCD Register.
// For HX8347G controller, the LCD registers are 8-bit length
// LCD_Reg: address of the selected register.
// returns LCD Register Value.
uint16_t
LCD_ReadReg(uint8_t LCD_Reg) {

	// Write 16-bit Index (then Read Reg)
	LCD_WriteRegIndex(LCD_Reg);

	// Read 16-bit Reg
	// Reset LCD control line(/CS) and Send Start-Byte
	LCD_nCS_StartByte(START_BYTE | LCD_READ_REG);

	// Wait until a data is sent(not busy), before reading dummy bytes
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
		;
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_TXE) == RESET)
		;
	SPI_SendData8(LCD_SPI, 0xFF);  // dummy write
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		;
	return SPI_ReceiveData8(LCD_SPI);

}

// Prepare to write to the LCD RAM.
void
LCD_WriteRAM_Prepare(void) {
	LCD_WriteRegIndex(LCD_REG_34); // Select GRAM Reg
	LCD_nCS_StartByte(START_BYTE | LCD_WRITE_REG);
}

// Writes 1 word to the LCD RAM.
// RGB_Code: the pixel color in RGB mode (5-6-5).
void
LCD_WriteRAMWord(uint16_t RGB_Code) {

	LCD_WriteRAM_Prepare();
	SPI_I2S_SendData16(LCD_SPI, RGB_Code);
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
		;
}

// Writes to the LCD RAM.
// RGB_Code: the pixel color in RGB mode (5-6-5).
void
LCD_WriteRAM(uint16_t RGB_Code) {

	SPI_SendData8(LCD_SPI, RGB_Code >> 8);
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_TXE) == RESET)
		;

	SPI_SendData8(LCD_SPI, RGB_Code & 0xFF);
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_TXE) == RESET)
		;
}

// Power on the LCD.
void
LCD_PowerOn(void) {
	// Power on setting up flow
	LCD_WriteReg(LCD_REG_24, 0x36); // Display frame rate = 70Hz RADJ = '0110'
	LCD_WriteReg(LCD_REG_25, 0x01); // OSC_EN = 1
	LCD_WriteReg(LCD_REG_28, 0x06); // AP[2:0] = 111
	LCD_WriteReg(LCD_REG_31, 0x90); // GAS=1, VOMG=00, PON=1, DK=0, XDK=0, DVDH_TRI=0, STB=0
	delay(10);
	// 262k/65k color selection
	LCD_WriteReg(LCD_REG_23, 0x05); // default 0x06 262k color,  0x05 65k color
	// SET PANEL */
	LCD_WriteReg(LCD_REG_54, 0x09); // SS_PANEL = 1, GS_PANEL = 0,REV_PANEL = 0, BGR_PANEL = 1
}

// Enables the Display.
void
LCD_DisplayOn(void) {
	// Display On
	LCD_WriteReg(LCD_REG_40, 0x38);
	delay(60);
	LCD_WriteReg(LCD_REG_40, 0x3C);
}

// Disables the Display.
void
LCD_DisplayOff(void) {
	// Display Off
	LCD_WriteReg(LCD_REG_40, 0x38);
	delay(60);
	LCD_WriteReg(LCD_REG_40, 0x04);
}


