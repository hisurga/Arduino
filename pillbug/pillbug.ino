#include<SPI.h>

#define MODE 7
#define APHASE 6
#define AENBL 5
#define BPHASE 4
#define BENBL 3

#define ECHO 9
#define TRIG 8
#define SCK 13
#define LATCH 10
#define SDI 11

int NEXT_TURN = 0;

const byte digits[] =
  {
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11110110, // 9
  };

void setup()
{
  //各ピンの初期化
  pinMode(MODE, OUTPUT);
  pinMode(APHASE, OUTPUT);
  pinMode(AENBL, OUTPUT);
  pinMode(BPHASE, OUTPUT);
  pinMode(BENBL, OUTPUT);
  digitalWrite(MODE, HIGH);
  //hc-sr04
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  Serial.begin( 9600 );
  //7seg
  pinMode(LATCH,INPUT);
  pinMode(SCK, OUTPUT);
  pinMode(SDI, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  SPI.setDataMode(0);
  //いきなり動き出すと困るので少し遅らす
  delay(5000);
}

void loop()
{
  //measureDistance関数で距離測定&7セグ更新
  int d_seg = 0;
  d_seg =  measureDistance();

  digitalWrite(APHASE, LOW);
  digitalWrite(BPHASE, LOW);

  //0距離になったら停止してturnBug()を実行
  if(d_seg == 0)
    {
      analogWrite(AENBL, 0);
      analogWrite(BENBL, 0);
      turnBug(); 
    }
  //若干AとBに数値の差があるのは、まっすぐ進むように微調整しただけです
  else
    {
      analogWrite(AENBL, 100);
      analogWrite(BENBL, 105);
    }
}

//呼ばれるたびに右左交互に旋回
void turnBug()
{
  if(NEXT_TURN == 0)
    {
      //距離30cmを超えるまで旋回
      while(measureDistance() < 3)
	{
	  digitalWrite(APHASE, LOW);
	  digitalWrite(BPHASE, HIGH);
	  analogWrite(AENBL, 50);
	  analogWrite(BENBL, 55);
	  delay(220);
	}
      NEXT_TURN = 1;
      return;
    }
  else
    {
      while(measureDistance() < 3)
	{
	  digitalWrite(APHASE, HIGH);
	  digitalWrite(BPHASE, LOW);
	  analogWrite(AENBL, 50);
	  analogWrite(BENBL, 55);
	  delay(220);
	}
      NEXT_TURN = 0;
      return;
    }
}

//距離を測定して返す
int measureDistance()
{
  double Interval = 0;
  double Distance = 0;
  int d_seg;
    
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  Interval = pulseIn(ECHO, HIGH);
  
  if (Interval != 0)
    {
      Interval = Interval / 2;
      Distance = Interval * 340 * 0.0001;
      Serial.print(Distance);
      Serial.println("cm");
    }
  if(90.0 < Distance)
    {
      d_seg = 9;
    }
  else
    {
      d_seg = Distance / 10;
    }
  digitalWrite(LATCH, 0);
  SPI.transfer (digits[d_seg]);
  digitalWrite(LATCH, 1);
  return d_seg;
}
