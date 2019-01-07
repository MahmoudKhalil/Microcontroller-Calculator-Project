
#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "lcd.h"
#include "keypad.h"
#include "parser.h"
#include "mathop.h"
#include "delay.h"
#include <stdbool.h>

void KeypadKeyHandler(void);
void clear_screen(void);
void  result_handler(int flag);
void result_handler_equal();
void CalculatorMain(void);

#endif /* CALCULATOR_H_ */