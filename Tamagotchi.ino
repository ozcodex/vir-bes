#include <U8g2lib.h>
#include "sprites.h"

const uint8_t CLOCK_PIN = 13,
              DATA_PIN = 11,
              CS_PIN = 10,
              DC_PIN = 9,
              RESET_PIN = 8;

U8G2_PCD8544_84X48_1_4W_HW_SPI u8g2 = 
  U8G2_PCD8544_84X48_1_4W_HW_SPI(U8G2_R0, CS_PIN, DC_PIN, RESET_PIN);

const static unsigned char bits[] = {
   0x00, 0x02, 0x00, 0x01, 0x02, 0x00, 0x02, 0x02, 0x00, 0x02, 0x01, 0x00,
   0x02, 0x11, 0x00, 0x04, 0x01, 0x00, 0x84, 0x00, 0x00, 0x88, 0x00, 0x1c,
   0x88, 0x10, 0x02, 0x90, 0x90, 0x02, 0x90, 0x10, 0x03, 0x50, 0x10, 0x02,
   0x60, 0x10, 0x02, 0x60, 0x10, 0x04, 0x42, 0x10, 0x04, 0x44, 0x10, 0x04,
   0x04, 0x20, 0x00, 0x04, 0x20, 0x00, 0x04, 0x00, 0x07, 0x0c, 0x18, 0x01,
   0x78, 0x24, 0x0e, 0xc8, 0x24, 0x18, 0x88, 0x15, 0x10, 0x08, 0x0d, 0x20,
   0x88, 0xf1, 0x24, 0x90, 0x00, 0x22, 0xf0, 0x00, 0x1e
   };

static char menu_names[][10] = {
  "cxefa",
  "stato",
  "mangxo",
  "ludo",
  "dusxu",
  "dormu",
  "purigu",
  "lernu",
  "kuracilo",
  "posxto",
  "agordo"
  };

int menu_len = 11;

unsigned char bits_buff[100];
unsigned char selected_bits[100];
int mode = 0;
int selected = 0;
bool backlight = true;

void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);  
  u8g2.begin();
  u8g2.setContrast(135);
}

void loop() {
  digitalWrite(4, backlight?HIGH:LOW);
  // put your main code here, to run repeatedly:
  u8g2.firstPage();
  do { draw(); } while ( u8g2.nextPage() );

    if (digitalRead(5) == LOW){
        if( mode == 0) mode = 1; else{
        selected--;
        if (selected < 0 ) selected = 0; }
      }
    if (digitalRead(6) == LOW){
        if( mode == 0) mode = 1;
        
      }
    if (digitalRead(7) == LOW){
        if( mode == 0) mode = 1; else{
        selected++;
        if (selected >= menu_len ) selected = menu_len - 1; }
      }
  delay(150);
}

void draw() {
  switch (mode){
  case 0:
    //first screen
    //u8g2.drawXBM( 5, 7, 70, 36, bits);
    u8g2.drawXBM( 29, 12, 22, 27, bits); //mini
    break;
  case 1:
    //main menu
    draw_menu();
    break;
  }
}

void draw_menu(){
  u8g2.drawLine(0, 10, 84, 10);
  build_selected();
  int offset = 0;
  int max_offset = menu_len - 8;
  if (selected > 4)
    offset += selected-4;
  if (offset > max_offset )
    offset = max_offset;
  for(int i = offset;i<menu_len;i++){
    memcpy_P(bits_buff, menu[i], 100);
    u8g2.drawXBM( (i-offset)*10, 0, 10, 10, selected == i? selected_bits:bits_buff);
  }
  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.setFontPosTop();
  u8g2.drawStr(0,40,menu_names[selected]);
}

void build_selected(){
  memcpy_P(bits_buff, menu[selected], 100);
  for(int i=0;i<100;i++){
    selected_bits[i] = ~bits_buff[i];
    }
  }
