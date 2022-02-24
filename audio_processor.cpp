/* Audio Processor for Teensy
 * Copyright (c) 2022, Antonin Novak, antonin.novak(at)univ-lemans.fr
 * 
 * Laboratoire d'Acoustique de l'Université du Mans (LAUM), 
 * UMR 6613, Institut d'Acoustique - Graduate School (IA-GS), 
 * CNRS, Le Mans Université, France 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 
#include "audio_processor.h"

void AudioProcessor::update(void)
{
  audio_block_t *blockL, *blockR;
  float inL, inR, outL, outR;
  unsigned int i;

  // obtain AUDIO_BLOCK_SAMPLES samples (by default 128)
  blockL = receiveWritable(0);
  if (!blockL) return;
  blockR = receiveWritable(1);
  if (!blockR) return;

  // The data[] is an array of 16 bit integers representing the audio (blockL->data[i] is of uint16_t type)
  // (Note: The data[] array is always 32 bit aligned in memory, so you can fetch pairs of samples 
  //        by type casting the address as a pointer to 32 bit data (uint32_t))

  for (i=0; i < AUDIO_BLOCK_SAMPLES; i++) {
    // read the input signal
    inL = blockL->data[i] * conversionConstADC;
    inR = blockR->data[i] * conversionConstADC;

    // processing (as float)
    outL = inL;
    outR = inR;

    // write the output signal
    blockL->data[i] = outL * conversionConstDAC;
    blockR->data[i] = outR * conversionConstDAC;    
  }

  transmit(blockL,0);
  transmit(blockR,1);
  release(blockL);
  release(blockR);
}
