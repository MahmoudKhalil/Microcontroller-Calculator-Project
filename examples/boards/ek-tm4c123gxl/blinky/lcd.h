#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "delay.h"

void lcd_init(void);
void lcd_command(unsigned char command);
void lcd_data(unsigned char data);
void lcd_char_data(unsigned char *data, int length);
void port_a_init(void);
void port_b_init(void);

#endif