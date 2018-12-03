#include "lcd.h"
#include "keypad.h"
#include "parser.h"

void clear_screen(void);

int main()
{
  lcd_init();
  keypad_init();
  
  while(1)
    {
      char key = keypad_get_key();
      /*if(key == '+' || key == '-' || key == '*') {
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
      if(key == '=') {
        unsigned char *pew = number_to_char(get_number());
        lcd_char_data(pew, get_number_char());
      } else {
        if(key != 0) {
          parse(key);
        }
      }
      
      if (key != 0) {
        if(key == 'C') {
          clear_screen();
        } else {
          //lcd_data(key);
        }
      }
      delay_ms(30);
  }
  //return 0;
}

void clear_screen(void) {
  lcd_command(0x01);
}
