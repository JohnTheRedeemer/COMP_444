/*
  SparkFun Inventor’s Kit
  Circuit 1D-RGB Nightlight

  Turns an RGB LED on or off based on the light level read by a photoresistor.
  Change colors by turning the potentiometer.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

int photoresistor = A0;          //variable for storing the photoresistor value
int potentiometer = A1;          //this variable will hold a value based on the position of the knob
int threshold = 700;            //if the photoresistor reading is lower than this value the light will turn on

long randomNumber = 0;
unsigned long lastUpdate = 0;

//LEDs are connected to these pins
int RedPin = 9;
int GreenPin = 10;
int BluePin = 11;

void setup() {
  Serial.begin(9600);           //start a serial connection with the computer

  //set the LED pins to output
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);

  randomSeed(analogRead(A2));
}

void loop() {

  photoresistor = analogRead(A0);         //read the value of the photoresistor
  potentiometer = analogRead(A1);

  long unsigned ms = millis();

  
  Serial.print("ms:");
  Serial.print(ms - lastUpdate); 
  Serial.print(" Photoresistor value:");
  Serial.print(photoresistor);          //print the photoresistor value to the serial monitor
  Serial.print("  Potentiometer value:");
  Serial.println(potentiometer);          //print the potentiometer value to the serial monitor*/

  if (photoresistor < threshold) {        //if it's dark (the photoresistor value is below the threshold) turn the LED on
      if(ms - lastUpdate > 3 * potentiometer){
        lastUpdate = ms;
      // update colour
      randomNumber = random(1, 8);
    
      switch(randomNumber){
        case 1:
          red();
          break;
        case 2:
          orange();
          break;
        case 3:
          yellow();
          break;
        case 4:
          green();
          break;
        case 5:
          cyan();
          break;
        case 6:
          blue();
          break;
        case 7:
          magenta();
          break;
        default:
          turnOff();
          break;
      }
    }
  }
  else {                                //if it isn't dark turn the LED off

    turnOff();                            //call the turn off function

  }

  delay(100);                             //short delay so that the printout is easier to read
}

void red () {

  //set the LED pins to values that make red
  analogWrite(RedPin, 50);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 0);
}
void orange () {

  //set the LED pins to values that make orange
  analogWrite(RedPin, 50);
  analogWrite(GreenPin, 25);
  analogWrite(BluePin, 0);
}
void yellow () {

  //set the LED pins to values that make yellow
  analogWrite(RedPin, 50);
  analogWrite(GreenPin, 50);
  analogWrite(BluePin, 0);
}
void green () {

  //set the LED pins to values that make green
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 50);
  analogWrite(BluePin, 0);
}
void cyan () {

  //set the LED pins to values that make cyan
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 50);
  analogWrite(BluePin, 50);
}
void blue () {

  //set the LED pins to values that make blue
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 50);
}
void magenta () {

  //set the LED pins to values that make magenta
  analogWrite(RedPin, 50);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 50);
}
void turnOff () {

  //set all three LED pins to 0 or OFF
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 0);
}
