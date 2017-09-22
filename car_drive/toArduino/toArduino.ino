#include "shared.h"
#pragma pack(1)
#include <Servo.h>

Servo servo;
Servo motor;

int read_block(char*, int);
void dump();

void _motor(signed int);
void _servo(signed int);
int err1 = 13;
int err2 = 2;
int err3 = 4;
bool err3State = true;


void setup () {
  Serial.begin(9600);
  servo.attach(6);
  motor.attach(5);
  pinMode(err1, OUTPUT);
  pinMode(err2, OUTPUT);
  pinMode(err3, OUTPUT);
  Serial.flush();

  digitalWrite(err3, err3State);
}

void p_error(char* msg) {
  //Serial.println(msg);
}

void send_error(unsigned short e) {
  //Serial.println(e);
}

void loop() {
  struct msg rcv;
  if(Serial.available() > 0) {
    delay(10);//3 bytes at 9600 = 2.5ms but wait 10
    unsigned int ret;
    ret = read_block((char*)&rcv,sizeof(rcv));
    if(ret) {
      //Serial.print(ret);
      return;
    }
    if(rcv.secret != SHARED_KEY) {
      //Serial.print(ERROR_INVALID_KEY);
      digitalWrite(err2, HIGH);
    } else {
      digitalWrite(err3, err3State);
      err3State = !err3State;
      _servo(rcv.servo); 
      _motor(rcv.motor);

      // sending feedback to NUC
      Serial.print(12345);
      //Serial.print(SUCCESS_ACK);
    }
  }             
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

int read_block(char* ptr, int size) {
  if(Serial.available() > size && Serial.available() % size == 0) {
    //Serial.println("too many bytes, flushing");
    while(Serial.available() > size){
      //Serial.print(Serial.read());
      //Serial.print("|");
    } 
      //Serial.println("");
    //dump();  
  } else if (Serial.available() % size != 0){
//    //Serial.println("too many bytes, flushing");
//    while(Serial.available() > size){
//      //Serial.print(Serial.read());
//      //Serial.print("|");
//    } 
//      //Serial.println("");
      return ERROR_INSUFFICIENT_BYTES;
  }
  
  int i;
  for(i=0;i<size;i++) {
    if(Serial.available() == 0)
      break;
    *ptr = Serial.read();
    ptr++;
  }

  return 0;
}

void dump() {
  while(Serial.available() > 0)
    Serial.read();
}
