#ifndef CONTROL_CONSTANT_H
#define CONTROL_CONSTANT_H

#include <Arduino.h>
#include "FIFO.cpp"

//extern MySerial mySerial;

union Data {
  unsigned char byteData[8];
  uint32_t uintData[2];
  int32_t intData[2];
  float floatData[2];
  double doubleData;
};
  
enum States
{
  WAIT_START_BYTE,
  WAIT_ADDRESS_1_BYTE,
  WAIT_ADDRESS_2_BYTE,
  WAIT_DATA_1_BYTE,
  WAIT_DATA_2_BYTE,
  WAIT_DATA_3_BYTE,
  WAIT_DATA_4_BYTE,
  WAIT_DATA_5_BYTE,
  WAIT_DATA_6_BYTE,
  WAIT_DATA_7_BYTE,
  WAIT_DATA_8_BYTE,
  CHECK_CRC
};


void cc_init(int speed);
void cc_send_to_pc(uint16_t address, unsigned char* data);
void cc_send_uint32(uint16_t address, uint32_t data);
void cc_send_int32(uint16_t address, int32_t data);
void cc_send_float(uint16_t address,float data);
void cc_send_double(uint16_t address, double data);
void reception_data(uint8_t number_interrupt);

void action(uint16_t address, Data& data);
void stateMachine(unsigned char rxByte);
void cc_addHandler(uint16_t address, void (*fun)());


extern void serialEventRun(void)
{   
    while(Serial.available()){
      unsigned char rxByte;
      Serial.readBytes(&rxByte,1);
      stateMachine(rxByte);
  }
}



#endif
