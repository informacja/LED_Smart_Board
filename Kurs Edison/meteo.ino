#define Termo A0
#define Fotod A1
#define Button 4
#define Led 3

#include <rgb_lcd.h>
#include <Wire.h>

rgb_lcd lcd; //Tworzenie obiektu lcd klasy rgb_lcd
int R = 0;
int G = 255;
int B = 0;

double temp = 0;  //Zerujemy temperature
double light = 0; //Zerujemy swiatlo
String odebraneDane = "";
double r = 0;
char s = 223;
int licznik = 0;
int rgb=1;

void Spr()
{
  if(rgb==0)
  {
    int R = 0;
    int G = 255;
    int B = 0;
    lcd.setRGB(R,G,B);
  }
  else if(rgb==1)
  {
    int R = 255;
    int G = 0;
    int B = 0;
    lcd.setRGB(R,G,B);
  }
  else if(rgb==2)
  {
    int R = 0;
    int G = 0;
    int B = 255;
    lcd.setRGB(R,G,B);
  }
  else if(rgb==3)
  {
       int R = 0;
       int G = 0;
       int B = 0;
    while(Button!=HIGH)
    {
      if (R<255)
      R++;
     else if(R==255&G<255){ G++; R--;}
     else if (G==255&B<255){ B++; G--;}
     else break;
      lcd.setRGB(R,G,B);
      delay(1);
      
    }
  }
  else{
    int R = 0;
    int G = 255;
    int B = 0;
    lcd.setRGB(R,G,B);
  }
  
}

void setup() {
  Serial.begin(9600);//Uruchomienie komunikacji przez USART
  pinMode(Termo, INPUT);
  pinMode(Fotod, INPUT);
  pinMode(Button, INPUT_PULLUP);
  pinMode(Led, OUTPUT);
  pinMode(8, INPUT_PULLUP);

  lcd.begin(16, 2);   //Przypisanie wiekosci wyswietlacza
  lcd.setRGB(R,G,B);  //Przypisanie kolorow wyswietlacza

}
void loop() {
  
   if(digitalRead(Button)==HIGH) // Zerowanie na przycisk
  {
    Spr();
    delay(250);
    rgb++;
    if (rgb == 4) rgb = 0;
  }
   
  temp = analogRead(Termo);   //Przypisanie zmiennej temp odczytĂłw z termometru
  light = analogRead(Fotod);  //Przypisanie zmiennej temp odczytĂłw z fotodiody
  
  if(licznik%30 == 0)
  {
   lcd.clear();   //Czysci wyswietlacz
   lcd.setCursor(0, 0); //Ustawia kursor
    r = ((1023.0/temp-1.0)*100000);
    //(temp/1024.0)*50
   Serial.println(s);
   lcd.print("Temp: ");  lcd.print(1.0/(log(r/100000)/4275+1/298.15)-273.15); lcd.print(s); lcd.print('C'); //Wypisuje w miejscu kursora
   lcd.setCursor(0, 1); //Ustawia kursor
   lcd.print("Osw: ");  lcd.print(exp(float(light)/80.0)); lcd.print(" LUX"); //Wypisuje w miejscu kursora
   licznik = 0;
  } 
  
   Serial.println(1.0/(log(r/100000)/4275+1/298.15)-273.15);  //WysyĹ‚a temp do monitora portu szeregowego
   Serial.println(exp(float(light)/80.0));
   analogWrite(Led, map(light,0,300,0,130)); //Przypisuje diodzie tyle napiÄ™cia ile swiatla ma fotodioda
   delay(25); //Czeka 2/10 sekundy, ĹĽeby liczicznik bardzo nie skakaĹ‚
  licznik++;
 // Serial.println(rgb);
}

