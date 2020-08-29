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
