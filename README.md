# Takataka_programs_2022 
3021-2022年高崎高等学校物理部のロボカップジュニアジャパン ライトウェイトのプログラム  
ハードウェア部分に関しては、[こちら](https://github.com/negi-tech/RoboCupJunior2021-2022_Lightweight)を参照

## 開発環境  
PC  :   [Chromebook 3100 2-in-1 ノートパソコン](https://www.dell.com/ja-jp/shop/デルのノートパソコン/chromebook-3100-2-in-1-ノートパソコン/spd/chromebook-11-3100-2-in-1-laptop)(CPU:Celeron N4020、メモリ:4GB、ストレージ:32GB)  
IDE :   Arduino IDE ver 1.8.19
  
## フォルダについて  
「libraries」に共有ライブラリが、「sketches」に書き込むスケッチが入っている。  
※「ads_〇〇」といった変数はアドレス、つまりポインタを表す。当時、new演算子等を理解していなかったため、グローバルでインスタンスを作ってそのポインタを渡すといったことを Compass_dircal_PID や Goal_detectでやっているがおすすめはしない。クラスを書く場合は先にポインタを理解してから書く方がいい  
※開発当初はgitを使用していなかったため、/**/などのコメントアウトが多い。個人的には時間があるならgitの使い方を覚えて、githubなどでソースを共同管理することをお勧めする。gitがどうしても難しいなら、学校のアカウントのgoogle driveの共用フォルダにプログラムのフォルダごと日付を付けて定期的にアップロードするなどしてバックアップを取っておいた方がいい。

## libraries 説明
自作ライブラリについては以下の通りである。また、角度の単位は基本的にラジアンである。
- Compare_function
    - 配列からの最大値・最小値の取り出しと絶対値の関数を同じ表記で統一するためにtemplate関数で書いている
    - 標準の絶対値の関数の型によるミスが発生し、その防止のために取り入れた
- Compass_dircal_PID  
    - 磁気センサーのデータを用いた姿勢制御のためのPID制御の計算を行う
    - 角度は、自分のゴールから相手のゴールへの方向を0とした±πで扱う
- Goal_detect
    - 超音波センサーによって得られた距離から三角測量の要領でフィールド内の自身の位置を推定し、ゴールのある角度を算出する
- IR_sensor
    - 赤外線センサーからの情報を取得し、ベクトル計算によってボールの角度と距離を計算する
    - 回り込みのために、ロボットとボールを円とみなしたときの接線の角度を算出する関数もある
- kicker
    - フォトトランジスタの値からボールが正面近くにあるかを判断し、キッカーとなるソレノイドを作動させる
- Line_checker
    - 1代目のロボットにおいて、ラインセンサー用のマイコンと通信を行い、送られてきた値からロボットの進行方向を変化させる
- motor_control
    - ロボットのモーターのパワーを計算し、制御する
    - 3軸のオムニホイールであり、`moter_move`などのメンバ関数の引数は、(進行角度、進行速度、モーメント)である
    - `moter_move`は1代目に使用したダイセンの4軸モータードライバー(DSR1202)のI<sup>2</sup>C通信用で、`moter_move_Serial`はそのドライバーのUSART(シリアル)通信用、`moter_move_SPI`は2代目のロボットに使用した自作モータードライバー(ATmega328Pを使用)とのSPI通信用である
- moving_average
    - 赤外線センサーの値のブレを緩和するための移動平均用
- Ultrasonic
    - 超音波センサの制御を行う

## sketches 説明
　mainと名前に入っているものが試合で本体に書き込むためのスケッチである。ロボットのメインマイコンには、1代目も2代目もATmega2560を使用しているため、ピン番号も共通させている。「〇〇_sample」というスケッチは、同名のライブラリ記述のためのスケッチである。また、その他のスケッチの概要については以下の通りである。  
- BLDC_calib
    - BLDCモーターのキャリブレーション用
- esc
    - 使用する頻度が少なくなったスケッチを退避させており、mainと名前に入っているスケッチは１代目用のものである。大会当日にはmain_turnを使用していた。以下はその他のスケッチの概要である。
        - BLDC_test
            - BLDCのモータードライバーに書き込むためのスケッチ
            - motor_control.hはこのスケッチ用のライブラリであり、名前が被っているのは別の環境で書かれたものだからである。
        - line_micro
            - １代目のロボットのラインセンサーを担当したpro micro用のスケッチ
            - 本体との通信はシリアル通信で決められた値を垂れ流して行っている
- line_angel
    - 2代目のラインセンサーを担当したATmega328P用のスケッチ
    - 特定の4本のデジタルピンのHIGHとLOWで16個のフォトトランジスタのどれが1つのアナログピンに繋がるかを選択し、得られた結果をあらかじめ決めた閾値で判定し、ライン上かどうかを判断する。
    - ライン上である場合は、ベクトル計算でラインと反対側の方向を計算する
    - レジストリでデジタルピンの切り替えと整数のみでの計算を行うことで高速化を図っている
    - 同じフォルダに入っているスケッチはこのラインセンサーに関連したものであり、概要は以下の通りである
        - line_sender
            - メインマイコンに書き込み、ラインセンサーのデバッグを行うためのもの
            - 設計の都合で、ラインセンサー用のATmega328Pに接続できるUSBポート及びシリアルポートが存在しなかったために作成した
            - PCから書き込まれた数字(16進数で15まで)があった場合にそれをATmega328Pに送信し、ATmega328Pから受信した値をPC側に表示する
        - line_tester
            -　ラインセンサー用のATmega328に書き込み、ラインセンサーのデバッグを行うためのもの
            - メインマイコンから送信された値があれば、その値に対応するフォトトランジスタに切り替え、その値を３バイト（ヘッダ＋int）で送信する
        - Serialsender
            - メインマイコンに書き込み、ラインセンサー用のATmega32からの値を表示するためのもの
        - simple_reader
            - メインマイコンに書き込み、ラインセンサー用のATmega328上でベクトル計算したラインと反対側の方向が正しいかを確認するためもの
- line_angel_advance
    - line_angelのものの発展形として、ライン上であるか以外に空中であるかを判定させようとしたもの
- main_SPI
    - 大会当日に2代目のロボットに書き込んだもの
- map_test
    - 関数の`map`の機能をテストしたもの
- moving_average_test
    - 関数の`moving_average`の機能をテストしたもの
- neopixel_test
    - ラインセンサーのLEDに使用したneopixelの動作を確認するためのもの




