#include "keypad.h"

void port_c_init(void (*handler_pin_4)(void)) {   
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);  
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) {}
  
  GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                      GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                      GPIO_PIN_7);
  
  GPIO_PORTC_PUR_R |= 0XFF; //enable pull-up resistors
  
  GPIOIntRegister(GPIO_PORTC_BASE, handler_pin_4);
  GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                 GPIO_PIN_7, GPIO_FALLING_EDGE);
  GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                 GPIO_PIN_7);
}

void port_e_init()
{
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

void keypad_init(void (*handler_pin_4)(void))
{
  port_c_init(handler_pin_4);
  port_e_init();
}

unsigned char keypad_get_key(int row, int col)
{
  const unsigned char keymap[4][4] = {
      {'1' , '2' , '3' , '+'},
      {'4' , '5' , '6' , '-'},
      {'7' , '8' , '9' , '*'},
      {'=' , '0' , 'C' , '/'}
  };
  
  /*int row,col;
  
  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | 
             GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
             0); //enable all rows;
  
  delay_ms(200);
  
  col = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | 
             GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7) & 0xF0;
  
  if (col == 0xF0)
      return 0;
  
  while(1)
  {
      row = 0;
      //GPIO_PORTE_DATA_R = 0x0E;
      GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | 
                   GPIO_PIN_0, 0x0E);
      delay_ms(2);
      
      col = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | 
             GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7) & 0xF0;
      if(col != 0xF0)
          break;
      
      row = 1;
      GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | 
                   GPIO_PIN_0, 0x0D);
      
      delay_ms(2);
      
      col = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | 
             GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7) & 0xF0;
      if(col != 0xF0)
          break;
      
      row = 2;
      GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | 
                   GPIO_PIN_0, 0x0B);
      
      delay_ms(2);
      
      col = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | 
             GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7) & 0xF0;
      if(col != 0xF0)
          break;
      
      row = 3;
      GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | 
                   GPIO_PIN_0, 0x07);
      delay_ms(2);
      col = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | 
             GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7) & 0xF0;
      if(col != 0xF0)
          break;
      
      return 0;
  }*/
  
  if (col == 0xE0) return keymap[row][0];
  if (col == 0xD0) return keymap[row][1];
  if (col == 0xB0) return keymap[row][2];
  if (col == 0x70) return keymap[row][3];
  
  //return 0;
}