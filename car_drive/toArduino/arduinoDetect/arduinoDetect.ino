

#include <Servo.h>

#define trigPin1 13
#define echoPin1 12
#define trigPin2 7
#define echoPin2 6
#define wait 5

Servo servo;
Servo motor;
void _motor(signed int);
void _servo(signed int);

void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  servo.attach(6);
  motor.attach(5);
}
void loop() {
  long timeout = 2000;
  long duration1, distance1,duration2, distance2;

  _motor(80);
  _servo(0);
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH, timeout);
  distance1 = (duration1/2) / 29.1;
  if (distance1 >= 200 || distance1 <= 0){
    Serial.print("Right: Out of range");
  }
  else if (distance1 < 15) {
    _motor(0);
  }

    delay(wait);
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH, timeout);
  distance2 = (duration2/2) / 29.1;
  if (distance2 >= 200 || distance2 <= 0){
    Serial.print("     Left: Out of range");
  }
  else if (distance1 < 15) {
    _motor(0);
  }
  delay(wait);

}

void _motor(signed int value) {
  //Serial.print("moving motor ");
  //Serial.println(value);
  value = map(value,0,100,1300,1700);
  motor.write(value);
}

void _servo(signed int value) {
  //Serial.print("moving servo ");
  //Serial.println(value);
  value = map(value,-45,45,60,130);
  servo.write(value);
}
