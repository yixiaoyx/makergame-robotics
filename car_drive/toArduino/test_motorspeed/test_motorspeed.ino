/*
The ESC needs a calibration pulse when it is turned on, this sets the zero position,
at the moment this is just set in the setup however if you turn the ESC off and back on
without resetting the arduino you might find the car goes insane

the values to use are:

Forward

zero speed = 1500
wheels just moving = 1580
slow speed = 1600
really fast = 1700
top speed = 1800

brake = 1000 (this is only the brake if you are moving forward)

Reverse: To get into reverse., if you are traveling forward you need to set speed to
zero speed, then to a small reverse speed, back to zero speed and then to the reverse
speed you want. An example would look something like this:

(assume we are already moving forward)
motor.write(1500);
motor.write(1420);
motor.write(1500);
motor.write(1400);   //this is the only value you need to change

wheels just moving = 1400
slow speed = 1350
really fast = 1250
top speed = ???? dont wanna push it too hard in reverse

brake = i havnt found the reverse command yet so the best you can do while
in reverse is either give the car zero speed i.e. 1500 or give it a really small
forwards value i.e. 1580 or something. Make sure not to jump from full reverse to
full forward or the gears will be damaged

*/
String readString;
#include <Servo.h>
Servo motor;  // create servo object to control a servo

void setup() {
  Serial.begin(9600);
  //myservo.writeMicroseconds(1500); //set initial servo position if desired
  motor.attach(5);  //the pin for the servo control
  motor.write(1500);  //this is for calibration
  //Serial.println("servo-test-22-dual-input"); // so I can keep track of what is loaded
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (readString.length() >0) {
    Serial.println(readString);  //so you can see the captured string
    int n = readString.toInt();  //convert readString into a number

    // auto select appropriate value, copied from someone elses code.

      Serial.print("writing: ");
      Serial.println(n);
      motor.write(n);


    readString=""; //empty for next input
  }
}
