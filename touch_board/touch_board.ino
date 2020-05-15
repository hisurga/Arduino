int EN1 = 5;
int EN2 = 7;
int VOLUME = 1;

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  Serial.begin( 9600 );
}

void loop() {
  // analogReadでvolumeから値を得る
  int interval = analogRead(VOLUME) * 5 + 100;
  Serial.println(interval);
  digitalWrite(EN1, HIGH);
  delay(250);
  digitalWrite(EN1, LOW);
  delay(interval);
  digitalWrite(EN2, HIGH);
  delay(250);
  digitalWrite(EN2, LOW);
  delay(interval);
}
