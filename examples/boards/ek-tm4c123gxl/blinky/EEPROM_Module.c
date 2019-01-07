#include "EEPROM_Module.h"
#include "keypad.h"
#include "lcd.h"

uint32_t ui32EEPROMInit;
uint32_t pui32Data[2];
uint32_t pui32Read[2];

short EEPRMIsKeyPressed = 0;

void EEPROMKeypadKeyHandler(void);

void EEPROMKeypadKeyHandler(void){
    GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                          GPIO_PIN_7);
    EEPRMIsKeyPressed = 1;
}

void EEPROM_Init(void){
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
  
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0))
  {
  }
  
  ui32EEPROMInit = EEPROMInit();
  
  if(ui32EEPROMInit != EEPROM_INIT_OK)
  {
    while(1)
    {
    }
   }
}

void EEPROM_Main(){
  EEPROM_Init();
  LCDInit();
  KeypadInit(EEPROMKeypadKeyHandler);
  
  unsigned char choice1[13] = {'1', ':', 'D', 'A', 'E', 'R', ' ', 'M', 'O', 'R', 'P', 'E', 'E'};
  unsigned char choice2[14] = {'2', 'E', 'T', 'I', 'R', 'W', ' ', 'W', 'M', 'O', 'R', 'P', 'E', 'E'};
  
  while(EEPRMIsKeyPressed  == 0) {
        LCDCharData(choice1, 13);
        DelayMs(1000);
        LCDCommand(0x01);

        LCDCharData(choice2, 14);
        DelayMs(1000);
        LCDCommand(0x01);

    }
  
  while(1) {
        if(EEPRMIsKeyPressed == 1) {
            char key = GetKeyPressed();
            if(key == '1') { //EEPROM READ
                EEPROMRead(pui32Read, 0x400, sizeof(pui32Read));
            } else if(key == '2') { //EEPROM WRITE
                  pui32Data[0] = 0x12345678;
                  pui32Data[1] = 0x56789abc;
                  EEPROMProgram(pui32Data, 0x400, sizeof(pui32Data));

        }
    }
  
  
  }

}
