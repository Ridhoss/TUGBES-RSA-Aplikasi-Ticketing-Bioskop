#include "header/ADTPemesanan.h"


// manipulation file file

void SimpanTransaksiKeFile(Transaksi trx) {
    FILE* file = fopen("database/transaksi.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d|%d|%d|%d|%d/%d/%d|%d|%d|%d|%s\n",
            trx.id, trx.idUser, trx.idFilm, trx.idBioskop, trx.tanggal.Tgl, trx.tanggal.Bln, trx.tanggal.Thn,
            trx.jumlahTiket, trx.harga, trx.totalHarga, trx.status);
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





// stack, list and file

void IsiStackTransaksiById(Stack *S, int idUser) {
    FILE* file = fopen("database/transaksi.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file transaksi.txt\n");
        return;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), file)) {
        Transaksi trx;
        if (sscanf(buffer, "%d|%d|%d|%d|%d/%d/%d|%d|%d|%d|%s", 
                    &trx.id, &trx.idUser, &trx.idFilm, &trx.idBioskop, &trx.tanggal.Tgl, &trx.tanggal.Bln, &trx.tanggal.Thn,
                    &trx.jumlahTiket, &trx.harga, &trx.totalHarga, &trx.status) == 11) {

            if (trx.idUser == idUser || idUser == -1) {
                Transaksi* salinan = (Transaksi*)malloc(sizeof(Transaksi));
                if (salinan != NULL) {
                    *salinan = trx;
                    Push(S, (infotype)salinan);
                }
            }
        }
    }

    fclose(file);
}

void IsiStackTransaksiByDate(Stack *S, int idUser, date tanggalTrans) {
    FILE* file = fopen("database/transaksi.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file transaksi.txt\n");
        return;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), file)) {
        Transaksi trx;
        if (sscanf(buffer, "%d|%d|%d|%d|%d/%d/%d|%d|%d|%d|%s", 
                    &trx.id, &trx.idUser, &trx.idFilm, &trx.idBioskop, &trx.tanggal.Tgl, &trx.tanggal.Bln, &trx.tanggal.Thn,
                    &trx.jumlahTiket, &trx.harga, &trx.totalHarga, &trx.status) == 11) {

            if ((trx.idUser == idUser || idUser == -1) && isSameDate(trx.tanggal, tanggalTrans)) {
                Transaksi* salinan = (Transaksi*)malloc(sizeof(Transaksi));
                if (salinan != NULL) {
                    *salinan = trx;
                    Push(S, (infotype)salinan);
                }
            }
        }
    }

    fclose(file);
}

void IsiStackTransaksiByBioskop(Stack* S, int idBioskop) {
    FILE* file = fopen("database/transaksi.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file transaksi.txt\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        Transaksi trx;

        if (sscanf(buffer, "%d|%d|%d|%d|%d/%d/%d|%d|%d|%d|%s", 
                    &trx.id, &trx.idUser, &trx.idFilm, &trx.idBioskop, &trx.tanggal.Tgl, &trx.tanggal.Bln, &trx.tanggal.Thn,
                    &trx.jumlahTiket, &trx.harga, &trx.totalHarga, &trx.status) == 11) {
            
            if (trx.idBioskop == idBioskop) {
                Transaksi* salinan = (Transaksi*)malloc(sizeof(Transaksi));
                if (salinan != NULL) {
                    *salinan = trx;
                    Push(S, (infotype)salinan);
                }
            }
        }
    }

    fclose(file);
}

void IsiStackPesananAktif(Stack *S, int idUser, address root) {
    FILE *file = fopen("database/transaksi.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file transaksi.txt\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        Transaksi trx;
        if (sscanf(buffer, "%d|%d|%d|%d|%d/%d/%d|%d|%d|%d|%s", 
                    &trx.id, &trx.idUser, &trx.idFilm, &trx.idBioskop, &trx.tanggal.Tgl, &trx.tanggal.Bln, &trx.tanggal.Thn,
                    &trx.jumlahTiket, &trx.harga, &trx.totalHarga, &trx.status) == 11) {

            if (trx.idUser == idUser) {
                List listDetail;
                AmbilDetailTransaksi(&listDetail, trx.id);

                boolean aktif = false;

                addressList p = listDetail.First;
                while (p != NULL && !aktif) {
                    DetailTransaksi *dt = (DetailTransaksi *)p->info;
                    address nodeJadwal = CariJadwalByIdGlobal(root, dt->idJadwal);

                    if (nodeJadwal != NULL) {
                        JadwalInfo *jadwal = (JadwalInfo *)nodeJadwal->info;

                        if (isDateTimeValid(jadwal->tanggal, jadwal->Start)) {
                            aktif = true;
                        }
                        
                    }

                    p = p->next;
                }

                DelAll(&listDetail);

                if (aktif) {
                    Transaksi *salinan = (Transaksi *)malloc(sizeof(Transaksi));
                    if (salinan != NULL) {
                        *salinan = trx;
                        Push(S, (infotype)salinan);
                    }
                }
            }
        }
    }

    fclose(file);
}

void PrintStackTransaksi(Stack S, List filmList, address root) {
    if (IsEmptyStack(S)) {
        printf("Belum ada transaksi.\n");
        printf("===================================================\n");

        return;
    }

    int i = 1;
    addressList p = S.First;

    printf("===================================================\n");
    printf("================ History Pemesanan ================\n");
    printf("===================================================\n");

    while (p != NULL) {
        Transaksi *trx = (Transaksi *)p->info;

        addressList film = cariFilm(filmList, trx->idFilm);
        FilmInfo* infoFilm = (FilmInfo*)(film->info);

        address nodeKota = CariKotaDariIdBioskop(root, trx->idBioskop);
        address nodeBioskop = SearchBioskopById(nodeKota, &trx->idBioskop);
        BioskopInfo* infoBioskop = (BioskopInfo*)(nodeBioskop->info);

        List kursi;
        AmbilDetailTransaksi(&kursi, trx->id);
        TimeInfo jamStart, jamEnd;

        Akun* users = CariAkunById(trx->idUser);

        if (kursi.First != NULL) {
            DetailTransaksi* d = (DetailTransaksi*)kursi.First->info;
            address nodeJadwal = CariJadwalByIdGlobal(root, d->idJadwal);
            if (nodeJadwal != NULL) {
                JadwalInfo* jadwal = (JadwalInfo*)nodeJadwal->info;
                jamStart = jadwal->Start;
                jamEnd = jadwal->End;
            }
        }


        printf("Transaksi #%d\n", i++);
        printf("ID Transaksi     : %d\n", trx->id);
        printf("Status Pemesanan : %s\n", trx->status);
        printf("Username         : %s\n", users->username);
        printf("Film             : %s\n", infoFilm->judul);
        printf("Jam Tayang       : %02d:%02d - %02d:%02d\n", jamStart.jam, jamStart.menit,  jamEnd.jam, jamEnd.menit);
        printf("Bioskop          : %s\n", infoBioskop->nama);
        printf("Tanggal          : %d/%d/%d\n", trx->tanggal.Tgl, trx->tanggal.Bln, trx->tanggal.Thn);
        printf("Jumlah Tiket     : %d\n", trx->jumlahTiket);
        printf("Harga Tiket      : %d\n", trx->harga);
        printf("Total Bayar      : %d\n", trx->totalHarga);

        printf("Daftar Kursi : ");
        if (kursi.First == NULL) {
            printf("Tidak ada\n");
        } else {
            addressList k = kursi.First;
            while (k != NULL) {
                DetailTransaksi *d = (DetailTransaksi *)k->info;
                char kolomHuruf = 'A' + d->kolom;
                printf("%c%d ", kolomHuruf, d->baris);
                k = k->next;
            }
            printf("\n");
        }

        DelAll(&kursi);
        printf("===================================================\n");


        p = p->next;
    }
}

void AmbilDetailTransaksi(List *L, int idTransaksi) {
    CreateList(L);

    FILE *file = fopen("database/detail_transaksi.txt", "r");
    if (!file) return;

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        DetailTransaksi detail;
        if (sscanf(buffer, "%d|%d|%d|%d", &detail.idTransaksi, &detail.idJadwal, &detail.baris, &detail.kolom) == 4) {
            if (detail.idTransaksi == idTransaksi) {
                DetailTransaksi *salinan = (DetailTransaksi *) malloc(sizeof(DetailTransaksi));
                if (salinan != NULL) {
                    *salinan = detail;
                    InsLast(L, (infotype)salinan);
                }
            }
        }
    }

    fclose(file);
}

Transaksi* SearchTransaksiById(int idTransaksi) {
    FILE* file = fopen("database/transaksi.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file transaksi.txt\n");
        return NULL;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        Transaksi trx;
        if (sscanf(buffer, "%d|%d|%d|%d|%d/%d/%d|%d|%d|%d|%s",
                   &trx.id, &trx.idUser, &trx.idFilm, &trx.idBioskop,
                   &trx.tanggal.Tgl, &trx.tanggal.Bln, &trx.tanggal.Thn,
                   &trx.jumlahTiket, &trx.harga, &trx.totalHarga, &trx.status) == 11) {

            if (trx.id == idTransaksi) {
                Transaksi* hasil = (Transaksi*)malloc(sizeof(Transaksi));
                if (hasil != NULL) {
                    *hasil = trx;
                    fclose(file);
                    return hasil;
                }
            }
        }
    }

    fclose(file);
    return NULL;
}

void UpdateStatusTransaksiById(int id, const char* statusBaru) {
    FILE* file = fopen("database/transaksi.txt", "r");
    FILE* temp = fopen("database/temp_transaksi.txt", "w");

    if (!file || !temp) {
        printf("Gagal membuka file transaksi.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        Transaksi trx;
        if (sscanf(buffer, "%d|%d|%d|%d|%d/%d/%d|%d|%d|%d|%s",
                   &trx.id, &trx.idUser, &trx.idFilm, &trx.idBioskop,
                   &trx.tanggal.Tgl, &trx.tanggal.Bln, &trx.tanggal.Thn,
                   &trx.jumlahTiket, &trx.harga, &trx.totalHarga, &trx.status) == 11) {

            if (trx.id == id) {
                strcpy(trx.status, statusBaru); // Ubah status
            }

            // Simpan ke file temp
            fprintf(temp, "%d|%d|%d|%d|%d/%d/%d|%d|%d|%d|%s\n",
                    trx.id, trx.idUser, trx.idFilm, trx.idBioskop,
                    trx.tanggal.Tgl, trx.tanggal.Bln, trx.tanggal.Thn,
                    trx.jumlahTiket, trx.harga, trx.totalHarga, trx.status);
        }
    }

    fclose(file);
    fclose(temp);
    remove("database/transaksi.txt");
    rename("database/temp_transaksi.txt", "database/transaksi.txt");
}








// modul utama

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

    int idBioskop = -1;
    if (jadwalNode->pr && jadwalNode->pr->pr && jadwalNode->pr->pr->type == BIOSKOP) {
        BioskopInfo* bioskop = (BioskopInfo*)jadwalNode->pr->pr->info;
        idBioskop = bioskop->id;
    } else {
        printf("Gagal mengambil data bioskop.\n");
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
    trx.idBioskop = idBioskop;
    trx.tanggal = today;
    trx.jumlahTiket = jumlahDipilih;
    trx.harga = hargaTiket;
    trx.totalHarga = trx.harga * trx.jumlahTiket;
    strcpy(trx.status, "ACTIVE");

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

    char finalIdStr[20];
    sprintf(finalIdStr, "%d%02d%02d%02d%02d", idUser, today.Tgl, today.Bln, today.Thn % 100, increment + 1);
    return atoi(finalIdStr);
}
