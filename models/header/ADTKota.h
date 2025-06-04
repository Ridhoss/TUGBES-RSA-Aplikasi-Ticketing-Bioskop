#ifndef ADTKota_h
#define ADTKota_h

#include "../../library/boolean.h"

#include "ADTTree.h"

typedef struct {
    char nama[100];
} KotaInfo;

address AlokasiKota(KotaInfo X);
void DeAlokasiKota(address P);

void TambahKota(address root, const char* namaKota);

void DeleteKota(address root, const char* namaKota);

int CompareKota(infotype a, infotype b);
address SearchKota(address root, const char* namaKota);

#endif
