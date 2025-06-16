#ifndef ADTKota_h
#define ADTKota_h

#include "../../library/boolean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTTree.h"
#include "ADTBioskop.h"
#include "ADTTeater.h"
#include "ADTJadwal.h"


typedef struct {
    int id;
    char nama[100];
} KotaInfo;

void SimpanKotaKeFile(const KotaInfo* kota);
int SearchKotaFile(const KotaInfo* kota);
void EditKotaKeFile(const KotaInfo* kotaLama, const KotaInfo* kotaBaru);
void HapusKotaKeFile(const KotaInfo* kotaLama);
void KosongkanFileKota();
void LoadKota(address root);
int AmbilIdKotaTerakhir();

address AlokasiKota(KotaInfo X);
void DeAlokasiKota(address P);

void TambahKota(address root, KotaInfo kotaBaru);
void TambahKotaBaru(address root, KotaInfo kotaBaru);

void UbahKota(address dataLama, KotaInfo dataBaru);

void DeleteKota(address kota);
void DeleteAllKota(address root);
    
int CompareKota(infotype a, infotype b);
int CompareKotaId(infotype a, infotype b);
address SearchKotaByName(address root, const char* namaKota);
address SearchKotaById(address root, const int* idKota);
address CariKotaDariIdBioskop(address root, int idBioskop);

void PrintKota(address node, int level);

#endif
