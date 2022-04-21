//このライブラリは"http://yunit.techblog.jp/archives/72016450.html"を参考にした

#ifndef IR_sensor_h 
#define IR_sensor_h
#include "Arduino.h"
#include <math.h>
#define IR_NUM 8 //IRセンサーの数
#define IR_CUR_MAX 1023//通常時の電圧

typedef struct {
    int active_num;      // 反応したセンサの個数
    int max_val;      // 最大のセンサ値
    int max_index;    // 最大の値を観測したセンサの番号
} sensorInfo_t;

typedef struct {
    float x;
    float y;
} vectorXY_t;

typedef struct {
    float radius;
    float theta;
} vectorRT_t;

class IR_sensor{
  public:
    IR_sensor(uint8_t* PIN_ads,float* theta_ads);
    void print_data();
    void print_csv_first();
    void print_csv();
    
    void set_cor(float* cor_ads);
    void set_radius(float unit,float boal,int max_r);
    
    void read_IR();
    vectorXY_t cal_XY();
    vectorRT_t cal_RT();
    
    void read_IR_cor();
    vectorRT_t cal_RT_cor();
    vectorXY_t cal_XY_cor();
    
    float cal_close(float now_boal_theta,float now_boal_radius);

    
  private:
    uint8_t Pin[IR_NUM];
    int IR_Cur[IR_NUM];
    float unit_theta[IR_NUM];
    float unit_sin[IR_NUM];
    float unit_cos[IR_NUM];
    float unit_cor[IR_NUM];//IRセンサーの補正用の関数
    float unit_radius = 9;
    float boal_radius = 3.6;
    float R = boal_radius + unit_radius;
    int MAX_R = 1600;
    sensorInfo_t IR_Info;
    vectorXY_t vector_XY;
    vectorRT_t vector_RT;
    vectorXY_t vector_XY_close;
    vectorRT_t vector_RT_close;
  };


#endif
