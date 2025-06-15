#include "header/views.h"

void HalamanMenuAdmin(address root, List *L) {

    char parentName[100], childName[100];
    char pilihan;

    
    do {
        printf("===================================================\n");
        printf("||                MENU ADMIN                     ||\n");
        printf("===================================================\n");
        printf("||                                               ||\n");
        printf("||     1. Manipulasi Kota                        ||\n");
        printf("||     2. Manipulasi Bioskop                     ||\n");
        printf("||     3. Manipulasi Film                        ||\n");
        printf("||     4. -                                      ||\n");
        printf("||     5. -                                      ||\n");
        printf("||     6. Logout                                 ||\n");
        printf("||                                               ||\n");
        printf("|| Silakan pilih menu (1-6):                     ||\n");
        printf("===================================================\n");
        printf(">> ");
        scanf(" %c", &pilihan);

        switch (pilihan) {
            case '1': {
                HalamanManipulasiKota(root, L);

                break;
            }
            case '2': {
                HalamanManipulasiBioskop(root, L);

                break;
            }
            case '3': {
                HalamanManipulasiFilm(L);

                break;
            }
            case '4': {

                break;
            }
            case '5': {

                break;
            }
            case '6': {
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
                printf("Pilihan tidak valid.\n");

                break;
        }
    
    } while (pilihan != '6');
    
    if (root != NULL) {
        DeleteAll(root);
        root = NULL;
    }

}

void HalamanManipulasiKota(address root, List *L) {
    char namaKota[100];

    KotaInfo dataBaru;

    int pil;
    int running = 1;

    while (running) {
        printf("\n==== Manipulasi Kota ====\n");
        printf("Pilihlah Menu Berikut : \n");
        printf("1. Tambah Kota\n");
        printf("2. Ubah Informasi Kota\n");
        printf("3. Hapus Kota\n");
        printf("4. Hapus Semua Kota\n");
        printf("5. Cari Kota\n");
        printf("6. Print Kota\n");
        printf("7. Kembali Ke Menu Utama\n");
        printf("Pilih : ");
        scanf("%d", &pil);
        while (getchar() != '\n');

        printf("\n========================= \n");

        switch (pil)
        {
            case 1: {
                printf("Masukkan nama kota baru: ");
                InputString(dataBaru.nama);

                while(SearchKotaByName(root, dataBaru.nama) != NULL) {
                    printf("Kota dengan nama '%s' sudah ada\n", dataBaru.nama);
                    printf("Masukan nama kota baru: ");
                    InputString(dataBaru.nama);
                }

                TambahKotaBaru(root, dataBaru);

                break;
            }
            case 2: {
                printf("Masukkan nama kota yang ingin diubah: ");
                InputString(namaKota);

                address dataLama = SearchKotaByName(root, namaKota);

                if (dataLama != NULL) {
                    printf("Masukkan nama kota baru: ");
                    InputString(dataBaru.nama);

                    while(SearchKotaByName(root, dataBaru.nama) != NULL) {
                        printf("Kota dengan nama '%s' sudah ada\n", dataBaru.nama);
                        printf("Masukan nama kota baru: ");
                        InputString(dataBaru.nama);
                    }

                    UbahKota(dataLama, dataBaru);
                } else {
                    printf("Kota dengan nama tersebut tidak ditemukan.\n");
                }

                break;
            }
            case 3: {
                printf("Masukkan nama node yang ingin dihapus: ");
                InputString(namaKota);

                address delNode = SearchKotaByName(root, namaKota);
    
                if (delNode == NULL) {
                    printf("Node %s tidak ditemukan.\n", namaKota);
                    return;
                }

                DeleteKota(delNode);

                break;
            }
            case 4: {
                char confirm;

                printf("Apakah Anda yakin ingin menghapus semua kota? (y/n): ");
                scanf(" %c", &confirm);

                if (confirm == 'y' || confirm == 'Y') {
                    DeleteAllKota(root);
                    printf("Semua kota berhasil dihapus.\n");
                } else {
                    printf("Batal Menghapus.\n");
                }

                break;
            }
            case 5:
                printf("Masukkan nama kota yang ingin dicari: ");
                InputString(namaKota);

                address hasilCari = SearchKotaByName(root, namaKota);

                if (hasilCari != NULL) {
                    KotaInfo* kota = (KotaInfo*)hasilCari->info;
                    printf("Kota ditemukan: %s\n", kota->nama);
                } else {
                    printf("Kota dengan nama '%s' tidak ditemukan.\n", namaKota);
                }

                break;
            case 6:
                PrintKota(root, 0);

                break;
            case 7:
                running = 0;

                break;
            default:
                printf("Pilihan tidak valid, coba lagi.\n");

                break;
        }
    }
}

void HalamanManipulasiBioskop(address root, List *L) {
    char namaKota[100];
    char namaBioskop[100];

    BioskopInfo dataBaru;

    int pil;
    int running = 1;

    PrintKota(root, 0);

    printf("Masukkan nama kota yang ingin dimanipulasi bioskopnya: ");
    InputString(namaKota);

    address nodeKota = SearchKotaByName(root, namaKota);
    
    if (nodeKota == NULL) {
        printf("Kota '%s' tidak ditemukan.\n", namaKota);
        return;
    }

    while (running) {
        KotaInfo* kotaData = (KotaInfo*) nodeKota->info;
        printf("\n==== Manipulasi Bioskop (Kota: %s) ====\n", kotaData->nama);
        printf("1. Tambah Bioskop\n");
        printf("2. Ubah Informasi Bioskop\n");
        printf("3. Hapus Bioskop\n");
        printf("4. Hapus Semua Bioskop\n");
        printf("5. Cari Bioskop\n");
        printf("6. Print Bioskop\n");
        printf("7. Manipulation Teater\n");
        printf("8. Kembali ke Menu Utama\n");
        printf("Pilih: ");
        scanf("%d", &pil);
        while (getchar() != '\n');

        printf("\n=============================\n");

        switch (pil) 
        {
            case 1:{
                printf("Masukkan nama bioskop baru: ");
                InputString(dataBaru.nama);
                
                while (SearchBioskopByName(nodeKota, dataBaru.nama) != NULL) {
                    printf("Bioskop dengan nama '%s' sudah ada.\n", dataBaru.nama);
                    printf("Masukkan nama bioskop baru: ");
                    InputString(dataBaru.nama);
                }

                TambahBioskopBaru(nodeKota, dataBaru);

                break;
            }
            case 2: {
                printf("Masukkan nama bioskop yang ingin diubah: ");
                InputString(namaBioskop);

                address nodeBioskop = SearchBioskopByName(nodeKota, namaBioskop);

                if (nodeBioskop != NULL) {
                    printf("Masukkan nama bioskop baru: ");
                    InputString(dataBaru.nama);

                    while(SearchBioskopByName(nodeKota, dataBaru.nama) != NULL) {
                        printf("Bioskop dengan nama '%s' sudah ada\n", dataBaru.nama);
                        printf("Masukan nama bioskop baru: ");
                        InputString(dataBaru.nama);
                    }

                    UbahBioskop(nodeBioskop, dataBaru);

                } else {
                    printf("Bioskop dengan nama tersebut tidak ditemukan.\n");
                }

                break;
            }
            case 3: {
                printf("Masukkan nama bioskop yang ingin dihapus: ");
                InputString(namaBioskop);

                address hasilCari = SearchBioskopByName(nodeKota, namaBioskop);
                if (!hasilCari) {
                    printf("Bioskop dengan nama '%s' tidak ditemukan.\n", namaBioskop);
                    break;
                }

                DeleteBioskop(hasilCari);

                break;
            }
            case 4: {
                char confirm;

                printf("Apakah Anda yakin ingin menghapus semua bioskop dari kota ini? (y/n): ");
                scanf(" %c", &confirm);
                while (getchar() != '\n');

                if (confirm == 'y' || confirm == 'Y') {
                    DeleteAllBioskop(nodeKota);
                    printf("Semua bioskop berhasil dihapus dari kota '%s'.\n", namaKota);
                } else {
                    printf("Batal Menghapus.\n");
                }

                break;
            }
            case 5:
                printf("Masukkan nama bioskop yang ingin dicari: ");
                InputString(namaBioskop);

                address hasilCari = SearchBioskopByName(nodeKota, namaBioskop);

                if (hasilCari != NULL) {
                    BioskopInfo* bioskop = (BioskopInfo*)hasilCari->info;
                    printf("Bioskop ditemukan: %s di kota %s\n", bioskop->nama, namaKota);
                } else {
                    printf("Bioskop dengan nama '%s' tidak ditemukan.\n", namaBioskop);
                }

                break;
            case 6:
                PrintBioskop(nodeKota, 0);

                break;
            case 7:
                HalamanManipulasiTeater(root, L, nodeKota);

                break;
            case 8:
                running = 0;

                break;
            default:
                printf("Pilihan tidak valid, silahkan coba lagi\n");

                break;
        }
    }
}

void HalamanManipulasiTeater(address root, List *L, address nodeKota) {
    char namaTeater[100];
    char namaBioskop[100];

    TeaterInfo teaterBaru;

    int jumlahKursi;
    int hargaTeater;

    int pil;
    int running = 1;

    PrintBioskop(nodeKota, 0);

    printf("Masukkan nama bioskop yang ingin dimanipulasi teaternya: ");
    InputString(namaBioskop);

    address nodeBioskop = SearchBioskopByName(nodeKota, namaBioskop);

    if (nodeBioskop == NULL) {
        printf("Bioskop '%s' tidak ditemukan.\n", namaBioskop);
        return;
    }

    while (running) {
        BioskopInfo* bioskopData = (BioskopInfo*) nodeBioskop->info;
        printf("\n==== Menu Manipulasi Teater Bioskop %s ====\n", bioskopData->nama);
        printf("1. Tambah Teater\n");
        printf("2. Ubah Informasi Teater\n");
        printf("3. Hapus Teater\n");
        printf("4. Hapus Semua Teater\n");
        printf("5. Cari Teater\n");
        printf("6. Tampilkan Semua Teater\n");
        printf("7. Manipulasi Jadwal di Teater\n");
        printf("8. Kembali ke Menu Bioskop\n");
        printf("Pilih: ");
        scanf("%d", &pil);
        while (getchar() != '\n');

        switch (pil) {
            case 1: {
                // Tambah Teater
                printf("Masukan Nama Teater : ");
                InputString(teaterBaru.nama);

                printf("Masukan Jumlah Kursi di Teater : ");
                scanf("%d", &teaterBaru.jumlahKursi);

                printf("Masukan Harga Tiket Teater : ");
                scanf("%d", &teaterBaru.harga);

                TambahTeaterBaru(nodeKota, nodeBioskop, teaterBaru);

                break;
            }
            case 2: {
                // Ubah Informasi Teater
                PrintTeater(nodeBioskop, 0);

                printf("Masukkan Nama Teater yang Ingin Diubah: ");
                InputString(namaTeater);

                address nodeTeater = SearchTeaterByName(nodeBioskop, namaTeater);
                if (!nodeTeater) {
                    printf("Teater dengan nama '%s' tidak ditemukan.\n", namaTeater);
                    break;
                }

                printf("Masukkan Nama Teater Baru: ");
                InputString(teaterBaru.nama);

                printf("Masukkan Jumlah Kursi Baru: ");
                scanf("%d", &teaterBaru.jumlahKursi);

                printf("Masukan Harga Tiket Teater : ");
                scanf("%d", &teaterBaru.harga);

                UbahTeater(nodeTeater, teaterBaru);

                break;
            }
            case 3: {
                // Hapus Teater
                PrintTeater(nodeBioskop, 0);

                printf("Masukkan Nama Teater yang Ingin Dihapus: ");
                InputString(namaTeater);

                address nodeTeater = SearchTeaterByName(nodeBioskop, namaTeater);
                if (!nodeTeater) {
                    printf("Teater dengan nama '%s' tidak ditemukan.\n", namaTeater);
                    break;
                }

                DeleteTeater(nodeTeater);

                break;
            }
            case 4: {
                // Hapus Semua Teater
                char konfirmasi;

                printf("Apakah Anda yakin ingin menghapus semua data teater dari bioskop ini? (y/n): ");
                scanf(" %c", &konfirmasi);
                while (getchar() != '\n');

                if (konfirmasi == 'y' || konfirmasi == 'Y') {
                    DeleteAllTeater(nodeBioskop);
                    printf("Semua teater berhasil dihapus.\n");
                } else {
                    printf("Penghapusan dibatalkan.\n");
                }

                break;
            }
            case 5:
                // Cari Teater                
                printf("Masukkan teater yang ingin dicari: ");
                InputString(namaTeater);

                address hasilCari = SearchTeaterByName(root, namaTeater);

                if (hasilCari != NULL) {
                    TeaterInfo* teater = (TeaterInfo*)hasilCari->info;
                    printf("Teater ditemukan: %s\n", teater->nama);
                } else {
                    printf("Teater dengan nama '%s' tidak ditemukan.\n", namaTeater);
                }

                break;
            case 6:
                // Tampilkan Semua Teater
                PrintTeater(nodeBioskop, 0);

                break;
            case 7:
                // halaman manipulasi Jadwal 
                HalamanManipulasiJadwal(root, L, nodeKota, nodeBioskop);

                break;
            case 8:
                running = 0;

                break;
            default:
                printf("Pilihan tidak valid, silahkan coba lagi\n");

                break;
        }
    }
}

void HalamanManipulasiJadwal(address root, List *L, address nodeKota, address nodeBioskop) {
    char namaTeater[100];
    char namaFilm[100];

    JadwalInfo jadwalBaru;
    TimeInfo starTime, endTime;
    date tglBaru;

    int jam, menit, tgl, bln, thn, jmlHari = 1;

    int pil;
    int running = 1;

    PrintTeater(nodeBioskop, 0);

    printf("Masukkan nama teater yang ingin dimanipulasi jadwalnya: ");
    InputString(namaTeater);

    address nodeTeater = SearchTeaterByName(nodeBioskop, namaTeater);

    if (nodeTeater == NULL) {
        printf("Teater '%s' tidak ditemukan.\n", namaTeater);

        return;
    }

    while (running) {
        TeaterInfo* teaterData = (TeaterInfo*) nodeTeater->info;
        printf("\n==== Menu Manipulasi Jadwal Teater %s ====\n", teaterData->nama);
        printf("1. Tambah Jadwal\n");
        printf("2. Ubah Informasi Jadwal\n");
        printf("3. Hapus Jadwal\n");
        printf("4. Hapus Semua Jadwal\n");
        printf("5. Cari Jadwal\n");
        printf("6. Tampilkan Jadwal\n");
        printf("7. Kembali ke Menu Teater\n");
        printf("Pilih: ");
        scanf("%d", &pil);
        while (getchar() != '\n');

        switch (pil) {
            case 1: {
                // Tambah jadwal

                int pilTam;
                int runningTam = 1;

                while (runningTam)
                {
                    printf("========= Menu Tambah Jadwal =========\n");
                    printf("1. Tambah Jadwal hari ini\n");
                    printf("2. Tambah Jadwal advance\n");
                    printf("3. Kembali\n");
                    printf("Pilih: ");
                    scanf("%d", &pilTam);
                    while (getchar() != '\n');

                    switch (pilTam) {
                        case 1: {
                            printf("========= Daftar Film =========\n");
                            printFilm(*L);
                            printf("===============================\n");

                            printf("Pilih Film: ");
                            InputString(namaFilm);

                            addressList filmTerpilih = cariFilmByJudul(*L, namaFilm);

                            if(filmTerpilih){
                                FilmInfo* film = (FilmInfo*)(filmTerpilih->info);

                                printf("%s film terpilih\n", film->judul);

                                GetToday(&tglBaru);

                                printf("Masukan waktu tayang jadwal film ( jam:menit ): ");
                                scanf("%d:%d", &jam, &menit);
                                
                                SetTime(&starTime, jam, menit);

                                jadwalBaru.film = film;
                                jadwalBaru.tanggal = tglBaru;
                                jadwalBaru.Start = starTime;
                                
                                PrintObjDate(jadwalBaru.tanggal);
                                PrintTime(jadwalBaru.Start);

                                TambahJadwalBaru(nodeKota, nodeBioskop, nodeTeater, jadwalBaru, jmlHari);
                            }

                            break;
                        }
                        case 2: {
                            printf("========= Daftar Film =========\n");
                            printFilm(*L);
                            printf("===============================\n");

                            printf("Pilih Film: ");
                            InputString(namaFilm);

                            addressList filmTerpilih = cariFilmByJudul(*L, namaFilm);

                            if(filmTerpilih){
                                FilmInfo* film = (FilmInfo*)(filmTerpilih->info);

                                printf("%s film terpilih\n", film->judul);

                                printf("Masukan tanggal tayang film ( dd/mm/yyyy ): ");
                                scanf("%d/%d/%d", &tgl, &bln, &thn);
                                ReadDate(tgl, bln, thn, &tglBaru);

                                printf("Jumlah hari jadwal film tayang: ");
                                scanf("%d", &jmlHari);

                                printf("Masukan waktu tayang jadwal film ( jam:menit ): ");
                                scanf("%d:%d", &jam, &menit);
                                
                                SetTime(&starTime, jam, menit);

                                jadwalBaru.film = film;
                                jadwalBaru.tanggal = tglBaru;
                                jadwalBaru.Start = starTime;
                                
                                PrintObjDate(jadwalBaru.tanggal);
                                PrintTime(jadwalBaru.Start);

                                TambahJadwalBaru(nodeKota, nodeBioskop, nodeTeater, jadwalBaru, jmlHari);
                            }

                            break;
                        }
                        case 3: {
                            runningTam = 0;

                            break;
                        }
                        default:
                            printf("Pilihan tidak valid, silahkan coba lagi\n");

                            break;
                    }
                }

                break;
            }
            case 2: {
                // Ubah Informasi jadwal
                
                date tanggalCari;
                TimeInfo jamCari;

                PrintJadwal(nodeTeater, 0);

                printf("Masukkan tanggal yang ingin diubah ( dd/mm/yyyy ): ");
                scanf("%d/%d/%d", &tanggalCari.Tgl, &tanggalCari.Bln, &tanggalCari.Thn);

                List listJadwalTgl;
                AmbilJadwalTeaterTanggalKeList(nodeTeater, tanggalCari, &listJadwalTgl);

                if (ListEmpty(listJadwalTgl)) {
                    printf("Tidak ada jadwal pada tanggal %d/%d/%d.\n", tanggalCari.Tgl, tanggalCari.Bln, tanggalCari.Thn);

                    DelAll(&listJadwalTgl);
                    break;
                }

                TampilkanListJadwal(listJadwalTgl);

                printf("Pilih jadwal yang ingin diubah ( jam:menit ): ");
                scanf("%d:%d", &jam, &menit);
                SetTime(&jamCari, jam, menit);

                address jadwalLama = SearchJadwalByName(nodeTeater, &tanggalCari, &jamCari);

                if(!jadwalLama){
                    printf("Jadwal tidak ditemukan.\n");

                    DelAll(&listJadwalTgl);
                    break;
                }

                printf("==== Masukan data baru ====\n");

                printf("Masukan waktu tayang jadwal film ( jam:menit ): ");
                scanf("%d:%d", &jam, &menit);
                SetTime(&starTime, jam, menit);

                printf("===== Daftar Film =====\n");
                printFilm(*L);
                printf("=======================\n");

                printf("Pilih Film: ");
                InputString(namaFilm);

                addressList filmTerpilih = cariFilmByJudul(*L, namaFilm);

                if(filmTerpilih) {
                    FilmInfo* film = (FilmInfo*)(filmTerpilih->info);

                    jadwalBaru.Start = starTime;
                    jadwalBaru.tanggal = tanggalCari;
                    jadwalBaru.film = film;
                }

                UbahJadwal(jadwalLama, jadwalBaru);

                DelAll(&listJadwalTgl);

                break;
            }
            case 3: {
                // Hapus jadwal

                date tanggalCari;
                TimeInfo jamCari;

                PrintJadwal(nodeTeater, 0);

                printf("Masukkan tanggal jadwl yang ingin dihapus ( dd/mm/yyyy ): ");
                scanf("%d/%d/%d", &tanggalCari.Tgl, &tanggalCari.Bln, &tanggalCari.Thn);

                List listJadwalTgl;
                AmbilJadwalTeaterTanggalKeList(nodeTeater, tanggalCari, &listJadwalTgl);

                if (ListEmpty(listJadwalTgl)) {
                    printf("Tidak ada jadwal pada tanggal %d/%d/%d.\n", tanggalCari.Tgl, tanggalCari.Bln, tanggalCari.Thn);

                    DelAll(&listJadwalTgl);
                    break;
                }

                TampilkanListJadwal(listJadwalTgl);

                printf("Pilih jadwal yang ingin dihapus ( jam:menit ): ");
                scanf("%d:%d", &jam, &menit);
                SetTime(&jamCari, jam, menit);

                address jadwalLama = SearchJadwalByName(nodeTeater, &tanggalCari, &jamCari);

                if(!jadwalLama){
                    printf("Jadwal tidak ditemukan.\n");

                    DelAll(&listJadwalTgl);
                    break;
                }

                DeleteJadwal(jadwalLama);

                break;
            }
            case 4: {
                // Hapus Semua jadwal

                char confirm;

                printf("Apakah Anda yakin ingin menghapus semua jadwal dari teater ini? (y/n): ");
                scanf(" %c", &confirm);
                while (getchar() != '\n');

                if (confirm == 'y' || confirm == 'Y') {
                    DeleteAllJadwal(nodeTeater);
                    printf("Semua jadwal berhasil dihapus dari kota '%s'.\n", namaTeater);
                } else {
                    printf("Batal Menghapus.\n");
                }

                break;
            }
            case 5: {
                // Cari jadwal

                date tanggalCari;
                TimeInfo jamCari;

                printf("Masukkan tanggal jadwal yang ingin dicari ( dd/mm/yyyy ): ");
                scanf("%d/%d/%d", &tanggalCari.Tgl, &tanggalCari.Bln, &tanggalCari.Thn);

                printf("Masukan jam jadwal yang ingin dicari ( jam:menit ): ");
                scanf("%d:%d", &jam, &menit);
                SetTime(&jamCari, jam, menit);

                address jadwalHasil = SearchJadwalByName(nodeTeater, &tanggalCari, &jamCari);
                
                if (jadwalHasil != NULL) {
                    JadwalInfo* jadwal = (JadwalInfo*)jadwalHasil->info;
                    printf("Jadwal dengan jam %d:%d pada tanggal %d/%d/%d Ditemukan.\n", jadwal->Start.jam, jadwal->Start.menit, jadwal->tanggal.Tgl, jadwal->tanggal.Bln, jadwal->tanggal.Thn);
                } else {
                    printf("Jadwal dengan jam %d:%d pada tanggal %d/%d/%d tidak ditemukan.\n", jamCari.jam, jamCari.menit, tanggalCari.Tgl, tanggalCari.Bln, tanggalCari.Thn);
                }

                break;
            }
            case 6:{
                // Tampilkan Semua jadwal

                List listPrintJadwal;
                date tanggalCari;
                int pilPrint;
                int runningPrint = 1;

                while (runningPrint)
                {
                    printf("========= Menu Print Jadwal =========\n");
                    printf("1. Print Jadwal Berdasarkan Film\n");
                    printf("2. Print Jadwal Berdasarkan Tanggal\n");
                    printf("3. Print Semua Jadwal\n");
                    printf("4. Kembali\n");
                    printf("Pilih: ");
                    scanf("%d", &pilPrint);
                    while (getchar() != '\n');

                    switch (pilPrint) {
                        case 1: {
                            printf("===== Daftar Film =====\n");
                            printFilm(*L);
                            printf("=======================\n");

                            printf("Pilih Film: ");
                            InputString(namaFilm);

                            addressList filmTerpilih = cariFilmByJudul(*L, namaFilm);

                            if (!filmTerpilih) {
                                printf("Film Tidak Ditemukan.\n");
                                break;
                            }

                            AmbilJadwalTeaterFilmKeList(nodeTeater, filmTerpilih, &listPrintJadwal);

                            FilmInfo* film = (FilmInfo*)(filmTerpilih->info);

                            if (ListEmpty(listPrintJadwal)) {
                                printf("Tidak ada jadwal untuk film %s.\n", film->judul);

                                DelAll(&listPrintJadwal);
                                break;
                            }

                            printf("===== Daftar Jadwal Film %s =====\n", film->judul);
                            TampilkanListJadwal(listPrintJadwal);

                            break;
                        }
                        case 2: {
                            printf("Masukkan tanggal jadwal yang ingin di print ( dd/mm/yyyy ): ");
                            scanf("%d/%d/%d", &tanggalCari.Tgl, &tanggalCari.Bln, &tanggalCari.Thn);

                            AmbilJadwalTeaterTanggalKeList(nodeTeater, tanggalCari, &listPrintJadwal);

                            if (ListEmpty(listPrintJadwal)) {
                                printf("Tidak ada jadwal pada tanggal %d/%d/%d.\n", tanggalCari.Tgl, tanggalCari.Bln, tanggalCari.Thn);

                                DelAll(&listPrintJadwal);
                                break;
                            }

                            printf("===== Daftar Jadwal Tanggal %d/%d/%d =====\n", tanggalCari.Tgl, tanggalCari.Bln, tanggalCari.Thn);
                            TampilkanListJadwal(listPrintJadwal);

                            break;
                        }
                        case 3: {
                            AmbilJadwalTeaterKeList(nodeTeater, &listPrintJadwal);

                            printf("===== Daftar Jadwal =====\n");
                            TampilkanListJadwal(listPrintJadwal);

                            break;
                        }
                        case 4: {
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
            case 7:
                running = 0;

                break;
            default:
                printf("Pilihan tidak valid, silahkan coba lagi\n");

                break;
        }
    }
}

void HalamanManipulasiFilm(List *L) {
    int pilihan, id, jam, menit;
    FilmInfo data;
    int jamBaru = -1;
    int menitBaru = -1;
    char buffer[255];
    char judulCari[100] = "";
    char judulBaru[100] = "";
    char produserBaru[100] = "";
    char deskripsiBaru[255] = "";
    do {
        printf("\n=== Halaman Manipulasi Film ===\n");
        printf("1. Tampilkan semua film\n");
        printf("2. Tambah Film baru\n");
        printf("3. Edit Film\n");
        printf("4. Hapus Film\n");
        printf("5. Cari Film\n");
        printf("6. Keluar\n");
        printf("Pilih opsi (1-6): ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
        case 1:
            printf("\n--- Daftar Semua Film ---\n");
            printFilm(*L);
            break;

        case 2:
            printf("\n--- Tambah Film Baru ---\n");

            FilmInfo newFilm;
            int jam, menit;

            printf("Masukkan judul film: ");
            fgets(newFilm.judul, sizeof(newFilm.judul), stdin);
            newFilm.judul[strcspn(newFilm.judul, "\n")] = 0;

            printf("Masukkan produser film: ");
            fgets(newFilm.produser, sizeof(newFilm.produser), stdin);
            newFilm.produser[strcspn(newFilm.produser, "\n")] = 0;

            printf("Masukkan deskripsi film: ");
            fgets(newFilm.deskripsi, sizeof(newFilm.deskripsi), stdin);
            newFilm.deskripsi[strcspn(newFilm.deskripsi, "\n")] = 0;

            printf("Masukkan durasi jam   : ");
            scanf("%d", &jam);
            printf("Masukkan durasi menit : ");
            scanf("%d", &menit);
            getchar();

            newFilm.durasi.jam = jam;
            newFilm.durasi.menit = menit;

            TambahFilmBaru(L, newFilm);

            printf("Film berhasil ditambahkan.\n");
            break;


        case 3:
            printf("\n--- Edit Film ---\n");
            printf("Masukkan judul film yang ingin diedit: ");
            fgets(judulCari, sizeof(judulCari), stdin);
            judulCari[strcspn(judulCari, "\n")] = 0;

            addressList filmLama = cariFilmByJudul(*L, judulCari);
            if (filmLama == NULL) {
                printf("Film dengan judul \"%s\" tidak ditemukan.\n", judulCari);
                break;
            }

            // Salin data lama dulu
            FilmInfo filmBaru = *(FilmInfo*)(filmLama->info);

            // Input perubahan
            printf("Masukkan judul baru (Enter untuk skip): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(filmBaru.judul, buffer);
            }

            printf("Masukkan produser baru (Enter untuk skip): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(filmBaru.produser, buffer);
            }

            printf("Masukkan deskripsi baru (Enter untuk skip): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(filmBaru.deskripsi, buffer);
            }

            printf("Jam durasi baru (Enter untuk skip): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                filmBaru.durasi.jam = atoi(buffer);
            } else {
                filmBaru.durasi.jam = -1; // skip
            }

            printf("Menit durasi baru (Enter untuk skip): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                filmBaru.durasi.menit = atoi(buffer);
            } else {
                filmBaru.durasi.menit = -1; // skip
            }

            editFilmByName(filmBaru, filmLama);
            printf("Film berhasil diperbarui!\n");
            simpanKeFile(*L, films);

            
            break;
        case 4:
            printf("\n--- Hapus Film ---\n");
            printf("Masukkan ID film yang ingin dihapus: ");
            scanf("%d", &id);
            getchar();
            hapusFilm(L, id);
            printf("Film dengan ID %d dihapus (jika ada).\n", id);
            break;

        case 5:
            printf("\n--- Cari Film ---\n");
            char judul[100];
            printf("Masukkan judul film yang ingin dicari: ");
            fgets(judul, sizeof(judul), stdin);
            judul[strcspn(judul, "\n")] = 0;

            addressList hasil = cariFilmByJudul(*L, judul);
            if (hasil != NULL) {
                printf("Film ditemukan:\n");
                FilmInfo* film = (FilmInfo*)(hasil->info);
                printf("ID         : %d\n", film->idFilm);
                printf("Judul      : %s\n", film->judul);
                printf("Produser   : %s\n", film->produser);
                printf("Deskripsi  : %s\n", film->deskripsi);
                printf("Durasi     : %d jam %d menit\n", film->durasi.jam, film->durasi.menit);

            } else {
                printf("Film dengan judul \"%s\" tidak ditemukan.\n", judul);
            }

            break;

        case 6:
            printf("Keluar dari halaman manipulasi film.\n");
            break;

        default:
            printf("Pilihan tidak valid. Silakan pilih 1-5.\n");
            break;
        }
    } while (pilihan != 6);
}
