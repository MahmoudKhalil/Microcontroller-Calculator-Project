#include "lcd.h"

void port_a_init(void) {
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);  
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {}
  
  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                      GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                      GPIO_PIN_7);
}

void port_b_init(void) {
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);  
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)) {}
  
  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                      GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                      GPIO_PIN_7);
}

void lcd_init(void) {
  port_a_init();
  port_b_init();
  
  lcd_command(0x30);
  delay_ms(10);
  
  lcd_command(0x38);
  delay_ms(200);
  lcd_command(0x06);
  delay_ms(200);
  lcd_command(0x01);
  delay_ms(200);
  lcd_command(0x0F);
  delay_ms(200);
  
}

void lcd_command(unsigned char command) {
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | 
               GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
               0);
  
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | 
               GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
               command);
  
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
  delay_us(10);
  
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | 
               GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
               0);
  
  if(command < 4) {
    delay_ms(2);
  } else {
    delay_us(40);
  }
}

void lcd_data(unsigned char data) {
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | 
               GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0);
  
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
  
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | 
               GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
               data);
  
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
  delay_ms(1);
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | 
               GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0);
  delay_ms(40);
}

void lcd_char_data(unsigned char *data, int length) {
  for(int i = length - 1; i >= 0; i--) {
    lcd_data(data[i]);
  }
}