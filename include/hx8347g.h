/*
 * hx8347g.h
 *
 * For driving a HX8347g LCD
 * Hacked from the internet
 *
 *  Created on: Apr 11, 2015
 *      Author: timotet
 */
#ifndef __HX8347G_H
#define __HX8347G_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f0xx.h"
#include "stdbool.h"

#define LCD_HX8347G        0x0075
#define LCD_SPI            SPI1

// all port B
#define LCD_Reset        GPIO_Pin_4
#define LCD_Reset_Low    GPIO_ResetBits(GPIOB, LCD_Reset)
#define LCD_Reset_High   GPIO_SetBits(GPIOB, LCD_Reset)
#define LCD_CS           GPIO_Pin_5
#define LCD_CS_Low       GPIO_ResetBits(GPIOB, LCD_CS)
#define LCD_CS_High      GPIO_SetBits(GPIOB, LCD_CS)

// LCD Registers
#define LCD_REG_0             0x00
#define LCD_REG_1             0x01  // Display mode control
#define LCD_REG_2             0x02  // Column address start upper byte
#define LCD_REG_3             0x03  // Column address start lower byte
#define LCD_REG_4             0x04  // Column address end upper byte
#define LCD_REG_5             0x05  // Column address end lower byte
#define LCD_REG_6             0x06  // Row address start upper byte
#define LCD_REG_7             0x07  // Row address start lower byte
#define LCD_REG_8             0x08  // Row address end upper byte
#define LCD_REG_9             0x09  // Row address end lower byte
#define LCD_REG_10            0x0A  // Partial area start row upper byte
#define LCD_REG_11            0x0B  // Partial area start row lower byte
#define LCD_REG_12            0x0C  // Partial area end row upper byte
#define LCD_REG_13            0x0D  // Partial area start row lower byte
#define LCD_REG_14            0x0E  // Vertical scroll upper fixed area upper byte
#define LCD_REG_15            0x0F  // Vertical scroll upper fixed area lower byte
#define LCD_REG_16            0x10  // Vertical scroll height upper byte
#define LCD_REG_17            0x11  // Vertical scroll height lower byte
#define LCD_REG_18            0x12  // Vertical scroll bottom fixed area upper byte
#define LCD_REG_19            0x13  // Vertical scroll bottom fixed area lower byte
#define LCD_REG_20            0x14  // Vertical scroll start upper byte
#define LCD_REG_21            0x15  // Vertical scroll start lower byte
#define LCD_REG_22            0x16
#define LCD_REG_23            0x17
#define LCD_REG_24            0x18
#define LCD_REG_25            0x19
#define LCD_REG_26            0x1A
#define LCD_REG_27            0x1B
#define LCD_REG_28            0x1C
#define LCD_REG_29            0x1D
#define LCD_REG_30            0x1E
#define LCD_REG_31            0x1F
#define LCD_REG_32            0x20
#define LCD_REG_33            0x21
#define LCD_REG_34            0x22
#define LCD_REG_35            0x23
#define LCD_REG_36            0x24
#define LCD_REG_37            0x25
#define LCD_REG_38            0x26
#define LCD_REG_39            0x27
#define LCD_REG_40            0x28
#define LCD_REG_41            0x29
#define LCD_REG_42            0x2A
#define LCD_REG_43            0x2B
#define LCD_REG_44            0x2C
#define LCD_REG_45            0x2D
#define LCD_REG_46            0x2E
#define LCD_REG_47            0x2F
#define LCD_REG_48            0x30
#define LCD_REG_49            0x31
#define LCD_REG_50            0x32
#define LCD_REG_51            0x33
#define LCD_REG_52            0x34
#define LCD_REG_53            0x35
#define LCD_REG_54            0x36
#define LCD_REG_55            0x37
#define LCD_REG_56            0x38
#define LCD_REG_57            0x39
#define LCD_REG_58            0x3A
#define LCD_REG_59            0x3B
#define LCD_REG_60            0x3C
#define LCD_REG_61            0x3D
#define LCD_REG_62            0x3E
#define LCD_REG_63            0x3F
#define LCD_REG_64            0x40
#define LCD_REG_65            0x41
#define LCD_REG_66            0x42
#define LCD_REG_67            0x43
#define LCD_REG_68            0x44
#define LCD_REG_69            0x45
#define LCD_REG_70            0x46
#define LCD_REG_71            0x47
#define LCD_REG_72            0x48
#define LCD_REG_73            0x49
#define LCD_REG_74            0x4A
#define LCD_REG_75            0x4B
#define LCD_REG_76            0x4C
#define LCD_REG_77            0x4D
#define LCD_REG_78            0x4E
#define LCD_REG_79            0x4F
#define LCD_REG_80            0x50
#define LCD_REG_81            0x51
#define LCD_REG_82            0x52
#define LCD_REG_83            0x53
#define LCD_REG_84            0x54
#define LCD_REG_85            0x55
#define LCD_REG_86            0x56
#define LCD_REG_87            0x57
#define LCD_REG_88            0x58
#define LCD_REG_89            0x59
#define LCD_REG_90            0x5A
#define LCD_REG_91            0x5B
#define LCD_REG_92            0x5C
#define LCD_REG_93            0x5D
#define LCD_REG_94            0x5E
#define LCD_REG_95            0x5F
#define LCD_REG_96            0x60
#define LCD_REG_97            0x61
#define LCD_REG_106           0x6A
#define LCD_REG_118           0x76
#define LCD_REG_128           0x80
#define LCD_REG_129           0x81
#define LCD_REG_130           0x82
#define LCD_REG_131           0x83
#define LCD_REG_132           0x84
#define LCD_REG_133           0x85
#define LCD_REG_134           0x86
#define LCD_REG_135           0x87
#define LCD_REG_136           0x88
#define LCD_REG_137           0x89
#define LCD_REG_139           0x8B
#define LCD_REG_140           0x8C
#define LCD_REG_141           0x8D
#define LCD_REG_143           0x8F
#define LCD_REG_144           0x90
#define LCD_REG_145           0x91
#define LCD_REG_146           0x92
#define LCD_REG_147           0x93
#define LCD_REG_148           0x94
#define LCD_REG_149           0x95
#define LCD_REG_150           0x96
#define LCD_REG_151           0x97
#define LCD_REG_152           0x98
#define LCD_REG_153           0x99
#define LCD_REG_154           0x9A
#define LCD_REG_157           0x9D
#define LCD_REG_192           0xC0
#define LCD_REG_193           0xC1
#define LCD_REG_226           0xE2
#define LCD_REG_227           0xE3
#define LCD_REG_228           0xE4
#define LCD_REG_229           0xE5
#define LCD_REG_230           0xE6
#define LCD_REG_231           0xE7
#define LCD_REG_232           0xE8
#define LCD_REG_233           0xE9
#define LCD_REG_234           0xEA
#define LCD_REG_235           0xEB
#define LCD_REG_236           0xEC
#define LCD_REG_237           0xED
#define LCD_REG_239           0xEF
#define LCD_REG_241           0xF1
#define LCD_REG_242           0xF2

// LCD color
#define LCD_COLOR_WHITE          0xFFFF
#define LCD_COLOR_BLACK          0x0000
#define LCD_COLOR_GREY           0xF7DE
#define LCD_COLOR_BLUE           0x001F
#define LCD_COLOR_BLUE2          0x051F
#define LCD_COLOR_RED            0xF800
#define LCD_COLOR_MAGENTA        0xF81F
#define LCD_COLOR_GREEN          0x07E0
#define LCD_COLOR_CYAN           0x7FFF
#define LCD_COLOR_YELLOW         0xFFE0

// LCD Direction
#define LCD_DIR_HORIZONTAL       0x0000
#define LCD_DIR_VERTICAL         0x0001

// LCD Size (Width and Height)
#define LCD_PIXEL_WIDTH          0x0140  // 320
#define LCD_PIXEL_HEIGHT         0x00F0  // 240

#define LCD_shortSide               240
#define LCD_longSide                320

void LCD_GPIO_Init(void);
void hx8347g_Init(void);
void LCD_flipOrientation(FunctionalState NewState);
void LCD_SetColors(__IO uint16_t _TextColor, __IO uint16_t _BackColor);
void LCD_SetTextColor(__IO uint16_t Color);
void LCD_SetBackColor(__IO uint16_t Color);
void LCD_Clear_Some(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t Color);
void LCD_Clear(uint16_t Color);
void setArea(uint16_t yStart, uint16_t xStart, uint16_t yEnd, uint16_t xEnd);
void setPixel(int16_t x, int16_t y, int16_t color);
void drawString5_7(uint16_t x, uint16_t y, char *string);
void drawChar5_7(uint16_t x, uint16_t y, char c);
void drawChar8_12(uint16_t x, uint16_t y, char c);
void drawString8_12(uint16_t x, uint16_t y, char *string);
void drawChar11_16(uint16_t x, uint16_t y, char c);
void drawString11_16(uint16_t x, uint16_t y, char *string);
void drawSevenSeg(uint16_t x, uint16_t y, char n);
void drawStringSeven(uint16_t x, uint16_t y, uint8_t len, char *string);
void LCD_SetDisplayWindow(uint16_t xStart, uint16_t xEnd);
void LCD_WindowModeDisable(void);
void LCD_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction);
void LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void LCD_DrawPict(const uint16_t *Pict, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
// Works with DMA
//void LCD_DrawPict(const uint16_t *Pict, uint16_t size, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void LCD_nCS_StartByte(uint8_t Start_Byte);
void LCD_WriteRegIndex(uint8_t LCD_Reg);
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAMWord(uint16_t RGB_Code);
uint16_t LCD_ReadReg(uint8_t LCD_Reg);
void LCD_WriteRAM(uint16_t RGB_Code);
void LCD_PowerOn(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);

#ifdef	__cplusplus
}
#endif

#endif /* HX8347G_H */
