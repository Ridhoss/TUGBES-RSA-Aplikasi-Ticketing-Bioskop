#ifndef ADTBioskop_h
#define ADTBioskop_h

#include "../../library/boolean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTTree.h"
#include "ADTKota.h"
 
typedef struct {
    int id;
    char nama[100];
} BioskopInfo;

void SimpanBioskopKeFile(const int* idkota, const BioskopInfo* bioskop);
int SearchBioskopFile(const BioskopInfo* bioskop);
void EditBioskopKeFile(const BioskopInfo* bioskop, const BioskopInfo* bioskopLama);
void HapusBioskopKeFile(const BioskopInfo* bioskopLama);
void KosongkanFileBioskop();
void LoadBioskop(address root);
int AmbilIdBioskopTerakhir();

address AlokasiBioskop(BioskopInfo X);
void DeAlokasiBioskop(address P);

void TambahBioskop(address kota, BioskopInfo bioskopBaru);
void TambahBioskopBaru(address kota, BioskopInfo bioskopBaru);

void UbahBioskop(address node, BioskopInfo dataBaru);

void DeleteBioskop(address bioskop);
void DeleteAllBioskop(address kota);

int CompareBioskop(infotype a, infotype b);
int CompareBioskopId(infotype a, infotype b);
address SearchBioskopByName(address kota, const char* namaBioskop);
address SearchBioskopById(address root, const int* idBioskop);

void PrintBioskop(address node, int level);

#endif