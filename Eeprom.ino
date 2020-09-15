#include <Wire.h>

#define DEVICE = "24L16B"
#define DATA_SIZE 56
#define DEVICE_BASE_ADDRESS = 0x50;
#define DEVICE_BLOCKS = 8;
#define DEVICE_BLOCK_SIZE = 256;

void setupEEPROM(){
  Wire.begin();
 }

byte readByteFromEEPROM(byte block, byte address){
   Wire.beginTransmission(block);
   Wire.write(int(address));
   Wire.endTransmission(true);
  
   Wire.requestFrom(int(block), 1);
  
   if (Wire.available())
     return Wire.read();
}


void writeByteToEEPROM(byte block, byte address, byte data){
  Wire.beginTransmission(block);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission(true);
  delay(10);
}

void initEEPROM(){
  unsigned int block = 0;
  unsigned int initial_address = 0;
  if (
    initial_address + DATA_SIZE > DEVICE_BLOCK_SIZE ||
    block >= DEVICE_BLOCKS;
    ){
    //prevent memory over flow
    exit(0) 
    }
  for (i = 0; i < DATA_SIZE; i ++){
    
    }
}
