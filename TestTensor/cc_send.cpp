/*id cc_send(uint_16 address, unsigned char* data)
{
  //calculate CRC
  unsigned char crc = ((unsigned char)(address >> 8))^
                      ((unsigned char)(address));
  for(int i = 0; i < 8; i++)
  {
    crc = crc ^ (data[i]);
  }
  //send data to PC
  Serial.write(0xE7); //start byte
  Serial.write((unsigned char)(address >> 8)); // Hi address
  Serial.write((unsigned char)(address)); // Low address
  for(i=0; i < 8; i++)
  {
    Serial.write(data[i]); //Writing 8 byte data
  }
  Serial.write(crc); //Writing crc 
}
}*/
