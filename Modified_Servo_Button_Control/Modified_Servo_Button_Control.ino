/*
  SparkFun Inventor’s Kit
  Circuit 3A-Servo

  Move a servo attached to pin 9 so that it's angle matches a potentiometer attached to A0.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

#include <Servo.h>          //include the servo library

int potPosition;           //this variable will store the position of the potentiometer
int servoPosition;         //the servo will move to this position
int SERVO_MAX = 1023;
int MIN_MOTOR_RANGE = 10;
int MAX_MOTOR_RANGE = 170;
int rangeModifier = 0;
int stepAmount = 2;
bool buttonPressed = true;
int currPosition = 90;

Servo myservo;              //create a servo object

void setup() {
  Serial.begin(9600);

  pinMode(4, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);

  myservo.attach(9);        //tell the servo object that its servo is plugged into pin 9

}

void loop() {

  potPosition = analogRead(A0);                     //use analog read to measure the position of the potentiometer (0-1023)

  if(digitalRead(4) == LOW){
    currPosition -= stepAmount;
  }
  if(digitalRead(2) == LOW){
    currPosition += stepAmount;
  }
  /*Serial.print("Current Position: ");
  Serial.println(currPosition);*/

  if(currPosition < MIN_MOTOR_RANGE){
    currPosition = MIN_MOTOR_RANGE;
  }

  if(currPosition > MAX_MOTOR_RANGE){
    currPosition = MAX_MOTOR_RANGE;
  }

  // use the potPosition to limit the range of motion of the motor
  if(potPosition >= 0 && potPosition < 255){
    rangeModifier = 0;
  } else if(potPosition > 254 && potPosition < 510){
    rangeModifier = 15;
  } else if(potPosition > 509 && potPosition < 765){
    rangeModifier = 30;
  } else {
    rangeModifier = 45;
  }
  /*if(potPosition == 0){
    potPosition = 1;
  }
  int rangeRestrict = 75 * (1/potPosition);*/
  int newMin = MIN_MOTOR_RANGE + rangeModifier;
  int newMax = MAX_MOTOR_RANGE - rangeModifier;

  servoPosition = map(currPosition, 0, 180, newMin, newMax); //convert the potentiometer number to a servo position from 10-170
                                                      //Note: its best to avoid driving the little SIK servos all the
                                                      //way to 0 or 180 degrees it can cause the motor to jitter, which is bad for the servo.
  //Serial.print("Servo Position: ");
  //Serial.println(servoPosition);

  myservo.write(servoPosition);                      //move the servo to the 10 degree position
  delay(16);

  // 
}
