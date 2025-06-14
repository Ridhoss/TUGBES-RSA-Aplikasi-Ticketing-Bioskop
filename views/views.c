#include "header/views.h"

void HalamanMenuAdmin(address root) {

    char parentName[100], childName[100];
    char pilihan;

    
    do {
        printf("\nMenu:\n");
        printf("1. Manipulasi Kota\n");
        printf("2. Manipulasi Bioskop\n");
        printf("3. Manipulasi Film\n");
        printf("4. -\n");
        printf("5. -\n");
        printf("6. Keluar\n");
        printf("Pilih opsi (1-6): ");
        scanf(" %c", &pilihan);

        switch (pilihan) {
            case '1': {
                HalamanManipulasiKota(root);

                break;
            }
            case '2': {
                HalamanManipulasiBioskop(root);

                break;
            }
            case '3': {

                break;
            }
            case '4': {

                break;
            }
            case '5': {

                break;
            }
            case '6': {
                printf("Keluar dari program.\n");
                
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

void HalamanManipulasiKota(address root) {
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

void HalamanManipulasiBioskop(address root) {
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
                HalamanManipulasiTeater(root, nodeKota);

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

void HalamanManipulasiTeater(address root, address nodeKota) {
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
                HalamanManipulasiJadwal(root, nodeKota, nodeBioskop);

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

void HalamanManipulasiJadwal(address root, address nodeKota, address nodeBioskop) {
    char namaTeater[100];

    JadwalInfo jadwalBaru;
    TimeInfo starTime, endTime;
    date tglBaru;

    int jam, menit, tgl, bln, thn;

    // dummy
    FilmInfo* filmBaru = (FilmInfo*) malloc(sizeof(FilmInfo));

    filmBaru->idFilm = 1;
    strcpy(filmBaru->judul, "Test Film1");
    strcpy(filmBaru->produser, "Test Produser 1");
    strcpy(filmBaru->deskripsi, "Ini film horror");
    filmBaru->durasi.jam = 1;
    filmBaru->durasi.menit = 30;

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
        printf("6. Tampilkan Semua Jadwal\n");
        printf("7. Kembali ke Menu Teater\n");
        printf("Pilih: ");
        scanf("%d", &pil);
        while (getchar() != '\n');

        switch (pil) {
            case 1: {

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
                            printf("Pilih Film: ");

                            if(filmBaru){
                                printf("Film terpilih\n");
                                GetToday(&tglBaru);

                                printf("Masukan waktu tayang jadwal film ( jam:menit ): ");
                                scanf("%d:%d", &jam, &menit);
                                
                                SetTime(&starTime, jam, menit);

                                jadwalBaru.film = filmBaru;
                                jadwalBaru.tanggal = tglBaru;
                                jadwalBaru.Start = starTime;
                                
                                PrintObjDate(jadwalBaru.tanggal);
                                PrintTime(jadwalBaru.Start);

                                TambahJadwalBaru(nodeKota, nodeBioskop, nodeTeater, jadwalBaru);
                            }

                            break;
                        }
                        case 2: {

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

                // Tambah jadwal

                break;
            }
            case 2: {
                // Ubah Informasi jadwal

                break;
            }
            case 3: {
                // Hapus jadwal

                break;
            }
            case 4: {
                // Hapus Semua jadwal

                break;
            }
            case 5:
                // Cari jadwal                

                break;
            case 6:
                // Tampilkan Semua jadwal

                break;
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

            printf("Masukkan judul film: ");
            fgets(data.judul, sizeof(data.judul), stdin);
            data.judul[strcspn(data.judul, "\n")] = 0;

            printf("Masukkan produser film: ");
            fgets(data.produser, sizeof(data.produser), stdin);
            data.produser[strcspn(data.produser, "\n")] = 0;

            printf("Masukkan deskripsi film: ");
            fgets(data.deskripsi, sizeof(data.deskripsi), stdin);
            data.deskripsi[strcspn(data.deskripsi, "\n")] = 0;

            printf("Masukkan durasi jam   : ");
            scanf("%d", &jam);
            printf("Masukkan durasi menit : ");
            scanf("%d", &menit);
            getchar();

            TambahFilmBaru(L, data.judul, data.produser, data.deskripsi, jam, menit);

            printf("Film berhasil ditambahkan.\n");
            break;

        case 3:
            printf("\n--- Edit Film ---\n");
            printf("Masukkan ID film yang ingin diedit: ");
            scanf("%d", &id);
            while (getchar() != '\n');

            printf("Masukkan judul baru (Enter untuk skip): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(judulBaru, buffer);
            }

            printf("Masukkan produser baru (Enter untuk skip): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(produserBaru, buffer);
            }

            printf("Masukkan deskripsi baru (Enter untuk skip): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(deskripsiBaru, buffer);
            }

            printf("Jam (Enter untuk skip): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                jamBaru = atoi(buffer);
            }

            printf("Menit (Enter untuk skip): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                menitBaru = atoi(buffer);
            }

            if (editFilmById(L, id, judulBaru, produserBaru, deskripsiBaru, jamBaru, menitBaru)) {
                printf("Film berhasil diperbarui!\n");
                simpanKeFile(*L, films);
            } else {
                printf("Film dengan ID %d tidak ditemukan.\n", id);
            }
            
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
