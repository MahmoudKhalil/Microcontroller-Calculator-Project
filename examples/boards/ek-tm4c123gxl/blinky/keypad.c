/*
 * keypad.c
 *
 *  Created on: Dec 28, 2018
 *      Author: mahmoud
 */
#include "keypad.h"
#include "delay.h"

void PortCInit(void (*KeypadKeyHandler)(void)) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) {}

    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                      GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                      GPIO_PIN_7);

    GPIO_PORTC_PUR_R |= 0XFF; //enable pull-up resistors

    GPIOIntRegister(GPIO_PORTC_BASE, KeypadKeyHandler);
    GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                 GPIO_PIN_7, GPIO_FALLING_EDGE);
    GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                      GPIO_PIN_7);
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                 GPIO_PIN_7);
}

void PortEInit(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)) {}

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                      GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                      GPIO_PIN_7);

    GPIO_PORTE_ODR_R |= 0XFF;
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                       GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
                       0);
}

void KeypadInit(void (*KeypadKeyHandler)(void)) {
    PortCInit(KeypadKeyHandler);
    PortEInit();
}

unsigned char GetKeyPressed(void) {
    GPIOIntDisable(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                     GPIO_PIN_7);

    const unsigned char keymap[4][4] = {
      {'1' , '2' , '3' , '+'},
      {'4' , '5' , '6' , '-'},
      {'7' , '8' , '9' , '*'},
      {'=' , '0' , 'C' , '/'}
    };

    int row,col;

    while(1)
    {
        row = 0;
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 |
                   GPIO_PIN_0, 0x0E);
        DelayUs(500);

        col = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
             GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7) & 0xF0;
        if(col != 0xF0)
          break;

        row = 1;
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 |
                   GPIO_PIN_0, 0x0D);

        DelayUs(500);

        col = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
             GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7) & 0xF0;
        if(col != 0xF0)
          break;

        row = 2;
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 |
                   GPIO_PIN_0, 0x0B);

        DelayUs(500);

        col = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
             GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7) & 0xF0;
        if(col != 0xF0)
          break;

        row = 3;
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 |
                   GPIO_PIN_0, 0x07);
        DelayUs(500);
        col = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
             GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7) & 0xF0;
        if(col != 0xF0)
          break;

        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                   GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
                   0);
        GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                       GPIO_PIN_7);

        return 0;
    }

    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                 GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
                 0);
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                     GPIO_PIN_7);

    if (col == 0xE0) return keymap[row][0];
    if (col == 0xD0) return keymap[row][1];
    if (col == 0xB0) return keymap[row][2];
    if (col == 0x70) return keymap[row][3];

    return 0;
}