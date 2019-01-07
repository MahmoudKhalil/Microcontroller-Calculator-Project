/*
 * delay.c
 *
 *  Created on: Dec 28, 2018
 *      Author: mahmoud
 */

#include "delay.h"

void DelayUs(unsigned int delay) {
  int i, j = 0;
  for(i = 0; i < delay; i++) {
    for(j = 0; j < 3; j++) {}
  }
}

void DelayMs(unsigned int delay) {
  int i, j = 0;
  for(i = 0; i < delay; i++) {
    for(j = 0; j < 3180; j++) {}
  }
}