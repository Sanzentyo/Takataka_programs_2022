void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);

}

int recv_data,i,temp;

void loop() {
    while(Serial.available() > 0){
    temp = Serial.read() - 48;
    if(temp != -38)
      if(temp < 10)i = temp;
      else i = temp - 7;
    Serial1.write(i);
    }//*/

    //Serial1.write(0);
  
  // 受信バッファに３バイト（ヘッダ＋int）以上のデータが着ているか確認
  while( Serial1.available() >= sizeof('H') + sizeof(int) ) {
    // ヘッダの確認
    if ( Serial1.read() == 'H' ) {
      int low = Serial1.read(); // 下位バイトの読み取り
      int high = Serial1.read(); // 上位バイトの読み取り
      recv_data = makeWord(high,low); // 上位バイトと下位バイトを合体させてint型データを復元
      Serial.println(recv_data);
    }
    //delay(500);
  /*
  while(Serial1.available() > 0){
  Serial.println(Serial1.read());
  }//*/
  }

}
