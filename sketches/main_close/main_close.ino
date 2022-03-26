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
#define I2C_Clock 8000000
#define BOAL_RADIUS 3.6
#define UNIT_RADIUS 8.5
#define MAX_R 1400

//ハードウェア依存
uint8_t IR_PIN[8] = {A1,A2,A3,A4,A5,A6,A7,A8};//ピンの番号
float IR_IN[8] = {5*PI/4, 3*PI/2, 7*PI/4, 0, PI/4, PI/2, 3*PI/4, PI};//ピンの角度
float IR_cor[8] = {1.07,1.11,1.03,1.00,1.14,1.00,1.14,1.10};
float theta_M[3] = {0.0,4*PI/3,2*PI/3};//モーターの角度
int power = 100;

//インスタンスの生成
IR_sensor IR_sen(IR_PIN,IR_IN);
MovingAverage ma_radius(20);
moter_control Mctrl(theta_M);
Adafruit_BNO055 Compass_ctrl = Adafruit_BNO055(-1, 0x28);
Cal_dir Cal_dir(0);
Ultrasonic Ultrasonic_back(25,ECHO_PIN,TRIG_PIN);

//グローバル変数
imu::Vector<3> euler;//絶対角度が入る
vectorRT_t Boal_RT;
float now_radius,now_theta,round_theta,G_dir = PI/2;
int Mom_now;

void setup() {
  Serial.begin(9600);//デバック
  Serial1.begin(9600);//ラインセンサー
  IR_sen.set_cor(IR_cor);
  IR_sen.set_radius(UNIT_RADIUS,BOAL_RADIUS,MAX_R);
  Wire.begin();//i2c コンパス　モーター
  Wire.setClock(I2C_Clock);
  //pinMode(START_PIN,INPUT);
  //button_stay();
  setup_compass(&Compass_ctrl,&Cal_dir);
  Cal_dir.set_PID_par(0.7,0.2,0.1,0.004);
}

void loop() {
  //Serial.println(Boal_RT.theta);
  bool flag = true;//line_check(&Mctrl,power);
  
  if(flag){
    euler = Compass_ctrl.getVector(Adafruit_BNO055::VECTOR_EULER);//現在の絶対角度を取得
    Mom_now = Cal_dir.Cal_Mom_PID(euler.x()/180*PI);
    Boal_RT = IR_sen.cal_RT();
    now_radius = ma_radius.updateData(Boal_RT.radius);
    Serial.println(now_radius);
    if(now_radius < 100)Mctrl.moter_move(0,0,Mom_now);
    else if(now_radius < 500)Mctrl.moter_move(Boal_RT.theta,power,Mom_now);
    else{
      if(Boal_RT.theta < -2*PI/3){
        round_theta = IR_sen.cal_close(Boal_RT.theta,now_radius);
        Mctrl.moter_move(round_theta,power,Mom_now);
      }else if(Boal_RT.theta < -PI/2){
        Mctrl.moter_move(0,power,Mom_now);
      }else if(Boal_RT.theta < -PI/3){
        Mctrl.moter_move(PI,power,Mom_now);
      }else if(Boal_RT.theta < G_dir-PI/6){
        round_theta = IR_sen.cal_close(Boal_RT.theta,now_radius);
        Mctrl.moter_move(round_theta,power,Mom_now);
      }else if(Boal_RT.theta < G_dir+PI/6){
        Mctrl.moter_move(G_dir,power,Mom_now);
      }else{
        round_theta = IR_sen.cal_close(Boal_RT.theta,now_radius);
        Mctrl.moter_move(round_theta,power,Mom_now);
      }
    }
    /*else if(now_radius < MAX_R*0.9){
      round_theta = IR_sen.cal_close(Boal_RT.theta,now_radius);
      Mctrl.moter_move(round_theta,power,Mom_now);
    }else{//Mctrl.moter_move(round_theta,0,Mom_now);
      if(-PI <= Boal_RT.theta && Boal_RT.theta <= -7*PI/12)Mctrl.moter_move(-PI/2,power,Mom_now);
      else if(-7*PI/12 < Boal_RT.theta && Boal_RT.theta <= -PI/2)Mctrl.moter_move(0,power,Mom_now);
      else if(-PI/2 < Boal_RT.theta && Boal_RT.theta <= -5*PI/12)Mctrl.moter_move(PI,power,Mom_now);
      else if(-5*PI/12 < Boal_RT.theta && Boal_RT.theta <= 0)Mctrl.moter_move(-PI/2,power,Mom_now);
      else if(0 < Boal_RT.theta && Boal_RT.theta <= PI/6)Mctrl.moter_move(Boal_RT.theta-PI/6,power,Mom_now);
      else if(PI/6 < Boal_RT.theta && Boal_RT.theta <= 5*PI/6)Mctrl.moter_move(Boal_RT.theta,power,Mom_now); 
      else if(5*PI/6 < Boal_RT.theta && Boal_RT.theta <= PI)Mctrl.moter_move(Boal_RT.theta+PI/6,power,Mom_now);
    }*/
  }
}

void button_stay(){
  noInterrupts();//割り込み停止
  while(true){
    if(digitalRead(START_PIN)==1)break;
    delayMicroseconds(10);
  }
  interrupts();//割り込み開始
}
