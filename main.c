#include "lcd.h"
#include "keypad.h"
#include "calculator.h"
#include "rtc.h";

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
            MainIsKeyPressed = 0;
            char key = GetKeyPressed();
            if(key == '1') { //For Calculator Functionality
                CalculatorMain();
            } else if(key == '2') { //For EEPROM Functionality

            } else if(key == '3') { //For RTC Functionality
                RTCMain();
            }
        }

        DisplayWelcomeMessage();
    }
	//return 0;
}

void DisplayWelcomeMessage(void) {
    unsigned char welcome[7] = {'e', 'm', 'o', 'c', 'l', 'e', 'W'};
    unsigned char choice1[5] = {'1', ':', 'C', 'L', 'C'};
    unsigned char choice2[8] = {'2', ':', 'M', 'O', 'R', 'P', 'E', 'E'};
    unsigned char choice3[5] = {'3', ':', 'C', 'T', 'R'};

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
    //GPIOIntUnregister(GPIO_PORTC_BASE);
}
