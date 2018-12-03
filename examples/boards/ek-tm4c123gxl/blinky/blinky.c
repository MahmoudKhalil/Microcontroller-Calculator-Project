#include "lcd.h"
#include "keypad.h"

void clear_screen(void);

void handler_1(void);

int main()
{
  lcd_init();
  keypad_init();
  
  while(1)
    {
      /*char key = keypad_get_key();
      if(key == '+' || key == '-' || key == '*') {
        op = key;
        operands[counter] = get_number();
        counter++;
        clear_parser();
      } else if(key != '=') {
        parse(key);
      } else if(key == '=') {
        operands[counter] = get_number();
        counter = 0;
      }*/
      /*if (key != 0) {
        if(key == 'C') {
          clear_screen();
        } else {
          lcd_data(key);
        }
      }
      delay_ms(30);*/
  }
  //return 0;
}

void clear_screen(void) {
  lcd_command(0x01);
}

void handler_1(void) {
  //int row = 0;
  lcd_data('1');
}
