#include <U8g2lib.h>
#include "sprites.h"

//Menu lenght
#define MENU_LENGTH 14
#define FOOD_MENU_LENGTH 9
#define OPTIONS_MENU_LENGTH 3
#define MENU_VISIBLE_ITEMS 8

//Sprite Sizes
#define SPRITE_SIZE 8
#define BIG_SPRITE_BYTES 20
#define SMALL_SPRITE_BYTES 7

#define BUTTON_TIMEOUT 200

//PIN constants definition 
#define CLOCK_PIN 13
#define DATA_PIN 11
#define DC_PIN 10
#define CE_PIN 9
#define RESET_PIN 8

#define BUZZ_PIN 7
#define BTN_A_PIN 6
#define BTN_B_PIN 5
#define BTN_C_PIN 4
#define BL_PIN 3


#define SCL_PIN A5
#define SDA_PIN A4

//Definition of display to use, here is Nokia 5110 84x48
U8G2_PCD8544_84X48_2_4W_HW_SPI u8g2 = 
  U8G2_PCD8544_84X48_2_4W_HW_SPI(U8G2_R0, CE_PIN, DC_PIN, RESET_PIN);

//Names of menu options, the sprites are located on sprites.h
static const char menu_names[][9] = {
  "cxefa",
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
  "amikoj",
  "posxto",
  "agordo"
  };
static const char food_names[][11] = { 
  "nuligi",
  "pomo",
  "supo",
  "fromagxo",
  "kokido",
  "hamburgero",
  "ringbulko",
  "glaciajxo",
  "tasokuko"
  };

static const char evolution_names[][8] = { "ovo", "infano", "juna", "matura", "maljuna" };
static const char grades[] = {'D','C','B','A','S' };

//Global Variables
byte loaded_sprite[SPRITE_SIZE];                //space where the sprites read from eeprom are saved0.
//old
bool redraw = true;                             //indicates the need of draw again the view
unsigned long up_time = 0;                      //time elapsed since turn-on
bool time_flags [5];                            //flags for time dependant actions
unsigned char bits_buff[BIG_SPRITE_BYTES];      //menu sprite buffer variable
unsigned char selected_bits[BIG_SPRITE_BYTES];  //temporal sprite of selected menu option
bool first_animation = true;                    //temp mark to know what sprite to draw
signed char animation_loop = 0;                 //number of times to repeat the animation before go back to standby
byte animation_offset = 0;                      //the current animation
byte selected = 0;                              //current menu option selected
byte sub_selected = 0;                          //for sub menus, the selected option
bool pull_down[] = {false,false,false};
int btn_clk_counter[] = {0,0,0};
//configuration variables
bool backlight = true;                          //status of backlight
byte contrast = 135;
int mode = 0;   /* stage of game:
                 * 0: initial screen
                 * 1: main menu view
                 * 2: status view
                 * 3: food view
                 * 11: settings
                 */
//Virbes data:
//char definition
char name[] = "LEX";
byte generation = 8;    //max:17 min:1
byte evolution = 4;     //0:ovo, 1:infano, 2:juna, 3:matura, 4:maljuna
byte iq = 3;            //max 4
byte constitution = 0;  //max 4
bool is_female= false;  //else male
byte main_char = 0;     //0:disciplined 1:glutton 2:introvert 3:playful

//status variables
byte hungry = 30;       // max: 255
byte joy = 128;         // max: 255 
byte age = 0;           // max: 255
byte weight = 25;       // max: 255
byte health = 200;      // max: 255

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
  tone(BUZZ_PIN, 440, 500); 
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
  if (redraw){
    u8g2.firstPage();
    do { draw(); } while ( u8g2.nextPage() );
  }

  //Trigger the time dependant actions, but only after start the game
  if (mode > 0) time_triggers();
  
  //Read buttons
  read_buttons();

  //Trigger Button A Action
  if (pull_down[0] && btn_clk_counter[0] == 1){
    redraw = true;
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
      case 14:
        sub_selected = rotate_sel_L(0,sub_selected);
        break;
    }
  }
  //Trigger Button B Action
  if (pull_down[1]  && btn_clk_counter[1] == 1){
    redraw = true;
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
        if (sub_selected > 0) { //0 is the back action
          eat_food(sub_selected);           
        }
        back_to_main();
        break;
      case 5:
        change_animation(0);
        back_to_main();
      break;
      case 14:
        change_settings(sub_selected);
        break;
      
    } 
  }
  //Trigger Button C Action
  if (pull_down[2]  && btn_clk_counter[2] == 1){
    redraw = true;
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
        sub_selected = rotate_sel_R(FOOD_MENU_LENGTH - 1,sub_selected);
      break;
      case 14:
        sub_selected = rotate_sel_R(OPTIONS_MENU_LENGTH,sub_selected);
      break;
    }
  }
}

//Main Draw Function
void draw() {
  //after draw there is no need to draw until something change
  redraw = false;
  switch (mode){
  case 0:
    //initial screen
    draw_initial();
    break;
  case 1:
    //home
    draw_menu(selected);
    draw_virbes();
    draw_help();
    break;
  case 2:
    //data info
    draw_menu(selected);
    draw_data();
    draw_help();
    break;
  case 3:
    //status info
    draw_menu(selected);
    draw_status();
    draw_help();
    break;
  case 4:
    //foods
    draw_menu(selected);
    draw_foods(sub_selected);
    draw_help();
    break;
  case 5:
    //play
    draw_menu(selected);
    change_animation(2);
    draw_play();
    draw_virbes();
    draw_help();
    break;
  case 14:
    draw_menu(selected);
    draw_options(sub_selected);
    break;
  }
}
