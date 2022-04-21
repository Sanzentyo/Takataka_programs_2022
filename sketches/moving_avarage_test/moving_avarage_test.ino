#include <moving_average.h>

void setup() {
  Serial.begin(115200);

}



MovingAverage ma0(10),ma1(10),ma2(10),ma3(10),ma4(10),ma5(10),ma6(10),ma7(10),ma8(10),ma9(10),ma10(10),ma11(10),ma12(10),ma13(10),ma14(10),ma15(10);
MovingAverage* ma_add[16] = {&ma0,&ma1,&ma2,&ma3,&ma4,&ma5,&ma6,&ma7,&ma8,&ma9,&ma10,&ma11,&ma12,&ma13,&ma14,&ma15};
MovingAverage ma[3](10);

void loop() {
  
  for(int i = 0;i < 3;i++){
    for(int j = 0;j < 20;j++){Serial.print(ma[i].updateData(j));Serial.print(" ");}
    Serial.println("/n=========");
  }
  //Serial.println("hello");

  delay(1000);
  
}
