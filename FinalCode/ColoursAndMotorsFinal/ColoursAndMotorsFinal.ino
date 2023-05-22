#include <Wire.h>
#include <Servo.h>
#include "Adafruit_TCS34725.h"

// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define motor1Pin 3
#define motor2Pin 5
#define motor3Pin 6
#define ledpin 8
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
#define commonAnode false

// our RGB -> eye-recognized gamma color
byte gammatable[256];


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_16X);
Servo firstMotor;
Servo secondMotor;
Servo thirdMotor;

int firstMotorPos;
int secondMotorPos;
int thirdMotorPos;
int SERVO_MAX = 1023;
int motorDelay = 1000;

void setup() {
    Serial.begin(9600);
    Serial.println("Color View Test!");

    if (tcs.begin()) {
    Serial.println("Found sensor");
    } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
    }

    // use these three pins to drive an LED
    pinMode(motor1Pin, OUTPUT);
    pinMode(motor2Pin, OUTPUT);
    pinMode(motor3Pin, OUTPUT);
    pinMode(ledpin, OUTPUT);

    // thanks PhilB for this gamma table!
    // it helps convert RGB colors to what humans see
    for (int i=0; i<256; i++) {
        float x = i;
        x /= 255;
        x = pow(x, 2.5);
        x *= 255;

        if (commonAnode) {
            gammatable[i] = 255 - x;
        } else {
            gammatable[i] = x;
        }
        //Serial.println(gammatable[i]);
    }

    Serial.println("Attaching motors");
    firstMotor.attach(motor1Pin);
    secondMotor.attach(motor2Pin);
    thirdMotor.attach(motor3Pin);

  
    // check motor servo range 0 degrees to 180 degrees
    Serial.println("Checking motor range");
    firstMotorPos = 0;
    secondMotorPos = 0;
    thirdMotorPos = 0;

    Serial.println("Moving firstMotor to 0 degrees");
    firstMotor.write(firstMotorPos);
    delay(motorDelay);
    Serial.println("Moving secondMotor to 0 degrees");
    secondMotor.write(secondMotorPos);
    delay(motorDelay);
    Serial.println("Moving thirdMotor to 0 degrees");
    thirdMotor.write(thirdMotorPos);
    delay(motorDelay);

    firstMotorPos = 180;
    secondMotorPos = 180;
    thirdMotorPos = 180;

    Serial.println("Moving firstMotor to 180 degrees");
    firstMotor.write(firstMotorPos);
    delay(motorDelay);
    Serial.println("Moving secondMotor to 180 degrees");
    secondMotor.write(secondMotorPos);
    delay(motorDelay);
    Serial.println("Moving thirdMotor to 180 degrees");
    thirdMotor.write(thirdMotorPos);
    delay(motorDelay);

    // set motors to neutral position
    firstMotorPos = 90;
    secondMotorPos = 90;
    thirdMotorPos = 90;

    Serial.println("Moving firstMotor to 90 degrees");
    firstMotor.write(firstMotorPos);
    delay(motorDelay);
    Serial.println("Moving secondMotor to 90 degrees");
    secondMotor.write(secondMotorPos);
    delay(motorDelay);
    Serial.println("Moving thirdMotor to 90 degrees");
    thirdMotor.write(thirdMotorPos);
    delay(motorDelay);

    Serial.println("Motors attached and tested");
}

void loop() {

    float red, green, blue;
    float offsetRed, offsetGreen, offsetBlue;
    float finalRed, finalGreen, finalBlue;

    // get rgb values from sensor without bead
        // turn on led
        // read rgb values into offset variables
        // turn off led
    Serial.println("Getting offset");
    delay(5000);
    digitalWrite(ledpin, HIGH);
    delay(600);  // take 600ms to read
    tcs.getRGB(&offsetRed, &offsetGreen, &offsetBlue);
    digitalWrite(ledpin, LOW);
    // write offset values to serial monitor
    Serial.print("oR: "); Serial.print(int(offsetRed));
    Serial.print("\toG: "); Serial.print(int(offsetGreen));
    Serial.print("\toB: "); Serial.print(int(offsetBlue));
    Serial.print("\n");

    // move first motor so bead is placed
    firstMotorPos = 10;
    firstMotor.write(firstMotorPos);
    delay(motorDelay);
    firstMotorPos = 160;
    firstMotor.write(firstMotorPos);
    delay(motorDelay);

    // get rgb values from sensor with bead
        // turn on led
        // read rgb values into variables
        // turn off led
    Serial.println("Reading bead colour");
    delay(5000);
    digitalWrite(ledpin, HIGH);
    delay(600);  // take 600ms to read
    tcs.getRGB(&red, &green, &blue);
    digitalWrite(ledpin, LOW);
    // write values to serial monitor
    Serial.print("R: "); Serial.print(int(red));
    Serial.print("\tG: "); Serial.print(int(green));
    Serial.print("\tB: "); Serial.print(int(blue));
    Serial.print("\n");

    // remove offsets from rgb values
    finalRed = red - offsetRed;
    finalGreen = green - offsetGreen;
    finalBlue = blue - offsetBlue;
    Serial.print("fR: "); Serial.print(int(finalRed));
    Serial.print("\tfG: "); Serial.print(int(finalGreen));
    Serial.print("\tfB: "); Serial.print(int(finalBlue));
    Serial.print("\n");

    // calculate which color is detected and store in string variable
    int color = 0;
    if (finalRed > finalGreen && finalRed > finalBlue) {
        color = 1;
        Serial.println("Red");
    } else if (finalGreen > finalRed && finalGreen > finalBlue) {
        color = 2;
        Serial.println("Green");
    } else if (finalBlue > finalRed && finalBlue > finalGreen) {
        color = 3;
        Serial.println("Blue");
    }
    Serial.print("Color: "); Serial.print(color);
    Serial.print("\n");
    delay(5000);

    // move motors to bin matching color detected (red, green, blue)
    switch (color) {
        case 1:
            Serial.println("Moving thirdMotor to red bin");
            thirdMotorPos = 10;
            thirdMotor.write(thirdMotorPos);
            delay(motorDelay);
            thirdMotorPos = 160;
            thirdMotor.write(thirdMotorPos);
            delay(motorDelay);
            break;
        case 2:
            Serial.println("Moving thirdMotor to green bin");
            thirdMotorPos = 10;
            thirdMotor.write(thirdMotorPos);
            delay(motorDelay);
            thirdMotorPos = 120;
            thirdMotor.write(thirdMotorPos);
            delay(motorDelay);
            break;
        case 3:
            Serial.println("Moving thirdMotor to blue bin");
            thirdMotorPos = 10;
            thirdMotor.write(thirdMotorPos);
            delay(motorDelay);
            thirdMotorPos = 80;
            thirdMotor.write(thirdMotorPos);
            delay(motorDelay);
            break;
        default: // no color detected
            thirdMotorPos = 10;
            thirdMotor.write(thirdMotorPos);
            delay(motorDelay);
            thirdMotorPos = 40;
            thirdMotor.write(thirdMotorPos);
            delay(motorDelay);
            break;
    }

    // drop bead into bin
    Serial.println("Dropping bead into bin");
    secondMotorPos = 10;
    secondMotor.write(secondMotorPos);
    delay(motorDelay);
    secondMotorPos = 160;
    secondMotor.write(secondMotorPos);
    delay(motorDelay);

    // move motors to neutral position
    Serial.println("Moving motors to neutral position");
    firstMotorPos = 90;
    firstMotor.write(firstMotorPos);
    delay(motorDelay);
    secondMotorPos = 90;
    secondMotor.write(secondMotorPos);
    delay(motorDelay);
    thirdMotorPos = 90;
    thirdMotor.write(thirdMotorPos);
    delay(motorDelay);

    // wait 5 seconds before repeating
    Serial.println("Waiting 5 seconds before repeating");
    delay(5000);
}