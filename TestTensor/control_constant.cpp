#include "control_constant.h"


/**
 * init function 
 */

void cc_init(int speed)
{
 Serial.begin(speed);
}

/**
 * Sends array data with address to UART 
 */
 
void cc_send_to_pc(uint16_t address, unsigned char* data)
{
    // calcuilate CRC
    unsigned char crc = ((unsigned char)(address >> 8)) ^
                        ((unsigned char)(address));
    for(int i = 0; i < 8; i++) {
      crc = crc ^ (data[i]);                 
    }
    

    // send data to PC
    Serial.write(0xE7); //start byte
    Serial.write((unsigned char)(address >> 8));    //Address Hi
    Serial.write((unsigned char)(address));         //Address lo

 
    
    for(int i = 0; i < 4; i++) {
      Serial.write(data[3-i]);                 
    }
    for(int i = 0; i < 4; i++) {
      Serial.write(data[7-i]);                 
    }    
    Serial.write(crc);
}

/**
 * Sends uint32 data with address to UART 
 */
 
void cc_send_uint32(uint16_t address, uint32_t data) //no pointer here
{
    union Data {
    char byteData[8];
    uint32_t uintData[2];
    float floatData[2];
  } unionData;
  unionData.uintData[0] = 0;
  unionData.uintData[1] = 0;
  unionData.uintData[1] = data;
  cc_send_to_pc(address,unionData.byteData);
}

/**
 * Sends float data with address to UART 
 */

void cc_send_float(uint16_t address,float data)
{
  union Data {
    char byteData[8];
    uint32_t uintData[2];
    float floatData[2];
  } unionData;
  unionData.uintData[0] = 0;
  unionData.uintData[1] = 0;
  unionData.floatData[1] = data;
 
  cc_send_to_pc(address,unionData.byteData);
  return;
}


 
