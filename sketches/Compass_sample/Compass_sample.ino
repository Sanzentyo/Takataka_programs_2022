/*
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Compass_dircal_PID.h"

Adafruit_BNO055 Compass_ctrl = Adafruit_BNO055(-1, 0x28);
imu::Vector<3> euler;//絶対角度が入る
int Mom_now;

Cal_dir Cal_dir(0);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setup_compass(&Compass_ctrl,&Cal_dir);
}

void loop() {
  euler = Compass_ctrl.getVector(Adafruit_BNO055::VECTOR_EULER);//現在の絶対角度を取得
  Mom_now = Cal_dir.Cal_Mom_set(euler.x());
  Serial.print("\neuler:");Serial.print(euler.x());
  Serial.print("delta:");Serial.println(Mom_now);
  
  delay(1000);

}
*/
