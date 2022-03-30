#include <math.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5

const int S[4] = {2,3,4,5};

void setup() {
  Serial.begin(9600);
  for(int i = 0;i < 4;i++)pinMode(S[i],OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(A0,INPUT);
}

byte bit = 0;

void loop() {
  digitalWrite(11,HIGH);
/*
  for(short i = 0;i < 4;i++){
    if(bit & (1<<i))digitalWrite(S[i],HIGH);
    else digitalWrite(S[i],LOW);
  }*/
  //Serial.println(analogRead(A0));
  delay(1000);
}
