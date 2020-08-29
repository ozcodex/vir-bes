int delta(int number){
  //fix the input between 0 and 2
  if (number > 2) number = 2;
  if (number < 0) number = 0;
  return number;
}
