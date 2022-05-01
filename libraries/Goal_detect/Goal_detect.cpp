#include "Goal_detect.h"
#include <math.h>
#include <Ultrasonic.h>

Goal_detecter::Goal_detecter(float height,float width){
  field_height = height;
  field_width = width;
};

void Goal_detecter::set_field(float height,float width){
  field_height = height;
  field_width = width;
};

void Goal_detecter::set_Sonics(Ultrasonic* a_ads,Ultrasonic* b_ads,Ultrasonic* c_ads){
  a_p = a_ads;
  b_p = b_ads;
  c_p = c_ads;
};

float Goal_detecter::detect(float now_diff,float a,float b,float c){
  float now_cos = cos(now_diff);
  if(a < c){
    return atan2(field_height-b*now_cos, field_width-a*now_cos);
  }else{
    return atan2(field_height-b*now_cos, -(field_width-c*now_cos));
  }

  return -1;
}
;
float Goal_detecter::detect(float now_diff){
  float now_cos = cos(now_diff);
  float a = a_p->measure();
  float b = b_p->measure();
  float c = c_p->measure();
  if(a < c){
    return atan2(field_height-b*now_cos, field_width-c*now_cos);
  }else{
    return atan2(field_height-b*now_cos, -(field_width-a*now_cos));
  }

  return -1;
}
