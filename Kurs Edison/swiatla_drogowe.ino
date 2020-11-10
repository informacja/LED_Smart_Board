#define zielony 8
#define zolty 4
#define czerwony 2
#define przycisk 7

void setup() {
  pinMode(zielony, OUTPUT);
  pinMode(zolty, OUTPUT);
  pinMode(czerwony, OUTPUT);
  pinMode(przycisk, INPUT_PULLUP);
  digitalWrite(przycisk, LOW);
}

void loop() {
  bool button;
  if (digitalRead(przycisk) == LOW)
      button = true;
      else button = false;

   if ( button == true )
   {
      delay(1000);
      digitalWrite(czerwony, LOW);
      digitalWrite(zolty, HIGH);
      delay(1000);
      digitalWrite(zolty, LOW);
      digitalWrite(zielony, HIGH);
      delay(5000);
  }
  else
  {
    digitalWrite(zielony, LOW);
    digitalWrite(czerwony, HIGH);
  } 
}
