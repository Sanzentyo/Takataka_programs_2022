#include <math.h>

#define DEV_NUM 16
#define AIR_TH 100
#define LINE_TH 400

float unit_theta[DEV_NUM] = {0,PI/8,PI/4,3*PI/8,PI/2,5*PI/8,3*PI/4,7*PI/8,PI,9*PI/8,5*PI/4,11*PI/8,3*PI/4,13*PI/8,7*PI/4,15*PI/8};
int unit_cos[DEV_NUM];
int unit_sin[DEV_NUM];
int S[4] = {2,3,4,5};

int line_val[DEV_NUM];
int line_x;
int line_y;
byte now_theta;
short air_flag = 0;
short line_flag = 0;

void setup() {
  Serial.begin(9600);
  for(short i = 0;i < DEV_NUM;i++){
    unit_cos[i] = cos(unit_theta[i])*1000;
    unit_sin[i] = sin(unit_theta[i])*1000;
  }
  for(int i = 0;i < 4;i++)pinMode(S[i],OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(A0,INPUT);
}

void loop() {
  while(true){
    for(byte i = 0;i < DEV_NUM;i++){
      //デジタル2
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
      //PORTD = i<<2;
      line_val[i] = analogRead(A0);
      if(line_val < AIR_TH)air_flag++;
      else if(LINE_TH < line_val){
        line_flag++;
        line_x += unit_cos[i];
        line_y += unit_sin[i];
      }
    }

    now_theta = (byte)(map(atan2(line_y,line_x),-PI,PI,1,254));

    if(line_flag == 0)Serial.write(0);
    else if(air_flag > 5)Serial.write(255);
    else Serial.write(now_theta);
  }

}
