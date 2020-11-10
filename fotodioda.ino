#include <rgb_lcd.h>
#include <Wire.h>

rgb_lcd lcd;
int R = 170;
int G = 170;
int B = 170;

double wyn=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A1, INPUT);
  lcd.begin(16, 2);
  lcd.setRGB(R,G,B);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<1000;i++)
  {
    double value = analogRead(A1);
    value = map(value, 0, 800, 0, 1000);
    wyn+=value;
    
    delay(1);
  }
  wyn/=1000;
  Serial.println(wyn);
  
  lcd.clear();
   lcd.setCursor(1, 0);
   lcd.print(wyn);
}
