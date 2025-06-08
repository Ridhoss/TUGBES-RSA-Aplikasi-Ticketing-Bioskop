#include "header/views.h"

// Deskripsi : Halaman untuk manipulasi kota
// IS : menerima address root dari tree kota
// FS : menampilkan menu manipulasi kota, termasuk tambah, ubah, hapus, cari, dan print kota
void HalamanManipulasiKota(address root) {
    char namaKota[100];

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
            case 1:
                printf("Masukkan nama kota baru: ");
                InputString(namaKota);

                while(SearchKota(root, namaKota) != NULL) {
                    printf("Kota dengan nama '%s' sudah ada\n", namaKota);
                    printf("Masukan nama kota baru: ");
                    InputString(namaKota);
                }

                TambahKotaBaru(root, namaKota);

                break;
            case 2: {
                KotaInfo dataBaru;

                printf("Masukkan nama node yang ingin diubah: ");
                InputString(namaKota);

                address pilihNode = SearchKota(root, namaKota);

                if (pilihNode != NULL) {
                    printf("Masukkan nama kota baru: ");
                    InputString(dataBaru.nama);

                    while(SearchKota(root, dataBaru.nama) != NULL) {
                        printf("Kota dengan nama '%s' sudah ada\n", dataBaru.nama);
                        printf("Masukan nama kota baru: ");
                        InputString(dataBaru.nama);
                    }

                    UbahKota(pilihNode, dataBaru);

                    printf("Nama kota berhasil diubah!\n");
                } else {
                    printf("Kota dengan nama tersebut tidak ditemukan.\n");
                }

                break;
            }
            case 3: {
                printf("Masukkan nama node yang ingin dihapus: ");
                InputString(namaKota);

                address delNode = SearchKota(root, namaKota);
    
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

                address hasilCari = SearchKota(root, namaKota);

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

    int pil;
    int running = 1;

    PrintKota(root, 0);

    printf("Masukkan nama kota yang ingin dimanipulasi bioskopnya: ");
    InputString(namaKota);

    address nodeKota = SearchKota(root, namaKota);
    
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
            case 1:
                printf("Masukkan nama bioskop baru: ");
                InputString(namaBioskop);
                
                while (SearchBioskop(nodeKota, namaBioskop) != NULL) {
                    printf("Bioskop dengan nama '%s' sudah ada.\n", namaBioskop);
                    printf("Masukkan nama bioskop baru: ");
                    InputString(namaBioskop);
                }

                TambahBioskopBaru(nodeKota, namaBioskop);

                break;
            case 2: {
                BioskopInfo dataBaru;
                
                printf("Masukkan nama bioskop yang ingin diubah: ");
                InputString(namaBioskop);

                address nodeBioskop = SearchBioskop(nodeKota, namaBioskop);

                if (nodeBioskop != NULL) {
                    printf("Masukkan nama bioskop baru: ");
                    InputString(dataBaru.nama);

                    while(SearchBioskop(nodeKota, dataBaru.nama) != NULL) {
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

                address hasilCari = SearchBioskop(nodeKota, namaBioskop);
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

                address hasilCari = SearchBioskop(nodeKota, namaBioskop);

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
    int jumlahKursi;
    int pil;
    int running = 1;

    PrintBioskop(nodeKota, 0);

    printf("Masukkan nama bioskop yang ingin dimanipulasi teaterya: ");
    InputString(namaBioskop);

    address nodeBioskop = SearchBioskop(nodeKota, namaBioskop);

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
            case 1:
                // Tambah Teater
                printf("Masukan Nama Teater : ");
                InputString(namaTeater);

                printf("Masukan Jumlah Kursi di Teater : ");
                scanf("%d", &jumlahKursi);

                TambahTeaterBaru(nodeKota, nodeBioskop, namaTeater, jumlahKursi);

                break;
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

                TeaterInfo dataBaru;
                printf("Masukkan Nama Teater Baru: ");
                InputString(dataBaru.nama);

                printf("Masukkan Jumlah Kursi Baru: ");
                scanf("%d", &dataBaru.jumlahKursi);

                UbahTeater(nodeTeater, dataBaru);

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

void HalamanRegister(Akun *akun, int role){

    char password_check[50];

    printf("== Registrasi Akun Baru ==\n");

    // Username
    printf("Masukkan Username: ");
    scanf("%49s", akun->username);

    // Password + konfirmasi
    for (;;) {
        printf("Masukkan Password: ");
        scanf("%49s", akun->password);

        printf("Konfirmasi Password: ");
        scanf("%49s", password_check);

        if (strcmp(akun->password, password_check) == 0) {
            break;
        }
        printf("Konfirmasi Password Salah! Silakan coba lagi.\n");
    }

    // Phone
    printf("Masukkan Nomor Telepon: ");
    scanf("%15s", akun->phone);

    // Alamat, hanya input jika role bukan 2 (admin)
    if (role != 2) {
        printf("Masukkan Alamat: ");
        getchar();
        fgets(akun->alamat, sizeof(akun->alamat), stdin);
        akun->alamat[strcspn(akun->alamat, "\n")] = '\0';
    } else {
        strcpy(akun->alamat, "null");
    }
}

void HalamanLogin(int *loggedIn, int *idLogin){
    char username[50];
    char password[50];
    Akun akun[100];
    int total_akun = BacaFileAkun(akun);

    printf("=======================\n");
    printf("======== MASUK ========\n");
    printf("=======================\n");

    printf("Masukan Username: ");
    scanf("%s", username);
    printf("Masukan Password: ");
    scanf("%s", password);

    *loggedIn = Login(username, password, akun, total_akun, idLogin);
    
    if (*loggedIn) {
        printf("Login berhasil!\n");
    } else {
        printf("=============================\n");
        printf("Username atau Password salah!\n");   
        printf("=============================\n");
    }
}