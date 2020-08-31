//Fix the input between 0 and 2
int delta(int number){
  if (number > 2) number = 2;
  if (number < 0) number = 0;
  return number;
}

//Turn a 255 integer in a range specific integer
int conv255(int input, int maxim){
  int out = (input*(maxim + 1))/255; // this should be kept as integer
  if (out > maxim) out = maxim;
  return out;
}

//Convert into roman
void toRoman(int input, char* output){
  char numerals[][6]={"I","II","III","IV","V","VI","VII","VIII","IX",
                      "X","XI","XII","XIII","XIV","XV","XVI","XVII","XVIII"};
  if (input >=1 && input <= 17){
    sprintf(output, "%s", numerals[input-1]);
  }else{
    //Out of range
    sprintf(output, "%d", input);
  }
}

//Prepare the selected option to be rendered
void build_selected(int pointer){
  //read sprite from PROGMEM
  memcpy_P(bits_buff, menu[pointer], 100);
  //invert each bit
  for(int i=0;i<100;i++){
    selected_bits[i] = ~bits_buff[i];
  }
}

//Define the offset to scroll menu
int get_offset(int sel,int list_len,int max_items){
  //max items is the lenght of menu bar
  int middle_item = max_items/2;
  int offset = 0;
  int max_offset = list_len - max_items;
  if (sel > middle_item)
    offset += sel-middle_item;
  if (offset > max_offset )
    offset = max_offset;
  return offset;
}

//Rotate sub_selected to left
int rotate_sel_L(int minv,int pointer){
  pointer--;
  if (pointer < minv ) pointer = minv;
  return pointer;
}

//Rotate sub_selected to right
int rotate_sel_R(int maxv,int pointer){
  pointer++;
  if (pointer >= maxv ) pointer = maxv;
  return pointer;
}
