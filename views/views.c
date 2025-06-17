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
        printf("||     4. Lihat History Transaksi                ||\n");
        printf("||     5. Konfirmasi E-Ticket ( %d )              ||\n", TotalQueue(QueueETicket));
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
                HalamanHistoryTransaksi(root, L);

                break;
            }
            case '5': {
                HalamanKonfirmasiETicket(root, L);

                break;
            }
            case '6': {
                char konfirmasi[5];
                printf("Apakah Anda yakin ingin logout? (y/n): ");
                scanf("%s", konfirmasi);

                if (strcmp(konfirmasi, "y") == 0 || strcmp(konfirmasi, "Y") == 0) {
                    // Logout(&loggedIn); 
                    loggedIn = 0;
                    idLogin = -1;
                    printf("Logout berhasil.\n");
                    HalamanAwal(&root, L);
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
                        char pilihan;
                        printf("Apakah ingin mengganti nama kota? (y/n): ");
                        scanf(" %c", &pilihan);

                        if (pilihan == 'y' || pilihan == 'Y') {
                            printf("Masukkan nama kota baru: ");
                            InputString(dataBaru.nama);

                            while (SearchKotaByName(root, dataBaru.nama) != NULL) {
                                printf("Kota dengan nama '%s' sudah ada.\n", dataBaru.nama);

                                printf("Masukkan nama kota baru: ");
                                InputString(dataBaru.nama);
                            }
                        } else {
                            printf("Penginputan dibatalkan.\n");
                            return;
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
                    char pilihan;
                    printf("Apakah ingin mengganti nama bioskop? (y/n): ");
                    scanf(" %c", &pilihan);

                    if (pilihan == 'y' || pilihan == 'Y') {
                        printf("Masukkan nama bioskop baru: ");
                        InputString(dataBaru.nama);

                        while(SearchBioskopByName(nodeKota, dataBaru.nama) != NULL) {
                            printf("Bioskop dengan nama '%s' sudah ada\n", dataBaru.nama);
                            printf("Masukan nama bioskop baru: ");
                            InputString(dataBaru.nama);
                        }
                    } else {
                        strcpy(dataBaru.nama, ((BioskopInfo*)nodeBioskop->info)->nama);
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

                while(SearchTeaterByName(nodeBioskop, teaterBaru.nama) != NULL) {
                    printf("Teater dengan nama '%s' sudah ada\n", teaterBaru.nama);
                    printf("Masukan nama Teater baru: ");
                    InputString(teaterBaru.nama);
                }

                do {
                    printf("Masukan Jumlah Kursi di Teater (max 400) : ");
                    scanf("%d", &teaterBaru.jumlahKursi);

                    if (teaterBaru.jumlahKursi > 400 || teaterBaru.jumlahKursi <= 0) {
                        printf("Jumlah kursi tidak valid. Masukkan angka antara 1 sampai 400.\n");
                    }
                } while (teaterBaru.jumlahKursi > 400 || teaterBaru.jumlahKursi <= 0);

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

                if(nodeTeater != NULL){
                    char pilihan;
                    printf("Apakah ingin mengganti nama teater? (y/n): ");
                    scanf(" %c", &pilihan);

                    if (pilihan == 'y' || pilihan == 'Y') {
                        printf("Masukkan Nama Teater Baru: ");
                        InputString(teaterBaru.nama);

                        while(SearchTeaterByName(nodeBioskop, teaterBaru.nama) != NULL) {
                            printf("Teater dengan nama '%s' sudah ada\n", teaterBaru.nama);
                            printf("Masukan nama Teater baru: ");
                            InputString(teaterBaru.nama);
                        }
                    } else {
                        strcpy(teaterBaru.nama, ((TeaterInfo*)nodeTeater->info)->nama);
                    }

                    do {
                        printf("Masukan Jumlah Kursi baru di Teater (max 400) : ");
                        scanf("%d", &teaterBaru.jumlahKursi);

                        if (teaterBaru.jumlahKursi > 400 || teaterBaru.jumlahKursi <= 0) {
                            printf("Jumlah kursi tidak valid. Masukkan angka antara 1 sampai 400.\n");
                        }
                    } while (teaterBaru.jumlahKursi > 400 || teaterBaru.jumlahKursi <= 0);

                    printf("Masukan Harga Tiket Teater : ");
                    scanf("%d", &teaterBaru.harga);

                    UbahTeater(nodeTeater, teaterBaru);
                }

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

                                do {
                                    printf("Masukkan tanggal tayang film (dd/mm/yyyy): ");
                                    scanf("%d/%d/%d", &tgl, &bln, &thn);
                                    ReadDate(tgl, bln, thn, &tglBaru);

                                    if (IsDateLessToday(tglBaru)) {
                                        printf("Tanggal tidak valid! Tidak boleh di bawah hari ini.\n");
                                    }

                                } while (IsDateLessToday(tglBaru));


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



void HalamanHistoryTransaksi(address root, List *L) {
    printf("===================================================\n");
    printf("============== Menu History Transaksi =============\n");
    printf("===================================================\n");

    date tanggalCari;
    int pilPrint;
    int runningPrint = 1;
    char namaKota[100], namaBioskop[100];

    Stack stackTransaksi;
    CreateStack(&stackTransaksi);

    while (runningPrint)
    {
        printf("1. Lihat Seluruh History Transaksi\n");
        printf("2. Lihat History Berdasarkan Tanggal\n");
        printf("3. Lihat History Berdasarkan Bioskop\n");
        printf("4. Lihat Total Pembelian Tiket\n");
        printf("5. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &pilPrint);
        while (getchar() != '\n');

        switch (pilPrint) {
            case 1: {
                IsiStackTransaksiById(&stackTransaksi, -1);
                PrintStackTransaksi(stackTransaksi, *L, root);
                DelAll(&stackTransaksi);  

                break;
            }
            case 2: {
                printf("Masukkan tanggal (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &tanggalCari.Tgl, &tanggalCari.Bln, &tanggalCari.Thn);
                IsiStackTransaksiByDate(&stackTransaksi, -1, tanggalCari);
                PrintStackTransaksi(stackTransaksi, *L, root);
                DelAll(&stackTransaksi);

                break;
            }
            case 3: {
                printf("===================================================\n");
                PrintKota(root, 0);
                printf("Pilih Kota: ");
                InputString(namaKota);
                address nodeKota = SearchKotaByName(root, namaKota);

                printf("===================================================\n");
                PrintBioskop(nodeKota, 0);
                printf("Pilih Bioskop: ");
                InputString(namaBioskop);
                address nodeBioskop = SearchBioskopByName(nodeKota, namaBioskop);

                BioskopInfo* bioskop = (BioskopInfo*)nodeBioskop->info;
                IsiStackTransaksiByBioskop(&stackTransaksi, bioskop->id);
                PrintStackTransaksi(stackTransaksi, *L, root);
                DelAll(&stackTransaksi);


                break;
            }
            case 4: {
                List ListLaporan;
                CreateList(&ListLaporan);
                AmbilSemuaBioskopKeList(root, &ListLaporan);
                TampilkanLaporanPenjualan(root, ListLaporan);
                
                DelAll(&ListLaporan);

                break;
            }
            case 5: {
                runningPrint = 0;

                break;
            }
            default:
                printf("Pilihan tidak valid, silahkan coba lagi\n");

                break;
        }
    }
}


void HalamanKonfirmasiETicket(address root, List *L) {
    printf("===================================================\n");
    printf("============== Konfirmasi E-Ticket (%d) ===========\n", TotalQueue(QueueETicket));
    printf("===================================================\n");

    if (IsEmptyQueue(QueueETicket)) {
        printf("Tidak ada e-ticket yang menunggu konfirmasi.\n");
        return;
    }

    Transaksi* trx = (Transaksi*) InfoTop(QueueETicket);
    if (trx == NULL) {
        printf("Data transaksi tidak valid.\n");
        return;
    }

    Akun* users = CariAkunById(trx->idUser);
    addressList film = cariFilm(*L, trx->idFilm);
    FilmInfo* infoFilm = (FilmInfo*)(film->info);

    address nodeKota = CariKotaDariIdBioskop(root, trx->idBioskop);
    address nodeBioskop = SearchBioskopById(nodeKota, &trx->idBioskop);
    BioskopInfo* infoBioskop = (BioskopInfo*)(nodeBioskop->info);

    List kursi;
    AmbilDetailTransaksi(&kursi, trx->id);
    TimeInfo jamStart, jamEnd;

    printf("ID Transaksi   : %d\n", trx->id);
    printf("Username       : %s\n", users->username);
    printf("Film           : %s\n", infoFilm->judul);
    printf("Bioskop        : %s\n", infoBioskop->nama);
    printf("Jam Tayang     : %02d:%02d - %02d:%02d\n", jamStart.jam, jamStart.menit,  jamEnd.jam, jamEnd.menit);
    printf("Jumlah Tiket   : %d\n", trx->jumlahTiket);
    printf("Total Harga    : %d\n", trx->totalHarga);
    printf("Status         : %s\n", trx->status);
    printf("Tanggal        : %02d/%02d/%04d\n", trx->tanggal.Tgl, trx->tanggal.Bln, trx->tanggal.Thn);
    printf("---------------------------------------------------\n");
    printf("1. Konfirmasi E-Ticket\n");
    printf("2. Batalkan / Kembali\n");
    printf("Pilihan: ");

    int pilihan;
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        UpdateStatusTransaksiById(trx->id, "USED");
        DeQueueWithFile(&QueueETicket);
        printf("E-ticket ID %d telah dikonfirmasi.\n", trx->id);
    } else {
        printf("Tidak ada perubahan. Kembali ke menu admin.\n");
    }
}

void TampilkanLaporanPenjualan(address root, List L) {
    if (root == NULL || ListEmpty(L)) {
        printf("Data tidak tersedia.\n");
        return;
    }

    printf("===================================================\n");
    printf("================ Laporan Penjualan ================\n");
    printf("===================================================\n");


    for (address nodeKota = root->fs; nodeKota != NULL; nodeKota = nodeKota->nb) {
        KotaInfo* kota = (KotaInfo*)nodeKota->info;
        int totalKota = 0;

        printf("Kota: %s\n", kota->nama);

        for (addressList P = L.First; P != NULL; P = P->next) {
            BioskopInfo* b = (BioskopInfo*) P->info;
            address nodeBioskop = SearchBioskopById(nodeKota, &b->id);

            if (nodeBioskop != NULL && nodeBioskop->pr == nodeKota) {
                int jumlahTiket = 0;
                int total = HitungPenjualanBioskop(b->id, &jumlahTiket);
                totalKota += total;

                printf("  - %s\n", b->nama);
                printf("    Tiket Terjual  : %d\n", jumlahTiket);
                printf("    Total Pendapatan: Rp. %d\n", total);
                printf("---------------------------------------------------\n");
            }
        }

        printf("Total Pendapatan Kota %s: Rp. %d\n", kota->nama, totalKota);
        printf("===================================================\n");
        printf("===================================================\n");

    }
}