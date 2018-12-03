#ifndef __MATHOP_H__
#define __MATHOP_H__

#include <stdint.h>
void set_current_operand(uint32_t value);
void reset_current_operand( void);
uint8_t get_current_operand(void);
void set_operation(char value);
uint32_t calculate_result(void);
#endif // __MATHOP_H__