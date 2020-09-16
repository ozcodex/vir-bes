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
void draw_menu(int pointer){
  //menu separator
  u8g2.drawLine(0, 10, 84, 10);
  //load the inverted sprite of selected optioon
  build_selected(pointer);
  //define menu render offset (for scrolling)
  int offset = get_offset(pointer,MENU_LENGTH,8);
  //render menu options
  for(int i = offset;i<MENU_LENGTH;i++){
    //load sprites from PROGMEM
    memcpy_P(bits_buff, menu[i], 100);
    //print each menu option visible
    u8g2.drawXBM( (i-offset)*10, 0, 10, 10, pointer == i? selected_bits:bits_buff);
  }
}

//virbes draw
void draw_virbes(){
  const short x= 42;
  const short y= 17;
  //draw body
  short anim_off_set = animation_mark;
  short prev_offset = 0;
  short prev_lenght = 0;
  short prev_fpo = 0;
  short prev_lpo = 0;
  short pows[] = {16,8,4,2,1};
  short j;
  for (j=0; j < 18; j++){
    short lenght = 0;
    short off_set = 0;
    byte row = pgm_read_byte(&(lex[anim_off_set][j]));
    //read first 5 bits
    for (short i = 0; i < 5; i++){
      lenght += bitRead(row,7-i)*pows[i];
    }
    if (lenght == 0) continue; //skip round
    off_set = (bitRead(row,2)?-1:1)*(2*bitRead(row,1)+bitRead(row,0))+prev_offset;
    short first_point_offset = -1*floor(lenght / 2)+off_set;
    u8g2.drawPixel(x+first_point_offset, y+j);
    short last_point_offset = first_point_offset + lenght;
    u8g2.drawPixel(x+last_point_offset, y+j);
    //fill spaces
    if (abs(first_point_offset - prev_fpo) >= 2) u8g2.drawLine(x+min(first_point_offset,prev_fpo), y+j, x+max(first_point_offset,prev_fpo), y+j);
    if (abs(last_point_offset - prev_lpo) >= 2) u8g2.drawLine(x+min(last_point_offset,prev_lpo), y+j, x+max(last_point_offset,prev_lpo), y+j);
    
    //save previous values
    prev_offset = off_set;
    prev_lenght = lenght;
    prev_fpo = first_point_offset;
    prev_lpo = last_point_offset;
  }
  //after finish draw a line between the points
  u8g2.drawLine(x+prev_fpo, y+j, x+prev_lpo, y+j);
  //draw face
  u8g2.setBitmapMode(1);
  anim_off_set = (animation_offset*2)+animation_mark;
  memcpy_P(bits_buff, lex_face[anim_off_set], 49);
  u8g2.drawXBM( 40, 23, 7, 7, bits_buff);
  u8g2.setBitmapMode(0);
}

//data of virbes
void draw_data(){
  u8g2.setCursor(3, 12);
  u8g2.print("Nomo:");
  u8g2.print("LEX ");
  char gen[6];
  toRoman(17,gen); //max: 17
  u8g2.print(gen);

  u8g2.setCursor(6, 22);
  u8g2.print("stadio");  //evoluo
  u8g2.setCursor(43, 22);
  u8g2.print("speco");

  u8g2.drawRFrame(1,21,38,18,2);
  u8g2.drawRFrame(41,21,28,18,2);

  u8g2.setCursor(3, 29);
  u8g2.print("maljuna");   //ovo, bebo, infano, juna, matura, maljuna
  u8g2.setCursor(47, 30);
  u8g2.print("D-A"); // IQ. and Constitution Ranking.

  memcpy_P(bits_buff, stats[1], 49); //0: male 1:female
  u8g2.drawXBM( 72, 14, 10, 10, bits_buff);
  memcpy_P(bits_buff, stats[5], 49); //2:disciplined 3:glutton 4:introvert 5:playful
  u8g2.drawXBM( 72, 26, 10, 10, bits_buff);
  
}

//Status of virbes
void draw_status(){
  int bar_level;
  //Draw Text
  u8g2.setCursor(3, 11);
  u8g2.print("sata");
  u8g2.setCursor(39, 12);
  u8g2.print("agxo");
  u8g2.setCursor(63, 12);
  u8g2.print("peza");
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
  bar_level = conv255(hungry,30);
  u8g2.drawBox(4,20,bar_level,2);
  bar_level = conv255(joy,30);
  u8g2.drawBox(4,34,bar_level,2);
  //Draw Numbers
  u8g2.setCursor(41, 20);
  u8g2.print(age);
  u8g2.setCursor(65, 20);
  u8g2.print(weight);
  //Draw Hearts
  memcpy_P(bits_buff, hearts[delta(conv255(health,6),2)], 49);
  u8g2.drawXBM( 60, 31, 7, 7, bits_buff);
  memcpy_P(bits_buff, hearts[delta(conv255(health,6)-2,2)], 49);
  u8g2.drawXBM( 68, 31, 7, 7, bits_buff);
  memcpy_P(bits_buff, hearts[delta(conv255(health,6)-4,2)], 49);
  u8g2.drawXBM( 76, 31, 7, 7, bits_buff);

}

//Draw food options
void draw_foods(int pointer){
  //draw foods
  int offset = get_offset(pointer,food_len,5);
  for (int i = offset;i < food_len;i++){
    memcpy_P(bits_buff, foods[i], 100);
    u8g2.drawXBM( 5+(i-offset)*16, 21, 10, 10, bits_buff);
  }
  //draw rectangle arround selected option
  u8g2.drawRFrame(3+16*(pointer-offset),19,14,14,2);
}

//Options draw function
void draw_options(int pointer){
  //first option, backlight configuration
  u8g2.setCursor(0, 12);
  u8g2.print(pointer == 0?">":"");
  u8g2.print("Lumo: ");
  u8g2.print(backlight?"on":"off");
  //second option, contrast configuration
  u8g2.setCursor(0, 20);
  u8g2.print(pointer == 1?">":"");
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
    case 3:
      u8g2.print(menu_names[selected]);
      break;
    case 4:
      u8g2.print(food_names[sub_selected]);
  }
  //write the name of selected option
  
  u8g2.setCursor(75, 40);
  //u8g2.print(selected);
  //reset the draw mode and color
  u8g2.setFontMode(0);
  u8g2.setDrawColor(1);
}
