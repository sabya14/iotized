#ifndef UTILS_H
#define UTILS_H
#include <Arduino.h>
void writeString(String stringData);
char StrContains(char *str, char *sfind);
String splitString(String data, char separator, int index);
#endif
