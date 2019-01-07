#include "calculator.h"

bool result_on_screen= false;
bool op_pressed = false;
short IsKeyPressed = 0;

void CalculatorMain(void) {
    LCDInit();
    KeypadInit(KeypadKeyHandler);

    while(1) {
      if(IsKeyPressed == 0) {
            SysCtlSleep();
        }
      else{
          IsKeyPressed = 0;
      char key = GetKeyPressed();
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
               LCDData(key);

             }

            }
      }
      DelayMs(30);
  }
  //return 0;
}

void result_handler(int flag) {

  unsigned char error[5] = {'R','O','R','R','E'};
  set_current_operand(get_number(), flag);
  clear_screen();
  int result = calculate_result();
  if (result == INT_MIN)
  {
    LCDCharData(error, 5);
    clear_parser();
    reset_current_operand();
    result_on_screen = true;
    return;
   }

   unsigned char* result_char = number_to_char(result);
   uint32_t length = get_number_char();
   LCDCharData(result_char,  length);
   result_on_screen = true;
   set_number(result); // in case they make another operation to result
}



void clear_screen(void) {

    LCDCommand(0x01);
    result_on_screen = false;
    clear_parser();
}

void KeypadKeyHandler(void) {
    GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
                      GPIO_PIN_7);
    IsKeyPressed = 1;
}