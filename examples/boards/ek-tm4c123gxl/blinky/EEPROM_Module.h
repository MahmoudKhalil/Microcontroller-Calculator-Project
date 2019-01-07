#ifndef __EEPROM_MODULE_H__
#define __EEPROM_MODULE_H__

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/eeprom.h"
#include "driverlib/sysctl.h"
#include "delay.h"




void EEPROM_Init(void);
void EEPROM_Main();

#endif