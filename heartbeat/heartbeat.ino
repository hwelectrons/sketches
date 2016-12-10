/*
Copyright (c) 2016, www.hwelectrons.com
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
  This tiny sketch is pulsing a LED in a style which reminds me a heartbeat.
  To achieve this effect I'm using a software PWM method to drive the LED
  with variable brightness. A pattern is pregenerated and used to modulate
  the PWM signal.
  This is kind of a "Hello, world" application but I prefer it much more
  than a simple blinking.
*/  

#include <stdint.h>
#include <math.h>

#define LED 13 //The pin where your LED is connected.
#define LUT_SIZE 64 //The size of the buffer where the pattern is generated.

uint8_t vLUT[LUT_SIZE];

void setup()
{
 for(uint16_t i=0;i<LUT_SIZE;++i)
 {
   float f=(i < (LUT_SIZE / 2)) ? sin((1.0/(LUT_SIZE/4))*M_PI*i) : 0.0;
   vLUT[i]= (uint8_t)(255*f*f);
 }
 pinMode(LED,OUTPUT);
}

void loop()
{
  uint8_t i=0;
  uint16_t time = millis() % 1024;
  uint8_t iValue = vLUT[time / (1024 / LUT_SIZE)];
  for(uint8_t k=0;k<16;++k)
  {
    do
    {
      digitalWrite(LED,(iValue <= (i++)) ? 0 : 1);
    }while(0 != i);
  }
}
