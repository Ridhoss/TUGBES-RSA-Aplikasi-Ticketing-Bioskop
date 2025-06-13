#include "header/views.h"

// void HalamanMenuAdmin(){
// }

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

    PrintBioskop(nodeKota, 0);
    while (running) {
        printf("\n==== Manipulasi Bioskop (Kota: %s) ====\n", namaKota);
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

    printf("Masukkan nama bioskop yang ingin dimanipulasi teaterya: ");
    InputString(namaBioskop);

    address nodeBioskop = SearchBioskopByName(nodeKota, namaBioskop);

    if (nodeBioskop == NULL) {
        printf("Bioskop '%s' tidak ditemukan.\n", namaBioskop);

        return;
    }

    while (running) {
        printf("\n==== Menu Manipulasi Teater Bioskop %s ====\n", nodeBioskop->info);
        printf("1. Tambah Teater\n");
        printf("2. Ubah Informasi Teater\n");
        printf("3. Hapus Teater\n");
        printf("4. Hapus Semua Teater\n");
        printf("5. Cari Teater\n");
        printf("6. Tampilkan Semua Teater\n");
        printf("7. Kembali ke Menu Bioskop\n");
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

                address nodeTeater = SearchTeater(nodeBioskop, namaTeater);
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

                address nodeTeater = SearchTeater(nodeBioskop, namaTeater);
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

                address hasilCari = SearchTeater(root, namaTeater);

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
                running = 0;

                break;
            default:
                printf("Pilihan tidak valid, silahkan coba lagi\n");

                break;
        }
    }
}

