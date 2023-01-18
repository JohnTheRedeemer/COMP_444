/*
  SparkFun Inventor’s Kit
  Circuit 1A-Blink

  Turns an LED connected to pin 13 on and off. Repeats forever.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download code at: https://github.com/sparkfun/SIK-Guide-Code
*/

int sTime = 500;
int oTime = 1000;

void setup() {

  pinMode(13, OUTPUT);      // Set pin 13 to output

}


void loop() {

  // Morse code S
  digitalWrite(13, HIGH);   // Turn on the LED

  delay(sTime);              // Wait 

  digitalWrite(13, LOW);    // Turn off the LED

  delay(sTime);              // Wait 

  digitalWrite(13, HIGH);   // Turn on the LED

  delay(sTime);              // Wait 

  digitalWrite(13, LOW);    // Turn off the LED

  delay(sTime);              // Wait 

  digitalWrite(13, HIGH);   // Turn on the LED

  delay(sTime);              // Wait 

  digitalWrite(13, LOW);    // Turn off the LED

  delay(oTime * 2);              // Wait between letters

  // Morse code O
  digitalWrite(13, HIGH);   // Turn on the LED

  delay(oTime);              // Wait 

  digitalWrite(13, LOW);    // Turn off the LED

  delay(oTime);              // Wait 

  digitalWrite(13, HIGH);   // Turn on the LED

  delay(oTime);              // Wait 

  digitalWrite(13, LOW);    // Turn off the LED

  delay(oTime);              // Wait 

  digitalWrite(13, HIGH);   // Turn on the LED

  delay(oTime);              // Wait 

  digitalWrite(13, LOW);    // Turn off the LED

  delay(oTime * 2);              // Wait 

  
  // Morse code S
  digitalWrite(13, HIGH);   // Turn on the LED

  delay(sTime);              // Wait 

  digitalWrite(13, LOW);    // Turn off the LED

  delay(sTime);              // Wait 

  digitalWrite(13, HIGH);   // Turn on the LED

  delay(sTime);              // Wait 

  digitalWrite(13, LOW);    // Turn off the LED

  delay(sTime);              // Wait 

  digitalWrite(13, HIGH);   // Turn on the LED

  delay(sTime);              // Wait 

  digitalWrite(13, LOW);    // Turn off the LED

  delay(oTime * 4);              // Wait 
}
