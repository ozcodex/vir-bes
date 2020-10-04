//this is just for test, must be moved to EEPROM
//Each byte represents the length of the note (beats) and the note itself
//0=4b 1=2b 2=1b 3=b/2 4=b/4 5=b/8 6=b/16 7=b/32
//0=C 1=C# 2=D 3=D# 4=E 5=F 6=F# 7=G 8=G# 9=A A=A# B=B F=silence
//the note duration is calculed as BEAT_DURATION*pow(2,-NOTE_DURATION+2)
//the note frecuency is calculated as INITIAL_TONE*pow(2,[(OCTAVE-1)*12+NOTE_INDEX]/12)

byte songs[] = {0,
                4,0x47,0x44,0x44,0x40,
                4,0x40,0x44,0x47,0x40};

//play the next note
void play_sound(){
  byte note_data;
  // check if the current note is not the last note
  if(note_counter < song_buff[0]){
    // check the elapsed time to know if is the proper time to play he next note
    if(up_time - last_note_time > note_duration){
      //increment the counter (position 0 is ignored, bacause it is the duration)
      note_counter++;
      //extract the data for duration
      note_data = bitmask(song_buff[note_counter],B1111,4);
      note_duration = beat_duration*pow(2,2-note_data);
      //ectract the data for note
      note_data = bitmask(song_buff[note_counter],B1111,0);
      //calculate frecuency
      unsigned short frecuency;
      if (note_data == 0xF){
          frecuency = 0; //silence
        }else{
          frecuency = INITIAL_TONE*pow(2,((float)(((OCTAVE-1)*12+note_data)))/12);
        }
      //play the note
      tone(BUZZ_PIN, frecuency, note_duration*NOTE_TIME_FACTOR);
      //set the time of the played note
      last_note_time = up_time;
    }
  }
}

void load_song(byte index){
  unsigned short song_offset = 0;
  //re initialize the note counter for the next song
  note_counter = 0;
  //determine the starting point of the songs array (address when reading from eeprom)
  while(index != 0){
    //read the first byte, this is the number of notes of the song
    //then add the song duration to go to the last note, and add 1 to go to next song.
    song_offset += songs[song_offset] + 1;
    //decrement the index
    index --; 
  }
  //store the duration of the song on the first position
  song_buff[0] = songs[song_offset];
  for (int i = 1; i <= song_buff[0]; i++){
    song_buff[i] = songs[i+song_offset];
  }
}
