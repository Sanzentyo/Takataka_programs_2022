#ifndef __Line_checker__
#define __Line_checker__

#include "Arduino.h"
#include <math.h>
#include <moter_control.h>

int line_check(moter_control* Mctrl,int power){
  int dir = -1;
  
  while(Serial1.available() > 0){
  dir = Serial1.read();
  }

  switch(dir){
    case 0:
      Mctrl->moter_move(-PI/2,power,0);
      return false;
    case 1:
      Mctrl->moter_move(-PI/4,power,0);
      return false;
    case 2:
      Mctrl->moter_move(0,power,0);
      return false;
    case 3:
      Mctrl->moter_move(PI/4,power,0);
      return false;
    case 4:
      Mctrl->moter_move(PI/2,power,0);
      return false;
    case 5:
      Mctrl->moter_move(3*PI/4,power,0);
      return false;
    case 6:
      Mctrl->moter_move(PI,power,0);
      return false;
    case 7:
      Mctrl->moter_move(-3*PI/4,power,0);
      return false;
    default:
      return true;
  }
    return true;//恐らく必要ないが念のため
}

int line_check_Serial(moter_control* Mctrl,int power){
  int dir = -1;
  
  while(Serial1.available() > 0){
  dir = Serial1.read();
  }

  switch(dir){
    case 0:
      Mctrl->moter_move_Serial(-PI/2,power,0);
      return false;
    case 1:
      Mctrl->moter_move_Serial(-PI/4,power,0);
      return false;
    case 2:
      Mctrl->moter_move_Serial(0,power,0);
      return false;
    case 3:
      Mctrl->moter_move_Serial(PI/4,power,0);
      return false;
    case 4:
      Mctrl->moter_move_Serial(PI/2,power,0);
      return false;
    case 5:
      Mctrl->moter_move_Serial(3*PI/4,power,0);
      return false;
    case 6:
      Mctrl->moter_move_Serial(PI,power,0);
      return false;
    case 7:
      Mctrl->moter_move_Serial(-3*PI/4,power,0);
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
