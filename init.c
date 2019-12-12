/*
 * 20190312.009
 * TFT 240x400
 *
 * File: init.c
 * Processor: PIC18F2455
 * Author: wizlab.it
 */

#include "init.h"


/*==============================================================================
 * System initialization
 *============================================================================*/
void init(void) {
    //Init Oscillator
    OSCCONbits.IDLEN = 0;         //Device enters in sleep mode on SLEEP
    OSCCONbits.IRCF = 0b111;      //8MHz (Not used, since valid only for internal oscillator)
    OSCCONbits.SCS = 0b00;        //Uses crystal
    OSCTUNEbits.INTSRC = 1;
    OSCTUNEbits.TUN = 0;

    //Wait a bit...
    __delay_ms(100);

    //Disbale USB / Allows RC4 and RC5 as digital inputs
    UCONbits.USBEN = 0;
    UCFGbits.UTRDIS = 1;

    /*
    * PORT A
    *  - RA[7]: 0 (Not implemented)
    *  - RA[6]: 0 (Not available - used by XTAL)
    *  - RA[5]: 1 (Input, Unused)
    *  - RA[4]: 1 (Input, Unused)
    *  - RA[3]: 1 (Input, Unused)
    *  - RA[2]: 1 (Input, Unused)
    *  - RA[1]: 1 (Input, Unused)
    *  - RA[0]: 0 (Output, Led)
    */
    TRISA = 0b00111110;
    PORTA = 0x00;
    LATA = 0x00;

    /*
    * PORT B
    *  - RB[7-0]: 0 (Digital output, TFT Data)
    */
    RBPU = 1; //Disable weak pull ups
    TRISB = 0x00;
    PORTB = 0x00;
    LATB = 0x00;

    /*
    * PORT C
    *  - RC[7]: 0 (Output, TFT RD)
    *  - RC[6]: 0 (Output, TFT WR)
    *  - RC[5]: 1 (Input, Unused)
    *  - RC[4]: 1 (Input, Unused)
    *  - RC[3]: 0 (Not implemented)
    *  - RC[2]: 0 (Output, TFT Reset)
    *  - RC[1]: 0 (Output, TFT CD/RS)
    *  - RC[0]: 0 (Output, TFT CS)
    */
    TRISC = 0b00110000;
    PORTC = 0x00;
    LATC = 0x00;

    //Interrupts
    SSPIE = 0;
    PEIE = 0;
    GIE = 0;

    return;
}

/*==============================================================================
 * Interrupt Service Routine
 *============================================================================*/
void __interrupt() isr(void) {
    return;
}