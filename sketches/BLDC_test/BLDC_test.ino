//使うマイコン(Uno,Mega)によってレジスタ(initialize関数内)と
//ピン(motor_control.h内)の設定を変えること
//Unoで使う場合delay・delayMicrosecondsは使えない
//プログラムをいじるときはなるべく変更箇所を消さずにコメントアウトする。

//I2Cでエラーが出る場合はI2C_Clockの値を4000000まで下げてみる
#include <SPI.h>
#include <Arduino.h>
#include <stdint.h>
#include "motor_control.h"

#define I2C_Clock 8000000

uint8_t power = 40;
bool turn = 1; //true(1) 正転 / false(0) 逆転

/*
void stop_motor();
uint16_t adjust_angle(uint16_t _Angle);
uint8_t judge_step(uint16_t _Angle,bool _turn);
void get_speed();
void initialization();
uint16_t EncoderRead();
uint16_t calibration();
void motor_control(uint8_t _step,uint8_t _power);*/

void setup() {
  // put your setup code here, to run once:
  initialization();
  delay(500);
  //offset = calibration();
}

void loop() {
  /*uint16_t data = calibration();
  Serial.println(data);
  delay(1500);*/
  Serial.println(turn);
  uint16_t Angle = EncoderRead();
  Angle = adjust_angle(Angle);
  uint8_t step = judge_step(Angle,turn);
  motor_control(step,power);
}

/*void serialEvent() {
  uint8_t data = (uint8_t)Serial.read();
  if (data == 0xFF) {
    uint8_t data = Serial.read();
    if (data <= 100) {
      turn = 1;
      power = map(data,0,100,0,200);
    }
    else if (data >= 101 && data <= 201) {
      turn = 0;
      power = map(data - 101,0,100,0,200);
    }
  }
}*/

void initialization() {
  //pwm
  TCCR0B = (TCCR0B & 0b11111000) | 0x01;  // 31.37255 [kHz]
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;  // 31.37255 [kHz] //Arduino Uno
  /*TCCR2B = (TCCR2B & 0b11111000) | 0x01;  // 31.37255 [kHz]
  TCCR3B = (TCCR3B & 0b11111000) | 0x01;  // 31.37255 [kHz]
  TCCR4B = (TCCR4B & 0b11111000) | 0x01;  // 31.37255 [kHz] //Arduino Mega*/

  //I2C
  Wire.begin();
  Wire.setClock(I2C_Clock);

  //タイマー割込み
  //絶対消さない!!!!!
  /*TCCR1A  = 0;
  TCCR1B  = 0;
  TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);  //CTCmode //prescaler to 256
  OCR1A   = 20000-1;
  TIMSK1 |= (1 << OCIE1A);*/

  //Serial
  Serial.begin(115200);
  
  //SPI
  SPCR |= bit(SPE);
  pinMode(MISO,OUTPUT);
  SPI.attachInterrupt();

  //BLDC pin
  for (uint8_t i = 0;i < 3;i++) {
    for (uint8_t j = 0;j < 2;j++) {
      pinMode(BLDC[i][j],OUTPUT);
    }
  }
  for (uint8_t i = 0;i < 3;i++) {
    analogWrite(BLDC[i][0],0);
    digitalWrite(BLDC[i][1],HIGH);
  }
  stop_motor();
  delay(3000);
}

ISR (SPI_STC_vect) {
  byte data = SPDR;
  if (data <= 100) {
    data *= 2;
    power = data;
    if (turn != 1) {
      motor_control(0,power);
      delay(2000);
      /*for (int i = 0;i < 6;i++) {
        motor_control(i,power);
        delayMicroseconds(2000);
      }*/
    }
    turn = 1;
  }
  else if (data >= 101 && data <= 201) {
    data = (uint8_t)data - 101;
    power = data * 2;
    if (turn != 0) {
      motor_control(0,power);
      delay(2000);
      /*for (int i = 5;i > -1;i--) {
        motor_control(i,power);
        delayMicroseconds(2000);
      }*/
    }
    turn = 0;
  }
}
