//標準ライブラリ
#include <Wire.h>
#include <math.h>

//外部ライブラリ
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//自作ライブラリ
#include <Compass_dircal_PID.h>
#include <Compare_function.h>
#include <IR_sensor.h>
#include <moter_control.h>
#include <moving_average.h>
#include <Ultrasonic.h>
#include <Goal_detect.h>
#include <kicker.h>

//定数
#define START_PIN 11
#define ECHO_PIN 48
#define TRIG_PIN 46
#define I2C_Clock 400000
#define BOAL_RADIUS 3.6
#define UNIT_RADIUS 10
#define IR_UNIT_RADIUS 450
#define MAX_R 1100

#define ECHO_PIN_a 12
#define ECHO_PIN_b 10
#define ECHO_PIN_c 14

#define TRIG_PIN_a 13
#define TRIG_PIN_b 11
#define TRIG_PIN_c 15

#define K_PIN 3
#define FT_PIN A9
#define TH_VAL 600
#define DELAY_TIME 750

#define TEMP_NOW 23

#define MOVE moter_move_SPI
#define STOP moter_stop_SPI

//ハードウェア依存
uint8_t IR_PIN[8] = {A1,A2,A3,A4,A5,A6,A7,A8};//ピンの番号
float IR_IN[8] = {PI, 3*PI/4, PI/2, PI/4, 0, 7*PI/4, 3*PI/2, 5*PI/4};//ピンの角度
float IR_cor[8] = {1.07,1.11,1.03,1.00,1.14,1.00,1.14,1.10};
//float theta_M[3] = {0,2*PI/3,4*PI/3};//モーターの角度
float theta_M[3] = {PI,-PI/3,PI/3};//モーターの角度 SPI
int power = 0, line_power = 50;

//インスタンスの生成
IR_sensor IR_sen(IR_PIN,IR_IN);
MovingAverage ma_radius(20);
moter_control Mctrl(theta_M);
Adafruit_BNO055 Compass_ctrl = Adafruit_BNO055(-1, 0x28);
Cal_dir Cal_dir(0);
Ultrasonic Ultrasonic_a(TEMP_NOW,ECHO_PIN_a,TRIG_PIN_a);
Ultrasonic Ultrasonic_b(TEMP_NOW,ECHO_PIN_b,TRIG_PIN_b);
Ultrasonic Ultrasonic_c(TEMP_NOW,ECHO_PIN_c,TRIG_PIN_c);
Goal_detecter detecter(176,49); //(height,wighth)
kicker kicker(K_PIN,FT_PIN,TH_VAL,DELAY_TIME);


//グローバル変数
vectorRT_t Boal_RT;
float now_radius,now_theta,round_theta,G_dir = PI/2,unit_dir;
int Mom_now;

void setup() {
  Serial.begin(115200);//デバック
  Serial1.begin(115200);//ラインセンサー
  
  //IR_sen.set_cor(IR_cor);
  IR_sen.set_radius(UNIT_RADIUS,BOAL_RADIUS,MAX_R);
  
  Wire.begin();//i2c コンパス　モーター
  Wire.setClock(I2C_Clock);
  
  setup_compass(&Compass_ctrl,&Cal_dir);
  Cal_dir.set_PID_par(0.64,0.2,0.1,0.004);

  detecter.set_Sonics(&Ultrasonic_a,&Ultrasonic_b,&Ultrasonic_c);
  
  Mctrl.SPI_setup();
  Mctrl.set_MAX_POW(70);
  
  //setupTimer5();//linechecker
  //pinMode(START_PIN,INPUT);
  //button_stay();
}

long time;
imu::Vector<3> euler;//絶対角度が入る

void loop() {
  //Serial.println(Boal_RT.theta);
  bool flag = line_check();
  if(flag){
  euler = Compass_ctrl.getVector(Adafruit_BNO055::VECTOR_EULER);//現在の絶対角度を取得
  Mom_now = Cal_dir.Cal_Mom_P(euler.x()/180*PI);
  Boal_RT = IR_sen.cal_RT();
  //if(kicker.scan())kicker.kick();
  Serial.println(kicker.scan_int());
  //Serial.println(Boal_RT.theta/PI*180);
  //Mctrl.MOVE(Boal_RT.theta,power,-Mom_now);
  //delay(50);
  }
  
  if(false){
    unit_dir = Compass_ctrl.getVector(Adafruit_BNO055::VECTOR_EULER).x()/180*PI;//現在の絶対角度を取得
    Mom_now = 0;//Cal_dir.Cal_Mom_P(unit_dir);Cal_dir.Cal_Mom_P_target(unit_dir,G_dir);
    Boal_RT = IR_sen.cal_RT();
    now_radius = ma_radius.updateData(Boal_RT.radius);
    //Serial.println(now_radius);
    if(now_radius < 100 && false)Mctrl.MOVE(0,0,Mom_now);
    else if(now_radius < 500 | true)Mctrl.MOVE(Boal_RT.theta,power,Mom_now);
    else/* if(now_radius < MAX_R*0.9)*/{
      float now_x = now_radius*cos(Boal_RT.theta);
      
      if((Boal_RT.theta < -2*PI/3) | (now_x < -IR_UNIT_RADIUS && Boal_RT.theta < 0)){
        round_theta = IR_sen.cal_close(Boal_RT.theta,now_radius);
        Mctrl.MOVE(round_theta,power,Mom_now);
      }else if(Boal_RT.theta < -PI/2){
        Mctrl.MOVE(0,power,Mom_now);//右
      }else if((Boal_RT.theta < -PI/3) && (now_x < IR_UNIT_RADIUS)){
        Mctrl.MOVE(PI,power,Mom_now);//左
      }else if((PI/6 < Boal_RT.theta) | (IR_UNIT_RADIUS < now_x)){
        round_theta = IR_sen.cal_close(Boal_RT.theta,now_radius);
        Mctrl.MOVE(round_theta,power,Mom_now);
      }else if((Boal_RT.theta < 5*PI/6) && (-IR_UNIT_RADIUS < now_x)){
        Mctrl.MOVE(G_dir,power,Mom_now);
      }else{
        round_theta = IR_sen.cal_close(Boal_RT.theta,now_radius);
        Mctrl.MOVE(round_theta,power,Mom_now);
      }
    }
    /*else if(now_radius < MAX_R*0.9){
      round_theta = IR_sen.cal_close(Boal_RT.theta,now_radius);
      Mctrl.MOVE(round_theta,power,Mom_now);
    }else{//Mctrl.MOVE(round_theta,0,Mom_now);
      if(-PI <= Boal_RT.theta && Boal_RT.theta <= -7*PI/12)Mctrl.MOVE(-PI/2,power,Mom_now);
      else if(-7*PI/12 < Boal_RT.theta && Boal_RT.theta <= -PI/2)Mctrl.MOVE(0,power,Mom_now);
      else if(-PI/2 < Boal_RT.theta && Boal_RT.theta <= -5*PI/12)Mctrl.MOVE(PI,power,Mom_now);
      else if(-5*PI/12 < Boal_RT.theta && Boal_RT.theta <= 0)Mctrl.MOVE(-PI/2,power,Mom_now);
      else if(0 < Boal_RT.theta && Boal_RT.theta <= PI/6)Mctrl.MOVE(Boal_RT.theta-PI/6,power,Mom_now);
      else if(PI/6 < Boal_RT.theta && Boal_RT.theta <= 5*PI/6)Mctrl.MOVE(Boal_RT.theta,power,Mom_now); 
      else if(5*PI/6 < Boal_RT.theta && Boal_RT.theta <= PI)Mctrl.MOVE(Boal_RT.theta+PI/6,power,Mom_now);
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

bool line_check(){
  byte dir = 0;
  //Serial.println("hey");
  
  while(Serial1.available() > 0){
    dir = Serial1.read();
  }

  if(dir == 0 | dir == 8){
    return true;
  }else{
    float esc_theta = map(dir,1,254,-180,180)*PI/180;
    unit_dir = Compass_ctrl.getVector(Adafruit_BNO055::VECTOR_EULER).x()/180*PI;//現在の絶対角度を取得
    Mom_now = 0;//Cal_dir.Cal_Mom_P(unit_dir);
    Mctrl.MOVE(esc_theta,line_power,-Mom_now);
    //delayMicroseconds(100);
    //Serial.println(dir);
    line_check();
    return false;
  }
}
