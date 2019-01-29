#include<SPI.h>

int sck = 13;
int latch = 10;
int sdi = 11;
int d_time = 300;
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
  pinMode(latch,INPUT);
  pinMode(sck, OUTPUT);
  pinMode(sdi, OUTPUT);
  //SPI通信の準備
  SPI.begin();
  //ビットオーダを指定します(LSBFIRST or MSBFIRST)
  SPI.setBitOrder(LSBFIRST);
  //データモードの設定
  SPI.setDataMode(0);
}

void loop()
{
  //digits分ループさせます
    for (int i = 0; i < 10; i ++)
    {
      //latchのON OFFでLEDを更新します
      digitalWrite(latch, 0);
      //引数をSPIで送信します　大きさは1バイトです
      SPI.transfer (digits[i]);
      digitalWrite(latch, 1);
      //一定時間待ちます = 表示時間
      delay(d_time);
    }
}

