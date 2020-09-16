#include <Wire.h>

#define DEVICE "24L16B"
#define DEVICE_BASE_ADDRESS 0x50
#define DEVICE_BLOCKS 8
#define DEVICE_BLOCK_SIZE 256

void setupEEPROM(){
  Wire.begin();
 }

byte readByteFromEEPROM(byte block, byte address){
   Wire.beginTransmission(DEVICE_BASE_ADDRESS+block);
   Wire.write(int(address));
   Wire.endTransmission(true);
  
   Wire.requestFrom(int(DEVICE_BASE_ADDRESS + block), 1);
  
   if (Wire.available())
     return Wire.read();
}


void writeByteToEEPROM(byte block, byte address, byte data){
  Wire.beginTransmission(DEVICE_BASE_ADDRESS+block);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission(true);
  delay(10);
}

void readSpriteFromEEPROM(byte block, byte address, int data_size, byte* output){
   Wire.beginTransmission(DEVICE_BASE_ADDRESS+block);
   Wire.write(int(address));
   Wire.endTransmission(true);

  for( int i = 0; i < data_size; i++ ){
    Wire.requestFrom(int(DEVICE_BASE_ADDRESS + block), 1);
    if (Wire.available())
    output[i] = Wire.read();
  }
   
}
