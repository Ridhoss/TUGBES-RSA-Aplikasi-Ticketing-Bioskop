#ifndef errorHandle_h
#define errorHandle_h

#include "boolean.h"

int isNumber(char str[]);
int InputAngkaValid(int min, int max);
void InputNomorTelepon(char *output, int maxLen) ;
int isValidUsername(char *str);
boolean isValidKursiFormat(const char *input);


#endif