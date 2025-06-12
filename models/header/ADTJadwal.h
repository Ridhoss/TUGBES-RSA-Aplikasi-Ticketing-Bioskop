#ifndef ADTJadwal_h
#define ADTJadwal_h

#include "../../library/boolean.h"
#include "../../library/date.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTTree.h"
#include "ADTTeater.h"

typedef struct {
    int id;
    char start[20];
    char end[20];
    date tanggal;
    char kursi[20][20]; 
    // FilmInfo *idFilm;
    int jumlahBaris;
    int jumlahKolom;
} JadwalInfo;

void SimpanJadwalKeFile(const int* idKota, const int* idBioskop, const int* idTeater, const int* idFilm, const JadwalInfo* jadwal);
int SearchJadwalFile(const JadwalInfo* jadwal);
void EditJadwalKeFile(const JadwalInfo* jadwal, const JadwalInfo* jadwalLama);
void HapusJadwalKeFile(const JadwalInfo* jadwalLama);
void KosongkanFileJadwal();
void LoadJadwal(address root);
int AmbilIdJadwalTerakhir();

address AlokasiJadwal(JadwalInfo X);
void DeAlokasiJadwal(address P);

void TambahJadwal(address teater, JadwalInfo jadwalBaru);
void TambahJadwalBaru(address kota, address bioskop, address teater, JadwalInfo jadwalBaru);
void InisialisasiKursi(JadwalInfo *jadwal, address teaterAddress);

void UbahJadwal(address node, JadwalInfo jadwalBaru);

void DeleteJadwal(address jadwal);
void DeleteAllJadwal(address teater);

int CompareJadwal(infotype a, infotype b);
int CompareJadwalId(infotype a, infotype b);
address SearchJadwalByName(address teater, const char* namaJadwal);
address SearchJadwalById(address teater, const int* idJadwal);

void PrintJadwal(address node, int level);

#endif
