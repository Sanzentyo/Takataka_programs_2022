//#include <rp2040_pio.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>

#define DEV_NUM 16
#define TO_INT 1000
#define AIR_TH 100
#define LINE_TH 400

float unit_theta[DEV_NUM] = {0,PI/8,PI/4,3*PI/8,PI/2,5*PI/8,3*PI/4,7*PI/8,PI,9*PI/8,5*PI/4,11*PI/8,3*PI/4,13*PI/8,7*PI/4,15*PI/8};
int unit_cos[DEV_NUM];
int unit_sin[DEV_NUM];
int air_th[DEV_NUM] = {100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
int line_th[DEV_NUM] = {400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400};
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

int val;
int i = 15;
int temp;
bool flag = false;

void loop() {
  while(true){
    //pixels.show();
    //for(byte i = 0;i < DEV_NUM;i++){
      //Serial.println(Serial.read() - 48);
  //シリアル通信で最後書き込んだ数値に対応したポートの値を表す
  while(Serial.available() > 0){
    i = Serial.read();
    /*
    temp = Serial.read() - 48;
    if(temp != -38)
      if(temp < 10)i = temp;
      else i = temp - 7;*/

  //Serial.println(i);
  }
    if(flag){
      flag = false;
      digitalWrite(11,HIGH);
    }else{
      flag = true;
      digitalWrite(11,LOW);  
    }
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
      //Serial.println(i);
      //val = 100;
      sendIntData(val); // int型データの送信
      //Serial.write(val);
      delay(1000);
      /*
      if(line_val < air_th[i])air_flag++;
      else if(line_th[i] < line_val){
        line_flag++;
        line_x += unit_cos[i];
        line_y += unit_sin[i];
      }
    }

    now_theta = (byte)(map(atan2(line_y,line_x)*TO_INT,-PI*TO_INT,PI*TO_INT,1,254));

    if(line_flag == 0)Serial.write(0);
    else if(air_flag > 5)Serial.write(255);
    else Serial.write(now_theta);
   */ 
  }

}


//from https://kougaku-navi.hatenablog.com/entry/20140501/p1
// int型のデータを送信する関数
void sendIntData(int value) {
  Serial.write('H'); // ヘッダの送信
  Serial.write(lowByte(value)); // 下位バイトの送信
  Serial.write(highByte(value)); // 上位バイトの送信
}
