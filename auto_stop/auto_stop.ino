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
  delay(5000);
}

void loop() {
  
  double Interval = 0;
  double Distance = 0;
  
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
  
  //7seg  
  int d_seg = 0;
  if(Distance < 10.0)
    {
      d_seg = 0;
    }
  else if(90.0 < Distance)
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

  digitalWrite(APHASE, LOW);
  digitalWrite(BPHASE, LOW);

  //急停止するのもつまらないので超音波メジャーから得た距離を利用し、近くなるにつれてスピードを落とすようにしました。  
  //値は適当です。
  if(d_seg == 0)
    {
      analogWrite(AENBL, 0);
      analogWrite(BENBL, 0);
    }
  else if(d_seg == 9)
    {
      analogWrite(AENBL, 255);
      analogWrite(BENBL, 255);

    }
  else
    {
      analogWrite(AENBL, d_seg * 30);
      analogWrite(BENBL, d_seg * 30);
    }
}
