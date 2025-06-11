#ifndef ADTJadwal_h
#define ADTJadwal_h

#include "../../library/boolean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTTree.h"
#include "ADTTeater.h"

typedef struct {
    char start[20];
    char end[20];
    // date tanggal;
    char kursi[20][20]; 
    // address film;
    int jumlahBaris;
    int jumlahKolom;
} JadwalInfo;

void SimpanJadwalKeFile(const char* namaKota, const char* namaBioskop, const char* namaTeater, const JadwalInfo* jadwal);
int SearchJadwalFile(const char* namaKota, const char* namaBioskop, const char* namaTeater, const JadwalInfo* jadwal);
void EditJadwalKeFile(const char* namaKota, const char* namaBioskop, const char* namaTeater, const JadwalInfo* jadwal, const JadwalInfo* jadwalLama);
void HapusJadwalKeFile(const char* namaKota, const char* namaBioskop, const char* namaTeater, const JadwalInfo* jadwalLama);
// void KosongkanFileTeater();
void LoadJadwal(address root);

address AlokasiJadwal(JadwalInfo X);
void DeAlokasiJadwal(address P);

void TambahJadwal(address teater, JadwalInfo jadwalBaru);
void TambahJadwalBaru(address kota, address bioskop, address teater, JadwalInfo jadwalBaru);
void InisialisasiKursi(JadwalInfo *jadwal, address teaterAddress);

void UbahJadwal(address node, JadwalInfo jadwalBaru);

void DeleteJadwal(address jadwal);
void DeleteAllJadwal(address teater);

int CompareJadwal(infotype a, infotype b);
address SearchJadwal(address teater, const char* namaJadwal);

void PrintJadwal(address node, int level);

#endif
