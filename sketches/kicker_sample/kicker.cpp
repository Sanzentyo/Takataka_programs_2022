#include "kicker.h"
#include "Arduino.h"

kicker::kicker(int k_pin,int ft_pin,int led_pin,int th_val,int delay_time){
  K_PIN = k_pin;
  FT_PIN = ft_pin;
  LED_PIN = led_pin;
  TH_VAL = th_val;
  DELAY_TIME = delay_time; 
}

void kicker::setup(){
  //K_PIN = キッカーを動作させる用のピン
  pinMode(K_PIN,OUTPUT);
  //FT_PIN = フォトトランジスタにつなぐピン
  pinMode(FT_PIN,INPUT);
  //LED_PIN = LEDにつなぐピン
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,HIGH);
}

bool kicker::scan(){
  return analogRead(LED_PIN) >= TH_VAL;
}

void kicker::kick(){
   digitalWrite(K_PIN,HIGH);//Kick!!
   delay(DELAY_TIME);
   digitalWrite(K_PIN,LOW);
}
