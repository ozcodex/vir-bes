
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
  int offset = get_offset(selected);
  //render menu options
  for(int i = offset;i<menu_len;i++){
    //load sprites from PROGMEM
    memcpy_P(bits_buff, menu[i], 100);
    //print each menu option visible
    u8g2.drawXBM( (i-offset)*10, 0, 10, 10, selected == i? selected_bits:bits_buff);
  }
}

//character draw
void draw_virbes(){
  int x_off= 0;
  int y_off= 0;
  memcpy_P(bits_buff, lex[0], 400);
  u8g2.drawXBM( 32+x_off, 17+y_off, 20, 20, bits_buff);
  memcpy_P(bits_buff, lex_face[0], 81);
  u8g2.drawXBM( 37+x_off, 22+y_off, 9, 9, bits_buff);
}

//Status of tamagotchi
void draw_status(){
  //Temporary: status variables
  int hungry = 7;   // max: 30
  int joy = 15;     // max: 30 
  int age = 23;     // max: 999
  int weight = 85;  // max: 999
  int health = 3;   // max: 6
  
  //Draw Text
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
  //Draw Lines
  u8g2.drawLine(2, 20, 2, 23);
  u8g2.drawLine(3, 23, 33, 23);
  u8g2.drawLine(2, 34, 2, 37);
  u8g2.drawLine(3, 37, 33, 37);
  //draw Boxes
  u8g2.drawRFrame(37,13,23,16,3);
  u8g2.drawRFrame(61,13,23,16,3);
  //draw Bars
  u8g2.drawBox(4,20,hungry,2);
  u8g2.drawBox(4,34,joy,2);
  //Draw Numbers
  u8g2.setCursor(41, 20);
  u8g2.print(age);
  u8g2.setCursor(65, 20);
  u8g2.print(weight);
  //Draw Hearts
  memcpy_P(bits_buff, hearts[delta(health)], 49);
  u8g2.drawXBM( 60, 31, 7, 7, bits_buff);
  memcpy_P(bits_buff, hearts[delta(health-2)], 49);
  u8g2.drawXBM( 68, 31, 7, 7, bits_buff);
  memcpy_P(bits_buff, hearts[delta(health-4)], 49);
  u8g2.drawXBM( 76, 31, 7, 7, bits_buff);

}

//Draw food options
void draw_foods(){
  //draw foods
  memcpy_P(bits_buff, foods[0], 100);
  u8g2.drawXBM( 5, 21, 10, 10, bits_buff);
  memcpy_P(bits_buff, foods[1], 100);
  u8g2.drawXBM( 21, 21, 10, 10, bits_buff);
  memcpy_P(bits_buff, foods[2], 100);
  u8g2.drawXBM( 37, 21, 10, 10, bits_buff);
  memcpy_P(bits_buff, foods[3], 100);
  u8g2.drawXBM( 53, 21, 10, 10, bits_buff);
  memcpy_P(bits_buff, foods[4], 100);
  u8g2.drawXBM( 69, 21, 10, 10, bits_buff);
  //draw rectangle arround selected option
  u8g2.drawRFrame(3+16*sub_selected,19,14,14,2);
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
  //change draw mode and color for inverted
  u8g2.setFontMode(1);
  u8g2.setDrawColor(0);
  //set the cursor in position
  u8g2.setCursor(1, 40);
  //draw matching text
  switch(mode){
    case 1:
    case 2:
      u8g2.print(menu_names[selected]);
      break;
    case 3:
      u8g2.print(food_names[sub_selected]);
  }
  //write the name of selected option
  
  u8g2.setCursor(75, 40);
  //u8g2.print(sub_selected);
  //reset the draw mode and color
  u8g2.setFontMode(0);
  u8g2.setDrawColor(1);
}
