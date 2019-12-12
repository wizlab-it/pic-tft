/* 
 * 20190314.008
 * TFT 240x400
 *
 * File: commons.h
 * Processor: PIC18F2455
 * Author: wizlab.it
 */

#ifndef COMMONS_H
#define	COMMONS_H

#include <xc.h>
#include <stdint.h>
#include "TFT.h"

#define _XTAL_FREQ 24000000     //CPU Frequency

//External functions
extern void init(void);

#endif