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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models/ADTBioskop.h"
#include "models/ADTTeater.h"

void Menu() {
    printf("\n=== MENU TEATER ===\n");
    printf("1. Tambah Teater (InsLast)\n");
    printf("2. Hapus Teater (DelP)\n");
    printf("3. Cari Teater\n");
    printf("4. Cetak Semua Teater\n");
    printf("5. Keluar\n");
    printf("Pilih menu: ");
}

TeaterInfo InputTeater() {
    TeaterInfo b;
    printf("ID: ");
    scanf("%d", &b.id);
    printf("Nama: ");
    scanf(" %[^\n]", b.nama);
    return b;
}

int main() {
    List listTeater;
    CreateList(&listTeater);

    int pilihan;
    do {
        Menu();
        scanf("%d", &pilihan);
        getchar();
        
        if (pilihan == 1) {
            printf("Masukkan data Teater:\n");
            TeaterInfo b = InputTeater();
            InsLastTeater(&listTeater, b);
            printf("Teater berhasil ditambahkan.\n");

        } else if (pilihan == 2) {
            int id;
            printf("Masukkan ID Teater yang ingin dihapus: ");
            scanf("%d", &id);
            DelPTeater(&listTeater, id);
            printf("Jika ID ditemukan, Teater telah dihapus.\n");

        } else if (pilihan == 3) {
            int id;
            printf("Masukkan ID Teater yang dicari: ");
            scanf("%d", &id);
            address P = SearchTeater(listTeater, id);
            if (P != NULL) {
                TeaterInfo *b = (TeaterInfo *)P->info;
                printf("Ditemukan: ID %d - %s\n", b->id, b->nama);
            } else {
                printf("Teater tidak ditemukan.\n");
            }

        } else if (pilihan == 4) {
            PrintTeater(listTeater);

        } else if (pilihan == 5) {
            printf("Keluar...\n");

        } else {
            printf("Pilihan tidak valid.\n");
        }

    } while (pilihan != 5);

    // Bersihkan memori
    DelAllTeater(&listTeater);

    return 0;
}
