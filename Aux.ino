//Fix the input between 0 and 2
int delta(int number){
  if (number > 2) number = 2;
  if (number < 0) number = 0;
  return number;
}

//Prepare the selected option to be rendered
void build_selected(){
  //read sprite from PROGMEM
  memcpy_P(bits_buff, menu[selected], 100);
  //invert each bit
  for(int i=0;i<100;i++){
    selected_bits[i] = ~bits_buff[i];
  }
}

//Define the offset to scroll menu
int get_offset(int sel){
  int max_items = 8;
  int middle_item = 4;
  int offset = 0;
  int max_offset = menu_len - max_items;
  if (sel > middle_item)
    offset += sel-middle_item;
  if (offset > max_offset )
    offset = max_offset;
  return offset;
}
