#include "tensor.h" 
#include <HX711.h> 


HX711 scale;
                                        

const int LOADCELL_DOUT_PIN = A1;                         
const int LOADCELL_SCK_PIN = A2;                           
                       

void cc_one() {                                         
  Serial.begin(57600);                                  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);     
 
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
    for(int i = 0; i < 8; i++) {
      Serial.write(data[i]);                 
    }
    Serial.write(crc);  // CRC
}

/**
 * Sends uint32 data with address to UART 
 */
void cc_send_uint32(uint16_t address, uint32_t data) //no pointer here
{
  unsigned char txdata[8];
  txdata[0] = 0x00;
  txdata[1] = 0x00;
  txdata[2] = 0x00;
  txdata[3] = 0x00;
  txdata[4] = (unsigned char)(data >> 24);
  txdata[5] = (unsigned char)(data >> 16);
  txdata[6] = (unsigned char)(data >> 8);
  txdata[7] = (unsigned char)(data);
  cc_send_to_pc(address, txdata);
  return;
}

void action()                                       
   {                            
    long reading = scale.read_average(10);
    //Serial.println(reading);
   cc_send_uint32(0x0001, reading);
 
    //cc_send_uint32(0x0003, 3.14);
    
  }
 
