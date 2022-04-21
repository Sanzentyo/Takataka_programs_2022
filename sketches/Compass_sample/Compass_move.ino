//標準ライブラリ
#include <Wire.h>
#include <math.h>

//外部ライブラリ
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//自作ライブラリ
#include "Compass_dircal_PID.h"
#include "Line_checker.h"
#include <Compare_function.h>
#include <IR_sensor.h>
#include <moter_control.h>
#include <moving_average.h>
#include <Ultrasonic.h>

//定数
#define START_PIN 11
#define STOP_PIN 12

#define ECHO_PIN_a 48
#define ECHO_PIN_b 49
#define ECHO_PIN_c 50

#define TRIG_PIN_a 46
#define TRIG_PIN_b 47
#define TRIG_PIN_c 48

#define TEMP_NOW 25

#define MOVE moter_move_SPI


//ハードウェア依存
uint8_t IR_PIN[8] = {A1,A2,A3,A4,A5,A6,A7,A8};//ピンの番号
float IR_IN[8] = {5*PI/4, 3*PI/2, 7*PI/4, 0, PI/4, PI/2, 3*PI/4, PI};//ピンの角度
float theta_M[3] = {0.0,4*PI/3,2*PI/3};//モーターの角度


//インスタンスの生成
IR_sensor IR_sen(IR_PIN,IR_IN);
moter_control Mctrl(theta_M);
Adafruit_BNO055 Compass_ctrl = Adafruit_BNO055(-1, 0x28);
Cal_dir Cal_dir(0);
Ultrasonic Ultrasonic_a(TEMP_NOW,ECHO_PIN_a,TRIG_PIN_a);
Ultrasonic Ultrasonic_b(TEMP_NOW,ECHO_PIN_b,TRIG_PIN_b);
Ultrasonic Ultrasonic_c(TEMP_NOW,ECHO_PIN_c,TRIG_PIN_c);

//グローバル変数
imu::Vector<3> euler;//絶対角度が入る
vectorRT_t Boal_RT;
int Mom_now;
bool line_flag;
int power = 50;

int st,i = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Wire.begin();
  Wire.setClock(400000UL);//i2cの高速化
  setup_compass(&Compass_ctrl,&Cal_dir);
  //pinMode(START_PIN,INPUT);
  //pinMode(STOP_PIN,INPUT_PULLUP);
  //button_stay();
  //attachInterrupt(digitalPinToInterrupt(STOP_PIN), button_stay, RISING);
  st = millis();
}

void loop() {
  //Serial.println(Boal_RT.theta);
  //bool flag = line_check(&Mctrl,power);
  //Serial.print("flag:");
  //Serial.println(flag);

  if((st-millis())>2000){
    st = millis();
    if(i < 4)i += 1;else i = 0;
    }

  euler = Compass_ctrl.getVector(Adafruit_BNO055::VECTOR_EULER);//現在の絶対角度を取得
  Mom_now = Cal_dir.Cal_Mom_P(euler.x()/180*PI);
  Serial.println(Mom_now);
  //Boal_RT = IR_sen.cal_RT();
  //Serial.println(Mom_now);
  //Serial.println(Boal_RT.radius);
  //Mctrl.MOVE(Boal_RT.theta,100,Mom_now);

  //delay(1000);
}



void button_stay(){
  noInterrupts();//割り込み停止
  while(true){
    if(digitalRead(START_PIN)==1)break;
    delayMicroseconds(10);
  }
  interrupts();//割り込み開始
}
