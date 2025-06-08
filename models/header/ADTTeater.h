#ifndef ADTTeater_h
#define ADTTeater_h

#include "../../library/boolean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTTree.h"
#include "ADTBioskop.h"

typedef struct {
    char nama[100];
    int jumlahKursi;
} TeaterInfo;

void SimpanTeaterKeFile(const char* namaKota, const char* namaBioskop, const TeaterInfo* teater);
int SearchTeaterFile(const char* namaKota, const char* namaBioskop, const TeaterInfo* teater);
void EditTeaterKeFile(const char* namaKota, const char* namaBioskop, const TeaterInfo* teater, const TeaterInfo* teaterLama);
void HapusTeaterKeFile(const char* namaKota, const char* namaBioskop, const TeaterInfo* teaterLama);
// void KosongkanFileTeater();
void LoadTeater(address root);

address AlokasiTeater(TeaterInfo X);
void DeAlokasiTeater(address P);

void TambahTeater(address bioskop, const char* namaTeater, int jumlahKursi);
void TambahTeaterBaru(address kota, address bioskop, const char* namaTeater, int jumlahKursi);

void UbahTeater(address node, TeaterInfo dataBaru);

void DeleteTeater(address teater);
void DeleteAllTeater(address bioskop);

int CompareTeater(infotype a, infotype b);
address SearchTeater(address bioskop, const char* namaTeater);

void PrintTeater(address node, int level);


#endif