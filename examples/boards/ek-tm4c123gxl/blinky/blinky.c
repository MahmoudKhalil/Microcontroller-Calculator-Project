#include "lcd.h"
#include "keypad.h"
#include "parser.h"
#include "mathop.h"
void clear_screen(void);
bool result_on_screen= false;
int main()
{
  lcd_init();
  keypad_init();
  
  while(1)
    {
      char key = keypad_get_key();
      if (key != 0) {
      if(key == '+' || key == '-' || key == '*'|| key == '/') {
        set_operation(key);
        set_current_operand(get_number());
     //   clear_parser();
        clear_screen();
      }
      else if(key == '=') {
        set_current_operand(get_number());
       // clear_parser();
        clear_screen();
        uint32_t result = calculate_result();
        lcd_char_data(number_to_char(result),  get_number_char());
        result_on_screen = true;
        set_number(result); // in case they make another operation to result 
        
      }
      else if(key == 'C') {
          clear_screen();
     }
      else  {
        if(result_on_screen) {  //Check if they insert a new number while result is being displayed
          clear_screen();
          reset_current_operand();
        }
        parse(key);
        lcd_data(key);

      } 
         }
   /*   if(key == '=') {
        unsigned char *pew = number_to_char(get_number());
        lcd_char_data(pew, get_number_char());
      } else {
        if(key != 0) {
          parse(key);
          lcd_data(key);
        }
      }
      
      if (key != 0) {
        if(key == 'C') {
          clear_screen();
        } else {
          //lcd_data(key);
        }
      }*/
      delay_ms(30);
  }
  //return 0;
}

void clear_screen(void) {
  lcd_command(0x01);
   result_on_screen = false;
   clear_parser();
}
