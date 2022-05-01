#include "kicker.h"

#define K_PIN 3
#define FT_PIN A9
#define TH_VAL 600
#define DELAY_TIME 2000

kicker kicker(K_PIN,FT_PIN,TH_VAL,DELAY_TIME);

void setup() {
  Serial.begin(115200);
  kicker.setup();
}

void loop() {
  //Serial.println(kicker.scan_int());
  //kicker.kick();
  
    //analogValue = analogRead(FT_PIN);
    //Serial.println(analogValue);//アナログへん換値を出力
   
 //ボールでLEDの光がかくれたらキック
    if(true){
       Serial.println("KICK!");
       digitalWrite(K_PIN,HIGH);//Kick!!
       delay(1000);
       digitalWrite(K_PIN,LOW);
      }
   delay(1000);
   
}
