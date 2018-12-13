#ifndef __MATHOP_H__
#define __MATHOP_H__

#include <stdint.h>
#include <limits.h>

void set_current_operand(int value, int flag);
void set_current_operand_equal(int value);
void reset_current_operand( void);
uint8_t get_current_operand(void);
void set_operation(char value);
int calculate_result(void);

#endif // __MATHOP_H__