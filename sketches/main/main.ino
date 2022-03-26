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

//定数
#define START_PIN 11
#define ECHO_PIN 48
#define TRIG_PIN 46

//ハードウェア依存
uint8_t IR_PIN[8] = {A1,A2,A3,A4,A5,A6,A7,A8};//ピンの番号
float IR_IN[8] = {5*PI/4, 3*PI/2, 7*PI/4, 0, PI/4, PI/2, 3*PI/4, PI};//ピンの角度
float theta_M[3] = {0.0,4*PI/3,2*PI/3};//モーターの角度
float IR_cor[8] = {1.07,1.11,1.03,1.00,1.14,1.00,1.14,1.10};
int power = 40;

//インスタンスの生成
IR_sensor IR_sen(IR_PIN,IR_IN);
moter_control Mctrl(theta_M);
Adafruit_BNO055 Compass_ctrl = Adafruit_BNO055(-1, 0x28);
Cal_dir Cal_dir(0);
Ultrasonic Ultrasonic_back(25,ECHO_PIN,TRIG_PIN);

//グローバル変数
imu::Vector<3> euler;//絶対角度が入る
vectorRT_t Boal_RT;
int Mom_now;

void setup() {
  Serial.begin(9600);//デバック
  Serial1.begin(9600);//ラインセンサー
  IR_sen.set_cor(IR_cor);
  Wire.begin();//i2c コンパス　モーター
  //pinMode(START_PIN,INPUT);
  //button_stay();
  setup_compass(&Compass_ctrl,&Cal_dir);
}

void loop() {
  //Serial.println(Boal_RT.theta);
  int flag = true;//line_check(&Mctrl,power);
  //Serial.println(flag);

  /*
  if(flag) {
  euler = Compass_ctrl.getVector(Adafruit_BNO055::VECTOR_EULER);//現在の絶対角度を取得
  Mom_now = Cal_dir.Cal_Mom_PID(euler.x());
  Boal_RT = IR_sen.calcRT();
  //Serial.println(180*Boal_RT.theta/PI);
  Mctrl.moter_move(Boal_RT.theta,70,Mom_now);
  }
  */
  //回り込みなどを書き足したもの
  if(flag){
    euler = Compass_ctrl.getVector(Adafruit_BNO055::VECTOR_EULER);//現在の絶対角度を取得
    Mom_now = Cal_dir.Cal_Mom_P(euler.x());
    Boal_RT = IR_sen.cal_RT();
    Serial.println(Boal_RT.theta);
    if(Boal_RT.radius > 100){
      if(-PI <= Boal_RT.theta && Boal_RT.theta <= -7*PI/12)Mctrl.moter_move(-PI/2,power,Mom_now);
      else if(-7*PI/12 < Boal_RT.theta && Boal_RT.theta <= -PI/2)Mctrl.moter_move(0,power,Mom_now);
      else if(-PI/2 < Boal_RT.theta && Boal_RT.theta <= -5*PI/12)Mctrl.moter_move(PI,power,Mom_now);
      else if(-5*PI/12 < Boal_RT.theta && Boal_RT.theta <= 0)Mctrl.moter_move(-PI/2,power,Mom_now);
      else if(0 < Boal_RT.theta && Boal_RT.theta <= PI/6)Mctrl.moter_move(Boal_RT.theta-PI/6,power,Mom_now);
      else if(PI/6 < Boal_RT.theta && Boal_RT.theta <= 5*PI/6)Mctrl.moter_move(Boal_RT.theta,power,Mom_now); 
      else if(5*PI/6 < Boal_RT.theta && Boal_RT.theta <= PI)Mctrl.moter_move(Boal_RT.theta+PI/6,power,Mom_now);
    }else{
      if(Ultrasonic_back.measure() > 25)Mctrl.moter_move(3*PI/2,power,Mom_now);
      else Mctrl.moter_stop();
    }
  }
  
  //Serial.println("running");
}



void button_stay(){
  noInterrupts();//割り込み停止
  while(true){
    if(digitalRead(START_PIN)==1)break;
    delayMicroseconds(10);
  }
  interrupts();//割り込み開始
}
