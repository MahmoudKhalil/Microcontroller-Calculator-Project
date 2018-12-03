#include "parser.h"

int number = 0;
char number_char[16] = {0};
int number_to_char_counter = 0;

int get_number(void) {
  return number;
}

void parse(char c) {
  int digit = c - '0';
  number = (number * 10) + digit;
}

void clear_parser(void) {
  number = 0;
}

char* number_to_char(int input) {
  number_to_char_counter = 0;
  while(input != 0) {
    number_char[number_to_char_counter] = input % 10;
    input  /= 10;
    number_to_char_counter++;
  }
  
  return number_char;
}

int get_number_char(void) {
  return number_to_char_counter;
}