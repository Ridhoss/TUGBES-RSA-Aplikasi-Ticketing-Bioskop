#ifndef ADTKota_h
#define ADTKota_h

#include "../../library/boolean.h"

#include "ADTList.h"

typedef struct {
    int id;
    char nama[100];
} KotaInfo;

address AlokasiKota(KotaInfo X);
void DeAlokasiKota(address P);

void InsLastKota(List *L, KotaInfo X);
address SearchKota(List L, int id);
address SearchPrecKota(List L, int id);

void DelPKota(List *L, int id);
void DelAllKota(List *L);

void PrintKota(List L);

void InsFirstKota(List *L, KotaInfo X);
void InsertAfterKota(List *L, KotaInfo X, address Prec);
void DelFirstKota(List *L, KotaInfo *X);
void DelLastKota(List *L, KotaInfo *X);

#endif
