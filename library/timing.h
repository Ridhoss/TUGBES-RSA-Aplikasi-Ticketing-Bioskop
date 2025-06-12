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
boolean isValid(int jam, int menit);

int ConvertTMenit(TimeInfo T);
TimeInfo ConvertTime(int totalMenit);
TimeInfo TambahWaktu(TimeInfo A, TimeInfo B);

#endif 