void back_to_main(){
  mode = 1;
  selected = 0;
}

void select_menu_option(){
  sub_selected = 0;
  mode = selected + 1;
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
