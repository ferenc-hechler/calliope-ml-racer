#include <MicroBit.h>
#include "platform/Utils.h"

#include<stdarg.h>


extern MicroBit uBit;

// from: https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/Print.cpp
size_t float2char(char* buf, float number, uint8_t digits) {
  size_t n = 0;

  if (isnan(number)) return sprintf(buf, "nan");
  if (isinf(number)) return sprintf(buf, "inf");
  if(number > 4294967040.0) {
      return sprintf(buf, "ovf");    // constant determined empirically
  }
  if(number < -4294967040.0) {
      return sprintf(buf, "ovf");    // constant determined empirically
}

  // Handle negative numbers
  if (number < 0.0)
  {
     n += sprintf((char*)(buf+n), "-");
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  float rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += sprintf((char*)(buf+n), "%lu", int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += sprintf((char*)(buf+n), ".");
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    n += sprintf((char*)(buf+n), "%d",toPrint);
    remainder -= toPrint;
  }

  return n;
}



void throwError(const char *errMsg) {
	while (true) {
		uBit.display.scroll(errMsg);
        uBit.sleep(1000);
        if ( uBit.buttonA.isPressed() == true ) {
        	uBit.sleep(24*60*60*1000);
        }
	}
}

void log(const char *msg) {
	uBit.display.scroll(msg);
}

void logFloat(float f) {
	char buf[100];
	float2char(buf, f, 3);
	log(buf);
}

void logInt(int i) {
	char buf[100];
	sprintf(buf, "%d", i);
	log(buf);
}

void logF(const char * format, ...) {
  char buf[100];
  va_list args;
  va_start (args, format);
  vsnprintf(buf, 100, format, args);
  log(buf);
  va_end(args);
}

void dbgLog(const char *msg) {
	uBit.serial.send(msg);
}

void dbgLogFloat(float f) {
	char buf[100];
	float2char(buf, f, 3);
	dbgLog(buf);
}

void dbgLogInt(int i) {
	char buf[100];
	sprintf(buf, "%d", i);
	dbgLog(buf);
}

void dbgLogF(const char * format, ...) {
  char buf[100];
  va_list args;
  va_start (args, format);
  vsnprintf(buf, 100, format, args);
  dbgLog(buf);
  va_end(args);
}

