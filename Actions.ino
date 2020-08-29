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
