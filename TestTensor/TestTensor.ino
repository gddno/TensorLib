#include <HX711.h>
#include "control_constant.h"

HX711 scale;
int flash_status = 0;

const int LOADCELL_DOUT_PIN = A1;                         
const int LOADCELL_SCK_PIN = A2;
const int CC_UART_SPEED = 9600;

void CCTensor0001(Data& data) {
  digitalWrite(13,HIGH);
  //delay(5000);
}

void CCTensor0002(Data& data) {
  digitalWrite(13,LOW);
  //delay(5000);
}

void Led13Read(Data& data) {
  cc_send_int32(0x0003, flash_status);
}

void Led13Write(Data& data) {
  flash_status = data.byteData[0];
}

void setup(){
      pinMode(13,OUTPUT);
      digitalWrite(13,LOW);
      cc_init(CC_UART_SPEED);
      
      cc_addHandler(0x0001, CCTensor0001);
      cc_addHandler(0x0002, CCTensor0002);
      cc_addHandler(0x0003, Led13Read);
      cc_addHandler(0x4003, Led13Write);
                                  
      scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
      
}

void loop(){
  long reading = scale.read_average(5);
  static int counter = 0;
  if(flash_status == 1 && counter  >= 255) {
    if(digitalRead(13)) {
      digitalWrite(13,LOW);
    } else {
      digitalWrite(13,HIGH);
    }
    counter = 0;
  }
  counter++;
  //cc_send_int32(0x0010, count);
  cc_send_float(0x0002, 13.14);
}
    
