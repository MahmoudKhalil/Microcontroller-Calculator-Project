#include "mathop.h"

int operands [2] = {INT_MIN, INT_MIN};
int current_operand= 0;
char operation;

void set_current_operand(int value, int flag){
  /*operands[current_operand] = value;
  current_operand = (current_operand +1)% 2 ;*/
  switch(current_operand) {
  case 0:
    operands[0] = value;
    current_operand = 1;
    break;
  case 1:
    operands[1] = value;
    current_operand = 2;
    break;
  case 2:
    if(flag == 1) {
      operands[0] = value;
      current_operand = 1;
    } else if(flag == 0) {
      operands[0] = value;
    }
  }
}


void reset_current_operand( void){
  current_operand= 0;
  operands [0]=INT_MIN;
  operands [1]=INT_MIN;

}
uint8_t get_current_operand(){

 return current_operand ;
}

void set_operation(char value){
  operation = value;
}
int calculate_result(void){

  if(operands[1] == INT_MIN) {
    return INT_MIN;
  }

  switch (operation){
  case '+':
      if(operands[0] == INT_MIN) {
          operands[0] = 0;
       }
      return operands[0]+operands[1];
      break;
  case '-':
      if(operands[0] == INT_MIN) {
        operands[0] = 0;
      }
      return operands[0]-operands[1];
      break;
  case '*':
      if(operands[0] == INT_MIN) {
        return INT_MIN;
      }
      return operands[0]*operands[1];
      break;
  case '/':
      if(operands[0] == INT_MIN) {
        return INT_MIN;
      }
      if(operands[1] == 0)
      {
        return INT_MIN;
      }
      return operands[0]/operands[1];
      break;

  }

}

