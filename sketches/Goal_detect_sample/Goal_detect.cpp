#include "Goal_detect.h"

Goal_detecter::Goal_detecter(int length,int width){
  field_length = length;
  field_width = width;
};

void Goal_detecter::set_field(int length,int width){
  field_length = length;
  field_width = width;
};

float Goal_detecter::detect(float now_diff,int a,int b,int c){
  if(a > b){
    a = a;
  }

  return -1;
}
