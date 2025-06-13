#ifndef TIMING_h
#define TIMING_h

#include "boolean.h"
#include <time.h>
#include <stdbool.h>


/***************************/
/* Type data */
/***************************/
/* Kamus */
typedef struct { 
    int jam; 
    int menit; 
} TimeInfo;

void InisialisasiWaktu(TimeInfo *T);
void SetTime(TimeInfo *T, int jam, int menit);
boolean isValidTime(int jam, int menit);

int ConvertTMenit(TimeInfo T);
TimeInfo ConvertTime(int totalMenit);
TimeInfo TambahWaktu(TimeInfo A, TimeInfo B);

TimeInfo DifferenceTime(TimeInfo A, TimeInfo B);
int CompareTime(TimeInfo A, TimeInfo B);
boolean CekBetweenTime(TimeInfo start, TimeInfo end, TimeInfo new);
void TimeString(TimeInfo T, char *buffer);
void PrintTime(TimeInfo T);

#endif 