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
    IR_sensor(uint8_t* PIN_ads,float* theta_ads,float radius_val);
    void print_data();
    void print_csv_first();
    void print_csv();
    void read_IR();
    vectorXY_t cal_XY();
    vectorRT_t cal_RT();
    vectorRT_t cal_close();

    
  private:
    uint8_t Pin[IR_NUM];
    int IR_Cur[IR_NUM];
    float unit_theta[IR_NUM];
    float unit_sin[IR_NUM];
    float unit_cos[IR_NUM];
    float unit_radius;
    float boal_radius = 3.6;
    sensorInfo_t IR_Info;
    vectorXY_t vector_XY;
    vectorRT_t vector_RT;
    vectorXY_t vector_XY_close;
    vectorRT_t vector_RT_close;
  };


#endif
