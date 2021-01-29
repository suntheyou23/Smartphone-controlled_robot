#include <SoftwareSerial.h>

// bluetoothモジュールとのシリアル通信用
SoftwareSerial BTSerial(16, 20); 

// 1個目のステッピングモーター用
const int DIR_a  = 5;//5,5
const int STEP_a = 6;//6,A7
const int MS1_a = 9;
const int MS2_a = 10;

// 2個目のステッピングモーター用
const int DIR_b  = 8;//8,A8
const int STEP_b = 7;//7,7
const int MS1_b = A0;
const int MS2_b = A1;

// ENABLE端子用
const int ENABLE = 4;//4,A6


// ロボットの走行状態を格納する関数
int GetState() {
  return BTSerial.read();
}


// モータテスト用関数
void TestMoter() {

  digitalWrite(ENABLE, LOW);

  // 前進
  digitalWrite(DIR_a, HIGH);
  digitalWrite(DIR_b, HIGH);
  //MS1,2設定
  digitalWrite(MS1_a, LOW);
  digitalWrite(MS2_a, LOW);
  digitalWrite(MS1_b, LOW);
  digitalWrite(MS2_b, LOW);
  for(int x = 0; x < 10000; x++) {
    digitalWrite(STEP_a,HIGH); 
    digitalWrite(STEP_b,HIGH);      
    delayMicroseconds(1000);
    digitalWrite(STEP_a,LOW);
    digitalWrite(STEP_b,LOW);      
    delayMicroseconds(1000);
  }

  // ステッピングモーターに過電流が流れないようにするため、ENABLEをHIGHに
  digitalWrite(ENABLE, HIGH);
  delay(10000);
}


// モータ制御関数
void ControlMoter(int state) {
  digitalWrite(ENABLE, HIGH);

  switch(state) {
    case 0: // 前進
      digitalWrite(ENABLE, LOW);
      // 進む向きを決定 (前進)
      digitalWrite(DIR_a, HIGH);
      digitalWrite(DIR_b, HIGH);
      //前進処理
      while (true) {
      digitalWrite(STEP_a,HIGH); 
      digitalWrite(STEP_b,HIGH);      
      delayMicroseconds(1000);
      digitalWrite(STEP_a,LOW);
      digitalWrite(STEP_b,LOW); 
      delayMicroseconds(1000);
      state = GetState();
      if (state != -1) ControlMoter(state);
      }
      break;
     case 1:  // 後進
      digitalWrite(ENABLE, LOW);
      // 進む向きを決定 (後進)
      digitalWrite(DIR_a, LOW);
      digitalWrite(DIR_b, LOW);  
      // 後進処理
      while(true) {
      digitalWrite(STEP_a,HIGH); 
      digitalWrite(STEP_b,HIGH);      
      delayMicroseconds(1000);
      digitalWrite(STEP_a,LOW);
      digitalWrite(STEP_b,LOW); 
      delayMicroseconds(1000);
      state = GetState();
      if (state != -1) ControlMoter(state);
      }
      break;
    case 2: // 右回転
      digitalWrite(ENABLE, LOW);
      // 進む向きを決定 (右回転)
      digitalWrite(DIR_a, HIGH);
      //右回転処理
      while (true) {
      digitalWrite(STEP_a,HIGH);     
      delayMicroseconds(1000);
      digitalWrite(STEP_a,LOW);
      delayMicroseconds(1000);
      state = GetState();
      if (state != -1) ControlMoter(state);
      }
      break;
     case 3:  // 左回転
      digitalWrite(ENABLE, LOW);
      // 進む向きを決定 (左回転)
      digitalWrite(DIR_b, HIGH);
      //左回転処理
      while (true) {
      digitalWrite(STEP_b,HIGH);      
      delayMicroseconds(1000);
      digitalWrite(STEP_b,LOW); 
      delayMicroseconds(1000);
      state = GetState();
      if (state != -1) ControlMoter(state);
      }
      break;
     default: // 停止
      digitalWrite(ENABLE, LOW);
      //停止処理
      digitalWrite(STEP_a,LOW);
      digitalWrite(STEP_b,LOW);
  }
}


void setup() {
  
  // 出力ピン設定
  pinMode(DIR_a, OUTPUT);
  pinMode(STEP_a, OUTPUT);
  pinMode(DIR_b, OUTPUT);
  pinMode(STEP_b, OUTPUT);
  pinMode(ENABLE, OUTPUT);  
  pinMode(MS1_a, OUTPUT);
  pinMode(MS2_a, OUTPUT);
  pinMode(MS1_b, OUTPUT);
  pinMode(MS2_b, OUTPUT);

  // 初期状態
  digitalWrite(DIR_a, LOW);
  digitalWrite(STEP_a, LOW);
  digitalWrite(DIR_b, LOW);
  digitalWrite(STEP_b, LOW);
  
  // MS1,2
  digitalWrite(MS1_a, HIGH);
  digitalWrite(MS2_a, LOW);
  digitalWrite(MS1_b, HIGH);
  digitalWrite(MS2_b, LOW);

  // ENABLEがLOWの時に出力有効
  digitalWrite(ENABLE, HIGH);

  // 9600bpsでシリアル通信を開始
  Serial.begin(9600);
  BTSerial.begin(9600);
}


void loop() {
  //TestMoter();
if (BTSerial.available()){ // bluetoothモジュールとシリアル通信しているとき
  int state = GetState();
  ControlMoter(state);              // モータを動作させる
 }
}
