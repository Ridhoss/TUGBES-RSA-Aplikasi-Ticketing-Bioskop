#ifndef adtpemesanan_h
#define adtpemesanan_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../library/boolean.h"
#include "../../library/date.h"

#include "ADTTree.h"
#include "ADTJadwal.h"



typedef struct {
    int id;
    int idUser;
    int idFilm;
    int jumlahTiket;
    int harga;
    int totalHarga;
} Transaksi;

typedef struct {
    int idTransaksi;
    int idJadwal;
    int baris;
    int kolom;
} DetailTransaksi;

void SimpanTransaksiKeFile(Transaksi trx);
void SimpanDetailTransaksiKeFile(DetailTransaksi detail);
void LoadKursiTerisi(JadwalInfo* jadwal);

void AksiTransaksi(address jadwalNode, Kursi kursiDipilih[], int jumlahDipilih, int idUser);
int BuatIdTransaksiBaru(int idUser, date today);

#endif 