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

static const char food_names[][12] = {
  "supo",
  "ananaso",
  "tasokuko",
  "kokido",
  "hamburgero"
  };
  
//Global Variables
const int menu_len = 11;          //lenght of menu array, important for loops
unsigned long up_time = 0;        //time elapsed since turn-on
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
                                   * 2: status view
                                   * 3: food view
                                   * 11: settings
                                   */
//Virbes data:
//status variables
int hungry = 7;   // max: 30
int joy = 15;     // max: 30 
int age = 23;     // max: 999
int weight = 85;  // max: 999
int health = 3;   // max: 6

void setup() {
  pinMode(BL_PIN, OUTPUT);
  pinMode(BTN_A_PIN, INPUT_PULLUP);
  pinMode(BTN_B_PIN, INPUT_PULLUP);
  pinMode(BTN_C_PIN, INPUT_PULLUP);  
  u8g2.begin();
  u8g2.setContrast(contrast);
  up_time = millis(); //caution: max=4294967295 (49 days 17 hours)
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
  read_buttons();

  //Trigger Button A Action
  if (pull_down[0] && btn_clk_counter[0] == 1){
    switch (mode){
      case 0:
        back_to_main();
        break;
      case 1:
      case 2:
        selected = rotate_sel_L(0,selected);
        break;
      case 3:
      case 11:
        sub_selected = rotate_sel_L(0,sub_selected);
        break;
    }
  }
  //Trigger Button B Action
  if (pull_down[1]  && btn_clk_counter[1] == 1){
    switch (mode){
      case 0:
        back_to_main();
        break;
      case 1:
      case 2:
        select_menu_option();
        break;
      case 3:
        eat_food(sub_selected);
        back_to_main();
        break;
      case 11:
        change_settings(sub_selected);
        break;
      
    } 
  }
  //Trigger Button C Action
  if (pull_down[2]  && btn_clk_counter[2] == 1){
    switch (mode){
      case 0:
        back_to_main();
        break;
      case 1:
      case 2:
        selected = rotate_sel_R(menu_len - 1,selected);
        break;
      case 3:
        sub_selected = rotate_sel_R(4,sub_selected);
      break;
      case 11:
        sub_selected = rotate_sel_R(2,sub_selected);
      break;
    }
  }
}

//Main Draw Function
void draw() {
  switch (mode){
  case 0:
    draw_initial();
    break;
  case 1:
    draw_menu(selected);
    draw_virbes();
    draw_help();
    break;
  case 2:
    draw_menu(selected);
    draw_status();
    draw_help();
    break;
  case 3:
    draw_menu(selected);
    draw_foods(sub_selected);
    draw_help();
    break;
  case 11:
    draw_menu(selected);
    draw_options(sub_selected);
    break;
  }
}
