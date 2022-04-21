void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

}

byte dir = 31;
float esc_theta;

void loop() {
  
  while(Serial1.available() > 0){
    Serial.println(Serial1.read());
  }//*/
  
  /*while(Serial1.available() > 0){
    dir = Serial1.read();
    esc_theta = map(dir,1,254,-180,180);
  }
  Serial.println(esc_theta);//*/
  //delay(500);

}
