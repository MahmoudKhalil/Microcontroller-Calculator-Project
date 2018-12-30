#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "delay.h"
#include "tm4c123gh6pm.h"

void KeypadInit(void (*KeypadKeyHandler)(void));
unsigned char GetKeyPressed(void);
void PortCInit(void (*KeypadKeyHandler)(void)) ;
void PortEInit(void);

#endif