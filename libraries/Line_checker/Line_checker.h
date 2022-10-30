#ifndef __Line_checker__
#define __Line_checker__

#include "Arduino.h"
#include <math.h>
#include <motor_control.h>

int line_check(motor_control* Mctrl,int power){
  int dir = -1;
  
  while(Serial1.available() > 0){
  dir = Serial1.read();
  }

  switch(dir){
    case 0:
      Mctrl->motor_move(-PI/2,power,0);
      return false;
    case 1:
      Mctrl->motor_move(-PI/4,power,0);
      return false;
    case 2:
      Mctrl->motor_move(0,power,0);
      return false;
    case 3:
      Mctrl->motor_move(PI/4,power,0);
      return false;
    case 4:
      Mctrl->motor_move(PI/2,power,0);
      return false;
    case 5:
      Mctrl->motor_move(3*PI/4,power,0);
      return false;
    case 6:
      Mctrl->motor_move(PI,power,0);
      return false;
    case 7:
      Mctrl->motor_move(-3*PI/4,power,0);
      return false;
    default:
      return true;
  }
    return true;//恐らく必要ないが念のため
}

int line_check_Serial(motor_control* Mctrl,int power){
  int dir = -1;
  
  while(Serial1.available() > 0){
  dir = Serial1.read();
  }

  switch(dir){
    case 0:
      Mctrl->motor_move_Serial(-PI/2,power,0);
      return false;
    case 1:
      Mctrl->motor_move_Serial(-PI/4,power,0);
      return false;
    case 2:
      Mctrl->motor_move_Serial(0,power,0);
      return false;
    case 3:
      Mctrl->motor_move_Serial(PI/4,power,0);
      return false;
    case 4:
      Mctrl->motor_move_Serial(PI/2,power,0);
      return false;
    case 5:
      Mctrl->motor_move_Serial(3*PI/4,power,0);
      return false;
    case 6:
      Mctrl->motor_move_Serial(PI,power,0);
      return false;
    case 7:
      Mctrl->motor_move_Serial(-3*PI/4,power,0);
      return false;
    default:
      return true;
  }
    return true;//恐らく必要ないが念のため
}

int line_int(){
  int dir = -1;
  
  while(Serial1.available() > 0){
    dir = Serial1.read();
  }

  return dir;
}



#endif
