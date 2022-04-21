#include "moter_control.h"
#include <math.h>

#define MOVE moter_move_SPI

float Moter_theta[3] = {0,4*PI/3,2*PI/3};
moter_control Mctrl(Moter_theta);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Mctrl.SPI_setup();
  Mctrl.set_MAX_POW(30);
}

long time;
int power = 30;

void loop(){
  time = millis();
  while(millis() - time < 1000){
  //Serial.println(Mom_now);
  Mctrl.MOVE(PI/2,power,0);
  }
  delay(1000);
  
  time = millis();
  while(millis() - time< 1000){
  Mctrl.MOVE(-PI/2,power,0);
  }
  delay(1000);
  
  /*//for(int i = -2;i < 2;i++){
   Mctrl.moter_move_SPI(PI/2,30,0);
   Serial.println("--------");
   delay(1000);
   Mctrl.moter_move_SPI(3*PI/2,30,0);
   Serial.println("--------");
   delay(1000);
  //}*/

}
