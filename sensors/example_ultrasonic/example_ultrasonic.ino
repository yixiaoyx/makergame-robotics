#define trigPin1 13
#define echoPin1 12
#define trigPin2 7
#define echoPin2 6
#define trigPin3 9
#define echoPin3 8
#define led 11
#define led2 10
#define wait 5

void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  long timeout = 2000;
  long duration1, distance1,duration2, distance2,duration3, distance3;
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
  else {
    Serial.print("Right: ");
    Serial.print(distance1);
    Serial.print(" cm");
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
  else {
    Serial.print("     Left: ");
    Serial.print(distance2);
    Serial.print(" cm");
  }

  delay(wait);
  digitalWrite(trigPin3, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin3, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH, timeout);
  distance3 = (duration3/2) / 29.1;
  if (distance3 >= 200 || distance3 <= 0){
    Serial.println("    Front: Out of range");
  }
  else {
    Serial.print("    Front:");
    Serial.print(distance3);
    Serial.println(" cm");
  }
  
  delay(wait);
  
}
