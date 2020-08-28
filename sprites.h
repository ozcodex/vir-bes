#ifndef sprites_h
#define sprites_h

const static PROGMEM unsigned char menu[][100] = {
  {0x30, 0x00, 0x48, 0x00, 0x84, 0x00, 0x02, 0x01, 0xff, 0x03, 0x84, 0x00,
   0x84, 0x00, 0x84, 0x00, 0xfc, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x78, 0x00, 0x84, 0x00, 0x32, 0x01, 0x02, 0x01, 0x32, 0x01,
   0x32, 0x01, 0xb4, 0x00, 0x78, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x4e, 0x01, 0x4e, 0x01, 0xce, 0x01, 0x84, 0x00, 0x84, 0x00,
   0x84, 0x00, 0x84, 0x00, 0x84, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x1c, 0x00, 0x22, 0x00, 0x22, 0x00, 0x22, 0x00, 0x14, 0x00,
   0x88, 0x00, 0x48, 0x00, 0x30, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0xe0, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0xfe, 0x01,
   0x04, 0x01, 0x08, 0x01, 0xf0, 0x00, 0x00, 0x00},
  {0xe0, 0x01, 0x80, 0x00, 0x40, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x1e, 0x00,
   0x08, 0x00, 0x04, 0x00, 0x1e, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x40, 0x00, 0x20, 0x00, 0x10, 0x00,
   0x08, 0x00, 0x3e, 0x00, 0x2a, 0x00, 0x00, 0x00},
  {0xdc, 0x00, 0x22, 0x01, 0x11, 0x02, 0x21, 0x02, 0x11, 0x02, 0x21, 0x02,
   0x11, 0x02, 0x79, 0x02, 0x87, 0x03, 0x00, 0x00},
  {0x78, 0x00, 0x48, 0x00, 0xfc, 0x00, 0x02, 0x01, 0x32, 0x01, 0x7a, 0x01,
   0x32, 0x01, 0x02, 0x01, 0xfe, 0x01, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x86, 0x01, 0x4a, 0x01, 0x32, 0x01,
   0x02, 0x01, 0x02, 0x01, 0xfe, 0x01, 0x00, 0x00},
  {0xfc, 0x00, 0x02, 0x01, 0x7a, 0x01, 0x02, 0x01, 0x7a, 0x01, 0x02, 0x01,
   0x7a, 0x01, 0x02, 0x01, 0xfc, 0x00, 0x00, 0x00}
};

const static PROGMEM unsigned char initial[][100] = {
  {0x30, 0x00, 0x70, 0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0xc0, 0x00,
   0xc0, 0x00, 0x80, 0x00, 0x80, 0x01, 0x80, 0x01},
  {0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0xc6, 0x00, 0xc6, 0x00,
   0x06, 0x00, 0x06, 0x00, 0xc6, 0x02, 0xc6, 0x02},
  {0x40, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x01,
   0x1c, 0x02, 0x3c, 0x02, 0x26, 0x00, 0x07, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x03, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xe0, 0x01, 0x01, 0x03, 0x01, 0x02, 0xc1, 0x03},
  {0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00,
   0x10, 0x00, 0x10, 0x00, 0x10, 0x02, 0x10, 0x02},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
   0x04, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x08, 0x00},
  {0x00, 0x03, 0x00, 0x03, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x88, 0x00},
  {0xc6, 0x00, 0xc7, 0x00, 0xc7, 0x00, 0xc3, 0x00, 0xc3, 0x01, 0xc1, 0x01,
   0x80, 0x01, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00},
  {0x07, 0x02, 0x86, 0x03, 0x0e, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x81, 0x00, 0x82, 0x00, 0x82, 0x00, 0x82, 0x00, 0x84, 0x00, 0x04, 0x01,
   0x08, 0x03, 0x08, 0x00, 0x10, 0x00, 0x10, 0x00},
  {0x22, 0x02, 0x22, 0x02, 0x22, 0x02, 0x22, 0x02, 0xe1, 0x03, 0x01, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x00, 0x21, 0x00, 0x03, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x08, 0x00, 0x0c, 0x00, 0x17, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x08, 0x01, 0x08, 0x01, 0x08, 0x01, 0x08, 0x01, 0x08, 0x01, 0x08, 0x01,
   0x08, 0x01, 0x08, 0x01, 0x08, 0x01, 0x08, 0x01},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x02, 0x06, 0x03, 0x09, 0x01},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x08, 0x00,
   0x10, 0x00, 0x11, 0x00, 0x12, 0x00, 0x10, 0x03},
  {0x00, 0x00, 0x80, 0x03, 0x88, 0x03, 0x08, 0x03, 0x08, 0x03, 0x48, 0x03,
   0x38, 0x03, 0x0e, 0x03, 0x08, 0x02, 0x08, 0x02},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x03, 0x83, 0x03, 0xcf, 0x02, 0xdd, 0x02},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00,
   0x3c, 0x02, 0x1d, 0x00, 0x79, 0x00, 0xf1, 0x00},
  {0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00,
   0x0f, 0x00, 0x01, 0x00, 0x61, 0x00, 0xd3, 0x00},
  {0x89, 0x00, 0x7e, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x11, 0x02, 0x31, 0x02, 0x23, 0x02, 0x1e, 0x02, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x10, 0x03, 0x18, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x09, 0x02, 0x09, 0x02, 0x09, 0x02, 0x08, 0x02, 0x28, 0x00, 0x30, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0xd9, 0x03, 0xd9, 0x01, 0x99, 0x03, 0x1f, 0x03, 0x1f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0xc0, 0x01, 0x82, 0x01, 0x33, 0x01, 0xb1, 0x01, 0xf0, 0x01, 0xe0, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x12, 0x01, 0x62, 0x02, 0xc2, 0x01, 0x06, 0x00, 0x0c, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};
#endif