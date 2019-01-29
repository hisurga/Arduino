#define ECHO 8
#define TRIG 13

void setup()
{
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  Serial.begin( 9600 );
}
void loop()
{
  double Interval = 0; //受信間隔
  double Distance = 0; //距離
 
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  //ECHOピンがLOWになるまでの時間を取得
  //タイムアウトで0が返る
  Interval = pulseIn(ECHO, HIGH);

  if (Interval != 0)
  {
    //片道
    Interval = Interval / 2;
    //距離を計算(音速:340m/s)
    Distance = Interval * 340 * 0.0001;
    Serial.print(Distance);
    Serial.println("cm");
  }
  delay(1000);
}
