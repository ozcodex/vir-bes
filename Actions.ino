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
  for (int i = 0; i < 5; i++){
    short time_check = int( up_time / pow(10,2+i) ) % 10;
    if (time_check == 0) time_flags[i] = true; //restart the flag
    if (time_check == 1 && time_flags[i]){
      time_flags[i] = false; //change the flag for only execute once
      time_actions(i);
    }
  }
}

void time_actions(int time_unit){
   switch (time_unit){
    case 0: // each second
      decrease_hungry();
    break;
    case 1: // each 10 seconds
      increase_age();
    break;
    case 2: // each 100 seconds (1.6 minutes)
    break;
    case 3: // each 1000 seconds (16.6 minutes)
    break;
    case 4: // each 10000 seconds (2.7 hours)
    break;
    case 5: // each 100000 sec. (27.7 hours)
    break;
  }
}

void decrease_hungry(){
  hungry--;
  if (hungry < 0 ){
    weight--;
    hungry = 0;
  }
  if (weight < 10){
    weight = 10;
    health--;
  }
  if (health < 0){
    health = 0;
  }
}

void increase_age(){
  age++;
  if (age > 999) age = 999;
}

void eat_food(int index){
  hungry += index*2;
  weight += index;
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
