void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

}

void loop() {
    while(Serial1.available() > 0){
    Serial.println(Serial1.read());
  }//*/

}
