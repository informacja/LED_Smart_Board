#include <rgb_lcd.h>
#include <Wire.h>

rgb_lcd lcd;
int R = 0;
int G = 255;
int B = 0;

int led = 3;

void Niebieski()
{ 
   R=0; 
   B=50; 
   lcd.setRGB(R,G,B);
   lcd.setCursor(0, 0);
   lcd.print("Niebieski");
}

void Czerwony()
{ 
    R=50; 
    B=0; 
    lcd.setRGB(R,G,B);
    lcd.setCursor(0, 0);
    lcd.print("Czerwony");
}


void setup() {
  Serial.begin(9600);//Uruchomienie komunikacji przez USART
  pinMode(A0, INPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  

  lcd.begin(16, 2);
  lcd.setRGB(R,G,B);
  lcd.setCursor(4, 0);
  lcd.print("Nacisnij");
  lcd.setCursor(4, 1);
  lcd.print("Przycisk");
   while(digitalRead(4)==LOW)
      delay(25);
   //led=3;
   G=0;
}

void loop() {
  if(digitalRead(4)==HIGH)
  {
     if(digitalRead(4)==HIGH && led == 6){
       delay(500);
       Niebieski();
       led=3;                           }
       
    if(digitalRead(4)==HIGH && led == 3){
       delay(500);
       Czerwony();
       led=6;                           }

       delay(25);
       
     if(digitalRead(4)==HIGH)
     {
        lcd.clear();
        G=255;
        delay(500);
        setup();
     }
  }   
     
  int wpoten = analogRead(A0);//Odczytujemy wartość napięcia
  wpoten = map(wpoten, 0, 1019, 0, 216);
  
  Serial.println(wpoten); //map(wpoten,0, 215 ,0 ,100));//Wysyłamy ją do terminala
  
  analogWrite(led,wpoten); // tu dioda

   lcd.clear();
   if(led == 3) Niebieski();
   if(led == 6) Czerwony();
   lcd.setCursor(0, 1);
   lcd.print(map(wpoten,0, 216 ,0 ,100));
   lcd.print("\%");
    
  delay(75);//Czekamy, aby wygodniej odczytywać wyniki  
}
