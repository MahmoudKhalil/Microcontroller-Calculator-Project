#include "lcd.h"
#include "keypad.h"
#include "parser.h"
#include "mathop.h"

void clear_screen(void);
void  result_handler(int flag);
void  result_handler_equal();
bool result_on_screen= false;
bool op_pressed = false;
int main()
{
  lcd_init();
  keypad_init();
    

  while(1)
    {
      char key = keypad_get_key();
      
      if (key != 0) 
      {
        if((key == '+' || key == '-' || key == '*'|| key == '/')) 
        {
          if((!op_pressed)) 
          {
            if (get_current_operand() == 1)
            {
            result_handler(1);
            }
            
            set_operation(key);
            set_current_operand(get_number(), 1);
            clear_screen();
            op_pressed = true;
            }
        }
        
        
        else if(key == '=') 
        {
          op_pressed = false;
          result_handler(0);
        }
      
      
        else if(key == 'C') 
        {
          op_pressed =false;
          clear_screen();
          reset_current_operand();
        }
      
      
        else  
        {
        
          op_pressed = false;
        
          if(result_on_screen) 
          {  //Check if they insert a new number while result is being displayed
            clear_screen();
            reset_current_operand();
          }
        
          parse(key);
          lcd_data(key);

        } 
        
       }
   
       delay_ms(30);
      
     }

}



void result_handler(int flag)
{

  unsigned char error[5] = {'R','O','R','R','E'};
  set_current_operand(get_number(), flag);
  clear_screen();
  int result = calculate_result();
  if (result == INT_MIN)
  {
    lcd_char_data(error, 5);
    clear_parser();
    reset_current_operand();
    result_on_screen = true;
    return;
   }
  
   unsigned char* result_char = number_to_char(result);
   uint32_t length = get_number_char();
   lcd_char_data(result_char,  length);
   result_on_screen = true;
   set_number(result); // in case they make another operation to result 
}



void clear_screen(void)
{

  lcd_command(0x01);
   result_on_screen = false;
   clear_parser();
}
