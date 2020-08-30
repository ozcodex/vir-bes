void back_to_main(){
  mode = 1;
  selected = 0;
}

void select_menu_option(){
  sub_selected = 0;
  mode = selected + 1;
}

//Trigger temporal related functions
void time_triggers(){
  //after a change switch the flag, to prevent multiple executions
  static bool flag_1, flag_10, flag_100; 
  int each_1 = ( up_time / 100 ) % 10;
  int each_10 = ( up_time / 1000 ) % 10;
  int each_100 = ( up_time / 10000 ) % 10;
  
  if (each_1 == 0) flag_1 = true; //reset the flag
  if (each_10 == 0) flag_10 = true; //reset the flag
  if (each_100 == 0) flag_100 = true; //reset the flag
  if (each_1 == 1 and flag_1){
    // this happens each second, and only executes once
    flag_1 = false;
    action_1();
  }
  if (each_10 == 1 and flag_10){
    // this happens each 10 second, and only executes once
    flag_10 = false;
    action_10();
  }
  if (each_100 == 1 and flag_100){
    // this happens each 100 second, and only executes once
    flag_100 = false;
    action_100();
  }
}

//execute each second
void action_1(){}
//execute each 10 seconds
void action_10(){
  hungry--;
  if (hungry < 0 ) hungry = 0;
  }
//execute each 100 seconds
void action_100(){
  age++;
  if (age > 999) age = 999;
  }

void eat_food(int index){
  hungry += index*2;
  weight += index*3;
  if (hungry > 30){
    hungry = 30;
    health--;
    if (health < -1){
      health = -1;
    }
  }
}

void change_settings(int index){
  if (index == 0) backlight = !backlight;
  if (index == 1) {
    contrast+=5;
    if (contrast > 200){
      contrast = 100;
      }
  }
  if (index == 2) {
    back_to_main();
  }  
}

void read_buttons(){
  int button_timeout = 10;
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
    if (btn_clk_counter[i] > button_timeout) btn_clk_counter[i] = 0;
  }
}
