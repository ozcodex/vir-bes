#include <U8g2lib.h>
#include "sprites.h"
#define MENU_LENGTH 12
#define FOOD_MENU_LENGTH 6

//PIN constants definition 
#define CLOCK_PIN 13
#define DATA_PIN 11
#define DC_PIN 10
#define CE_PIN 9
#define RESET_PIN 8

#define BL_PIN 3
#define BTN_A_PIN 6
#define BTN_B_PIN 5
#define BTN_C_PIN 4

#define SCL_PIN A5
#define SDA_PIN A4

//Definition of display to use, here is Nokia 5110 84x48
U8G2_PCD8544_84X48_1_4W_HW_SPI u8g2 = 
  U8G2_PCD8544_84X48_1_4W_HW_SPI(U8G2_R0, CE_PIN, DC_PIN, RESET_PIN);

//Names of menu options, the sprites are located on sprites.h
static const char menu_names[][10] = {
  "nuligi",
  "datumoj",
  "stato",
  "mangxo",
  "ludo",
  "dusxu",
  "dormu",
  "purigu",
  "lernu",
  "eliru",
  "kuracilo",
  "agordo"
  };

static const char food_names[][13] = {
  "nuligi",
  "supo",
  "ananaso",
  "fromagxo",
  "tasokuko",
  "tempomfritoj",
  "kokido",
  "pico",
  "hamburgero"
  };
  
//Global Variables
const int food_len = 6;
unsigned long up_time = 0;        //time elapsed since turn-on
bool time_flags [5];              //flags for time dependant actions
unsigned char bits_buff[20];     //menu sprite buffer variable
unsigned char selected_bits[20]; //temporal sprite of selected menu option
int animation_mark = 0;           //temp mark to know what sprite to draw
int animation_loop = 0;           //number of times to repeat the animation before go back to standby
int animation_offset = 0;         //the current animation
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
int hungry = 30;   // max: 255
int joy = 128;     // max: 255 
int age = 0;     // max: 255
int weight = 25;  // max: 255
int health = 128;   // max: 255

void setup() {
  pinMode(BL_PIN, OUTPUT);
  pinMode(BTN_A_PIN, INPUT_PULLUP);
  pinMode(BTN_B_PIN, INPUT_PULLUP);
  pinMode(BTN_C_PIN, INPUT_PULLUP); 
  Serial.begin(9600);
  setupEEPROM(); 
  u8g2.begin();
  u8g2.setContrast(contrast);
  u8g2.setDisplayRotation(U8G2_R2);
}

void loop() {
  up_time = millis(); //caution: max=429767295 (7 days 17 hours)
  //Write the backlight status
  digitalWrite(BL_PIN, backlight?HIGH:LOW);
  //Configure graphics
  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.setFontPosTop();
  u8g2.setContrast(contrast);
  //Manage graphics
  u8g2.firstPage();
  do { draw(); } while ( u8g2.nextPage() );

  //Trigger the time dependant actions, but only after start the game
  if (mode > 0) time_triggers();
  
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
      case 3:
        selected = rotate_sel_L(0,selected);
        break;
      case 4:
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
      case 3:
        select_menu_option();
        break;
      case 4:
        if (sub_selected > 0) eat_food(sub_selected); //0 is the back action
        change_animation(1);
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
      case 3:
        selected = rotate_sel_R(MENU_LENGTH - 1,selected);
        break;
      case 4:
        sub_selected = rotate_sel_R(food_len - 1,sub_selected);
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
    draw_data();
    draw_help();
    break;
  case 3:
    draw_menu(selected);
    draw_status();
    draw_help();
    break;
  case 4:
    draw_menu(selected);
    draw_foods(sub_selected);
    draw_help();
    break;
  case 5:
    draw_menu(selected);
    change_animation(2);
    draw_virbes();
    draw_help();
    break;
  case 11:
    draw_menu(selected);
    draw_options(sub_selected);
    break;
  }
}
