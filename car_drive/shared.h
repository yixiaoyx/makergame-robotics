#ifndef SHARED_H
#define SHARED_H
#pragma pack(1)

#define SHARED_KEY 'a'
#define SERVO 1
#define MOTOR 2

const unsigned char SUCCESS_ACK  = 0;
const unsigned char ERROR_INVALID_KEY = 1;
const unsigned char ERROR_INVALID_TYPE = 2;
const unsigned char ERROR_INSUFFICIENT_BYTES = 3;

struct msg {
  char secret;
  char type;
  char servo;
  char motor;
};

struct response {
  unsigned char secret;
  unsigned char value;
};

#endif
