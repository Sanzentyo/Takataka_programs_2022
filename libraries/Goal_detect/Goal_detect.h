#ifndef __Goal_detect_H__
#define __Goal_detect_H__

#include <Arduino.h>
#include <Ultrasonic.h>


class Goal_detecter{
  public:
    Goal_detecter(float height,float width);
    void set_field(float height,float width);
    void set_Sonics(Ultrasonic* a_ads,Ultrasonic* b_ads,Ultrasonic* c_ads);
    float detect(float now_diff,float a,float b,float c);
    float detect(float now_diff);

    private:
      int field_height;
      int field_width; 
      Ultrasonic* a_p,*b_p,*c_p;
};

#endif
