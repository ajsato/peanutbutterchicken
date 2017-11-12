//load library for display RGB Backlit (LCD)
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int buttonPin = 2;
const int yesPin = 3;
const int noPin = 4;
const int ledPin = 5;
const int led2Pin = 6;
const int vibrationPin = 7;
const int touchPin = 8;

const int rotaryPin = 0;
//const int tempPin = 1;
const int soundPin = 2;

int colorR = 255;
int colorG = 255;
int colorB = 255;

int favIndex = 0;
int favCurr = 0;
int favR = 0;
int favG = 0;
int favB = 0;

bool redSet = false;
bool greenSet = false;
bool blueSet = false;

bool runOnlyOnce = true;
bool runOnlyOnce2 = true;
int stressCount = 0;
bool stressCounter50 = true;
bool stressCounter100 = true;
bool stressCounter150 = true;
bool stressCounter200 = true;

void setup() {
  pinMode(buttonPin, INPUT); // set mode for the pin (INPUT/OUTPUT)
  pinMode(yesPin, INPUT);
  pinMode(noPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(touchPin, INPUT);

  pinMode(rotaryPin, INPUT);
  //pinMode(tempPin, INPUT);
  pinMode(soundPin, INPUT);

  lcd.begin(16, 2);
}

void loop() {
  //Introduction
  if (runOnlyOnce) {
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
    lcd.print("Before we begin,");
    lcd.setCursor(0, 1);
    lcd.print("let's choose a");
    delay(2000);
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("color that");
    lcd.setCursor(0, 1);
    lcd.print("relaxes you.");
    delay(2000);

    // chooses color based on rotary and button input
    while (!(redSet && greenSet && blueSet)) {
      setIndex_M();
    }

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
    lcd.setRGB(favR, favG, favB);
    delay(100);
    lcd.setRGB(0, 0, 0);
    delay(10);
    lcd.setRGB(colorR, colorG, colorB);
    lcd.setCursor(0, 0);
    lcd.print("please press any");
    lcd.setCursor(0, 1);
    lcd.print("button to begin.");
    delay(2000);
    while (!pressAnyButtonButResetAndPower()) {

    }
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("Let's try it.");
    delay(2000);

    runOnlyOnce = false;
  }

  //Operation

  //button
  if (digitalRead(buttonPin)) {
    turnRed();
    if (colorG == 0 || colorB == 0) {
      alert();
    }
  }
  else {
    turnWhite();
  }

  //Sound
  aggressiveSound();
  lcd.setCursor(0, 0);
  lcd.print("Stress Counter: ");
  lcd.setCursor(0, 1);
  lcd.print(stressCount);

  //Have to check yes no if it works correctly or not.

  //TEMP SENSOR
  //  lcd.setCursor(0, 1);
  //  lcd.print(analogRead(tempPin));
  //  delay(1);
  //  lcd.print("     ");

  //TOUCH SENSOR
  while (digitalRead(touchPin))
  {
    digitalWrite(led2Pin, HIGH);
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("Relax~");
    lcd.setRGB(255, 255, 255);
    delay(500);
    lcd.setRGB(favR, favG, favB);
    delay(500);
  }

  //VIBRATION SENSOR
  earthquake();

  //EASTER EGGS
  if (stressCount != 0)
    easterEgg1();

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
  stressCount++;
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

//======================================================================
//press any button
bool pressAnyButtonButResetAndPower()
{
  if (digitalRead(yesPin) || (digitalRead(noPin) || digitalRead(buttonPin))) {
    return true;
  }
  return false;
}
//======================================================================

//======================================================================
//clear the LCD screen
void clearLcd()
{
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("                ");
}
//======================================================================

/*
  float calculateTemp()
  {
  float voltage = (analogRead(tempPin) / 1024.0) * 5.0;
  float temperature = (voltage - .5) * 100;
  return temperature;
  }
*/
//======================================================================
//Detect stress from sound
void aggressiveSound()
{
  if (analogRead(soundPin) >= 900)
  {
    alert();
    colorG = 0;
    colorB = 0;
  }
}
//======================================================================

//======================================================================
//flash LED
void blinkLed(int x)
{
  digitalWrite(x, HIGH);
  delay(100);
  digitalWrite(x, LOW);
}
//======================================================================

//======================================================================
//measure vibration
void earthquake()
{
  if (digitalRead(vibrationPin))
  {
    alert();
    colorG = 0;
    colorB = 0;
  }
}

//======================================================================
//It is a secret! Keep quiet!
void easterEgg1()
{

  if (stressCount == 50 && stressCounter50)
  {
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("Hooray! You are");
    lcd.setCursor(0, 1);
    lcd.print("a stress newbie");
    delay(2000);
    clearLcd();
    stressCounter50 = false;
  }
  else if (stressCount == 100 && stressCounter100)
  {
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("Wow! You are a");
    lcd.setCursor(0, 1);
    lcd.print("stress amateur!");
    delay(2000);
    clearLcd();
    stressCounter100 = false;
  }
  else if (stressCount == 150 && stressCounter150)
  {
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("OMG! You are a ");
    lcd.setCursor(0, 1);
    lcd.print("stress master!");
    delay(2000);
    clearLcd();
    stressCounter150 = false;
  }
  else if (stressCount == 200 && stressCounter200)
  {
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("...You must have");
    lcd.setCursor(0, 1);
    lcd.print("a tough life");
    delay(2000);
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("    (@_____@)   ");
    clearLcd();
    stressCounter200 = false;
  }
}
//======================================================================

//======================================================================
//ROTARY
float rotary() {
  clearLcd();
  lcd.setCursor(0, 1);
  lcd.print(floor(analogRead(rotaryPin) / 4));
  delay(1);
  lcd.print("     ");
  return  floor(analogRead(rotaryPin) / 4);
}

//======================================================================


//======================================================================
// left, yes, right
void setIndex() {

  delay(100);
  clearLcd();

  // right button is right cursor
  if (digitalRead(buttonPin)) {
    switch (favIndex) {
      case 0:
      case 1:
        favIndex++;
        break;

      default:
        break;
    }
  }

  // left button is left cursor
  if (digitalRead(noPin)) {
    switch (favIndex) {
      case 1:
      case 2:
        favIndex--;
        break;

      default:
        break;
    }
  }

  // middle button is choose
  if (digitalRead(yesPin)) {
    switch (favIndex) {
      case 0:
        favCurr = rotary();
        favR = favCurr;
        lcd.setRGB(favR, favG, favB);
        lcd.setCursor(0, 0);
        lcd.print("Red Set");
        redSet = true;
        break;

      case 1:
        favCurr = rotary();
        favG = favCurr;
        lcd.setRGB(favR, favG, favB);
        lcd.setCursor(0, 0);
        lcd.print("Green Set");
        greenSet = true;
        break;

      case 2:
        favCurr = rotary();
        favB = favCurr;
        lcd.setRGB(favR, favG, favB);
        lcd.setCursor(0, 0);
        lcd.print("Blue Set");
        blueSet = true;
        break;

      default:
        break;
    }
  }
  // display final color
  lcd.setRGB(favR, favG, favB);
}
//--------------------------------------------------------------------------------------------------------------------------------------
void setIndex_M() {

  if (favIndex == 0) { //Red state
    lcd.setCursor(0, 0);
    lcd.print("Red");
    favCurr = rotary();
    lcd.setRGB(favCurr, favG, favB);
    if (digitalRead(buttonPin)) {
      favIndex = 1;
      delay(100);
    }
    else if (digitalRead(yesPin)) {
      favR = favCurr;
      redSet = true;
      delay(100);
    }


  }
  if (favIndex == 1) { //Green state
    lcd.setCursor(0, 0);
    lcd.print("Green");
    favCurr = rotary();
    lcd.setRGB(favR, favCurr, favB);
    if (digitalRead(buttonPin)) {
      favIndex = 2;
      delay(100);
    }
    else if (digitalRead(yesPin)) {
      favG = favCurr;
      greenSet = true;
      delay(100);
    }
    else if (digitalRead(noPin)) {
      favIndex = 0;
      delay(100);
    }
  }
  if (favIndex == 2) { //Blue state
    lcd.setCursor(0, 0);
    lcd.print("Blue");
    favCurr = rotary();
    lcd.setRGB(favR, favG, favCurr);
    if (digitalRead(yesPin)) {
      favB = favCurr;
      blueSet = true;
      delay(100);
    }
    else if (digitalRead(noPin)) {
      favIndex = 1;
      delay(100);
    }
  }
}
