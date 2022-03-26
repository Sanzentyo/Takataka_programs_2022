#include "Arduino.h" 
#include "Compass_dircal_PID.h"
#include <math.h>

void setup_compass(Adafruit_BNO055* ads_compass,Cal_dir* ads_Cal_dir){
  //コンパスが使用可能になるまで無限ループ
  if(!ads_compass->begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  //コンパスの電源を入れていると思われる
  ads_compass->setExtCrystalUse(true);

  ads_Cal_dir->set_front_dir(ads_compass->getVector(Adafruit_BNO055::VECTOR_EULER).x()/180*PI);

  return;
};

Cal_dir::Cal_dir(float set_front_dir){
  front_dir = set_front_dir;
  pre_time = micros();
};

void Cal_dir::set_front_dir(float set_front_dir){
  front_dir = set_front_dir;
  pre_time = micros();
};

void Cal_dir::set_PID_par(float p,float i,float d,float t){
  P_par = p/PI*180;
  I_par = i/PI*180;
  D_par = d/PI*180;
  delta_T = t;
}

int Cal_dir::Cal_Mom_set(float now_dir){
  int mom_caled;
  
  float delta_dir = now_dir - front_dir;
  if(delta_dir > PI)delta_dir += -2*PI;//ゴールへの角度を-180度から180度で表す

  for(int i = 0;i < 8;i++){
    if(delta_dir < Mom_set_dir_boader[i]){
      mom_caled = Mom_set[i];
      break;
    }
  }
  
  return mom_caled;  
}

int Cal_dir::Cal_Mom_P(float now_dir){
  int mom_caled;

  //目的までの偏差を求める
  float delta_dir = now_dir - front_dir;
  if(delta_dir > PI)delta_dir += -2*PI;//ゴールへの角度を-180度から180度で表す

  //P制御
  float P = delta_dir*P_par;

  //すべてを加算
  mom_caled = P;

  pre_dir = delta_dir;
  return mom_caled;
}

int Cal_dir::Cal_Mom_P_target(float now_dir,float target){
  int mom_caled;

  //目的までの偏差を求める
  float delta_dir = now_dir - (target + front_dir);

  if(delta_dir > PI)delta_dir += -2*PI;//ゴールへの角度を-180度から180度で表す
  else if(delta_dir < -PI)delta_dir += 2*PI;
  
  //P制御
  float P = delta_dir*P_par;

  //すべてを加算
  mom_caled = P;

  pre_dir = delta_dir;
  return mom_caled;
}

int Cal_dir::Cal_Mom_PD_target(float now_dir,float target){
  int mom_caled;

  //目的までの偏差を求める
  float delta_dir = now_dir - (target + front_dir);

  if(delta_dir > PI)delta_dir += -2*PI;//ゴールへの角度を-180度から180度で表す
  else if(delta_dir < -PI)delta_dir += 2*PI;
  
  //P制御
  float P = delta_dir*P_par;

  //D制御
  float D = (delta_dir-pre_dir)/delta_T*D_par;

  //すべてを加算
  mom_caled = P + D;

  pre_dir = delta_dir;
  return mom_caled;
}

int Cal_dir::Cal_Mom_PID(float now_dir){
  int mom_caled;

  //目的までの偏差を求める
  float delta_dir = now_dir - front_dir;
  if(delta_dir > PI)delta_dir += -2*PI;//ゴールへの角度を-180度から180度で表す

  //P制御
  float P = delta_dir*P_par;

  //I制御
  integral += (delta_dir+pre_dir)/2*delta_T;
  float I = integral*I_par;
  
  //D制御
  float D = (delta_dir-pre_dir)/delta_T*D_par;
  
  //すべてを加算
  mom_caled = P + I + D;

  pre_dir = delta_dir;
  return mom_caled;
}

int Cal_dir::Cal_Mom_PID_target(float now_dir,float target){
    int mom_caled;

  //目的までの偏差を求める
  float delta_dir = now_dir - (target + front_dir);

  if(delta_dir > PI)delta_dir += -2*PI;//ゴールへの角度を-180度から180度で表す
  else if(delta_dir < -PI)delta_dir += 2*PI;

  //P制御
  float P = delta_dir*P_par;

  //I制御
  integral += (delta_dir+pre_dir)/2*delta_T;
  float I = integral*I_par;
  
  //D制御
  float D = (delta_dir-pre_dir)/delta_T*D_par;
  
  //すべてを加算
  mom_caled = P + I + D;

  pre_dir = delta_dir;
  return mom_caled;
}

void Cal_dir::reset_PID(){
  integral = 0;
  pre_dir = 0;
}
