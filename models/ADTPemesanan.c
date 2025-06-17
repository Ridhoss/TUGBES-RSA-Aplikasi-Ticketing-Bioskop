#include "header/ADTPemesanan.h"

// Deskripsi: Procedure untuk menyimpan data transaksi ke dalam file teks transaksi.txt
// I.S.: Data transaksi trx sudah tersedia
// F.S.: Data transaksi trx ditulis ke dalam file transaksi.txt.
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

// Deskripsi: Procedure untuk menyimpan detail kursi yang dipesan dalam sebuah transaksi ke file detail_transaksi.txt
// I.S.: Data detail transaksi tersedia
// F.S.: Data detail transaksi ditambahkan ke detail_transaksi.txt
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

// Deskripsi: Procedure untuk menandai kursi yang sudah terisi pada jadwal yang sesuai
// I.S.: data kursi terisi; data jadwal belum ditandai.
// F.S.: kursi pada jadwal->kursi ditandai 'X' sesuai data di file.
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

// Deskripsi: Procedure untuk membaca data dari file transaksi.txt dan memasukkan transaksi milik idUser ke dalam stack S.
// I.S.: Stack S kosong
// F.S.: Stack S berisi transaksi milik idUser
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

// Deskripsi: Procedure untuk memasukkan transaksi milik idUser dengan tanggal tertentu ke dalam stack S.
// I.S.: Stack S belum berisi transaksi
// F.S.: Stack S berisi transaksi milik idUser pada tanggal tanggalTrans
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

// Deskripsi: Procedure untuk memasukkan transaksi dengan idBioskop tertentu ke dalam stack S.
// I.S.: Stack S belum terisi
// F.S.: Stack S terisi dengan transaksi yang memiliki idBioskop sesuai parameter input.
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

// Deskripsi: Procedure untuk memuat transaksi aktif milik user tertentu dari file transaksi.txt, memeriksa validitas waktu jadwal dari data global, dan menyimpannya ke dalam stack S.
// I.S.: Stack S kosong dan file transaksi.txt tersedia; data jadwal berada pada root.
// F.S.: Stack S berisi transaksi aktif milik idUser, ditentukan dari waktu jadwal yang masih berlaku.
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

// Deskripsi: Procedure untuk mencetak riwayat seluruh transaksi dalam stack S, lengkap dengan informasi film, bioskop, waktu tayang, dan detail kursi yang dipesan.
// I.S.: Stack S sudah berisi transaksi pengguna, dan semua data pendukung (film, bioskop, jadwal) tersedia.
// F.S.: Riwayat transaksi pengguna ditampilkan ke layar
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

// Deskripsi: Procedure untuk mengambil semua data kursi untuk ID transaksi tertentu, dan menyimpannya ke dalam list L.
// I.S.: List L belum berisi data kursi
// F.S.: List L terisi data DetailTransaksi yang sesuai dengan idTransaksi yang dicari.
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

// Deskripsi: Fungsi untuk mencari dan mengembalikan data transaksi dari file berdasarkan ID transaksi yang dicari.
// I.S.: ID transaksi diketahui.
// F.S.: Jika ditemukan, data transaksi dikembalikan dalam pointer
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

// Deskripsi: Procedure untuk memperbarui status suatu transaksi berdasarkan ID-nya dalam file transaksi.txt
// I.S.: File transaksi.txt berisi data transaksi dengan status lama.
// F.S.: Status transaksi dengan ID yang sesuai diperbarui dan disimpan kembali ke file.
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

// Deskripsi: Procedure untuk menyimpan transaksi pembelian tiket berdasarkan kursi yang dipilih user, lalu memperbarui kursi yang telah dipesan dan menyimpan detail transaksi ke file.
// I.S.: Jadwal, user ID, dan array kursi dipilih telah ditentukan.
// F.S.: Transaksi disimpan di file transaksi.txt, detail kursi disimpan di detail_transaksi.txt, dan kursi di jadwal ditandai 'X'.
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

// Deskripsi: Fungsi untuk menghasilkan ID transaksi unik berdasarkan idUser, tanggal hari ini, dan Jumlah transaksi yang sudah dilakukan user tersebut di tanggal yang sama.
// I.S.: File transaksi.txt berisi daftar transaksi.
// F.S.: ID transaksi baru dibentuk dan dikembalikan sebagai int.
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

// Deskripsi: Fungsi untuk menghitung total pendapatan dan jumlah tiket yang terjual dari sebuah bioskop tertentu berdasarkan ID bioskop yang diberikan
// I.S.: File transaksi.txt sudah tersedia
// F.S.: jumlahTiket berisi total tiket terjual untuk bioskop tersebut dan return value adalah total pendapatan.
int HitungPenjualanBioskop(int idBioskop, int* jumlahTiket) {
    FILE* file = fopen("database/transaksi.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file transaksi.\n");
        *jumlahTiket = 0;
        return 0;
    }

    char buffer[256];
    int totalPendapatan = 0;
    *jumlahTiket = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        int idTrans, idUser, idFilm, idBioskopTrans, jumlah, harga, total;
        char tanggal[20], status[20];

        sscanf(buffer, "%d|%d|%d|%d|%[^|]|%d|%d|%d|%s",
               &idTrans, &idUser, &idFilm, &idBioskopTrans, tanggal, &jumlah, &harga, &total, status);

        if (idBioskopTrans == idBioskop) {
            *jumlahTiket += jumlah;
            totalPendapatan += total;
        }
    }

    fclose(file);
    return totalPendapatan;
}

