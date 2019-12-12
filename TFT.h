/*
 * 20190314.027
 * TFT 240x400
 *
 * File: TFT.h
 * Processor: PIC18F2455
 * Author: wizlab.it
 */

#ifndef TFT_H
#define	TFT_H

#include "commons.h"

#define _TFT_WIDTH  240
#define _TFT_HEIGHT 400

#define _TFT_DELAY_FLAG     0xFFFF

#define _TFT_COLOR_BLACK    0x0000
#define	_TFT_COLOR_BLUE     0x001F
#define	_TFT_COLOR_RED      0xF800
#define	_TFT_COLOR_GREEN    0x07E0
#define _TFT_COLOR_CYAN     0x07FF
#define _TFT_COLOR_MAGENTA  0xF81F
#define _TFT_COLOR_YELLOW   0xFFE0
#define _TFT_COLOR_WHITE    0xFFFF

#define _TFT_CS         PORTCbits.RC0   //TFT CS Pin
#define _TFT_CD         PORTCbits.RC1   //TFT CD/RS Pin
#define _TFT_WR         PORTCbits.RC6   //TFT WR Pin
#define _TFT_RD         PORTCbits.RC7   //TFT RD Pin
#define _TFT_RESET      PORTCbits.RC2   //TFT Reset Pin
#define _TFT_DATA       PORTB
#define _TFT_DATA_DIR   TRISB

#define _TFT_CS_ACTIVE      _TFT_CS = 0
#define _TFT_CS_IDLE        _TFT_CS = 1
#define _TFT_CD_COMMAND     _TFT_CD = 0
#define _TFT_CD_DATA        _TFT_CD = 1
#define _TFT_WR_ACTIVE      _TFT_WR = 0
#define _TFT_WR_IDLE        _TFT_WR = 1
#define _TFT_WR_STROBE      { _TFT_WR_ACTIVE; _TFT_WR_IDLE; }
#define _TFT_RD_ACTIVE      _TFT_RD = 0
#define _TFT_RD_IDLE        _TFT_RD = 1
#define _TFT_RESET_ACTIVE   _TFT_RESET = 0;
#define _TFT_RESET_IDLE     _TFT_RESET = 1;

#define _TFT_DATA_DIR_WR        _TFT_DATA_DIR = 0x00
#define _TFT_DATA_DIR_RD        _TFT_DATA_DIR = 0xFF
#define _TFT_WRITE_CMD(x)       { _TFT_CD_COMMAND; _TFT_WRITE_16BIT(x); }
#define _TFT_WRITE_DATA(x)      { _TFT_CD_DATA; _TFT_WRITE_16BIT(x); }
#define _TFT_WRITE_16BIT(x)     { uint8_t h = (x)>>8, l = (uint8_t)x; _TFT_WRITE_8BIT(h); _TFT_WRITE_8BIT(l); }
#define _TFT_WRITE_8BIT(x)      { _TFT_DATA = x; _TFT_WR_STROBE; }
#define _TFT_READ_16BIT(value)  { uint8_t hi; _TFT_READ_8BIT(hi); _TFT_READ_8BIT(value); value |= (hi << 8); }
#define _TFT_READ_8BIT(value)   { _TFT_RD_ACTIVE; __delay_us(1); value = _TFT_DATA; _TFT_RD_IDLE; }

void TFT_WriteRegister(uint16_t reg, uint16_t data);
void TFT_WriteRegisters(uint16_t reg, uint8_t *data, uint8_t dataSize);
uint16_t TFT_ReadRegister(uint16_t reg);
uint16_t TFT_ReadID(void);
void TFT_Reset(void);
void TFT_SetAddrWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void TFT_FullScreen(void);
void TFT_Init(void);
void TFT_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void TFT_DrawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void TFT_Flood(uint16_t color, uint32_t len);
void TFT_FillScreen(uint16_t color);
uint16_t TFT_ColorRGBTo16Bit(uint8_t r, uint8_t g, uint8_t b);

const uint16_t TFT_Init_Sequence[] = {
    //Initial Sequence
    0x0702, 0x3008,     //Internal timing
    0x0705, 0x0036,     //Internal timing
    0x070B, 0x1213,     //Internal timing
    0x0001, 0x0100,     //SS and SM bit
    0x0002, 0x0100,     //1 line inversion
    0x0003, 0x1030,     //GRAM write direction and BGR=1.
    0x0008, 0x0202,     //Back and front porch
    0x0009, 0x0000,     //Non-display area refresh cycle ISC[3:0]
    0x000C, 0x0000,     //RGB interface setting
    0x000F, 0x0000,     //RGB interface polarity
    //Power On sequence
    0x0100, 0x0000,     //SAP, BT[3:0], AP, DSTB, SLP, STB
    0x0102, 0x0000,     //VREG1OUT voltage
    0x0103, 0x0000,     //VDV[4:0] for VCOM amplitude
    _TFT_DELAY_FLAG, 0x0001,    //Delay (discharge capacitor power voltage)
    0x0100, 0x1190,     //SAP, BT[3:0], AP, DSTB, SLP, STB
    0x0101, 0x0227,     //DC1[2:0], DC0[2:0], VC[2:0]
    _TFT_DELAY_FLAG, 0x0001,    //Delay
    0x0102, 0x01BD,     //VREG1OUT voltage
    _TFT_DELAY_FLAG, 0x0001,    //Delay
    0x0103, 0x2D00,     //VDV[4:0] for VCOM amplitude
    0x0281, 0x000E,     //VCM[5:0] for VCOMH
    _TFT_DELAY_FLAG, 0x0001,    //Delay
    0x0200, 0x0000,     //GRAM horizontal Address
    0x0201, 0x0000,     //GRAM Vertical Address
    //Adjust Gamma Curve
    0x0300, 0x0000,
    0x0301, 0x0707,
    0x0302, 0x0606,
    0x0305, 0x0000,
    0x0306, 0x0D00,
    0x0307, 0x0706,
    0x0308, 0x0005,
    0x0309, 0x0007,
    0x030C, 0x0000,
    0x030D, 0x000A,
    //Set GRAM area
    0x0210, 0x0000,     //Horizontal GRAM Start Address
    0x0211, 0x00EF,     //Horizontal GRAM End Address
    0x0212, 0x0000,     //Vertical GRAM Start Address
    0x0213, 0x018f,     //Vertical GRAM Start Address
    0x0400, 0x3100,     //Gate Scan Line 400 lines
    0x0401, 0x0001,     //NDL,VLE, REV
    0x0404, 0x0000,     //Scrolling line
    //Partial Display Control
    0x0500, 0x0000,     //Partial Image 1 Display Position
    0x0501, 0x0000,     //Partial Image 1 RAM Start/End Address
    0x0502, 0x0000,     //Partial Image 1 RAM Start/End Address
    0x0503, 0x0000,     //Partial Image 2 Display Position
    0x0504, 0x0000,     //Partial Image 2 RAM Start/End Address
    0x0505, 0x0000,     //Partial Image 2 RAM Start/End Address
    //Panel Contro
    0x0010, 0x0010,     //DIVI[1:0];RTNI[4:0]
    0x0011, 0x0600,     //NOWI[2:0];SDTI[2:0]
    0x0020, 0x0002,     //DIVE[1:0];RTNE[5:0]
    0x0007, 0x0173      //262K color and display ON
};
#endif