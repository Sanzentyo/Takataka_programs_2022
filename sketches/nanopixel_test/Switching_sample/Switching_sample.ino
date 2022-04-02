#include <math.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5

const int S[4] = {2,3,4,5};

void setup() {
  Serial.begin(9600);
  //D5(PE3),D7(PH4),D9(PH6)を出力に設定
  DDRE |= (0b1 << 3); // bit3だけHighにする
  DDRH |= (0b1 << 4); // bit4だけHighにする
  DDRH |= (0b1 << 6); // bit6だけHighにする
}

void loop() {
  PORTE |= (0b1 << 3); // bit3だけHighにする
  PORTH |= (0b1 << 4); // bit4だけHighにする
  PORTH |= (0b1 << 6); // bit6だけHighにする
  delay(3000);

/*
  PORTE &= ~(0b1 << 3); // bit3だけLowにする
  PORTH &= ~(0b1 << 4); // bit4だけLowにする
  PORTH &= ~(0b1 << 6); // bit6だけLowにする
  delay(3000);//*/
}
