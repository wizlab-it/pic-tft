/*
 * 20190314.006
 * TFT 240x400
 *
 * File: init.h
 * Processor: PIC18F2455
 * Author: wizlab.it
 */

#ifndef INIT_H
#define	INIT_H

#include "commons.h"

#pragma config PLLDIV = 1           // PLL Prescaler Selection bits (Divide by 1 (4 MHz oscillator input))
#pragma config CPUDIV = OSC2_PLL3   //System Clock Postscaler Selection bits ([Primary Oscillator Src: /2][96 MHz PLL Src: /3])
#pragma config USBDIV = 2           // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)
#pragma config FOSC = HSPLL_HS      // Oscillator Selection bits (XT oscillator, PLL enabled (XTPLL))
#pragma config FCMEN = OFF          // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF           // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
#pragma config PWRT = OFF           // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF            // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 0             // Brown-out Reset Voltage bits (Maximum setting)
#pragma config VREGEN = OFF         // USB Voltage Regulator Enable bit (USB voltage regulator disabled)
#pragma config WDT = OFF            // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768        // Watchdog Timer Postscale Select bits (1:32768)
#pragma config CCP2MX = ON          // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF         // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF        // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF          // MCLR Pin Enable bit (RE3 input pin enabled; MCLR pin disabled)
#pragma config STVREN = OFF         // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF            // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF          // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled)
#pragma config CP0 = OFF            // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF            // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF            // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CPB = OFF            // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF            // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)
#pragma config WRT0 = OFF           // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF           // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF           // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRTC = OFF           // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF           // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF           // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)
#pragma config EBTR0 = OFF          // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF          // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF          // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTRB = OFF          // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

void init(void);
void __interrupt() isr(void);

#endif