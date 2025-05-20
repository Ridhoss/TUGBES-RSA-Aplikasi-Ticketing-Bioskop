// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "models/ADTBioskop.h"

// void Menu() {
//     printf("\n=== MENU BIOSKOP ===\n");
//     printf("1. Tambah Bioskop (InsLast)\n");
//     printf("2. Hapus Bioskop (DelP)\n");
//     printf("3. Cari Bioskop\n");
//     printf("4. Cetak Semua Bioskop\n");
//     printf("5. Keluar\n");
//     printf("Pilih menu: ");
// }

// BioskopInfo InputBioskop() {
//     BioskopInfo b;
//     printf("ID: ");
//     scanf("%d", &b.id);
//     printf("Nama: ");
//     scanf(" %[^\n]", b.nama);
//     printf("Kota: ");
//     scanf(" %[^\n]", b.kota);
//     return b;
// }

// int main() {
//     List listBioskop;
//     CreateList(&listBioskop);

//     int pilihan;
//     do {
//         Menu();
//         scanf("%d", &pilihan);
//         getchar();

//         if (pilihan == 1) {
//             printf("Masukkan data bioskop:\n");
//             BioskopInfo b = InputBioskop();
//             InsLastBioskop(&listBioskop, b);
//             printf("Bioskop berhasil ditambahkan.\n");

//         } else if (pilihan == 2) {
//             int id;
//             printf("Masukkan ID bioskop yang ingin dihapus: ");
//             scanf("%d", &id);
//             DelPBioskop(&listBioskop, id);
//             printf("Jika ID ditemukan, bioskop telah dihapus.\n");

//         } else if (pilihan == 3) {
//             int id;
//             printf("Masukkan ID bioskop yang dicari: ");
//             scanf("%d", &id);
//             address P = SearchBioskop(listBioskop, id);
//             if (P != NULL) {
//                 BioskopInfo *b = (BioskopInfo *)P->info;
//                 printf("Ditemukan: ID %d - %s (%s)\n", b->id, b->nama, b->kota);
//             } else {
//                 printf("Bioskop tidak ditemukan.\n");
//             }

//         } else if (pilihan == 4) {
//             PrintBioskop(listBioskop);

//         } else if (pilihan == 5) {
//             printf("Keluar...\n");

//         } else {
//             printf("Pilihan tidak valid.\n");
//         }

//     } while (pilihan != 5);

//     // Bersihkan memori
//     DelAllBioskop(&listBioskop);

//     return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "models/header/ADTBioskop.h"
// #include "models/header/ADTTeater.h"

// void Menu() {
//     printf("\n=== MENU TEATER ===\n");
//     printf("1. Tambah Teater (InsLast)\n");
//     printf("2. Hapus Teater (DelP)\n");
//     printf("3. Cari Teater\n");
//     printf("4. Cetak Semua Teater\n");
//     printf("5. Keluar\n");
//     printf("Pilih menu: ");
// }

// TeaterInfo InputTeater() {
//     TeaterInfo b;
//     printf("ID: ");
//     scanf("%d", &b.id);
//     printf("Nama: ");
//     scanf(" %[^\n]", b.nama);
//     return b;
// }

// int main() {
//     List listTeater;
//     CreateList(&listTeater);

//     int pilihan;
//     do {
//         Menu();
//         scanf("%d", &pilihan);
//         getchar();
        
//         if (pilihan == 1) {
//             printf("Masukkan data Teater:\n");
//             TeaterInfo b = InputTeater();
//             InsLastTeater(&listTeater, b);
//             printf("Teater berhasil ditambahkan.\n");

//         } else if (pilihan == 2) {
//             int id;
//             printf("Masukkan ID Teater yang ingin dihapus: ");
//             scanf("%d", &id);
//             DelPTeater(&listTeater, id);
//             printf("Jika ID ditemukan, Teater telah dihapus.\n");

//         } else if (pilihan == 3) {
//             int id;
//             printf("Masukkan ID Teater yang dicari: ");
//             scanf("%d", &id);
//             address P = SearchTeater(listTeater, id);
//             if (P != NULL) {
//                 TeaterInfo *b = (TeaterInfo *)P->info;
//                 printf("Ditemukan: ID %d - %s\n", b->id, b->nama);
//             } else {
//                 printf("Teater tidak ditemukan.\n");
//             }

//         } else if (pilihan == 4) {
//             PrintTeater(listTeater);

//         } else if (pilihan == 5) {
//             printf("Keluar...\n");

//         } else {
//             printf("Pilihan tidak valid.\n");
//         }

//     } while (pilihan != 5);

//     // Bersihkan memori
//     DelAllTeater(&listTeater);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models/header/ADTKota.h"
#include "models/header/ADTJadwal.h"
#include "models/header/ADTTeater.h" 

int main() {
    List listKota, listJadwal, listTeater;
    CreateList(&listKota);
    CreateList(&listJadwal);
    CreateList(&listTeater);

    int pilihan;

    do {
        printf("\n=== MENU UTAMA ===\n");
        printf("1. Menu Kota\n");
        printf("2. Menu Jadwal\n");
        printf("3. Menu Teater\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar();

        if (pilihan == 1) {
            int subpil;
            do {
                printf("\n--- MENU KOTA ---\n");
                printf("1. Tambah Kota (InsLast)\n");
                printf("2. Hapus Kota (DelP)\n");
                printf("3. Cari Kota\n");
                printf("4. Cetak Semua Kota\n");
                printf("5. Kembali ke Menu Utama\n");
                printf("Pilih menu Kota: ");
                scanf("%d", &subpil);
                getchar();

                if (subpil == 1) {
                    KotaInfo k;
                    printf("Masukkan ID Kota: ");
                    scanf("%d", &k.id);
                    getchar();
                    printf("Masukkan Nama Kota: ");
                    fgets(k.nama, sizeof(k.nama), stdin);
                    k.nama[strcspn(k.nama, "\n")] = 0;
                    InsLastKota(&listKota, k);
                    printf("Kota berhasil ditambahkan.\n");
                }
                else if (subpil == 2) {
                    int id;
                    printf("Masukkan ID Kota yang akan dihapus: ");
                    scanf("%d", &id);
                    DelPKota(&listKota, id);
                    printf("Jika ada, kota dengan ID %d sudah dihapus.\n", id);
                }
                else if (subpil == 3) {
                    int id;
                    printf("Masukkan ID Kota yang dicari: ");
                    scanf("%d", &id);
                    address hasil = SearchKota(listKota, id);
                    if (hasil != NULL) {
                        KotaInfo *info = (KotaInfo *)hasil->info;
                        printf("Kota ditemukan: ID %d, Nama %s\n", info->id, info->nama);
                    } else {
                        printf("Kota dengan ID %d tidak ditemukan.\n", id);
                    }
                }
                else if (subpil == 4) {
                    PrintKota(listKota);
                }
            } while (subpil != 5);
        }
        else if (pilihan == 2) {
            int subpil;
            do {
                printf("\n--- MENU JADWAL ---\n");
                printf("1. Tambah Jadwal (InsLast)\n");
                printf("2. Hapus Jadwal (DelP)\n");
                printf("3. Cari Jadwal\n");
                printf("4. Cetak Semua Jadwal\n");
                printf("5. Kembali ke Menu Utama\n");
                printf("Pilih menu Jadwal: ");
                scanf("%d", &subpil);
                getchar();

                if (subpil == 1) {
                    JadwalInfo j;
                    printf("Masukkan ID Jadwal: ");
                    scanf("%d", &j.id);
                    getchar();
                    printf("Masukkan Start Time (HH:MM): ");
                    fgets(j.start, sizeof(j.start), stdin);
                    j.start[strcspn(j.start, "\n")] = 0;
                    printf("Masukkan End Time (HH:MM): ");
                    fgets(j.end, sizeof(j.end), stdin);
                    j.end[strcspn(j.end, "\n")] = 0;
                    printf("Masukkan ID Film: ");
                    scanf("%d", &j.id_film);
                    InsLastJadwal(&listJadwal, j);
                    printf("Jadwal berhasil ditambahkan.\n");
                }
                else if (subpil == 2) {
                    int id;
                    printf("Masukkan ID Jadwal yang akan dihapus: ");
                    scanf("%d", &id);
                    DelPJadwal(&listJadwal, id);
                    printf("Jika ada, jadwal dengan ID %d sudah dihapus.\n", id);
                }
                else if (subpil == 3) {
                    int id;
                    printf("Masukkan ID Jadwal yang dicari: ");
                    scanf("%d", &id);
                    address hasil = SearchJadwal(listJadwal, id);
                    if (hasil != NULL) {
                        JadwalInfo *info = (JadwalInfo *)hasil->info;
                        printf("Jadwal ditemukan: ID %d, Start %s, End %s, ID Film %d\n",
                               info->id, info->start, info->end, info->id_film);
                    } else {
                        printf("Jadwal dengan ID %d tidak ditemukan.\n", id);
                    }
                }
                else if (subpil == 4) {
                    PrintJadwal(listJadwal);
                }
            } while (subpil != 5);
        }
        else if (pilihan == 3) {
            int subpil;
            do {
                printf("\n--- MENU TEATER ---\n");
                printf("1. Tambah Teater (InsLast)\n");
                printf("2. Hapus Teater (DelP)\n");
                printf("3. Cari Teater\n");
                printf("4. Cetak Semua Teater\n");
                printf("5. Kembali ke Menu Utama\n");
                printf("Pilih menu Teater: ");
                scanf("%d", &subpil);
                getchar();

                if (subpil == 1) {
                    TeaterInfo t;
                    printf("Masukkan ID Teater: ");
                    scanf("%d", &t.id);
                    getchar();
                    printf("Masukkan Nama Teater: ");
                    fgets(t.nama, sizeof(t.nama), stdin);
                    t.nama[strcspn(t.nama, "\n")] = 0;
                    InsLastTeater(&listTeater, t);
                    printf("Teater berhasil ditambahkan.\n");
                }
                else if (subpil == 2) {
                    int id;
                    printf("Masukkan ID Teater yang akan dihapus: ");
                    scanf("%d", &id);
                    DelPTeater(&listTeater, id);
                    printf("Jika ada, teater dengan ID %d sudah dihapus.\n", id);
                }
                else if (subpil == 3) {
                    int id;
                    printf("Masukkan ID Teater yang dicari: ");
                    scanf("%d", &id);
                    address hasil = SearchTeater(listTeater, id);
                    if (hasil != NULL) {
                        TeaterInfo *info = (TeaterInfo *)hasil->info;
                        printf("Teater ditemukan: ID %d, Nama %s\n", info->id, info->nama);
                    } else {
                        printf("Teater dengan ID %d tidak ditemukan.\n", id);
                    }
                }
                else if (subpil == 4) {
                    PrintTeater(listTeater);
                }
            } while (subpil != 5);
        }
        else if (pilihan == 0) {
            printf("Keluar program.\n");
        }
        else {
            printf("Pilihan tidak valid!\n");
        }

    } while (pilihan != 0);

    // Bebaskan semua list sebelum keluar
    DelAllKota(&listKota);
    DelAllJadwal(&listJadwal);
    DelAllTeater(&listTeater);

    return 0;
}
