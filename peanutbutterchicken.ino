//load library for display RGB Backlit (LCD)
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int buttonPin = 2;
int yesPin = 3;
int noPin = 4;
int ledPin = 5;
//int touchPin = 7;
int buzzPin = 8;

int rotaryPin = 0;
int tempPin = 1;
int soundPin = 2;

int colorR = 255;
int colorG = 255;
int colorB = 255;

char answer = 'w';
bool runOnlyOnce = true;

void setup() {

  pinMode(buttonPin, INPUT); // set mode for the pin (INPUT/OUTPUT)
  pinMode(yesPin, INPUT);
  pinMode(noPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);

  pinMode(rotaryPin, INPUT);
  pinMode(tempPin, INPUT);
  pinMode(soundPin, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);


}

void loop() {
  //Introduction
  /*if (runOnlyOnce) {
    lcd.setCursor(0, 0);
    lcd.print("Greetings, my");
    lcd.setCursor(0, 1);
    lcd.print("name is Hans.");
    delay(3000);
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("    (^___^)");
    delay(2000);
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("Press any button");
    lcd.setCursor(0, 1);
    lcd.print("to continue.");
    while (!pressAnyButtonButResetAndPower()) {

    }
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("I am your stress");
    lcd.setCursor(0, 1);
    lcd.print("assistant.");
    delay(2000);
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("I am your stress");
    lcd.setCursor(0, 1);
    lcd.print("assistant.");
    delay(2000);
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("I will give you");
    lcd.setCursor(0, 1);
    lcd.print("activities");
    delay(2000);
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("that relieve");
    lcd.setCursor(0, 1);
    lcd.print("stress.");
    delay(2000);
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("When you see the");
    lcd.setCursor(0, 1);
    lcd.print("screen flash,");
    delay(2000);
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("please press the");
    lcd.setCursor(0, 1);
    lcd.print("button to begin.");
    delay(2000);
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("Let's try it.");
    delay(2000);

    runOnlyOnce = false;
    } */

  //Operation
  if (digitalRead(buttonPin)) {
    turnRed();
    if (colorG == 0 || colorB == 0) {
      alert();
    }
  }
  else {
    turnWhite();
  }

  //Have to check yes no if it works correctly or not.

  //ROTARY
    if (analogRead(rotaryPin) != 0) {
    lcd.setCursor(0, 1);
    lcd.print(analogRead(rotaryPin));
    delay(1);
    lcd.print("     ");
    }

  //TEMP SENSOR
  //  lcd.setCursor(0, 1);
  //  lcd.print(analogRead(tempPin));
  //  delay(1);
  //  lcd.print("     ");

  //BUZZ
  //digitalWrite(buzzPin, HIGH);
  //delay(1);
  //  digitalWrite(buzzPin, LOW);
  //  delay(1);


//problem...
//  lcd.setCursor(0, 0);
//  lcd.print(analogRead(soundPin));
//  delay(100);
//  lcd.setCursor(0, 0);
//  lcd.print("     ");

  lcd.setRGB(colorR, colorG, colorB);

}

//======================================================================
//if button is pressed, the screen turns red.
void turnRed()
{
  if (colorG > 0) {
    colorG--;
  }
  if (colorB > 0) {
    colorB--;
  }
  delay(50);
}
//======================================================================

//======================================================================
//function restore the screen to white light.
void turnWhite()
{
  if (colorG < 255) {
    colorG++;
  }
  if (colorB < 255) {
    colorB++;
  }
  delay(100);
}
//======================================================================

//======================================================================
//Blink RED LED
void alert()
{
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
}
//======================================================================

//======================================================================
bool isYes()
{
  while (!(digitalRead(yesPin) || digitalRead(noPin))) {
    if (digitalRead(yesPin))
      return true;
    if (digitalRead(noPin))
      return false;
  }
  return false;
}
//======================================================================

bool pressAnyButtonButResetAndPower()
{
  if (digitalRead(yesPin) || (digitalRead(noPin) || digitalRead(buttonPin))) {
    return true;
  }
  return false;
}

void clearLcd()
{
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("                ");
}
