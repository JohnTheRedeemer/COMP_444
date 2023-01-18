/*
  SparkFun Inventor’s Kit
  Circuit 1C-Photoresistor

  Use a photoresistor to monitor how bright a room is, and turn an LED on when it gets dark.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

int photoresistor = 0;              //this variable will hold a value based on the brightness of the ambient light
int threshold = 750;                //if the photoresistor reading is below this value the the light will turn on
int thresholdLevel1 = 250;
int thresholdLevel2 = 500;
int thresholdLevel3 = 750;
int blinkThreshold = 1000;          // how often we should blink
int state = LOW;

const long counter = 1;
unsigned long prevMs = 0;

void setup()
{
  Serial.begin(9600);               //start a serial connection with the computer

  pinMode(11, OUTPUT);              //set pin 11 as an output that can be set to HIGH or LOW
  pinMode(12, OUTPUT);              //set pin 12 as an output that can be set to HIGH or LOW
  pinMode(13, OUTPUT);              //set pin 13 as an output that can be set to HIGH or LOW
}

void loop()
{
  //read the brightness of the ambient light
  photoresistor = analogRead(A0);   //set photoresistor to a number between 0 and 1023 based on how bright the ambient light is
  Serial.println(photoresistor);    //print the value of photoresistor in the serial monitor on the computer

  //if the photoresistor value is below the threshold turn the light on, otherwise turn it off
  if (photoresistor < threshold) {
    digitalWrite(13, HIGH);         // Turn on the LED
  } else {
    digitalWrite(13, LOW);          // Turn off the LED
  }

  if (photoresistor > threshold) {
    digitalWrite(12, HIGH);         // Turn on the LED
  } else {
    digitalWrite(12, LOW);          // Turn off the LED
  }

  // depending on the threshold, blink faster the brighter it is

  // we're just changing the threshold based on how bright it is
  // the brighter it is, the shorter the time difference between blinks
  unsigned long currentMillis = millis();
  unsigned long msDiff = currentMillis - prevMs;
  if(photoresistor > thresholdLevel3){
    blinkThreshold = 250;
    
  } else if(photoresistor >= thresholdLevel2){
    blinkThreshold = 500;
    
  } else if(photoresistor >= thresholdLevel1){
    blinkThreshold = 1000;
    
  } else {
    state = LOW;
  }
  
  if(msDiff > blinkThreshold){
    prevMs = currentMillis;
    if(state == LOW){
        state = HIGH;
      } else {
        state = LOW;
    }
  }
  digitalWrite(11, state);  
  
  //delay(100);                       //short delay to make the printout easier to read
}
