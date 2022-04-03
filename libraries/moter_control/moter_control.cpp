#include <Arduino.h>
#include <math.h>
#include <Wire.h>
#include "moter_control.h"
#include "moter_control_Serial.h"
#include <Compare_function.h>
#include <SPI.h>

#define POSI_DATA 255
#define NEGA_DATA 254
#define STOP_DATA 253

void Store_i2c(char* ads,float M_val){
  int val = M_val;
    
  if(val < 0 && val >= -100){
    *ads = abs_temp(val) + 128;
  }else if(val >= 0 && val <= 100){
    *ads = val;
  }else if(val == 999){
    *ads = 128;
  }else{
    return;
  }
  
  return;
}


void Send_i2c(char* ads){

  //この部分でi2c通信で信号をモーターボードに送っている
  //4chでも6ch分送らないと作動しない
  Wire.beginTransmission(0x14>>1);
  Wire.write(ads[0]); // 1ch
  Wire.write(ads[1]); // 2ch
  Wire.write(ads[2]); // 3ch
  Wire.write(ads[3]); // 4ch
  Wire.write(ads[4]); // 5ch
  Wire.write(ads[5]); // 6ch
  Wire.endTransmission();

  return;
}


moter_control::moter_control(float* theta_ads){
  
  //予めベクトル計算に用いる固定の三角比を計算させておく 全て定数
  for(int i = 0;i < 3;i++){
  theta[i] = theta_ads[i]; //そのモーターによって進む方向　現在は{0,2*PI/3,4*PI/3}
  sin_M[i] = sin(theta[i]);//yにかける
  cos_M[i] = cos(theta[i]);//xにかける
  }
}

void moter_control::moter_move(float theta, int V_str, int V_rol){
  float V_x = V_str*cos(theta);
  float V_y = V_str*sin(theta);
  float M[3];
  float max_per;
  
  //ベクトル計算
  M[0] = V_x*cos_M[0] + V_y*sin_M[0] + V_rol;
  M[1] = V_x*cos_M[1] + V_y*sin_M[1] + V_rol;
  M[2] = V_x*cos_M[2] + V_y*sin_M[2] + V_rol;

  

  float V_st = abs_temp(V_str) + abs_temp(V_rol);
  if(V_st <= 100){
    max_per = V_st/max_ele_abs(M,3);
  }else{
    max_per = 100/max_ele_abs(M,3);
  }
  
  for(int i = 0;i < 3;i++){
    M[i] *= max_per;
  }
  

  Store_i2c(&moter_pow[3],M[0]);//モーターボードの1番の調子が悪いので4番を使っている
  Store_i2c(&moter_pow[1],M[1]);
  Store_i2c(&moter_pow[2],M[2]);
  //デバック用

  Serial.println("-------------------------");
  Serial.print("theta:");
  Serial.println(180*(theta/PI));
  Serial.print("M[0]:");
  Serial.println(M[0]);
  Serial.print("M[1]:");
  Serial.println(M[1]);
  Serial.print("M[2]:");
  Serial.println(M[2]);
  Serial.println("-------------------------");

  
  Wire.beginTransmission(0x14>>1);
  Wire.write(moter_pow[0]); // 1ch
  Wire.write(moter_pow[1]); // 2ch
  Wire.write(moter_pow[2]); // 3ch
  Wire.write(moter_pow[3]); // 4ch
  Wire.write(moter_pow[4]); // 5ch
  Wire.write(moter_pow[5]); // 6ch
  Wire.endTransmission();

  return;
};


void moter_control::moter_stop(){

  Wire.beginTransmission(0x14>>1);
  Wire.write(stop_pow[0]); // 1ch
  Wire.write(stop_pow[1]); // 2ch
  Wire.write(stop_pow[2]); // 3ch
  Wire.write(stop_pow[3]); // 4ch
  Wire.write(stop_pow[4]); // 5ch
  Wire.write(stop_pow[5]); // 6ch
  Wire.endTransmission();
  
  return;
}

void moter_control::moter_move_Serial(float theta, int V_str, int V_rol){
  float V_x = V_str*cos(theta);
  float V_y = V_str*sin(theta);
  float M[3];
  float max_per;
  
  //ベクトル計算
  M[0] = V_x*cos_M[0] + V_y*sin_M[0] + V_rol;
  M[1] = V_x*cos_M[1] + V_y*sin_M[1] + V_rol;
  M[2] = V_x*cos_M[2] + V_y*sin_M[2] + V_rol;
  
  float V_st = abs_temp(V_str) + abs_temp(V_rol);
  if(V_st <= 100){
    max_per = V_st/max_ele_abs(M,3);
  }else{
    max_per = 100/max_ele_abs(M,3);
  }
  
  for(int i = 0;i < 3;i++){
    M[i] *= max_per;
  }

  moter_Serial_send(M[0],M[1],M[2]);

  
}

void moter_control::moter_stop_Serial(){
  moter_Serial_send(0,0,0);
}

void moter_control::SPI_setup(){
  //SPI通信のためのセットアップ
  *mySPISettings = SPISettings(8000000, MSBFIRST, SPI_MODE0);
  SPI.begin();
  SPI.beginTransaction(*mySPISettings);
  
  //D5(PE3),D7(PH4),D9(PH6)を出力に設定
  DDRE |= (0b1 << 3); // bit3だけHighにする
  DDRH |= (0b1 << 4); // bit4だけHighにする
  DDRH |= (0b1 << 6); // bit6だけHighにする
}

void moter_control::set_MAX_POW(unsigned char max_pow){
  MAX_POW = max_pow;
}

void moter_control::moter_move_SPI(float theta, int V_str, int V_rol){
  float V_x = V_str*cos(theta);
  float V_y = V_str*sin(theta);
  float M[3];
  float max_per;
  
  //ベクトル計算
  M[0] = V_x*cos_M[0] + V_y*sin_M[0] + V_rol;
  M[1] = V_x*cos_M[1] + V_y*sin_M[1] + V_rol;
  M[2] = V_x*cos_M[2] + V_y*sin_M[2] + V_rol;
  
  float V_st = abs_temp(V_str) + abs_temp(V_rol);
  if(V_st <= MAX_POW){
    max_per = V_st/max_ele_abs(M,3);
  }else{
    max_per = MAX_POW/max_ele_abs(M,3);
  }
  
  for(int i = 0;i < 3;i++){
    M[i] *= max_per;
  }

  

  //M0,M1,M2までそれぞれSSピンはD5(PE3),D7(PH4),D9(PH6)に対応する
  //https://ht-deko.com/arduino/portregisters.html
  byte send_data;//送信用

  //M0 D5 PE3
  // 3. 現在の設定を退避し、指定した設定をマイコンに反映させSPI通信を開始する
  SPI.beginTransaction(*mySPISettings);

  // 4. 制御するデバイスに通信の開始を通知する
  PORTE &= ~(0b1 << 3); // bit3だけLowにする
  
  // 5. 2バイトを送受信する
  //正転(時計回り)か逆転(反時計回り)かを先に伝える
  if(M[0] > 0)SPI.transfer(POSI_DATA);
  else SPI.transfer(POSI_DATA);
  
  //powerに該当するdataを送る
  send_data = abs_temp(M[0]);
  SPI.transfer(send_data);

  // 6. 制御するデバイスに通信の終了を通知する
  PORTE |= (0b1 << 3); // bit3だけHighにする

  // 7. SPI通信を終了し設定を以前の状態に戻す
  SPI.endTransaction();

  //M1 D7 PH4
  SPI.beginTransaction(*mySPISettings);
  PORTH &= ~(0b1 << 4);
  if(M[1] > 0)SPI.transfer(POSI_DATA);
  else SPI.transfer(POSI_DATA);
  send_data = abs_temp(M[1]);
  SPI.transfer(send_data);
  PORTH |= (0b1 << 4);
  SPI.endTransaction();

  //M2 D9 PH6
  SPI.beginTransaction(*mySPISettings);
  PORTH &= ~(0b1 << 6);
  if(M[2] > 0)SPI.transfer(POSI_DATA);
  else SPI.transfer(POSI_DATA);
  send_data = abs_temp(M[2]);
  SPI.transfer(send_data);
  PORTH |= (0b1 << 6);
  SPI.endTransaction();
  
}

void moter_control::moter_stop_SPI(){
  //M0 D5 PE3
  SPI.beginTransaction(*mySPISettings);
  PORTE &= ~(0b1 << 3);
  SPI.transfer(STOP_DATA);
  PORTE |= (0b1 << 3);
  SPI.endTransaction();
  
  //M1 D7 PH4
  SPI.beginTransaction(*mySPISettings);
  PORTH &= ~(0b1 << 4);
  SPI.transfer(STOP_DATA);
  PORTH |= (0b1 << 4);
  SPI.endTransaction();

  //M2 D9 PH6
  SPI.beginTransaction(*mySPISettings);
  PORTH &= ~(0b1 << 6);
  SPI.transfer(STOP_DATA);
  PORTH |= (0b1 << 6);
  SPI.endTransaction();
}
