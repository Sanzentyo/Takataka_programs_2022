#ifndef __Goal_detect_H__
#define __Goal_detect_H__

#include <Arduino.h>


class Goal_detecter{
  public:
    Goal_detecter(int length,int width);
    void set_field(int length,int width);
    float detect(float now_diff,int a,int b,int c);

    private:
      int field_length;
      int field_width; 
}
#endif
