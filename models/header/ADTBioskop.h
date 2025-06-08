#ifndef ADTBioskop_h
#define ADTBioskop_h

#include "../../library/boolean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTTree.h"
#include "ADTKota.h"

typedef struct {
    char nama[100];
} BioskopInfo;

void SimpanBioskopKeFile(const char* namaKota, const BioskopInfo* bioskop);
int SearchBioskopFile(const char* namaKota, const BioskopInfo* bioskop);
void EditBioskopKeFile(const char* namaKota, const BioskopInfo* bioskop, const BioskopInfo* bioskopLama);
void HapusBioskopKeFile(const char* namaKota, const BioskopInfo* bioskopLama);
void KosongkanFileBioskop();
void LoadBioskop(address root);

address AlokasiBioskop(BioskopInfo X);
void DeAlokasiBioskop(address P);

void TambahBioskop(address kota, const char* namaBioskop);
void TambahBioskopBaru(address kota, const char* namaBioskop);

void UbahBioskop(address node, BioskopInfo dataBaru);

void DeleteBioskop(address bioskop);
void DeleteAllBioskop(address kota);

int CompareBioskop(infotype a, infotype b);
address SearchBioskop(address kota, const char* namaBioskop);

void PrintBioskop(address node, int level);

#endif