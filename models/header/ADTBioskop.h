#ifndef ADTBioskop_h
#define ADTBioskop_h

#include "../../library/boolean.h"

#include "ADTKota.h"
#include "ADTTree.h"

typedef struct {
    char nama[100];
} BioskopInfo;

address AlokasiBioskop(BioskopInfo X);
void DeAlokasiBioskop(address P);

void TambahBioskop(address kota, const char* namaBioskop);
void TambahBioskopBaru(address kota, const char* namaBioskop);
void PrintBioskop(address nodeKota, int level);

void SimpanBioskopKeFile(const char* namaKota, const BioskopInfo* bioskop);

int CompareBioskop(infotype a, infotype b);
address SearchBioskop(address kota, const char* namaBioskop);

int SearchBioskopFile(const char* namaKota, const char* namaBioskop);
void EditBioskopKeFile(const char* namaKota, const char* namaLama, const char* namaBaru);
void UbahBioskop(address node, BioskopInfo dataBaru);

void HapusBioskopKeFile(const char* namaKota, const char* namaBioskop);
void KosongkanFileBioskop();

void DeleteBioskop(address kota, const char* namaBioskop);
void DeleteAllBioskop(address kota);

#endif