//ピン
#define FRONT_PIN A0
#define RIGHT_PIN A1
#define LEFT_PIN A2
#define BACK_PIN A3

//閾値
#define FRONT_TH 850  
#define RIGHT_TH 850
#define LEFT_TH 850
#define BACK_TH 850

//型の宣言
typedef struct{
  float front;
  float right;
  float left;
  float back;
}line_pow_t;

typedef struct{
  bool front;
  bool right;
  bool left;
  bool back;
}line_flag_t;


//変数の宣言
line_pow_t line_pow;
line_flag_t line_flag;

void setup() {
  Serial1.begin( 9600 );
  Serial.begin( 9600 );
  pinMode( FRONT_PIN, INPUT );
  pinMode( RIGHT_PIN, INPUT );
  pinMode( LEFT_PIN, INPUT );
  pinMode( BACK_PIN, INPUT );
  Serial.println("start");
}

void loop() {
  //読み込み
  line_pow.front = analogRead( FRONT_PIN );
  line_pow.right = analogRead( RIGHT_PIN );
  line_pow.left = analogRead( LEFT_PIN );
  line_pow.back = analogRead( BACK_PIN );


  //初期化処理
  line_flag = {false,false,false,false};//前、右、左、後ろ


  //前
  if(line_pow.front > FRONT_TH){
    line_flag.front = true;
  }
  
  //右
  if(line_pow.right > RIGHT_TH){
    line_flag.right = true;
  }
  
  //左
  if(line_pow.left > LEFT_TH){
    line_flag.left = true;
  }
  
  //後ろ
  if(line_pow.back > BACK_TH){
    line_flag.back = true;
  }
  

  //どこに動くか
  if(line_flag.front && line_flag.right){
    Serial1.write(1);
  }else if(line_flag.right && line_flag.back){
    Serial1.write(3);
  }else if(line_flag.back && line_flag.left){
    Serial1.write(5);
  }else if(line_flag.left && line_flag.front){
    Serial1.write(7);
  }else if(line_flag.front){
    Serial1.write(0);
  }else if(line_flag.right){
    Serial1.write(2);
  }else if(line_flag.back){
    Serial1.write(4);
  }else if(line_flag.left){
    Serial1.write(6);
  }

  Serial.print("前:");Serial.println(line_pow.front);
  Serial.print("右:");Serial.println(line_pow.right);
  Serial.print("後:");Serial.println(line_pow.back);
  Serial.print("左:");Serial.println(line_pow.left);
  Serial.println("-------------------------------");
}
