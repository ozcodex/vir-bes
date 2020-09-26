#ifndef sprites_h
#define sprites_h

const static PROGMEM unsigned char lex_face[][8] = {
  //standby
  {0x00, 0xee, 0x88, 0x00, 0x38, 0x10, 0x28, 0x00},
  {0x00, 0x00, 0xee, 0x88, 0x00, 0x38, 0x10, 0x28},
  //eat
  {0x00, 0x44, 0xaa, 0x00, 0x00, 0x38, 0x38, 0x00},
  {0x00, 0x00, 0x82, 0x6c, 0x82, 0x00, 0x38, 0x00},
  //play
  {},
  {},
};

const static PROGMEM byte lex[][18] = {
  //standby 1
  {0x28, 0x48, 0x58, 0x68, 0x78, 0x81, 0x88, 0x90, 0x90, 0x90, 0x90, 0x90,
   0x98, 0xa5, 0xb5, 0xb5, 0xc5, 0xb6},
  //standby 2
  {0x00, 0x28, 0x48, 0x58, 0x68, 0x78, 0x81, 0x88, 0x90, 0x90, 0x90, 0x90,
   0x98, 0xa5, 0xb5, 0xb5, 0xc5, 0xb6},
};

#endif
