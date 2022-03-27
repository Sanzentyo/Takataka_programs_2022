#include "Arduino.h" 
#include "IR_sensor.h"
#include <Compare_function.h>
#include <math.h>

#define A 54
//#define MAX_R 1600
#define COR_VAL 10

IR_sensor::IR_sensor(uint8_t* PIN_ads,float* theta_ads){

  //PinのアドレスとIRの角度を格納
  for(int i = 0;i < IR_NUM;i++){
    Pin[i] = PIN_ads[i];
    pinMode(Pin[i],INPUT);
    unit_theta[i] = theta_ads[i];//IRセンサーの向いてる向き
    unit_cos[i] = cos(unit_theta[i]);//xにかけるやつ
    unit_sin[i] = sin(unit_theta[i]);//yにかけるやつ
  }
  
}

void IR_sensor::print_data(){
  Serial.println("IR_data");
    for(int i = 0;i < IR_NUM;i++){
     Serial.print("\tPin");Serial.print(Pin[i]-A);Serial.print(" : ");Serial.println(IR_Cur[i]);
    }
  Serial.print("反応数 : ");Serial.println(IR_Info.active_num);
  Serial.print("最大値\tPin");Serial.print(IR_Info.max_index-A);Serial.print(" : ");Serial.println(IR_Info.max_val);

  Serial.println("\nVector_XY");
    Serial.print("\tx : ");Serial.print(vector_XY.x);
    Serial.print("\ty : ");Serial.println(vector_XY.y);

  Serial.println("\nVector_RT");
    Serial.print("\tradius : ");Serial.print(vector_RT.radius);
    Serial.print("\ttheta : ");Serial.println(vector_RT.theta/PI*180);
  
  Serial.print("\n------------------------------\n");
}

void IR_sensor::print_csv_first(){
  Serial.print("時間");
  for(int i = 0;i < IR_NUM;i++){
     Serial.print(",Pin");Serial.print(Pin[i]);
  }
  Serial.println(",反応数,最大値のPin,最大値,x,y,radius,theta");
}

void IR_sensor::print_csv(){
  Serial.print(micros());
  for(int i = 0;i < IR_NUM;i++){
     Serial.print(",");Serial.print(IR_Cur[i]);
  }
  Serial.print(",");Serial.print(IR_Info.active_num);Serial.print(",");Serial.print(IR_Info.max_index-A);Serial.print(",");Serial.print(IR_Info.max_val);Serial.print(",");
  Serial.print(vector_XY.x);Serial.print(",");Serial.print(vector_XY.y);Serial.print(",");
  Serial.print(vector_RT.radius);Serial.print(",");Serial.println(vector_RT.theta/PI*180);
}

void IR_sensor::set_cor(float* cor_ads){
  for(int i = 0;i < IR_NUM;i++){
    unit_cor[i] = cor_ads[i];
  }
}

void IR_sensor::set_radius(float unit,float boal,int max_r){
  unit_radius = unit;
  boal_radius = boal;
  R = boal + unit;
  MAX_R = max_r;
}

void IR_sensor::read_IR(){
    //アナログでIRセンサーの値を読み込む
  for(int i = 0;i < IR_NUM;i++){
    IR_Cur[i] = IR_CUR_MAX - analogRead(Pin[i]);
    //IR_Cur[i] = analogRead(Pin[i]);
  }

  // ベクトル計算のみでセンシングを行うのであれば以下の実装は不要
  // ボールに反応しているセンサの個数
  IR_Info.active_num    = 0; 
  IR_Info.max_val  = 0; // 一番反応の強いセンサのパルス幅
  IR_Info.max_index  = 0; // 一番反応の強いセンサの番号
  for(int i = 0; i < IR_NUM; i++) {
    if(IR_Cur[i] > 5) {
        IR_Info.active_num += 1;
      }
    if(IR_Cur[i] > IR_Info.max_val){
        IR_Info.max_val = IR_Cur[i];
        IR_Info.max_index = Pin[i];
      }
  }
}

//vector_XYの計算
vectorXY_t IR_sensor::cal_XY(){
  this->read_IR();

  vector_XY = {0,0};//メンバ関数vector_XYの初期化

  //ベクトル計算でx成分とy成分
  for(int i = 0; i < IR_NUM; i++) {
        vector_XY.x += IR_Cur[i] * unit_cos[i];
        vector_XY.y += IR_Cur[i] * unit_sin[i];
  }

  return vector_XY;
}

vectorRT_t IR_sensor::cal_RT(){
  this->cal_XY();

  //ボールの角度(theta)と距離(radius)を出す　角度は弧度法
  vector_RT.radius  = sqrt(pow(vector_XY.x, 2.0) + pow(vector_XY.y, 2.0));
  vector_RT.theta   = atan2(vector_XY.y, vector_XY.x);//double atan2(double y, double x);

  return vector_RT;
}

void IR_sensor::read_IR_cor(){
    //アナログでIRセンサーの値を読み込む
  for(int i = 0;i < IR_NUM;i++){
    IR_Cur[i] = (IR_CUR_MAX - analogRead(Pin[i]))*unit_cor[i];
    //IR_Cur[i] = analogRead(Pin[i]);
  }

  // ベクトル計算のみでセンシングを行うのであれば以下の実装は不要
  // ボールに反応しているセンサの個数
  IR_Info.active_num    = 0; 
  IR_Info.max_val  = 0; // 一番反応の強いセンサのパルス幅
  IR_Info.max_index  = 0; // 一番反応の強いセンサの番号
  for(int i = 0; i < IR_NUM; i++) {
    if(IR_Cur[i] > 5) {
        IR_Info.active_num += 1;
      }
    if(IR_Cur[i] > IR_Info.max_val){
        IR_Info.max_val = IR_Cur[i];
        IR_Info.max_index = Pin[i];
      }
  }
}

//vector_XYの計算
vectorXY_t IR_sensor::cal_XY_cor(){
  this->read_IR_cor();

  vector_XY = {0,0};//メンバ関数vector_XYの初期化

  //ベクトル計算でx成分とy成分
  for(int i = 0; i < IR_NUM; i++) {
        vector_XY.x += IR_Cur[i] * unit_cos[i];
        vector_XY.y += IR_Cur[i] * unit_sin[i];
  }

  return vector_XY;
}

vectorRT_t IR_sensor::cal_RT_cor(){
  this->cal_XY_cor();

  //ボールの角度(theta)と距離(radius)を出す　角度は弧度法
  vector_RT.radius  = sqrt(pow(vector_XY.x, 2.0) + pow(vector_XY.y, 2.0));
  vector_RT.theta   = atan2(vector_XY.y, vector_XY.x);//double atan2(double y, double x);

  return vector_RT;
}

//必ずcal_RT()を用いてから実行する
float IR_sensor::cal_close(float now_boal_theta,float now_boal_radius){
  float x,y,x_pre,y_pre;
  x_pre = now_boal_radius*cos(now_boal_theta);
  y_pre = now_boal_radius*sin(now_boal_theta);
  if(x_pre >= 0)x = (MAX_R - x_pre)/COR_VAL;else x = -(MAX_R + x_pre)/COR_VAL;
  if(y_pre >= 0)y = (MAX_R - y_pre)/COR_VAL;else y = -(MAX_R + y_pre)/COR_VAL;

  //与えられるthetaが -PI〜PI であるのが前提
  //atan()は -PI/2〜PI/2 を戻り値とする
  if(-PI/2 <= now_boal_theta && now_boal_theta <= PI/2){
   //a2,b2 red
   //Serial.println("red");
    float d = sqrt(x*x + y*y - R*R);
    float a = x*R - y*d;
    float b = y*R + x*d;
    if(b == 0){
      if(now_boal_theta > 0)return PI/2;
      else return -PI/2;
    }
    else return atan(-a/b);
  }else{
   //a1,b1 blue
    float d = sqrt(x*x + y*y - R*R);
    float a = x*R + y*d;
    float b = y*R - x*d;
    if(b == 0){
      if(now_boal_theta > 0)return PI/2;
      else return -PI/2;
    }
    else return atan(-a/b)+PI;
  }
}
