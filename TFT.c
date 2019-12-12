/*
 * 20190314.020
 * TFT 240x400
 *
 * File: TFT.c
 * Processor: PIC18F2455
 * Author: wizlab.it
 */

#include "TFT.h"

void TFT_WriteRegister(uint16_t reg, uint16_t data) {
    _TFT_CS_ACTIVE;
    _TFT_WRITE_CMD(reg);
    _TFT_WRITE_DATA(data);
    _TFT_CS_IDLE;
}

void TFT_WriteRegisters(uint16_t reg, uint8_t *data, uint8_t dataSize) {
    _TFT_CS_ACTIVE;
    _TFT_WRITE_CMD(reg);
    _TFT_CD_DATA;
    uint8_t i = 0;
    while(i != dataSize) {
        _TFT_WRITE_8BIT(data[i++]);
    }
    _TFT_CS_IDLE;
}

uint16_t TFT_ReadRegister(uint16_t reg) {
    uint16_t data;
    _TFT_CS_ACTIVE;
    _TFT_WRITE_CMD(reg);
    _TFT_DATA_DIR_RD;
    _TFT_CD_DATA;
    _TFT_READ_16BIT(data);
    _TFT_CS_IDLE;
    _TFT_DATA_DIR_WR;
    return data;
}

uint16_t TFT_ReadID(void) {
    return TFT_ReadRegister(0x0000);
}

void TFT_Reset(void) {
    _TFT_DATA_DIR_WR;
    _TFT_CS_IDLE;
    _TFT_WR_IDLE;
    _TFT_RD_IDLE;
    _TFT_RESET_ACTIVE;
    __delay_ms(2);
    _TFT_RESET_IDLE;
}

void TFT_SetAddrWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    //Set address window
    TFT_WriteRegister(0x0210, x1);
    TFT_WriteRegister(0x0211, x2);
    TFT_WriteRegister(0x0212, y1);
    TFT_WriteRegister(0x0213, y2);

    //Set address counter to top left
    TFT_WriteRegister(0x0200, x1);
    TFT_WriteRegister(0x0201, y2);
}

void TFT_FullScreen(void) {
    TFT_SetAddrWindow(0, 0, _TFT_WIDTH - 1, _TFT_HEIGHT - 1);
}

void TFT_Init(void) {
    TFT_Reset();
    __delay_ms(200);

    //Send init sequence
    uint16_t i=0, cmd, data;
    uint16_t initSequenceSize = sizeof(TFT_Init_Sequence) / sizeof(uint16_t);
    while(i != initSequenceSize) {
        cmd = TFT_Init_Sequence[i++];
        data = TFT_Init_Sequence[i++];
        if(cmd == _TFT_DELAY_FLAG) {
            __delay_ms(200);
        } else {
            TFT_WriteRegister(cmd, data);
        }
    }

    //Set display size and clear it
    TFT_FullScreen();
    TFT_FillScreen(_TFT_COLOR_BLACK);
}

void TFT_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    TFT_WriteRegister(0x0200, x);
    TFT_WriteRegister(0x0201, y);
    TFT_WriteRegister(0x0202, color);
}

void TFT_DrawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    TFT_SetAddrWindow(x, y, (x + w - 1), (y + h -1));
    TFT_Flood(color, (w * h));
    TFT_FullScreen();
}

void TFT_Flood(uint16_t color, uint32_t len) {
    uint16_t blocks;
    uint8_t i;
    uint8_t color_hi = color >> 8;
    uint8_t color_lo = color;

    //Send first pixel
    TFT_WriteRegister(0x0202, color);
    len--;

    //Send other pixels, in 4 pixels per block to optimize speed
    //If high and low part of the color are the same, then only send the strobes, no need to change the value on the port (super optimizes speed)
    _TFT_CS_ACTIVE;
    blocks = (uint16_t)(len / 4);
    if(color_hi == color_lo) {
        while(blocks--) {
            _TFT_WR_STROBE; _TFT_WR_STROBE; //1st pixel
            _TFT_WR_STROBE; _TFT_WR_STROBE; //2nd pixel
            _TFT_WR_STROBE; _TFT_WR_STROBE; //3rd pixel
            _TFT_WR_STROBE; _TFT_WR_STROBE; //4th pixel
        }
        for(i = (uint8_t)len & 3; i--; ) {
            _TFT_WR_STROBE; _TFT_WR_STROBE; //Remaining pixels if len is not a len multiply
        }
    } else {
        while(blocks--) {
            _TFT_WRITE_8BIT(color_hi); _TFT_WRITE_8BIT(color_lo); //1st pixel
            _TFT_WRITE_8BIT(color_hi); _TFT_WRITE_8BIT(color_lo); //2nd pixel
            _TFT_WRITE_8BIT(color_hi); _TFT_WRITE_8BIT(color_lo); //3rd pixel
            _TFT_WRITE_8BIT(color_hi); _TFT_WRITE_8BIT(color_lo); //4th pixel
        }
        for(i = (uint8_t)len & 3; i--; ) {
            _TFT_WRITE_8BIT(color_hi); _TFT_WRITE_8BIT(color_lo); //Remaining pixels if len is not a len multiply
        }
    }
    _TFT_CS_IDLE;
}

void TFT_FillScreen(uint16_t color) {
    TFT_WriteRegister(0x0200, 0);
    TFT_WriteRegister(0x0201, 0);
    TFT_Flood(color, (uint32_t)_TFT_WIDTH * (uint32_t)_TFT_HEIGHT);
}

uint16_t TFT_ColorRGBTo16Bit(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}