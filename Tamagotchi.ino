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

static const char food_names[][12] = {
  "supo",
  "kokido",
  "ananaso",
  "kuko",
  "hamburgero"
  };
  
//Global Variables
unsigned char bits_buff[400];     //menu sprite buffer variable
unsigned char selected_bits[100]; //temporal sprite of selected menu option
int selected = 0;                 //current menu option selected
int sub_selected = 0;             //for sub menus, the selected option
bool pull_down[] = {false,false,false};
int btn_clk_counter[] = {0,0,0};
//configuration variables
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

  //Read buttons
  pull_down[0] = digitalRead(BTN_A_PIN) == LOW;
  pull_down[1] = digitalRead(BTN_B_PIN) == LOW;
  pull_down[2] = digitalRead(BTN_C_PIN) == LOW;
  //reset buttons
  for( int i = 0; i < 3; i++ ){
    //count while the button is pressed to avoid fast repeating actions
    if (pull_down[i]) {
      btn_clk_counter[i] += 1;
    }else{
      btn_clk_counter[i] = 0;
      }
    //in long press reset counter to take action
    if (btn_clk_counter[i] > 10) btn_clk_counter[i] = 0;
  }

  //Trigger Button A Action
  if (pull_down[0] && btn_clk_counter[0] == 1){
    switch (mode){
      case 0:
        mode = 1;
        break;
      case 1:
      case 2:
        selected--;
        if (selected < 0 ) selected = 0;
        break;
      case 3:
      case 11:
        rotate_sub_sel_L(0);
        break;
    }
  }
  //Trigger Button B Action
  if (pull_down[1]  && btn_clk_counter[1] == 1){
    switch (mode){
      case 0:
        mode = 1;
        break;
      case 1:
      case 2:
        sub_selected = 0;
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
  //Trigger Button C Action
  if (pull_down[2]  && btn_clk_counter[2] == 1){
    switch (mode){
      case 0:
        mode = 1;
        break;
      case 1:
      case 2:
        selected++;
        if (selected >= menu_len ) selected = menu_len - 1;
        break;
      case 3:
        rotate_sub_sel_R(4);
      break;
      case 11:
        rotate_sub_sel_R(2);
      break;
    }
  }
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
    //Render the character
    draw_virbes();
    //Render the help text
    draw_help();
    break;
  case 2:
    draw_menu();
    draw_status();
    draw_help();
    break;
  case 3:
    draw_menu();
    draw_foods();
    draw_help();
    break;
  case 11:
    draw_menu();
    draw_options();
    break;
  }
}
