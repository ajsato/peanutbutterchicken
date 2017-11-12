//load library for display RGB Backlit (LCD)
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int buttonPin = 2;
int ledPin = 3;
int colorR = 255;
int colorG = 255;
int colorB = 255;

void setup() {

  pinMode(buttonPin, INPUT); // set mode for the pin (INPUT/OUTPUT)
  lcd.begin(16, 2);
  lcd.print(""); // print to LCD
  
}

void loop() {

//======================================================================
    if (digitalRead(buttonPin)) {
      turnRed();
    }
    else {
      turnWhite();
    }
    lcd.setRGB(colorR, colorG, colorB);
//======================================================================

}

//if button is pressed, the screen turns red.
void turnRed()
{
  if (colorG>0) {
    colorG--;
  }
  if (colorB>0) {
    colorB--;
  }
    delay(40); 
}

//function restore the screen to white light.
void turnWhite()
{
    if (colorG<255) {
      colorG++;
    }
    if (colorB<255) {
      colorB++;
    }
    delay(30);
}

void alert()
{
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
}

