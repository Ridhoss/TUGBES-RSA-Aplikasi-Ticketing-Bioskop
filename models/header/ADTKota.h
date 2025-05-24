#ifndef ADTKota_h
#define ADTKota_h

#include "../../library/boolean.h"

#include "ADTTree.h"

typedef struct {
    char nama[100];
} KotaInfo;

address AlokasiKota(KotaInfo X);
void DeAlokasiKota(address P);

void InsKota(List *L, KotaInfo X);

address SearchKota(List L, int id);

void DelPKota(List *L, int id);
void DelAllKota(List *L);

void PrintKota(List L);

#endif
