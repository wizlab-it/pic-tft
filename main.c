/*
 * 20190314.012
 * TFT 240x400
 *
 * File: main.c
 * Processor: PIC18F2455
 * Author: wizlab.it
 */

#include "main.h"

uint16_t drX=0, drY=0;
uint8_t r=0, g=0, b=0;
int8_t xDir=1, yDir=1, rDir=1, gDir=1, bDir=1, cCol='r';

void main(void) {
    //Init everything
    init();
    TFT_Init();

    //Check device ID
    /*
    if(TFT_ReadID() == 0x9326) {
        PORTAbits.RA0 = 1;
    }
    */

    //Loop forever
    while(1) loop();
}


/*==============================================================================
 * Loop routine
 *============================================================================*/
void loop(void) {
    //Draw white pixel at drX,drY
    switch(cCol) {
        case 'r':
            r += rDir;
            if((r == 0xFF) || (r == 0x00)) rDir *= -1;
            //if(r == 0xFF) cCol = 'g';
            if(r == 0x00) cCol = 'b';
            break;
        case 'g':
            g += gDir;
            if((g == 0xFF) || (g == 0x00)) gDir *= -1;
            //if(g == 0xFF) cCol = 'b';
            if(g == 0x00) cCol = 'r';
            break;
        case 'b':
            b += bDir;
            if((b == 0xFF) || (b == 0x00)) bDir *= -1;
            //if(b == 0xFF) cCol = 'r';
            if(b == 0x00) cCol = 'g';
            break;
    }
    TFT_DrawPixel(drX, drY, TFT_ColorRGBTo16Bit(r, g, b));
    drX += xDir;
    drY += yDir;
    if((drX == 0) || (drX == (_TFT_WIDTH - 1))) xDir *= -1;
    if((drY == 0) || (drY == (_TFT_HEIGHT - 1))) yDir *= -1;
}