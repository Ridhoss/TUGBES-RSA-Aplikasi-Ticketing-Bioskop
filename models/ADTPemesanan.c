#include "header/ADTPemesanan.h"

void SimpanTransaksiKeFile(Transaksi trx) {
    FILE* file = fopen("database/transaksi.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d|%d|%d|%d|%d|%d\n",
            trx.id, trx.idUser, trx.idFilm,
            trx.jumlahTiket, trx.harga, trx.totalHarga);
        fclose(file);
    } else {
        printf("Gagal membuka file transaksi.txt\n");
    }
}

void SimpanDetailTransaksiKeFile(DetailTransaksi detail) {
    FILE* file = fopen("database/detail_transaksi.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d|%d|%d|%d\n",
            detail.idTransaksi, detail.idJadwal,
            detail.baris, detail.kolom);
        fclose(file);
    } else {
        printf("Gagal membuka file detail_transaksi.txt\n");
    }
}

void LoadKursiTerisi(JadwalInfo* jadwal) {
    FILE* file = fopen("database/detail_transaksi.txt", "r");
    if (!file) return;

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        int idTransaksi, idJadwal, baris, kolom;
        if (sscanf(buffer, "%d|%d|%d|%d", &idTransaksi, &idJadwal, &baris, &kolom) == 4) {
            if (idJadwal == jadwal->id) {

                jadwal->kursi[baris - 1][kolom] = 'X';
            }
        }
    }

    fclose(file);
}


void AksiTransaksi(address jadwalNode, Kursi kursiDipilih[], int jumlahDipilih, int idUser) {
    if (jadwalNode == NULL || jadwalNode->info == NULL) return;

    JadwalInfo* jadwal = (JadwalInfo*)jadwalNode->info;
    TeaterInfo* teater = NULL;

    if (jadwalNode->pr->type == TEATER) {
        teater = (TeaterInfo*)jadwalNode->pr->info;
    } else {
        printf("Gagal mengambil data teater.\n");
        return;
    }

    date today;
    GetToday(&today);
    int idBaru = BuatIdTransaksiBaru(idUser, today);

    int hargaTiket = teater->harga;
    if (IsWeekend(jadwal->tanggal)) {
        hargaTiket += 5000;
    }

    Transaksi trx;
    trx.id = idBaru;
    trx.idUser = idUser;
    trx.idFilm = jadwal->film->idFilm;
    trx.jumlahTiket = jumlahDipilih;
    trx.harga = hargaTiket;
    trx.totalHarga = trx.harga * trx.jumlahTiket;

    SimpanTransaksiKeFile(trx);

    for (int i = 0; i < jumlahDipilih; i++) {
        int baris = kursiDipilih[i].baris;
        int kolom = kursiDipilih[i].kolom - 'A';

        jadwal->kursi[baris - 1][kolom] = 'X';

        DetailTransaksi dt;
        dt.idTransaksi = idBaru;
        dt.idJadwal = jadwal->id;
        dt.baris = baris;
        dt.kolom = kolom;

        SimpanDetailTransaksiKeFile(dt);
    }

    printf("Transaksi berhasil disimpan dengan ID #%d.\n", idBaru);
}

int BuatIdTransaksiBaru(int idUser, date today) {
    FILE* file = fopen("database/transaksi.txt", "r");
    if (!file) file = fopen("database/transaksi.txt", "w");
    if (!file) return -1;

    char buffer[200];
    int increment = 0;
    char targetTanggal[7];
    sprintf(targetTanggal, "%02d%02d%02d", today.Tgl, today.Bln, today.Thn % 100);

    while (fgets(buffer, sizeof(buffer), file)) {
        int id;
        if (sscanf(buffer, "%d|", &id) == 1) {
            char idStr[20];
            sprintf(idStr, "%d", id);

            if (strstr(idStr, targetTanggal) != NULL) {
                increment++;
            }
        }
    }

    fclose(file);

    // Susun ID: [idUser][tanggal][urutan]
    char finalIdStr[20];
    sprintf(finalIdStr, "%d%02d%02d%02d%02d", idUser, today.Tgl, today.Bln, today.Thn % 100, increment + 1);
    return atoi(finalIdStr);
}

