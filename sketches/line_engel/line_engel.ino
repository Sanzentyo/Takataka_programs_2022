//#include <rp2040_pio.h>
#include <Adafruit_NeoPixel.h>
#include <moving_average.h>
#include <math.h>

#define DEV_NUM 16
#define TO_INT 1000
#define AIR_TH 100
#define LINE_TH 550
#define BRIGHTNESS (255) // 0-255
#define MA_TIME 10

float unit_theta[DEV_NUM] = {25*PI/16,27*PI/16,29*PI/16,31*PI/16,PI/16,3*PI/16,5*PI/16,7*PI/16,9*PI/16,11*PI/16,13*PI/16,15*PI/16,17*PI/16,19*PI/16,21*PI/16,23*PI/16};
int unit_cos[DEV_NUM];
int unit_sin[DEV_NUM];
//int air_th[DEV_NUM] = {100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
//int line_th[DEV_NUM] = {600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600};
int unit_index[DEV_NUM] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int S[4] = {2,3,4,5};

int line_val[DEV_NUM];
int line_x;
int line_y;
byte now_theta;
//short air_flag = 0;
short line_flag = 0;

const int DIN_PIN = 6; // D6
const int LED_COUNT = 15; // LEDの数

Adafruit_NeoPixel pixels(LED_COUNT, DIN_PIN, NEO_GRB + NEO_KHZ800);

//MovingAverage ma0(10),ma1(10),ma2(10),ma3(10),ma4(10),ma5(10),ma6(10),ma7(10),ma8(10),ma9(10),ma10(10),ma11(10),ma12(10),ma13(10),ma14(10),ma15(10);
//MovingAverage* ma_add[16] = {&ma0,&ma1,&ma2,&ma3,&ma4,&ma5,&ma6,&ma7,&ma8,&ma9,&ma10,&ma11,&ma12,&ma13,&ma14,&ma15};
MovingAverage ma[16](MA_TIME);

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
   pixels.setPixelColor(i, pixels.Color(255, 255, 255)); // 0番目の色を変える
  }
  pixels.setBrightness(BRIGHTNESS);
  for(int i = 0;i < 5;i++)pixels.show();//*/
  for(int i = 0;i < MA_TIME;i++)for(int j = 0;j < 16;j++){
    PORTD = j<<2;
    ma[j].updateData(analogRead(A0)); 
  }
}


void loop() {
  
  while(true){
    //air_flag = 0;
    line_flag = 0;
    line_x = 0;
    line_y = 0;
    for(byte i = 0;i < DEV_NUM;i++){
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
      //line_val[i] = analogRead(A0);
      //Serial.write(val);
      /*if(line_val[i] < air_th[i])air_flag++;
      else*/ if(LINE_TH < /*ma[i].updateData(*/analogRead(A0)){
        if (i != 2) {
        line_flag++;
        line_x += unit_cos[i];
        line_y += unit_sin[i];
        }
      }
    }

    now_theta = (byte)(map(atan2(line_y,line_x)*TO_INT,-PI*TO_INT,PI*TO_INT,1,254));

    if(line_flag < 1)Serial.write(0);
    else Serial.write(now_theta);
  }

}
/*
int update_line_vals(short j){
  int rslt;
  switch(j){
    case 0:
      rslt = ma0.updateData(analogRead(A0));
      break;
    case 1:
      rslt = ma1.updateData(analogRead(A0));
      break;
    case 2:
      rslt = ma2.updateData(analogRead(A0));
      break;
    case 3:
      rslt = ma3.updateData(analogRead(A0));
      break;
    case 4:
      rslt = ma4.updateData(analogRead(A0));
      break;
    case 5:
      rslt = ma5.updateData(analogRead(A0));
      break;
    case 6:
      rslt = ma6.updateData(analogRead(A0));
      break;
    case 7:
      rslt = ma7.updateData(analogRead(A0));
      break;
    case 8:
      rslt = ma8.updateData(analogRead(A0));
      break;
    case 9:
      rslt = ma9.updateData(analogRead(A0));
      break;
    case 10:
      rslt = ma10.updateData(analogRead(A0));
      break;
    case 11:
      rslt = ma11.updateData(analogRead(A0));
      break;
    case 12:
      rslt = ma12.updateData(analogRead(A0));
      break;
    case 13:
      rslt = ma13.updateData(analogRead(A0));
      break;
    case 14:
      rslt = ma14.updateData(analogRead(A0));
      break;
    case 15:
      rslt = ma15.updateData(analogRead(A0));
      break;
    }

  return rslt;
}
*/
