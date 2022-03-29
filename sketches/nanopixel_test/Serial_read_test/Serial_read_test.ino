void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  
  byte dir = 0;
  
  while(Serial1.available() > 0){
    dir = Serial1.read();
  }

  Serial.println(dir);
  delay(50);
}
