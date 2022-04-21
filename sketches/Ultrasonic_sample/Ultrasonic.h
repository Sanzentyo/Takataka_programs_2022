#ifndef __Ultrasonic_H__
#define __Ultrasonic_H__
#include <Arduino.h>

class Ultrasonic {
  public:
    Ultrasonic(float temp,int set_echo_pin,int set_trig_pin);
    float measure();

  private:
    float speed_of_sound;
    int echo_pin;
    int trig_pin;
};

#endif
