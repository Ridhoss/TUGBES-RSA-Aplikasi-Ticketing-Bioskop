#ifndef ADTJadwal_h
#define ADTJadwal_h

#include "../../library/boolean.h"
#include "../../library/date.h"

#include "ADTList.h"

typedef struct {
    int id;
    date tanggal;
    char start[20];
    char end[20];
    address film;
    char kursi[20][20];
} JadwalInfo;

#endif
