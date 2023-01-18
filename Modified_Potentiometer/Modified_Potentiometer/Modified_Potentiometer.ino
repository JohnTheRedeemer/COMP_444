/*
  SparkFun Inventor’s Kit
  Circuit 1B-Potentiometer

  Changes how fast an LED connected to pin 13 blinks, based on a potentiometer connected to pin A0

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download code at: https://github.com/sparkfun/SIK-Guide-Code
*/

int potPosition;       //this variable will hold a value based on the position of the potentiometer
const long rCounter = 1;
int rState = LOW;
unsigned long previousRMillis = 0;
const long gCounter = 1;
int gState = LOW;
unsigned long previousGMillis = 0;
const long bCounter = 1;
int bState = LOW;
unsigned long previousBMillis = 0;


void setup()
{
  Serial.begin(9600);       //start a serial connection with the computer

  pinMode(13, OUTPUT);      //set pin 13 as an output that can be set to HIGH or LOW
  pinMode(12, OUTPUT);      //set pin 12 as an output that can be set to HIGH or LOW
  pinMode(11, OUTPUT);      //set pin 11 as an output that can be set to HIGH or LOW
}

void loop()
{    
  //read the position of the pot
  potPosition = analogRead(A0);    //set potPosition to a number between 0 and 1023 based on how far the knob is turned
  Serial.println(potPosition);     //print the value of potPosition in the serial monitor on the computer

  unsigned long currentMillis = millis();
  if(currentMillis - previousRMillis >= (rCounter * potPosition)){
    previousRMillis = currentMillis;

    if(rState == LOW){
      rState = HIGH;
    } else {
      rState = LOW;
    }
    digitalWrite(13, rState);    
  }

  if(currentMillis - previousGMillis >= (gCounter * 2) * potPosition){
    previousGMillis = currentMillis;

    if(gState == LOW){
      gState = HIGH;
    } else {
      gState = LOW;
    }
    digitalWrite(12, gState);
  }

  if(currentMillis - previousBMillis >= (gCounter * 4) * potPosition){
    previousBMillis = currentMillis;

    if(bState == LOW){
      bState = HIGH;
    } else {
      bState = LOW;
    }
    digitalWrite(11, bState);
  }
}
