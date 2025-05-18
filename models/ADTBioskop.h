#ifndef ADTBioskop_h
#define ADTBioskop_h

#include "boolean.h"
#include "ADTList.h"

typedef struct {
    int id;
    char nama[100];
    char kota[100];
} BioskopInfo;

address AlokasiBioskop(BioskopInfo X);
void DeAlokasiBioskop(address P);

void InsLastBioskop(List *L, BioskopInfo X);

address SearchBioskop(List L, int id);
address SearchPrecBioskop(List L, int id);

void DelPBioskop(List *L, int id);
void DelAllBioskop(List *L);

void PrintBioskop(List L);

void InsFirstBioskop(List *L, BioskopInfo X);
void InsertAfterBioskop(List *L, BioskopInfo X, address Prec);
void DelFirstBioskop(List *L, BioskopInfo *X);
void DelLastBioskop(List *L, BioskopInfo *X);

#endif