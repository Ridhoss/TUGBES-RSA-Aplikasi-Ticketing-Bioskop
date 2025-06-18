#ifndef adtpemesanan_h
#define adtpemesanan_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../library/boolean.h"
#include "../../library/date.h"

#include "ADTTree.h"
#include "ADTJadwal.h"
#include "ADTStack.h"
#include "ADTQueue.h"
#include "ADTAkun.h"

typedef struct transaksi {
    int id;
    int idUser;
    int idFilm;
    int idBioskop;
    date tanggal;
    int jumlahTiket;
    int harga;
    int totalHarga;
    char status[100];
} Transaksi;

typedef struct detailTransaksi {
    int idTransaksi;
    int idJadwal;
    int baris;
    int kolom;
} DetailTransaksi;

void SimpanTransaksiKeFile(Transaksi trx);
void SimpanDetailTransaksiKeFile(DetailTransaksi detail);
void LoadKursiTerisi(JadwalInfo* jadwal);

void IsiStackTransaksiById(Stack *S, int idUser);
void IsiStackTransaksiByDate(Stack *S, int idUser, date tanggalTrans);
void IsiStackTransaksiByBioskop(Stack* S, int idBioskop);
void IsiStackPesananAktif(Stack *S, int idUser, address root);
void PrintStackTransaksi(Stack S, List filmList, address root);
void AmbilDetailTransaksi(List *L, int idTransaksi);
Transaksi* SearchTransaksiById(int idTransaksi);
void UpdateStatusTransaksiById(int id, const char* statusBaru);


void AksiTransaksi(address jadwalNode, Kursi kursiDipilih[], int jumlahDipilih, int idUser);
int BuatIdTransaksiBaru(int idUser, date today);
int HitungPenjualanBioskop(int idBioskop, int* jumlahTiket);

void formatRibuan(int angka, char *output);

#endif 