#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display
int count = 0;

// my curr/last frame code is inspired by my game programming, checking button states between game frames to see if an input has been checked
bool pressedLastFrame = false;
bool pressedCurrFrame = false;

void setup() {

  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display

  pinMode(3, INPUT_PULLUP);
}

void loop() {
  // assign button press to last frame/loop
  pressedLastFrame = pressedCurrFrame;

  // check to see if button is pressed this frame
  pressedCurrFrame = digitalRead(3) == LOW;

  if (pressedCurrFrame == false && pressedLastFrame == true) {
    count++;
  }

  lcd.setCursor(0, 0);              //set the cursor to the 0,0 position (top left corner)
  lcd.print("Pressed Count:");       //print hello, world! starting at that position

  lcd.setCursor(0, 1);              //move the cursor to the first space of the bottom row
  lcd.print(count);       //print the number of seconds that have passed since the last reset
}
