#ifndef ADTJadwal_h
#define ADTJadwal_h

#include "../../library/boolean.h"
#include "../../library/date.h"
#include "../../library/timing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTTree.h"
#include "ADTTeater.h"
#include "ADTFilm.h"

typedef struct {
    int id;
    TimeInfo Start;
    TimeInfo End;
    date tanggal;
    FilmInfo *film;
    char kursi[20][20]; 
    int jumlahBaris;
    int jumlahKolom;
} JadwalInfo;

void SimpanJadwalKeFile(const int* idKota, const int* idBioskop, const int* idTeater, const JadwalInfo* jadwal);
int SearchJadwalFile(const JadwalInfo* jadwal);
void EditJadwalKeFile(const JadwalInfo* jadwal, const JadwalInfo* jadwalLama);
void HapusJadwalKeFile(const JadwalInfo* jadwalLama);
void KosongkanFileJadwal();
void LoadJadwal(address root, List ListFilm);
int AmbilIdJadwalTerakhir();

address AlokasiJadwal(JadwalInfo X);
void DeAlokasiJadwal(address P);

void TambahJadwal(address teater, JadwalInfo jadwalBaru);
void TambahJadwalBaru(address kota, address bioskop, address teater, JadwalInfo jadwalBaru, int jmlHari);
void InisialisasiKursi(JadwalInfo *jadwal, address teaterAddress);
void AmbilJadwalTeaterKeList(address nodeTeater, List* L);
boolean AdaJadwalBentrok(List L, date tanggal, TimeInfo start, TimeInfo end, int idKecuali);
void AmbilJadwalTeaterTanggalKeList(address teater, date tanggal, List* hasil);
void AmbilJadwalTeaterFilmKeList(address teater, addressList filmNode, List* hasil);
void TampilkanListJadwal(List L);

void UbahJadwal(address node, JadwalInfo jadwalBaru);

void DeleteJadwal(address jadwal);
void DeleteAllJadwal(address teater);

int CompareJadwal(infotype a, infotype b);
int CompareJadwalId(infotype a, infotype b);
address SearchJadwalByName(address teater, const date* tanggal, const TimeInfo* start);
address SearchJadwalById(address teater, const int* idJadwal);

void PrintJadwal(address node, int level);

#endif
