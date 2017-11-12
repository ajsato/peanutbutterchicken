//load library for display RGB Backlit (LCD)
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int buttonPin = 2;
int ledPin = 3;
int colorR = 0;
int colorG = 0;
int colorB = 0;

void setup() {

  pinMode(buttonPin, INPUT); // set mode for the pin (INPUT/OUTPUT)
  lcd.begin(16, 2);
  lcd.print("hello, world!"); // print to LCD
  
}

void loop() {
  
  lcd.setRGB(colorR, colorG, colorB);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  
  lcd.setCursor(0, 1); // print the number of seconds since reset
  if (digitalRead(buttonPin))
  {
    colorR++; // increase Red intensity
    digitalWrite(ledPin,HIGH); //led is on
    delay(500); // sleep 0.5 sec
  }
  
  digitalWrite(ledPin,LOW); // led is off
  colorDecay(colorR);
}

void stressAlert()
{
  colorR = 0;
  colorR--;
  lcd.setRGB(colorR, colorG, colorB);
}

void colorDecay(int colorX)
{
  if (colorX>0){
  delay(500);
  colorX--;
  }
}

