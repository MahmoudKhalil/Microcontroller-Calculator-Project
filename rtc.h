#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "lcd.h"
#include "parser.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void PortFInit(void);
void Timer0AIntHandler(void);
void Timer0Init(void);
void RTCMain(void);

#endif /* RTC_H_ */
