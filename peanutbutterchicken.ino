//load library for display RGB Backlit (LCD)
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int buttonPin = 2;
int yesPin = 3;
int noPin = 4;
int ledPin = 5;
int colorR = 255;
int colorG = 255;
int colorB = 255;

char answer = 'w';

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

  // while waiting for user to push button
  if (answer != ('y' || 'n')) {
    if (answer == 'y') // if yes
      lcd.print("y"); 
    else // if no
      lcd.print("n"); 
  }

}

//if button is pressed, the screen turns red.
void turnRed()
{
  if (colorG > 0) {
    colorG--;
  }
  if (colorB > 0) {
    colorB--;
  }
  delay(40);
}

//function restore the screen to white light.
void turnWhite()
{
  if (colorG < 255) {
    colorG++;
  }
  if (colorB < 255) {
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

void isYes()
{
  while (!(digitalRead(yesPin) || digitalRead(noPin))) {
    if (digitalRead(yesPin))
      answer = 'y';
    if (digitalRead(noPin))
      answer = 'n';
  }
}

