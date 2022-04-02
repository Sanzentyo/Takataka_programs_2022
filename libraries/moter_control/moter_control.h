#ifndef MOTER_CONTROL
#define MOTER_CONTROL
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

void Store_i2c(char* ads,float M_val);
//void Send_i2c(char* ads);

class moter_control {
  public:
    moter_control(float* theta_ads);

    //ダイセン
    void moter_move(float theta, int V_str, int V_rol);
    void moter_stop();
    void moter_move_Serial(float theta, int V_str, int V_rol);
    void moter_stop_Serial();

    //BLDCモーター
    void SPI_setup();
    void set_MAX_POW(unsigned char max_pow);
    void moter_move_SPI(float theta, int V_str, int V_rol);
    void moter_stop_SPI();
    
  private:
    //予めベクトル計算に用いる固定の三角比を計算させておく 全て定数
    float theta[3]; //そのモーターによって進む方向
    float sin_M[3];//yにかける
    float cos_M[3];//xにかける

    //シリアル通信用
  
    //処理に用いられるグローバル変数
    char moter_pow[6] = {0,0,0,0,0,0}; //モーター出力用
    char stop_pow[6] = {0,0,0,0,0,0}; //停止用

    //SPI通信のための変数
    unsigned char MAX_POW = 100;
    SPISettings* mySPISettings;
};


#endif
