void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
}

byte i;

void loop() {
  
  while(Serial1.available()){
    i = Serial1.read();
  }
}

void M1(){
  digitalWrite(5,LOW);
}
