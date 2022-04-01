#include "moter_control.h"
#include <math.h>

float Moter_theta[3] = {0,2*PI/3,4*PI/3};
moter_control Mctrl(Moter_theta);

void setup() {
  Serial.begin(9600);
  Serial2.begin(115200);
  Wire.begin();
}

void loop(){
  
  //for(int i = -2;i < 2;i++){
   Mctrl.moter_move(PI/2,0,100);
   delay(1000);
  //}

}
