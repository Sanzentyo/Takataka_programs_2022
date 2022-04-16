void setup() {
  Serial.begin(9600);
  for(int i = 3;i < 9;i++)pinMode(i,OUTPUT);
}

void loop() {
  
  //for(int i = 3;i < 9;i++)digitalWrite(i,HIGH);
  //delay(500);
  //for(int i = 3;i < 9;i++)digitalWrite(i,LOW);
  //delay(500);
  Serial.println(digitalRead(7));
}
