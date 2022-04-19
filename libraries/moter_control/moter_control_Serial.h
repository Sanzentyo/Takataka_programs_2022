//変えることがないと思われるのでシリアル2を使用している setup で必ずSerial2.begin()を書く

#ifndef Moter_Control_Serial_H
#define Moter_Control_Serial_H

#include <Compare_function.h>

void moter_Serial_send(int a, int b, int c){
  int val = 0;
  int input[3] = {a, b, c};
  int output[3] = {0, 0, 0};
  String StringA = "0";
  String StringB = "0";
  String StringC = "0";
  String StringD = "0";
  String StringX = "0";
  String StringY = "0";
  String StringZ = "0";
  String String0 = "0";

/*
  StringX = String(1);
  val = input[0];
  if (val < 0 && val >= -100)
  {
    StringY = String('R');
    val = abs_temp(val);
    StringZ = String(val);
  }
  else if (val >= 0 && val <= 100)
  {
    StringY = String('F');
    StringZ = String(val);
  }
  else
  {
    StringY = String('F');
    StringZ = String(0);
  }
  if (val < 10)
  {
    String0 = String("00");
    StringZ = String0 + StringZ;
  }
  else if (val < 100)
  {
    String0 = String('0');
    StringZ = String0 + StringZ;
  }
  else
  {
    String0 = String("");
  }
  StringA = StringX + StringY + StringZ;
*/

  StringX = String(2);
  val = input[1];
  if (val < 0 && val >= -100)
  {
    StringY = String('R');
    val = abs_temp(val);
    StringZ = String(val);
  }
  else if (val >= 0 && val <= 100)
  {
    StringY = String('F');
    StringZ = String(val);
  }
  else
  {
    StringY = String('F');
    StringZ = String(0);
  }
  if (val < 10)
  {
    String0 = String("00");
    StringZ = String0 + StringZ;
  }
  else if (val < 100)
  {
    String0 = String('0');
    StringZ = String0 + StringZ;
  }
  else
  {
  }
  StringB = StringX + StringY + StringZ;


  StringX = String(3);
  val = input[2];
  if (val < 0 && val >= -100)
  {
    StringY = String('R');
    val = abs_temp(val);
    StringZ = String(val);
  }
  else if (val >= 0 && val <= 100)
  {
    StringY = String('F');
    StringZ = String(val);
  }
  else
  {
    StringY = String('F');
    StringZ = String(0);
  }
  if (val < 10)
  {
    String0 = String("00");
    StringZ = String0 + StringZ;
  }
  else if (val < 100)
  {
    String0 = String('0');
    StringZ = String0 + StringZ;
  }
  else
  {
  }
  StringC = StringX + StringY + StringZ;


  StringX = String(4);
  val = input[0];
  if (val < 0 && val >= -100)
  {
    StringY = String('R');
    val = abs(val);
    StringZ = String(val);
  }
  else if (val >= 0 && val <= 100)
  {
    StringY = String('F');
    StringZ = String(val);
  }
  else
  {
    StringY = String('F');
    StringZ = String(0);
  }
  if (val < 10)
  {
    String0 = String("00");
    StringZ = String0 + StringZ;
  }
  else if (val < 100)
  {
    String0 = String('0');
    StringZ = String0 + StringZ;
  }
  else
  {
  }
  StringD = StringX + StringY + StringZ;


  StringA = "1F000";
  Serial2.println(StringA + StringB + StringC + StringD);
}

#endif
