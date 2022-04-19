#include <moter_control.h>
#include <math.h>

#define I2C_Clock 8000000
#define MOVE moter_move

float Moter_theta[3] = {0,2*PI/3,4*PI/3};
moter_control Mctrl(Moter_theta);

void setup() {
  Serial.begin(115200);//デバック
  Serial2.begin(115200);//モーター
  Wire.begin();
  Wire.setClock(I2C_Clock);
  //Mctrl.SPI_setup();
  //Mctrl.set_MAX_POW(30);
}



void loop(){
  
  //for(int i = -2;i < 2;i++){
  time = micros();
  Mctrl.moter_move(PI/2,40,20);
  Serial.println(micros()-time);
  delay(1000);
  //}

}
