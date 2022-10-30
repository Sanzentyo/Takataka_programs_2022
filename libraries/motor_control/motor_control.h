
#ifndef motor_CONTROL
#define motor_CONTROL
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

void Store_i2c(char* ads,float M_val);
//void Send_i2c(char* ads);

class motor_control {
  public:
    motor_control(float* theta_ads);

    //ダイセン
    void motor_move(float theta, int V_str, int V_rol);
    void motor_stop();
    void motor_move_Serial(float theta, int V_str, int V_rol);
    void motor_stop_Serial();

    //BLDCモーター
    void SPI_setup();
    void set_MAX_POW(unsigned char max_pow);
    void motor_move_SPI(float theta, int V_str, int V_rol);
    void motor_stop_SPI();
    
  private:
    //予めベクトル計算に用いる固定の三角比を計算させておく 全て定数
    float theta[3]; //そのモーターによって進む方向
    float sin_M[3];//yにかける
    float cos_M[3];//xにかける

    //シリアル通信用
  
    //処理に用いられるグローバル変数
    char motor_pow[6] = {0,0,0,0,0,0}; //モーター出力用
    char stop_pow[6] = {0,0,0,0,0,0}; //停止用

    //SPI通信のための変数
    unsigned char MAX_POW = 30;
};


#endif
