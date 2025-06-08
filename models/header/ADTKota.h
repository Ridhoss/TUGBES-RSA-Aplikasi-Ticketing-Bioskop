#ifndef ADTKota_h
#define ADTKota_h

#include "../../library/boolean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTTree.h"

typedef struct {
    char nama[100];
} KotaInfo;

void SimpanKotaKeFile(const KotaInfo* kota);
int SearchKotaFile(const KotaInfo* kota);
void EditKotaKeFile(const KotaInfo* kotaLama, const KotaInfo* kotaBaru);
void HapusKotaKeFile(const KotaInfo* kotaLama);
void KosongkanFileKota();
void LoadKota(address root);

address AlokasiKota(KotaInfo X);
void DeAlokasiKota(address P);

void TambahKota(address root, const char* namaKota);
void TambahKotaBaru(address root, const char* namaKota);

void UbahKota(address node, KotaInfo dataBaru);

void DeleteKota(address kota);
void DeleteAllKota(address root);

int CompareKota(infotype a, infotype b);
address SearchKota(address root, const char* namaKota);

void PrintKota(address node, int level);

#endif
