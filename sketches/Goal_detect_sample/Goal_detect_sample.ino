//標準ライブラリ
#include <Wire.h>
#include <math.h>

//外部ライブラリ
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//自作ライブラリ
#include <Compass_dircal_PID.h>
#include <Line_checker.h>
#include <Compare_function.h>
#include <IR_sensor.h>
#include <moter_control.h>
#include <moving_average.h>
#include <Ultrasonic.h>
#include "Goal_detect.h"


//定数
#define START_PIN 11

#define ECHO_PIN_a 12
#define ECHO_PIN_b 10
#define ECHO_PIN_c 14

#define TRIG_PIN_a 13
#define TRIG_PIN_b 11
#define TRIG_PIN_c 15

#define TEMP_NOW 25


//ハードウェア依存
uint8_t IR_PIN[8] = {A1,A2,A3,A4,A5,A6,A7,A8};//ピンの番号
float IR_IN[8] = {5*PI/4, 3*PI/2, 7*PI/4, 0, PI/4, PI/2, 3*PI/4, PI};//ピンの角度
float theta_M[3] = {0.0,4*PI/3,2*PI/3};//モーターの角度
uint8_t power = 40;


//インスタンスの生成
IR_sensor IR_sen(IR_PIN,IR_IN);
moter_control Mctrl(theta_M);
Adafruit_BNO055 Compass_ctrl = Adafruit_BNO055(-1, 0x28);
Cal_dir Cal_dir(0);
Ultrasonic Ultrasonic_a(TEMP_NOW,ECHO_PIN_a,TRIG_PIN_a);
Ultrasonic Ultrasonic_b(TEMP_NOW,ECHO_PIN_b,TRIG_PIN_b);
Ultrasonic Ultrasonic_c(TEMP_NOW,ECHO_PIN_c,TRIG_PIN_c);
Goal_detecter detecter(170,80);
//ロボ自体　直径17
//weight 132cm  1/2= 66cm -robo= 49cm
//hegiht 193cm            -robo= 176cm

void setup() {
    Serial.begin(115200);
    detecter.set_Sonics(&Ultrasonic_a,&Ultrasonic_b,&Ultrasonic_c);
}

void loop() {
  //a = millis();
  Serial.println(detecter.detect(0)*180/PI);
  /*st = millis()-a;
  Serial.print(",");
  Serial.println(st);
  delay(50-st);*/

}
