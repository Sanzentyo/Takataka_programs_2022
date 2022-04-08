#include <math.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5

const int S[4] = {2,3,4,5};

void setup() {
  Serial.begin(9600);
  //pinMode(5,OUTPUT);
  //pinMode(7,OUTPUT);
  //pinMode(9,OUTPUT);
  //D5(PE3),D7(PH4),D9(PH6)を出力に設定
  DDRE |=  0b00001000; // bit3だけHighにする
  DDRH |=  0b00010000; // bit4だけHighにする
  DDRH |=  0b01000000; // bit6だけHighにする
}

void loop() {
  //digitalWrite(5,HIGH);
  //digitalWrite(7,HIGH);
  //digitalWrite(9,HIGH);
  PORTE |= 0b00001000; // bit3だけHighにする
  PORTH |= 0b00010000; // bit4だけHighにする
  PORTH |= 0b01000000; // bit6だけHighにする
  delay(1000);


  PORTE &= ~0b00001000; // bit3だけLowにする
  PORTH &= ~0b00010000; // bit4だけLowにする
  PORTH &= ~0b01000000; // bit6だけLowにする
  delay(1000);//*/
}
