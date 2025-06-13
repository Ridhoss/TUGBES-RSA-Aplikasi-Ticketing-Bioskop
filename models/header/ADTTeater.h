#ifndef ADTTeater_h
#define ADTTeater_h

#include "../../library/boolean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTTree.h"
#include "ADTBioskop.h"

typedef struct {
    int id;
    char nama[100];
    int jumlahKursi;
    int harga;
} TeaterInfo;

void SimpanTeaterKeFile(const int* idKota, const int* idBioskop, const TeaterInfo* teater);
int SearchTeaterFile(const TeaterInfo* teater);
void EditTeaterKeFile(const TeaterInfo* teater, const TeaterInfo* teaterLama);
void HapusTeaterKeFile(const TeaterInfo* teaterLama);
void KosongkanFileTeater();
void LoadTeater(address root);
int AmbilIdTeaterTerakhir();

address AlokasiTeater(TeaterInfo X);
void DeAlokasiTeater(address P);

void TambahTeater(address bioskop, TeaterInfo teaterBaru);
void TambahTeaterBaru(address kota, address bioskop, TeaterInfo teaterBaru);

void UbahTeater(address node, TeaterInfo dataBaru);

void DeleteTeater(address teater);
void DeleteAllTeater(address bioskop);

int CompareTeater(infotype a, infotype b);
int CompareTeaterId(infotype a, infotype b);
address SearchTeaterByName(address bioskop, const char* namaTeater);
address SearchTeaterById(address bioskop, const int* idTeater);

void PrintTeater(address node, int level);


#endif