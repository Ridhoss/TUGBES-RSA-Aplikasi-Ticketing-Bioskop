#include "header/viewsUser.h"

void HalamanMenuUser(address root, List *L) {
    int idKotaDipilih;
    char namaKota[100], namaFilm[100];
    address kotaNode;
    List tampilFilm;
    
    printf("===================================================\n");
    printf("||          SELAMAT DATANG DI BIOSKOP            ||\n");
    printf("===================================================\n");
    PrintKota(root, 0);
    
    do {
        printf("\n>> Pilih kota: ");
        InputString(namaKota);

        kotaNode = SearchKotaByName(root, namaKota);

        if (!kotaNode) {
            printf("Kota '%s' tidak ditemukan. Silakan coba lagi.\n", namaKota);
        }
    } while (!kotaNode);

    int pilihan;
    do {
        printf("===================================================\n");
        KotaInfo* info = (KotaInfo*)(kotaNode->info);
        printf("           Menu User - Kota : %s            \n", info->nama);
        printf("===================================================\n");
        printf("||                                               ||\n");
        printf("||     1. Cari dan pilih film                    ||\n");
        printf("||     2. Lihat film upcoming                    ||\n");
        printf("||     3. Cari jadwal film                       ||\n");
        printf("||     4. Lihat daftar pesanan                   ||\n");
        printf("||     5. Keluar                                 ||\n");
        printf("||                                               ||\n");
        printf("|| Silakan pilih menu (1-5):                     ||\n");
        printf("===================================================\n");
        printf(">> ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: {
                KotaInfo* info = (KotaInfo*)(kotaNode->info);
                printf("===================================================\n");
                printf("         Film yang tersedia di %s      \n", info->nama);
                GetFilmByKota(kotaNode, &tampilFilm);

                if (ListEmpty(tampilFilm)) {
                    printf("Tidak ada film yang sedang tayang di kota ini.\n");
                } else {
                    printFilm(tampilFilm);
                    printf("===================================================\n");
                }

                printf("Pilih Film: ");
                InputString(namaFilm);

                addressList filmTerpilih = cariFilmByJudul(*L, namaFilm);

                HalamanPilihJadwal(root, L, kotaNode, filmTerpilih);

                break;
            }
            case 2:
                printUpcomingFilmsByKota(root, kotaNode);
                
                break;
            case 3:
                printf("belum tersedia)\n");

                break;
            case 4:
                printf("belum tersedia)\n");

                break;
            case 5:
                printf("Terima kasih telah menggunakan aplikasi.\n");
                
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 5);
}

void HalamanPilihJadwal(address root, List *L, address kotaNode, addressList filmNode) {
    FilmInfo* infoFilm = (FilmInfo*)(filmNode->info);
    date selectedDate;
    GetToday(&selectedDate);

    char namaBioskop[100], namaTeater[100];
    int jam, menit;
    TimeInfo jadwalTerpilih;

    int menu;
    do {
        printf("===================================================\n");
        printf("||           PILIH BIOSKOP DAN JADWAL            ||\n");
        printf("===================================================\n");
        printf("Judul      : %s\n", infoFilm->judul);
        printf("Produser   : %s\n", infoFilm->produser);
        printf("Deskripsi  : %s\n", infoFilm->deskripsi);
        printf("Durasi     : %d menit\n", ConvertMenit(infoFilm->durasi));
        printf("Tanggal    : %02d-%02d-%04d\n", selectedDate.Tgl, selectedDate.Bln, selectedDate.Thn);
        printf("===================================================\n");

        List semuaJadwalFilm;
        AmbilSeluruhJadwalKotaKeListByFilm(kotaNode, filmNode, &semuaJadwalFilm);

        int ditemukan = 0;
        address nodeBioskop = kotaNode->fs;
        while (nodeBioskop != NULL) {
            BioskopInfo* bioskop = (BioskopInfo*)nodeBioskop->info;
            int adaJadwalBioskop = 0;

            address nodeTeater = nodeBioskop->fs;
            while (nodeTeater != NULL) {
                TeaterInfo* teater = (TeaterInfo*)nodeTeater->info;
                int adaJadwalTeater = 0;

                addressList p = semuaJadwalFilm.First;
                while (p != NULL) {
                    address jadwalNode = (address)p->info;
                    JadwalInfo* j = (JadwalInfo*)jadwalNode->info;

                    if (jadwalNode->pr == nodeTeater &&
                        j->tanggal.Tgl == selectedDate.Tgl &&
                        j->tanggal.Bln == selectedDate.Bln &&
                        j->tanggal.Thn == selectedDate.Thn) {

                        if (!adaJadwalBioskop) {
                            printf("===================================================\n");
                            printf("Bioskop  : %s\n", bioskop->nama);
                            adaJadwalBioskop = 1;
                            ditemukan = 1;
                        }

                        if (!adaJadwalTeater) {
                            printf("--------------------------------------------------\n");
                            printf("  Teater : %s\n", teater->nama);
                            printf("  Harga  : Rp%d\n", teater->harga);
                            printf("    Jam  : ");
                            adaJadwalTeater = 1;
                        }

                        printf("| %02d:%02d |", j->Start.jam, j->Start.menit);
                    }

                    p = p->next;
                }

                if (adaJadwalTeater) {
                    printf("\n");
                }

                nodeTeater = nodeTeater->nb;
            }

            if (adaJadwalBioskop) {
                printf("===================================================\n");
            }

            nodeBioskop = nodeBioskop->nb;
        }

        if (!ditemukan) {
            printf("Belum ada jadwal film ini untuk tanggal tersebut.\n");
        }

        DelAll(&semuaJadwalFilm);

        // Menu navigasi
        printf("\nMenu:\n");
        printf("1. Lihat Jadwal Besok\n");
        printf("2. Cari Berdasarkan Tanggal\n");
        printf("3. Pilih Jadwal\n");
        printf("4. Kembali\n");
        printf("Pilihan Anda: ");
        scanf("%d", &menu);
        getchar();

        if (menu == 1) {
            selectedDate = TambahHari(selectedDate, 1);

        } else if (menu == 2) {
            printf("Masukan tanggal ( dd/mm/yyyy ): ");
            scanf("%d/%d/%d", &selectedDate.Tgl, &selectedDate.Bln, &selectedDate.Thn);

        } else if (menu == 3 && ditemukan) {
            // Lanjut ke proses pemilihan jadwal/tiket
            printf("Nama bioskop yang dipilih: ");
            InputString(namaBioskop);
            address nodeBioskop = SearchBioskopByName(kotaNode, namaBioskop);

            printf("Nama teater yang dipilih: ");
            InputString(namaTeater);
            address nodeTeater = SearchTeaterByName(nodeBioskop, namaTeater);

            printf("Masukan jam jadwal yang dipilih ( jam:menit ): ");
            scanf("%d:%d", &jam, &menit);
            SetTime(&jadwalTerpilih, jam, menit);
            address nodeJadwal = SearchJadwalByName(nodeTeater, &selectedDate, &jadwalTerpilih);

            HalamanPilihKursi(root, L, nodeJadwal);

            system("pause");
        }

    } while (menu != 4);
}


void HalamanPilihKursi(address root, List *L, address nodeJadwal) {
    if (nodeJadwal == NULL || nodeJadwal->info == NULL) {
        printf("Data jadwal tidak ditemukan.\n");
        return;
    }

    JadwalInfo* jadwalInfo = (JadwalInfo*)(nodeJadwal->info);
    FilmInfo* infoFilm = jadwalInfo->film;

    printf("Jumlah Baris: %d, Kolom: %d\n", jadwalInfo->jumlahBaris, jadwalInfo->jumlahKolom); // debug

    printf("===================================================\n");
    printf("||           PILIH BIOSKOP DAN JADWAL            ||\n");
    printf("===================================================\n");
    printf("Judul      : %s\n", infoFilm->judul);
    printf("Produser   : %s\n", infoFilm->produser);
    printf("Deskripsi  : %s\n", infoFilm->deskripsi);
    printf("Durasi     : %d menit\n", ConvertMenit(infoFilm->durasi));
    printf("Tanggal    : %02d-%02d-%04d\n", jadwalInfo->tanggal.Tgl, jadwalInfo->tanggal.Bln, jadwalInfo->tanggal.Thn);
    printf("Jam        : %02d:%02d\n", jadwalInfo->Start.jam, jadwalInfo->Start.menit);
    printf("===================================================\n");

    printf("Tampilan Kursi (O = kosong, X = terisi)\n\n");

    printf("    ");
    for (int j = 0; j < jadwalInfo->jumlahKolom; j++) {
        printf(" %c ", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < jadwalInfo->jumlahBaris; i++) {
        printf("%2d  ", i + 1);
        for (int j = 0; j < jadwalInfo->jumlahKolom; j++) {
            printf(" %c ", jadwalInfo->kursi[i][j]);
        }
        printf("\n");
    }

    printf("===================================================\n");

    // Meminta input dari pengguna
    Kursi pilih;
    printf("Masukkan kursi (contoh 4C): ");
    scanf("%d%c", &pilih.baris, &pilih.kolom);

    int i = pilih.baris - 1;
    int j = pilih.kolom - 'A';

    if (i < 0 || i >= jadwalInfo->jumlahBaris || 
        j < 0 || j >= jadwalInfo->jumlahKolom) {
        printf("Pilihan kursi tidak valid.\n");
        return;
    }

    if (jadwal->kursi[i][j] == '0') {
        jadwal->kursi[i][j] = 'X';
        printf("Kursi %d%c berhasil dipesan!\n", pilih.baris, pilih.kolom);
    } else {
        printf("Kursi %d%c sudah terisi.\n", pilih.baris, pilih.kolom);
    }
}
