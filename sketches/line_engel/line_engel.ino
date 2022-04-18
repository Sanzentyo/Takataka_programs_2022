//#include <rp2040_pio.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>

#define DEV_NUM 16
#define TO_INT 1000
#define AIR_TH 100
#define LINE_TH 400

float unit_theta[DEV_NUM] = {9*PI/16,11*PI/16,13*PI/16,15*PI/16,17*PI/16,19*PI/16,21*PI/16,23*PI/16,25*PI/16,27*PI/16,29*PI/16,31*PI/16,PI/16,3*PI/16,5*PI/16,7*PI/16};
int unit_cos[DEV_NUM];
int unit_sin[DEV_NUM];
int air_th[DEV_NUM] = {100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
int line_th[DEV_NUM] = {600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600};
int unit_index[DEV_NUM] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int S[4] = {2,3,4,5};

int line_val[DEV_NUM];
int line_x;
int line_y;
byte now_theta;
short air_flag = 0;
short line_flag = 0;

const int DIN_PIN = 6; // D6
const int LED_COUNT = 15; // LEDの数

Adafruit_NeoPixel pixels(LED_COUNT, DIN_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  for(short i = 0;i < DEV_NUM;i++){
    unit_cos[i] = cos(unit_theta[i])*TO_INT;
    unit_sin[i] = sin(unit_theta[i])*TO_INT;
  }
  for(int i = 0;i < 4;i++)pinMode(S[i],OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(A0,INPUT);
  pixels.begin();
  pixels.clear();
  for (int i = 0;i < 15;i++) {
   pixels.setPixelColor(i, pixels.Color(128, 128, 128)); // 0番目の色を変える
  }
  for(int i = 0;i < 5;i++)pixels.show();//*/
}

byte val;

void loop() {
  while(true){
    //for(byte i = 0;i < DEV_NUM;i++){
    byte i = 15;
      /*//デジタル2
      if(i & (1<<0))digitalWrite(2,HIGH);
      else digitalWrite(2,LOW);
      //デジタル3
      if(i & (1<<1))digitalWrite(3,HIGH);
      else digitalWrite(3,LOW);
      //デジタル4
      if(i & (1<<2))digitalWrite(4,HIGH);
      else digitalWrite(4,LOW);
      //デジタル5
      if(i & (1<<3))digitalWrite(5,HIGH);
      else digitalWrite(5,LOW);
      //*/PORTD = i<<2;
      val = analogRead(A0);
      //Serial.write(val);
      if(line_val < air_th[i])air_flag++;
      else if(line_th[i] < line_val){
        line_flag++;
        line_x += unit_cos[i];
        line_y += unit_sin[i];
      }

    now_theta = (byte)(map(atan2(line_y,line_x)*TO_INT,-PI*TO_INT,PI*TO_INT,1,254));

    if(line_flag == 0)Serial.write(0);
    else if(air_flag > 5)Serial.write(255);
    else Serial.write(now_theta);
  }

}
