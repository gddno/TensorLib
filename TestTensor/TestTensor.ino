#include <HX711.h>
#include "tensor.h"

HX711 scale;

const int LOADCELL_DOUT_PIN = A1;                         
const int LOADCELL_SCK_PIN = A2;
   
void setup(){
      Serial.begin(57600);                                  
      scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    
}

void loop(){
     long reading = scale.read_average(10);
     cc_send_uint32(0x0001, 2000);
     cc_send_float(0x0003, 3.14);
  delay(100);
}
    
