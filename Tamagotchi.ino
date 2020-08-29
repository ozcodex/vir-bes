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
      case 2:
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
      case 2:
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
        if (sub_selected == 2) {
          mode = 1;
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
      case 2:
        selected++;
        if (selected >= menu_len ) selected = menu_len - 1;
        break;
      case 11:
        int sub_len = 3;
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
    draw_initial();
    break;
  case 1:
    //Render main menu
    draw_menu();
    //Render the help text
    draw_help();
    break;
  case 2:
    draw_menu();
    draw_status();
    draw_help();
    break;
  case 11:
    draw_menu();
    draw_options();
    break;
  }
}

//Draw initial screen
void draw_initial(){
  int x = 5;
  int y = 7;
  for(int i=0; i < 7; i++){
    for(int j=0; j < 4; j++){
      //read sprite from PROGMEM
      memcpy_P(bits_buff, initial[i+j*7], 100);
      //draw sprite
      u8g2.drawXBM( x+i*10, y+j*10, 10, 10, bits_buff);
    }
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
//Status of tamagotchi
void draw_status(){
  //Draw text
  u8g2.setCursor(3, 11);
  u8g2.print("sata");
  u8g2.setCursor(39, 12);
  u8g2.print("agxo");
  u8g2.setCursor(63, 12);
  u8g2.print("pezo");
  u8g2.setCursor(3, 25);
  u8g2.print("gxoja");
  u8g2.setCursor(39, 29);
  u8g2.print("sana");
  //Draw Numbers
  u8g2.setCursor(42, 20);
  u8g2.print("999");
  u8g2.setCursor(65, 20);
  u8g2.print("999");
  //Draw lines
  u8g2.drawLine(2, 20, 2, 23);
  u8g2.drawLine(3, 23, 33, 23);
  u8g2.drawLine(2, 34, 2, 37);
  u8g2.drawLine(3, 37, 33, 37);
  //draw boxes
  u8g2.drawRFrame(37,13,23,16,3);
  u8g2.drawRFrame(61,13,23,16,3);
  //draw bars
  u8g2.drawBox(4,20,30,2);
  u8g2.drawBox(4,34,30,2);

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
  
  //last option, exit
  u8g2.setCursor(0, 28);
  u8g2.print(sub_selected == 2?">":"");
  u8g2.print("Forlasi!");
  }

//draws help text in the last line
void draw_help(){
  //draw black rectangle
  u8g2.drawBox(0,40,84,8);
  u8g2.setFontMode(1);
  u8g2.setDrawColor(0);
  u8g2.setCursor(1, 40);
  u8g2.print(menu_names[selected]);
  u8g2.setFontMode(0);
  u8g2.setDrawColor(1);
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
