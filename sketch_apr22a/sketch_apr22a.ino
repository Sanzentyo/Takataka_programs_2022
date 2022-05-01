int pin = 3;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin,HIGH);
  Serial.println("Kick");
  delay(1000);
  digitalWrite(pin,LOW);
  delay(5000);
}
