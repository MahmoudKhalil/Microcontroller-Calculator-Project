#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdint.h>

int get_number(void);

void parse(char c);

void clear_parser(void);

char* number_to_char(int input);

int get_number_char(void);
#endif // __PARSER_H__