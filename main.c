#include "lcd.h"
#include "keypad.h"
#include "calculator.h"

void MainKeypadKeyHandler(void);
void DisplayWelcomeMessage(void);

short MainIsKeyPressed = 0;

int main(void)
{
    LCDInit();
    KeypadInit(MainKeypadKeyHandler);
    DisplayWelcomeMessage();

    while(1) {
        if(MainIsKeyPressed == 1) {
            char key = GetKeyPressed();
            if(key == '1') { //For Calculator Functionality
                CalculatorMain();
            } else if(key == '2') { //For EEPROM Functionality

            } else if(key == '3') { //For RTC Functionality

            }
        }
    }
	//return 0;
}

void DisplayWelcomeMessage(void) {
    unsigned char welcome[7] = {'W', 'e', 'l', 'c', 'o', 'm', 'e'};
    unsigned char choice1[5] = {'C', 'l', 'c', ':', '1'};
    unsigned char choice2[8] = {'E', 'E', 'P', 'R', 'O', 'M', ':', '2'};
    unsigned char choice3[5] = {'R', 'T', 'C', ':', '3'};

    LCDCharData(welcome, 7);
    DelayMs(1000);
    LCDCommand(0x01);
    while(MainIsKeyPressed == 0) {
        LCDCharData(choice1, 5);
        DelayMs(1000);
        LCDCommand(0x01);

        LCDCharData(choice2, 8);
        DelayMs(1000);
        LCDCommand(0x01);

        LCDCharData(choice3, 5);
        DelayMs(1000);
        LCDCommand(0x01);
    }
}

void MainKeypadKeyHandler(void) {
    GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                          GPIO_PIN_7);
    MainIsKeyPressed = 1;
}
