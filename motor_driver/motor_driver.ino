#define MODE 7
#define APHASE 6
#define AENBL 5
#define BPHASE 4
#define BENBL 3

void setup()
{
  pinMode(MODE, OUTPUT);
  pinMode(APHASE, OUTPUT);
  pinMode(AENBL, OUTPUT);
  pinMode(BPHASE, OUTPUT);
  pinMode(BENBL, OUTPUT);
  digitalWrite(MODE, HIGH);
}

void loop()
{
  digitalWrite(APHASE,  LOW);
  analogWrite(AENBL, 100);
  digitalWrite(BPHASE, LOW);
  analogWrite(BENBL, 100);
  
  delay(1000);
  
  digitalWrite(APHASE,  HIGH);
  analogWrite(AENBL, 100);
  digitalWrite(BPHASE, HIGH);
  analogWrite(BENBL, 100);
  
  delay(1000);
  
  for(int i = 50; i < 255; i++)
    {
      digitalWrite(APHASE, LOW);
      analogWrite(AENBL, i);
      digitalWrite(BPHASE, HIGH);
      analogWrite(BENBL, i);
      delay(50);
    }
  delay(2000);
  
  
  digitalWrite(APHASE, LOW);
  analogWrite(AENBL, 0);
  digitalWrite(BPHASE, LOW);
  analogWrite(BENBL, 0);
  
  delay(1000);
}
