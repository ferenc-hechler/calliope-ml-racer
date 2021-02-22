#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stddef.h>

size_t float2char(char* buf, float number, uint8_t digits);
float char2float(const char* buf);

void throwError(const char *errMsg);

void log(const char *msg);
void logFloat(float f);
void logInt(int i);
void logF(const char *format, ...);

void show(const char *msg);
void showFloat(float f);
void showInt(int i);
void showF(const char *format, ...);


#endif // UTILS_H
