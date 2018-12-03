#include "delay.h"

void delay_us(unsigned int delay) {
  int i, j = 0;
  for(i = 0; i < delay; i++) {
    for(j = 0; j < 3; j++) {}
  }
}

void delay_ms(unsigned int delay) {
  int i, j = 0;
  for(i = 0; i < delay; i++) {
    for(j = 0; j < 3180; j++) {}
  }
}