#include "Compare_function.h"
#include "IR_sensor.h"
#include <moving_average.h>
#include <math.h>

uint8_t IR_PIN[8] = {A1,A2,A3,A4,A5,A6,A7,A8};
//float IR_IN[8] = {5*PI/4, 3*PI/2, 7*PI/4, 0, PI/4, PI/2, 3*PI/4, PI};//i2c
float IR_IN[8] = {PI, 3*PI/4, PI/2, PI/4, 0, 7*PI/4, 3*PI/2, 5*PI/4};//SPI
float IR_cor[8] = {1.00,1.04,1.07,1.05,1.25,1.07,1.15,1.07};
//float IR_IN[8] = {5*PI/4, 3*PI/2, 7*PI/4, 0, PI/4, PI/2, 3*PI/4, PI};//main_Serial
IR_sensor IR_sen(IR_PIN,IR_IN);
MovingAverage ma_radius(20);
MovingAverage ma_x(20);
MovingAverage ma_y(20);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  IR_sen.set_cor(IR_cor);
  IR_sen.set_radius(10,3.6,1100);
}

float now_radius;
vectorRT_t now_RT;

void loop() {
  float a = micros();
  now_RT = IR_sen.cal_RT();
  IR_sen.print_data();
  now_radius = ma_radius.updateData(now_RT.radius);
  //Serial.println(now_RT.theta/PI*180);
  //Serial.println(IR_sen.cal_close(now_RT.theta,now_radius)/PI*180);
  //Serial.println(micros()-a);
  delay(500);

}
