#ifndef adtpemesanan_h
#define adtpemesanan_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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


void AksiTransaksi(address jadwalNode, Kursi kursiDipilih[], int jumlahDipilih, int idUser);
int BuatIdTransaksiBaru(int idUser, date today);

#endif 