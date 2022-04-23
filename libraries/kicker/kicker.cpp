#include "kicker.h"
#include "Arduino.h"

kicker::kicker(int k_pin,int ft_pin,int th_val,int delay_time){
  K_PIN = k_pin;
  FT_PIN = ft_pin;
  TH_VAL = th_val;
  DELAY_TIME = delay_time; 
}

void kicker::setup(){
  //K_PIN = キッカーを動作させる用のピン
  pinMode(K_PIN,OUTPUT);
  //FT_PIN = フォトトランジスタにつなぐピン
  pinMode(FT_PIN,INPUT);
}

bool kicker::scan(){
  return analogRead(FT_PIN) >= TH_VAL;
}

int kicker::scan_int(){
  return analogRead(FT_PIN);
}

void kicker::kick(){
   digitalWrite(K_PIN,HIGH);//Kick!!
   delay(DELAY_TIME);
   digitalWrite(K_PIN,LOW);
}
