#include <Arduino.h>
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(float temp,int set_echo_pin,int set_trig_pin){
  speed_of_sound = 331.5 + 0.6 * temp; // temp℃の時の音速
  echo_pin = set_echo_pin;
  trig_pin = set_trig_pin;
  
  pinMode(echo_pin, INPUT );
  pinMode(trig_pin, OUTPUT );
}

float Ultrasonic::measure(){
  digitalWrite(trig_pin, LOW); 
  delayMicroseconds(2); 
  digitalWrite( trig_pin, HIGH );
  delayMicroseconds( 10 ); 
  digitalWrite( trig_pin, LOW );
  float duration = pulseIn( echo_pin, HIGH ); // 往復にかかった時間が返却される[マイクロ秒]
  
  if (duration > 0) {
    duration = duration / 2; // 往路にかかった時間
    float distance = duration * speed_of_sound * 100 / 1000000;//距離
    return distance;
  }else{
    return -1;
  }
}
