#ifndef Compass_dircal_PID_h 
#define Compass_dircal_PID_h
#include "Arduino.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>

//コンパスのセットアップとモーターの回転方向(モーメント)を計算するライブラリ

class Cal_dir{
  public:
    Cal_dir(float set_front_dir);
    void set_front_dir(float set_front_dir);
    void set_PID_par(float p,float i,float d,float t);
    int Cal_Mom_set(float now_dir);
    int Cal_Mom_P(float now_dir);
    int Cal_Mom_P_target(float now_dir,float target);
    int Cal_Mom_PD_target(float now_dir,float target);
    int Cal_Mom_PID(float now_dir);
    int Cal_Mom_PID_target(float now_dir,float target);
    void reset_PID();
    
  private:
    float front_dir;
    int Mom_set[9] = {-100,-90,-60,-30,0,30,60,90,100};
    int Mom_set_dir_boader[8] = {-11*PI/12,-2*PI/3,-5*PI/15,-PI/12,PI/12,5*PI/12,2*PI/3,11*PI/12};
    float pre_dir = 0;
    float P_par = 0.64/PI*180;
    float I_par = 0.2/PI*180;
    float D_par = 0.1/PI*180;
    float P_tar = 0.73/PI*180;
    float integral = 0;
    float pre_time;
    float delta_T = 0.004;
};

void setup_compass(Adafruit_BNO055* ads_compass,Cal_dir* ads_Cal_dir);

#endif
