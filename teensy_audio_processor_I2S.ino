
/*
 * Teensy + Audio Adaptor Board
 */

#include <Audio.h>


#include "audio_processor.h"

// --- connections
AudioInputI2S            i2s1;
AudioOutputI2S           i2s2;

AudioProcessor           proc; 

AudioConnection          patchCord1(i2s1, 0, proc, 0);
AudioConnection          patchCord2(i2s1, 1, proc, 1);
AudioConnection          patchCord3(proc, 0, i2s2, 0);
AudioConnection          patchCord4(proc, 1, i2s2, 1);

AudioControlSGTL5000     sgtl5000_1;

// -------------------------------------
void setup() {
  AudioMemory(12);

  // Enable the audio shield with LineIn
  sgtl5000_1.enable();  
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);

  // set volume level of lineIn
  sgtl5000_1.lineInLevel(0); 
  // set volume level of linOut
  sgtl5000_1.lineOutLevel(13); 
}

// -------------------------------------
void loop() {
}
