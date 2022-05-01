int SS_Pin[4] = {2,3,4,5};
void setup() {
  // put your setup code here, to run once:
  for (int i = 0;i < 4;i++) {
    pinMode(SS_Pin[i],OUTPUT);
  }
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(SS_Pin[0],LOW);
  digitalWrite(SS_Pin[1],LOW);
  digitalWrite(SS_Pin[2],HIGH);
  digitalWrite(SS_Pin[3],HIGH);
  delay(10);
  int data = analogRead(A0);
  Serial.println(data);
  delay(300);
}
