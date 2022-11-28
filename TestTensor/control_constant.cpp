#include "control_constant.h"


/**
 * Union 
 */


/**
 * Queue 
 */
Queue<void(*)(Data&)> handlerFun;
Queue<uint16_t> handlerAddresses;



/**
 * init function 
 */

void cc_init(int speed)
{
  Serial.begin(speed);
  Serial.setTimeout(5);
 
}

/**
 * Sends array data with address to UART 
 */
 
void cc_send_to_pc(uint16_t address, unsigned char* data)
{    Serial.println("Hello World");
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
    //for(int i = 0; i > 1; i--){
    //Serial.write(data[i-1]);   
    
    Serial.write(crc);
}

/**
 * Sends uint32 data with address to UART 
 */
 
void cc_send_uint32(uint16_t address, uint32_t data) //no pointer here
{
  Data unionData;
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
  Data unionData;
  unionData.uintData[0] = 0;
  unionData.floatData[1] = data;
 
  cc_send_to_pc(address,unionData.byteData);
  return;
}

/**
 *Send double data with address to UART 
 */
 
void cc_send_double(uint16_t address, double data)
{
  Data unionData;
  unionData.doubleData = data;
  
  
 cc_send_to_pc(address, unionData.byteData);
  return;
}

/**
 *Send int_32 data with address to UART 
 */

void cc_send_int32(uint16_t address, int32_t data) //no pointer here
{
  Data unionData;
  unionData.intData[0] = 0;
  unionData.intData[1] = 0;
  unionData.intData[1] = data;
  cc_send_to_pc(address, unionData.byteData);
}


void action(uint16_t address, Data& data)
{
   int index = handlerAddresses.indexOf(address);
   if(index >=0) { handlerFun[index](data); }
}


void stateMachine(unsigned char rxByte)
{
  static int state = States::WAIT_START_BYTE;
  static uint16_t address;
  static Data data;
  static int data_byte_id; 
  
  switch(state) {
    case States::WAIT_START_BYTE: {
      if(rxByte == 0xE7) { 
        state = States::WAIT_ADDRESS_1_BYTE;
      }
    } break;
    case States::WAIT_ADDRESS_1_BYTE: {
      address = (uint16_t)rxByte << 8;
      state = States::WAIT_ADDRESS_2_BYTE;
    } break;
    case States::WAIT_ADDRESS_2_BYTE: {
      address = address | ((uint16_t)rxByte);
      state = States::WAIT_DATA_1_BYTE;
    } break;
    case States::WAIT_DATA_1_BYTE: {
      data.byteData[7] = rxByte;
      state = States::WAIT_DATA_2_BYTE;
    } break;
    case States::WAIT_DATA_2_BYTE: {
      data.byteData[6] = rxByte;
      state = States::WAIT_DATA_3_BYTE;
    } break;
    case States::WAIT_DATA_3_BYTE: {
      data.byteData[5] = rxByte;
      state = States::WAIT_DATA_4_BYTE;
    } break;
    case States::WAIT_DATA_4_BYTE: {
      data.byteData[4] = rxByte;
      state = States::WAIT_DATA_5_BYTE;
    } break;
    case States::WAIT_DATA_5_BYTE: {
      data.byteData[3] = rxByte;
      state = States::WAIT_DATA_6_BYTE;
    } break;
    case States::WAIT_DATA_6_BYTE: {
      data.byteData[2] = rxByte;
      state = States::WAIT_DATA_7_BYTE;
    } break;
    case States::WAIT_DATA_7_BYTE: {
      data.byteData[1] = rxByte;
      state = States::WAIT_DATA_8_BYTE;
    } break;
    case States::WAIT_DATA_8_BYTE: {
      data.byteData[0] = rxByte;
      state = States::CHECK_CRC;
    } break;
    case States::CHECK_CRC: {
      unsigned char crc = ((unsigned char)(address >> 8)) ^ ((unsigned char)(address));
      for(int i = 0; i < 8; i++) {
        crc = crc ^ (data.byteData[i]);                 
      }
      if(rxByte == crc) {
        action(address, data);
      }
      state = States::WAIT_START_BYTE;
    } break;
  }
}



void cc_addHandler(uint16_t address, void (*fun)()) {
  handlerAddresses.push(address);
  handlerFun.push(fun); 
  
  //handlerFun.pop()();
}
