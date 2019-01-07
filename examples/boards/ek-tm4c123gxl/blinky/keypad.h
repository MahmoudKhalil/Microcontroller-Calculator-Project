/*
 * keypad.h
 *
 *  Created on: Dec 28, 2018
 *      Author: mahmoud
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/tm4c123gh6pm.h"

void KeypadInit(void (*KeypadKeyHandler)(void));
void PortCInit(void (*KeypadKeyHandler)(void));
void PortEInit(void);
unsigned char GetKeyPressed(void);

#endif /* KEYPAD_H_ */