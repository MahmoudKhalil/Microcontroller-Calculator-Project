#include "lcd.h"
#include "keypad.h"
#include "parser.h"
#include "mathop.h"
void clear_screen(void);
void  result_handler(void);
bool result_on_screen= false;
void handler_pin_4(void);
int count_flag = 0;
//int row = 0;
int main()
{
  lcd_init();
  keypad_init(handler_pin_4);
  
  while(1) {
    count_flag = 0;
    /*row = 0;
    //GPIO_PORTE_DATA_R = 0x0E;
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | 
                 GPIO_PIN_0, 0x0E);
    delay_ms(2);
    
    row = 1;
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | 
                 GPIO_PIN_0, 0x0D);
    
    delay_ms(2);
    
    row = 2;
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | 
                 GPIO_PIN_0, 0x0B);
    
    delay_ms(2);
    
    row = 3;
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | 
                 GPIO_PIN_0, 0x07);
    delay_ms(2);*/
  }
  
  /*while(1)
    {
      char key = keypad_get_key();
      if (key != 0) {
      if(key == '+' || key == '-' || key == '*'|| key == '/') {
        if (get_current_operand() == 1){
        result_handler();
        }
        set_operation(key);
        set_current_operand(get_number());
     //   clear_parser();
        clear_screen();
      }
      else if(key == '=') {
        result_handler();
        /*set_current_operand(get_number());
       // clear_parser();
        clear_screen();
        uint32_t result = calculate_result();
        lcd_char_data(number_to_char(result),  get_number_char());
        result_on_screen = true;
        set_number(result); // in case they make another operation to result */
        
      /*}
      else if(key == 'C') {
          clear_screen();
          reset_current_operand();
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

void result_handler(){
        set_current_operand(get_number());
       // clear_parser();
        clear_screen();
        int result = calculate_result();
        unsigned char* result_char = number_to_char(result);
        uint32_t length = get_number_char();
        lcd_char_data(result_char,  length);
        result_on_screen = true;
        set_number(result); // in case they make another operation to result 
}

void clear_screen(void) {
  lcd_command(0x01);
   result_on_screen = false;
   clear_parser();
}

void handler_pin_4(void) {
  /*GPIOIntDisable(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | 
               GPIO_PIN_7);*/
  GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | 
               GPIO_PIN_7);
  count_flag++;
  int row, col;
  
  if(count_flag <= 1) {
  delay_ms(100);
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
      break;
    }
    lcd_data(keypad_get_key(row, col));
    delay_ms(100);
  }
  
  /*GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | 
               GPIO_PIN_7);*/
}