#include "Compare_function.h"
#include "IR_sensor.h"
#include <math.h>

uint8_t IR_PIN[8] = {A1,A2,A3,A4,A5,A6,A7,A8};
float IR_IN[8] = {5*PI/4, 3*PI/2, 7*PI/4, 0, PI/4, PI/2, 3*PI/4, PI};//main
//float IR_IN[8] = {5*PI/4, 3*PI/2, 7*PI/4, 0, PI/4, PI/2, 3*PI/4, PI};//main_Serial
IR_sensor IR_sen(IR_PIN,IR_IN,9.0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {

  IR_sen.cal_RT();
  IR_sen.print_data();
   
  delay(1000);

}
