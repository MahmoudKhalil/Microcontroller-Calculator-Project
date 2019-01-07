/*
 * lcd.h
 *
 *  Created on: Dec 28, 2018
 *      Author: mahmoud
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/tm4c123gh6pm.h"

void LCDInit(void);
void LCDCommand(unsigned char c);
void LCDData(unsigned char c);
void LCDCharData(unsigned char *data, int length);

#endif /* LCD_H_ */
