void setup() {
  Serial.begin(115200);//デバック
}

int i;


void loop() {
  Serial.println(map(i,1,254,-180,180)*PI/180);
  if(i < 255)i++;
  else i = 1;
  delay(1000);
}
