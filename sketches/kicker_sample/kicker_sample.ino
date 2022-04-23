#define K_PIN 3
#define FT_PIN A9
#define TH_VAL 600
#define DELAY_TIME 750

void setup() {
  Serial.begin(9600);
  //K_PIN = キッカーを動作させる用のピン
  pinMode(K_PIN,OUTPUT);
  //FT_PIN = フォトトランジスタにつなぐピン
  pinMode(FT_PIN,INPUT);
}

double analogValue;

void loop() {
    analogValue = analogRead(FT_PIN);
    Serial.println(analogValue);//アナログへん換値を出力
   
 //ボールでLEDの光がかくれたらキック
    if(analogValue >= 600){
       Serial.println("KICK!");
       digitalWrite(K_PIN,HIGH);//Kick!!
       delay(1000);
       digitalWrite(K_PIN,LOW);
      }
   delay(400);
}
