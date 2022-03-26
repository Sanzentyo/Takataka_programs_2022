#include "Arduino.h" 
#include "IR_sensor.h"
#include <Compare_function.h>
#include <math.h>

IR_sensor::IR_sensor(uint8_t* PIN_ads,float* theta_ads,float radius_val){

  //PinのアドレスとIRの角度を格納
  for(int i = 0;i < IR_NUM;i++){
    Pin[i] = PIN_ads[i];
    pinMode(Pin[i],INPUT);
    unit_theta[i] = theta_ads[i];//IRセンサーの向いてる向き
    unit_cos[i] = cos(unit_theta[i]);//xにかけるやつ
    unit_sin[i] = sin(unit_theta[i]);//yにかけるやつ
  }

  unit_radius = radius_val;
  
}

void IR_sensor::print_data(){
  Serial.println("IR_data");
    for(int i = 0;i < IR_NUM;i++){
     Serial.print("\tPin");Serial.print(Pin[i]);Serial.print(" : ");Serial.println(IR_Cur[i]);
    }
  Serial.print("反応数 : ");Serial.println(IR_Info.active_num);
  Serial.print("最大値\tPin");Serial.print(IR_Info.max_index-54);Serial.print(" : ");Serial.println(IR_Info.max_val);

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
  Serial.print(",");Serial.print(IR_Info.active_num);Serial.print(",");Serial.print(IR_Info.max_index);Serial.print(",");Serial.print(IR_Info.max_val);Serial.print(",");
  Serial.print(vector_XY.x);Serial.print(",");Serial.print(vector_XY.y);Serial.print(",");
  Serial.print(vector_RT.radius);Serial.print(",");Serial.println(vector_RT.theta/PI*180);
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

//必ずcal_RT()を用いてから実行する
vectorRT_t IR_sensor::cal_close(){

  vectorXY_t vector_close_unit[4];
  vectorXY_t vector_close_boal[4];
  vectorXY_t vector_unit_boal[4];  

 // vector_close_unit[0] = 0;

  

  //ボールの角度(theta)と距離(radius)を出す　角度は弧度法
  //vector_RT_close.radius  = sqrt(pow(vector_XY_close.x, 2.0) + pow(vector_XY_close.y, 2.0));
  //vector_RT_close.theta   = atan2(vector_XY_close.y, vector_XY_close.x);//double atan2(double y, double x);

  return vector_RT_close;
}
