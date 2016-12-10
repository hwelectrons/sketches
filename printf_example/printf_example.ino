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
  Example: How to use standard IO facilities (stdio.h) within the Arduino framework.
  Note: For the full functionality including floating point conversions 
  the following linker options are required:
  -Wl,-u,vfprintf -lprintf_flt -lm
  
  For more information see: http://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html
*/  

#include <stdio.h>

//Wrapper function for output
int uart_putchar(char c, FILE *stream)
{
  Serial.write(c);
  return 0;
}

//Wrapper funtion for input
int uart_getchar(FILE *stream)
{
  int ch;
  do
  {
    ch = Serial.read();
  }while(ch < 0);
  return ch;
}

void setup()
{ 
  Serial.begin(57600);
  
  //Register ouput and input handler funtions.
  fdevopen(uart_putchar,uart_getchar);
} 

void loop()
{
  static int i1=0;
  static unsigned int i2=0x1234;
  
  if (i1 < 3)
  {
    //Normal printf
    printf("\r\n  %s %s \r\n","Hello,","World!");
    
    //Store your format string in progam memory and use printf_P to save data memory. 
    printf_P(PSTR("An integer: %d; An integer in hexadecimal: %#06x\r\n"),i1,i2);

    ++i1;
    ++i2;
  }
  else
  {
    char sFirstname [80];
    char sLastname [80];
    int age;
    printf_P(PSTR("\r\nPlease enter your first name:"));
    scanf_P(PSTR("%79s"),sFirstname);
    printf_P(PSTR("\r\nPlease enter your last name:"));
    scanf_P(PSTR("%79s"),sLastname);
    printf_P(PSTR("\r\nPlease enter your age (you can give hexadecimal as well as negative number too):"));
    scanf_P(PSTR("%i"),&age);
    
    printf_P(PSTR("\r\n%s %s is %i years old."),sFirstname,sLastname,age);
  }
  delay(2000);
}
