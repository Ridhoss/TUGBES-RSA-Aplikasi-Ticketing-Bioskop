#include "header/views.h"

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
          case 3:
            printf("Masukkan nama node yang ingin dihapus: ");
            InputString(namaKota);

            DeleteKota(root, namaKota);

            break;
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


    printf("Masukkan nama kota yang ingin dimanipulasi bioskopnya: ");
    InputString(namaKota);

    address nodeKota = SearchKota(root, namaKota);
    if (nodeKota == NULL) {
        printf("Kota '%s' tidak ditemukan.\n", namaKota);
        return;
    }

    // LoadBioskop(nodeKota);

    while (running) {
        printf("\n==== Manipulasi Bioskop (Kota: %s) ====\n", namaKota);
        printf("1. Tambah Bioskop\n");
        printf("2. Ubah Informasi Bioskop\n");
        printf("3. Hapus Bioskop\n");
        printf("4. Hapus Semua Bioskop\n");
        printf("5. Cari Bioskop\n");
        printf("6. Print Bioskop\n");
        printf("7. Manipulasi Teater\n");
        printf("8. Kembali ke Menu Utama\n");
        printf("Pilih: ");
        scanf("%d", &pil);
        while (getchar() != '\n');

        printf("\n=============================\n");

        switch (pil) {
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
            case 2:
               {
                printf("Masukkan nama bioskop yang ingin diubah: ");
                InputString(namaBioskop);

                address nodeBioskop = SearchBioskop(nodeKota, namaBioskop);
                if (nodeBioskop == NULL) {
                    printf("Bioskop '%s' tidak ditemukan.\n", namaBioskop);
                } else {
                    char namaBaru[100];
                    printf("Masukkan nama bioskop baru: ");
                    InputString(namaBaru);

                    BioskopInfo dataBaru;
                    strcpy(dataBaru.nama, namaBaru);
                    UbahBioskop(nodeBioskop, dataBaru);
                    printf("Bioskop berhasil diubah menjadi '%s'.\n", namaBaru);
                }
                break;
            }
 
            case 3:
                // printf("Masukkan nama bioskop yang ingin dihapus: ");
                // InputString(namaBioskop);

                // if (SearchBioskop(nodeKota, namaBioskop) != NULL) {
                //     DeleteBioskop(nodeKota, namaBioskop);
                //     printf("Bioskop '%s' berhasil dihapus.\n", namaBioskop);
                // } else {
                //     printf("Bioskop '%s' tidak ditemukan.\n", namaBioskop);
                // }
                // break;

            case 4:
                // printf("Apakah Anda yakin ingin menghapus semua bioskop dari kota ini? (y/n): ");
                // char konfirmasi;
                // scanf(" %c", &konfirmasi);
                // while (getchar() != '\n');

                // if (konfirmasi == 'y' || konfirmasi == 'Y') {
                //     DeleteAllBioskop(nodeKota);
                //     printf("Semua bioskop berhasil dihapus dari kota '%s'.\n", namaKota);
                // } else {
                //     printf("Penghapusan dibatalkan.\n");
                // }
                // break;

            case 5:
                printf("Masukkan nama bioskop yang ingin dicari: ");
                InputString(namaBioskop);
                if (SearchBioskop(nodeKota, namaBioskop) != NULL) {
                    printf("Bioskop '%s' ditemukan di kota '%s'.\n", namaBioskop, namaKota);
                } else {
                    printf("Bioskop '%s' tidak ditemukan di kota '%s'.\n", namaBioskop, namaKota);
                }
                break;

            case 6:
                PrintBioskop(nodeKota, 0);
                break;

            case 7:
                printf("Masukkan nama bioskop yang ingin dimanipulasi teaterya: ");
                InputString(namaBioskop);
                
                address nodeBioskop = SearchBioskop(nodeKota, namaBioskop);
                if (nodeBioskop == NULL) {
                    printf("Bioskop '%s' tidak ditemukan.\n", namaBioskop);
                } else {
                    HalamanManipulasiTeater(nodeBioskop); 
                }

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

// void HalamanManipulasiTeater(address nodeBioskop) {
//     if (nodeBioskop == NULL) {
//         printf("Bioskop tidak valid.\n");
//         return;
//     }

//     int pil;
//     int running = 1;

//     while (running) {
//         printf("\n==== Menu Manipulasi Teater ====\n");
//         printf("1. Tambah Teater\n");
//         printf("2. Ubah Informasi Teater\n");
//         printf("3. Hapus Teater\n");
//         printf("4. Cari Teater\n");
//         printf("5. Tampilkan Semua Teater\n");
//         printf("6. Kembali ke Menu Bioskop\n");
//         printf("Pilih: ");
//         scanf("%d", &pil);
//         while (getchar() != '\n');

//         switch (pil) {
//             case 1:
//                 // Tambah Teater
//                 break;
//             case 2:
//                 // Ubah Informasi Teater
//                 break;
//             case 3:
//                 // Hapus Teater
//                 break;
//             case 4:
//                 // Cari Teater
//                 break;
//             case 5:
//                 // Tampilkan Semua Teater
//                 break;
//             case 6:
//                 running = 0;
//                 break;
//             default:
//                 printf("Pilihan tidak valid, silahkan coba lagi\n");
//                 break;
//         }
//     }
// }
