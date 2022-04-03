#include "Goal_detect.h"
#include <math.h>

Goal_detecter::Goal_detecter(int height,int width){
  field_height = height;
  field_width = width;
};

void Goal_detecter::set_field(int height,int width){
  field_height = height;
  field_width = width;
};

float Goal_detecter::detect(float now_diff,int a,int b,int c){
  float now_cos = cos(now_diff);
  if(a < c){
    return atan2(field_height-b*now_cos,field_width-a*now_cos);
  }else{
    return atan2(field_height-b*now_cos,-(field_width-c*now_cos));
  }

  return -1;
}
