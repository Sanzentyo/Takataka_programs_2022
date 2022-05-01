#include "Ultrasonic.h"

#define ECHO_PIN_a 14
#define ECHO_PIN_b 10
#define ECHO_PIN_c 12

#define TRIG_PIN_a 15
#define TRIG_PIN_b 11
#define TRIG_PIN_c 13

#define TEMP_NOW 25

//Ultrasonic Sonic_uno(temp,9,8);
Ultrasonic Ultrasonic_a(TEMP_NOW,ECHO_PIN_a,TRIG_PIN_a);
Ultrasonic Ultrasonic_b(TEMP_NOW,ECHO_PIN_b,TRIG_PIN_b);
Ultrasonic Ultrasonic_c(TEMP_NOW,ECHO_PIN_c,TRIG_PIN_c);

void setup() {
  Serial.begin(115200);
}

void loop() {
  //float a = micros();
  //Sonic_uno.measure();
  //for(int i = 0;i < 100;i++){if((i%2)==0)digitalWrite(2,LOW);else digitalWrite(2,HIGH);} 
  Serial.print("Sonic_a:");Serial.println(Ultrasonic_a.measure());
  Serial.print("Sonic_b:");Serial.println(Ultrasonic_b.measure());
  Serial.print("Sonic_c:");Serial.println(Ultrasonic_c.measure());
  //Serial.println((micros()-a));
  Serial.println("------------------------");
  delay(500);
}
