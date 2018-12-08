#include "mathop.h"
int operands [2];
int current_operand= 0;
char operation;

void set_current_operand(int value){
  operands[current_operand] = value;
  current_operand = (current_operand +1)% 2 ;
}
void reset_current_operand( void){
  current_operand= 0;
  operands [0]=0;
  operands [1]=0;

}
uint8_t get_current_operand(){
  
 return current_operand ;
}

void set_operation(char value){
  operation = value;
}
int calculate_result(void){
  
  switch (operation){
  case '+':
      return operands[0]+operands[1];
      break;
  case '-':
      return operands[0]-operands[1];
      break;
  case '*':
      return operands[0]*operands[1];
      break;    
  case '/':
      return operands[0]/operands[1];
      break;
   
  }
  
}

