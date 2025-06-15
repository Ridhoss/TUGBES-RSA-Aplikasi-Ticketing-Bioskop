#include "header/viewsUser.h"

void HalamanMenuUser(address root, List *L) {
    // StackMenu stackMenu;
    // CreateStack(&stackMenu);
    // Push(&stackMenu, "Menu Utama");

    date selectedDate;
    GetToday(&selectedDate);

    int idKotaDipilih;
    char namaKota[100], namaFilm[100];
    address kotaNode;
    List tampilFilm;

    TimeInfo jamAwal, jamAkhir;
    int jam, mnt;

    
    printf("===================================================\n");
    printf("||          SELAMAT DATANG DI BIOSKOP            ||\n");
    printf("===================================================\n");
    PrintKota(root, 0);
    
    do {
        printf("\n>> Pilih kota ");
        InputString(namaKota);

        kotaNode = SearchKotaByName(root, namaKota);

        if (!kotaNode) {
            printf("Kota '%s' tidak ditemukan. Silakan coba lagi.\n", namaKota);
        }
    } while (!kotaNode);

    int pilihan;
    do {
        KotaInfo* info = (KotaInfo*)(kotaNode->info);
        printf("===================================================\n");
        printf("           Menu User - Kota : %s       \n", info->nama);
        printf("===================================================\n");
        printf("||                                               ||\n");
        printf("||     1. Cari dan pilih film                    ||\n");
        printf("||     2. Lihat film upcoming                    ||\n");
        printf("||     3. Cari jadwal film                       ||\n");
        printf("||     4. Lihat History Transaksi                ||\n");
        printf("||     5. Logout                                 ||\n");
        printf("||                                               ||\n");
        printf("|| Pilihan menu (1-5):                           ||\n");
        printf("===================================================\n");
        printf(">> ");
        scanf("%d", &pilihan);
        getchar();
        
        switch (pilihan) {
            case 1: {
                // Push(&stackMenu, "Cari dan pilih film");

                KotaInfo* info = (KotaInfo*)(kotaNode->info);
                printf("===================================================\n");
                printf("         Film yang tersedia di %s      \n", info->nama);
                GetFilmByKota(kotaNode, &tampilFilm);

                if (ListEmpty(tampilFilm)) {
                    printf("Tidak ada film yang sedang tayang di kota ini.\n");

                    // Pop(&stackMenu);

                    break;
                } else {
                    printFilm(tampilFilm);
                    printf("===================================================\n");
                }

                printf("Pilih Film: ");
                InputString(namaFilm);

                addressList filmTerpilih = cariFilmByJudul(*L, namaFilm);
                if (filmTerpilih == NULL) {
                    printf("Film tidak ditemukan.\n");

                    // Pop(&stackMenu);

                    break;
                }

                HalamanPilihJadwal(root, L, kotaNode, filmTerpilih, selectedDate);

                // Pop(&stackMenu);

                break;
            }
            case 2:{
                // Push(&stackMenu, "Lihat film upcoming");
                
                KotaInfo* info = (KotaInfo*)(kotaNode->info);
                printf("===================================================\n");
                printf("         Film yang upcoming di %s      \n", info->nama);
                GetFilmUpcoming(kotaNode, &tampilFilm);
                
                if (ListEmpty(tampilFilm)) {
                    printf("Tidak ada film yang upcoming di kota ini.\n");
                    
                    // Pop(&stackMenu);

                    break;
                } else {
                    printFilm(tampilFilm);
                    printf("===================================================\n");
                }

                printf("Pilih Film: ");
                InputString(namaFilm);

                addressList filmTerpilih = cariFilmByJudul(*L, namaFilm);
                if (filmTerpilih == NULL) {
                    printf("Film tidak ditemukan.\n");

                    // Pop(&stackMenu);

                    break;
                }

                FilmInfo* infoFilm = (FilmInfo*)(filmTerpilih->info);
                date tanggalTayang = CariTanggalTayangPertama(kotaNode, infoFilm);

                HalamanPilihJadwal(root, L, kotaNode, filmTerpilih, tanggalTayang);

                // Pop(&stackMenu);

                break;
            }
            case 3: {
                printf("===================================================\n");
                printf("========== Cari Film Berdasarkan Tanggal ==========\n");
                printf("===================================================\n");

                do {
                    printf("Masukkan tanggal nonton film (dd/mm/yyyy): ");
                    scanf("%d/%d/%d", &selectedDate.Tgl, &selectedDate.Bln, &selectedDate.Thn);
                    ReadDate(selectedDate.Tgl, selectedDate.Bln, selectedDate.Thn, &selectedDate);

                    if (IsDateLessToday(selectedDate)) {
                        printf("Tanggal tidak valid! Tidak boleh di bawah hari ini.\n");
                    }

                } while (IsDateLessToday(selectedDate));


                printf("Masukan range jam nonton: \n");

                printf("Dari (hh:mm): ");
                scanf("%d:%d", &jam, &mnt);
                SetTime(&jamAwal, jam, mnt);

                printf("Sampai (hh:mm): ");
                scanf("%d:%d", &jam, &mnt);
                SetTime(&jamAkhir, jam, mnt);

                KotaInfo* info = (KotaInfo*)(kotaNode->info);
                printf("===================================================\n");
                printf("         Film yang tersedia di %s      \n", info->nama);

                GetFilmByRangeWaktu(kotaNode, selectedDate, jamAwal, jamAkhir, &tampilFilm);

                if (ListEmpty(tampilFilm)) {
                    printf("Tidak ada film yang sedang tayang di kota ini.\n");

                    break;
                } else {
                    printFilm(tampilFilm);
                    printf("===================================================\n");
                }

                printf("Pilih Film: ");
                InputString(namaFilm);

                addressList filmTerpilih = cariFilmByJudul(*L, namaFilm);
                if (filmTerpilih == NULL) {
                    printf("Film tidak ditemukan.\n");
                    // Pop(&stackMenu);
                    break;
                }

                FilmInfo* infoFilm = (FilmInfo*)(filmTerpilih->info);

                HalamanPilihJadwal(root, L, kotaNode, filmTerpilih, selectedDate);

                break;
            }
            case 4: { 
                printf("===================================================\n");
                printf("============== Menu History Transaksi =============\n");
                printf("===================================================\n");

                date tanggalCari;
                int pilPrint;
                int runningPrint = 1;

                Stack stackTransaksi;
                CreateStack(&stackTransaksi);

                while (runningPrint)
                {
                    printf("1. Lihat Seluruh History Pemesanan\n");
                    printf("2. Lihat History Berdasarkan Tanggal\n");
                    printf("3. Kembali\n");
                    printf("Pilih: ");
                    scanf("%d", &pilPrint);
                    while (getchar() != '\n');

                    switch (pilPrint) {
                        case 1: {
                            IsiStackTransaksiById(&stackTransaksi, idLogin);
                            PrintStackTransaksi(stackTransaksi, *L, root);
                            DelAll(&stackTransaksi);  

                            break;
                        }
                        case 2: {
                            printf("Masukkan tanggal (dd/mm/yyyy): ");
                            scanf("%d/%d/%d", &tanggalCari.Tgl, &tanggalCari.Bln, &tanggalCari.Thn);
                            IsiStackTransaksiByDate(&stackTransaksi, idLogin, tanggalCari);
                            PrintStackTransaksi(stackTransaksi, *L, root);
                            DelAll(&stackTransaksi);

                            break;
                        }
                        case 3: {
                            runningPrint = 0;

                            break;
                        }
                        default:
                            printf("Pilihan tidak valid, silahkan coba lagi\n");

                            break;
                    }
                }

                break;
            }
            case 5: {
                char konfirmasi[5];
                printf("Apakah Anda yakin ingin logout? (y/n): ");
                scanf("%s", konfirmasi);
                if (strcmp(konfirmasi, "y") == 0 || strcmp(konfirmasi, "Y") == 0) {
                    printf("Logout berhasil.\n");
                    Logout(&loggedIn);
                    idLogin = -1;   
                    HalamanAwal();  
                    return;
                } else {
                    printf("Kembali ke menu.\n");
                }
                break;
            }
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (loggedIn);
}

void HalamanPilihJadwal(address root, List *L, address kotaNode, addressList filmNode, date tanggalAwal) {
    FilmInfo* infoFilm = (FilmInfo*)(filmNode->info);
    date selectedDate = tanggalAwal;

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

                    if (jadwalNode->pr == nodeTeater && isSameDate(j->tanggal, selectedDate)) {

                        if (!isDateTimeValid(j->tanggal, j->Start)) {
                            p = p->next;
                            continue;
                        }

                        if (!adaJadwalBioskop) {
                            printf("===================================================\n");
                            printf("Bioskop  : %s\n", bioskop->nama);
                            adaJadwalBioskop = 1;
                            ditemukan = 1;
                        }

                        if (!adaJadwalTeater) {
                            int hargaTiket = teater->harga;
                            if (IsWeekend(selectedDate)) {
                                hargaTiket += 5000;
                            }
                            printf("--------------------------------------------------\n");
                            printf("  Teater : %s\n", teater->nama);
                            printf("  Harga  : Rp%d\n", hargaTiket);
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

    printf("Jumlah Baris: %d, Kolom: %d\n", jadwalInfo->jumlahBaris, jadwalInfo->jumlahKolom);

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

    // Input jumlah tiket
    int jumlahTiket;
    printf("Masukkan jumlah tiket yang ingin dipesan (maks 10): ");
    scanf("%d", &jumlahTiket);

    if (jumlahTiket <= 0 || jumlahTiket > 10) {
        printf("Jumlah tiket tidak valid (1-10).\n");
        return;
    }


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


    Kursi kursiDipilih[10];
    int jumlahDipilih = 0;

    for (int k = 0; k < jumlahTiket; k++) {
        Kursi pilih;
        printf("Pilih kursi ke-%d (contoh A1): ", k + 1);
        scanf(" %c%d", &pilih.kolom, &pilih.baris);

        int i = pilih.baris - 1;
        int j = pilih.kolom - 'A';

        if (i < 0 || i >= jadwalInfo->jumlahBaris || 
            j < 0 || j >= jadwalInfo->jumlahKolom) {
            printf("Kursi %c%d tidak valid. Pilih ulang.\n", pilih.kolom, pilih.baris);
            k--;
            continue;
        }

        // Cek duplikasi
        int sudahDipilih = 0;
        for (int x = 0; x < jumlahDipilih; x++) {
            if (kursiDipilih[x].baris == pilih.baris && kursiDipilih[x].kolom == pilih.kolom) {
                sudahDipilih = 1;
                break;
            }
        }

        if (sudahDipilih) {
            printf("Kursi %c%d sudah Anda pilih sebelumnya.\n", pilih.kolom, pilih.baris);
            k--;
            continue;
        }

        if (jadwalInfo->kursi[i][j] == 'O') {
            kursiDipilih[jumlahDipilih++] = pilih;
            printf("Kursi %c%d dipilih.\n", pilih.kolom, pilih.baris);
        } else {
            printf("Kursi %c%d sudah terisi. Pilih kursi lain.\n", pilih.kolom, pilih.baris);
            k--;
        }
    }

    printf("\nKursi yang Anda pilih:\n");
    for (int i = 0; i < jumlahDipilih; i++) {
        printf("- %c%d\n", kursiDipilih[i].kolom, kursiDipilih[i].baris);
    }

    HalamanKonfirmasiPemesanan(nodeJadwal, kursiDipilih, jumlahDipilih);

}


void HalamanKonfirmasiPemesanan(address nodeJadwal, Kursi kursiDipilih[], int jumlahDipilih) {
    if (nodeJadwal == NULL) {
        printf("Data jadwal tidak valid.\n");
        return;
    }

    JadwalInfo* jadwalInfo = (JadwalInfo*)(nodeJadwal->info);
    FilmInfo* film = jadwalInfo->film;
    TeaterInfo* teater = (TeaterInfo*)nodeJadwal->pr->info;
    BioskopInfo* bioskop = (BioskopInfo*)nodeJadwal->pr->pr->info;

    int hargaTiket = teater->harga;
    if (IsWeekend(jadwalInfo->tanggal)) {
        hargaTiket += 5000;
    }

    printf("==========================================\n");
    printf("        KONFIRMASI PEMESANAN TIKET        \n");
    printf("==========================================\n");
    printf("Film       : %s\n", film->judul);
    printf("Bioskop    : %s\n", bioskop->nama);
    printf("Teater     : %s\n", teater->nama);
    printf("Tanggal    : %02d-%02d-%04d\n", jadwalInfo->tanggal.Tgl, jadwalInfo->tanggal.Bln, jadwalInfo->tanggal.Thn);
    printf("Jam        : %02d:%02d\n", jadwalInfo->Start.jam, jadwalInfo->Start.menit);
    printf("Harga/tiket: Rp%d\n", hargaTiket);
    printf("Jumlah     : %d tiket\n", jumlahDipilih);
    printf("Total Bayar: Rp%d\n", jumlahDipilih * hargaTiket);
    printf("------------------------------------------\n");
    printf("Kursi yang dipilih:\n");
    for (int i = 0; i < jumlahDipilih; i++) {
        printf("- %c%d\n", kursiDipilih[i].kolom, kursiDipilih[i].baris);
    }

    printf("==========================================\n");
    printf("Lanjutkan pemesanan? (y/n): ");
    char jawab;
    scanf(" %c", &jawab);

    if (jawab == 'y' || jawab == 'Y') {
        for (int i = 0; i < jumlahDipilih; i++) {
            int baris = kursiDipilih[i].baris - 1;
            int kolom = kursiDipilih[i].kolom - 'A';
            jadwalInfo->kursi[baris][kolom] = 'X';
        }

        AksiTransaksi(nodeJadwal, kursiDipilih, jumlahDipilih, idLogin);

    } else {
        printf("Pemesanan dibatalkan.\n");
    }

    printf("Tekan ENTER untuk kembali ke menu...\n");
    getchar(); getchar();
}