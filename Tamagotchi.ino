#include <U8g2lib.h>
#include "sprites.h"

const uint8_t CLOCK_PIN = 13,
              DATA_PIN = 11,
              CE_PIN = 10,
              DC_PIN = 9,
              RESET_PIN = 8;

const uint8_t BL_PIN = 4,
              BTN_A_PIN = 5,
              BTN_B_PIN = 6,
              BTN_C_PIN = 7;

//Definition of display to use, here is Nokia 5110 84x48
U8G2_PCD8544_84X48_1_4W_HW_SPI u8g2 = 
  U8G2_PCD8544_84X48_1_4W_HW_SPI(U8G2_R0, CE_PIN, DC_PIN, RESET_PIN);

//Initial Screen
const static unsigned char bits[] = {
   0x30, 0x30, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x30, 0x00,
   0x04, 0x00, 0x00, 0x40, 0x00, 0x00, 0x60, 0x30, 0x00, 0x04, 0x00, 0x00,
   0x40, 0x00, 0x00, 0x60, 0x30, 0x00, 0x04, 0x00, 0x00, 0x40, 0x00, 0x00,
   0x60, 0x18, 0x03, 0x08, 0x00, 0x00, 0x40, 0x00, 0x00, 0xc0, 0x18, 0x03,
   0x08, 0x00, 0x00, 0x40, 0x00, 0x00, 0xc0, 0x18, 0xc0, 0x11, 0x00, 0xe0,
   0x41, 0x70, 0x00, 0x80, 0x18, 0xc0, 0x13, 0x00, 0x01, 0x43, 0x40, 0x00,
   0x80, 0x19, 0x6b, 0xa2, 0x01, 0x01, 0x42, 0xc0, 0x00, 0x80, 0x19, 0x7b,
   0x60, 0x00, 0xc1, 0x43, 0xb8, 0x00, 0x00, 0x1b, 0x73, 0x30, 0x20, 0x22,
   0x42, 0x88, 0x00, 0x00, 0x1f, 0x63, 0x5c, 0x20, 0x22, 0x42, 0x88, 0x00,
   0x00, 0x1e, 0xe3, 0x40, 0x20, 0x22, 0x42, 0xc8, 0x00, 0x00, 0x0e, 0xc3,
   0x40, 0x20, 0x22, 0x42, 0x78, 0x01, 0x00, 0x0c, 0xc7, 0x80, 0x20, 0xe1,
   0x87, 0x00, 0x03, 0x00, 0x04, 0xc7, 0x80, 0x40, 0x01, 0x0c, 0x00, 0x00,
   0x00, 0x00, 0x06, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06,
   0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
   0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x88, 0x00, 0x00,
   0x00, 0xc0, 0x01, 0x00, 0x08, 0x00, 0x88, 0x00, 0x00, 0x00, 0xc1, 0x01,
   0x00, 0x08, 0x00, 0x88, 0x00, 0x40, 0x00, 0x81, 0x01, 0x00, 0x08, 0x00,
   0x88, 0x00, 0x80, 0x00, 0x81, 0x01, 0x00, 0x08, 0x00, 0x88, 0x00, 0x80,
   0x00, 0x89, 0x01, 0xe0, 0x08, 0x00, 0x88, 0x00, 0x00, 0x01, 0x87, 0x01,
   0xf6, 0x7c, 0x00, 0x88, 0x00, 0x1b, 0xc1, 0x81, 0x07, 0x37, 0x08, 0x00,
   0x88, 0x0c, 0x2c, 0x01, 0x01, 0x9f, 0xed, 0x09, 0x06, 0x88, 0x12, 0x04,
   0x31, 0x01, 0xbb, 0xcd, 0x1b, 0x0d, 0x49, 0x22, 0x08, 0x49, 0x01, 0xb3,
   0x06, 0x16, 0x11, 0x3e, 0x62, 0x08, 0x49, 0x01, 0xa3, 0x03, 0x16, 0x26,
   0x08, 0x46, 0x08, 0x49, 0x01, 0x33, 0xdf, 0x14, 0x1c, 0x00, 0x3c, 0x08,
   0x31, 0x01, 0x37, 0xce, 0x36, 0x00, 0x00, 0x00, 0x80, 0x01, 0x05, 0x3e,
   0xc0, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x80, 0x03, 0x00
   };

//Names of menu options, the sprites are located on sprites.h
static const char menu_names[][10] = {
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
const int menu_len = 11;          //lenght of menu array, important for loops

//Global Variables
unsigned char bits_buff[100];     //menu sprite buffer variable
unsigned char selected_bits[100]; //temporal sprite of selected menu option
int selected = 0;                 //current menu option selected
int sub_selected = 0;
bool backlight = true;            //status of backlight
int contrast = 135;
int mode = 0;                     /* stage of game:
                                   * 0: initial screen
                                   * 1: main menu view
                                   * 11: settings
                                   */

void setup() {
  pinMode(BL_PIN, OUTPUT);
  pinMode(BTN_A_PIN, INPUT_PULLUP);
  pinMode(BTN_B_PIN, INPUT_PULLUP);
  pinMode(BTN_C_PIN, INPUT_PULLUP);  
  u8g2.begin();
  u8g2.setContrast(contrast);
}

void loop() {
  //Write the backlight status
  digitalWrite(BL_PIN, backlight?HIGH:LOW);

  //Configure graphics
  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.setFontPosTop();
  u8g2.setContrast(contrast);
  //Manage graphics
  u8g2.firstPage();
  do { draw(); } while ( u8g2.nextPage() );

  //Read Button A Input
  if (digitalRead(BTN_A_PIN) == LOW){
    switch (mode){
      case 0:
        mode = 1;
        break;
      case 1:
        selected--;
        if (selected < 0 ) selected = 0;
        break;
      case 11:
        sub_selected--;
        if (sub_selected < 0 ) sub_selected = 0;
        break;
    }
  }
  //Read Button B Input
  if (digitalRead(BTN_B_PIN) == LOW){
    switch (mode){
      case 0:
        mode = 1;
        break;
      case 1:
        mode = selected + 1;
        break;
      case 11:
        if (sub_selected == 0) backlight = !backlight;
        if (sub_selected == 1) {
          contrast+=5;
          if (contrast > 200){
            contrast = 100;
            }
        }
        break;
      
    } 
  }
  //Read Button C Input
  if (digitalRead(BTN_C_PIN) == LOW){
    switch (mode){
      case 0:
        mode = 1;
        break;
      case 1:
        selected++;
        if (selected >= menu_len ) selected = menu_len - 1;
        break;
      case 11:
        int sub_len = 2;
        sub_selected++;
        if (sub_selected >= sub_len ) sub_selected = sub_len -1;
        break;
    }
  }
  //underclocking the arduino 
  delay(180);
}

//Main Draw Function
void draw() {
  switch (mode){
  case 0:
    //Render first screen
    //  full: 5x7 w:70 h:36
    //  mini: 29x12 w:22 h:27 
    u8g2.drawXBM( 5, 7, 70, 36, bits);
    break;
  case 1:
    //Render main menu
    draw_menu();
    //Render the help text
    draw_help();
    break;
  case 11:
    //Render main menu
    draw_menu();
    //Render options
    draw_options();
    break;
  }
}

//Main Menu draw function
void draw_menu(){
  //menu separator
  u8g2.drawLine(0, 10, 84, 10);
  //load the inverted sprite of selected optioon
  build_selected();
  //define menu render offset (for scrolling)
  int offset = 0;
  int max_offset = menu_len - 8;
  if (selected > 4)
    offset += selected-4;
  if (offset > max_offset )
    offset = max_offset;
  //render menu options
  for(int i = offset;i<menu_len;i++){
    //load sprites from PROGMEM
    memcpy_P(bits_buff, menu[i], 100);
    //print each menu option visible
    u8g2.drawXBM( (i-offset)*10, 0, 10, 10, selected == i? selected_bits:bits_buff);
  }
}

//Options draw function
void draw_options(){
  //first option, backlight configuration
  u8g2.setCursor(0, 12);
  u8g2.print(sub_selected == 0?">":"");
  u8g2.print("Lumo: ");
  u8g2.print(backlight?"on":"off");
  //second option, contrast configuration
  u8g2.setCursor(0, 20);
  u8g2.print(sub_selected == 1?">":"");
  u8g2.print("Kontrasto: ");
  u8g2.print(contrast);
  }

//draws help text in the last line
void draw_help(){
  u8g2.drawStr(0,40,menu_names[selected]);
}

//Prepare the selected option to be rendered
void build_selected(){
  //read sprite from PROGMEM
  memcpy_P(bits_buff, menu[selected], 100);
  //invert each bit
  for(int i=0;i<100;i++){
    selected_bits[i] = ~bits_buff[i];
    }
  }
