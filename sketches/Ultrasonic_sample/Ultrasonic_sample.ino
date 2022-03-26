#include "Ultrasonic.h"

const float temp = 25;
const int echo_pins[3] = {48,44,40};
const int trig_pins[3] = {46,42,36};

Ultrasonic Sonic_uno(temp,9,8);
//Ultrasonic Sonic0(temp,echo_pins[0],trig_pins[0]);
//Ultrasonic Sonic1(temp,echo_pins[1],trig_pins[1]);
//Ultrasonic Sonic2(temp,echo_pins[2],trig_pins[2]);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float a = micros();
  Sonic_uno.measure();
  //for(int i = 0;i < 100;i++){if((i%2)==0)digitalWrite(2,LOW);else digitalWrite(2,HIGH);} 
  //Serial.print("Sonic0:");Serial.println(Sonic0.measure());
  //Serial.print("Sonic1:");Serial.println(Sonic1.measure());
  //Serial.print("Sonic2:");Serial.println(Sonic2.measure());
  Serial.println((micros()-a));
  Serial.println("------------------------");
  //delay(500);
}
