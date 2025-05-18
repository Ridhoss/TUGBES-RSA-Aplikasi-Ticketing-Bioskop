#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models/ADTBioskop.h"

void Menu() {
    printf("\n=== MENU BIOSKOP ===\n");
    printf("1. Tambah Bioskop (InsLast)\n");
    printf("2. Hapus Bioskop (DelP)\n");
    printf("3. Cari Bioskop\n");
    printf("4. Cetak Semua Bioskop\n");
    printf("5. Keluar\n");
    printf("Pilih menu: ");
}

BioskopInfo InputBioskop() {
    BioskopInfo b;
    printf("ID: ");
    scanf("%d", &b.id);
    printf("Nama: ");
    scanf(" %[^\n]", b.nama);
    printf("Kota: ");
    scanf(" %[^\n]", b.kota);
    return b;
}

int main() {
    List listBioskop;
    CreateList(&listBioskop);

    int pilihan;
    do {
        Menu();
        scanf("%d", &pilihan);
        getchar();
        
        if (pilihan == 1) {
            printf("Masukkan data bioskop:\n");
            BioskopInfo b = InputBioskop();
            InsLastBioskop(&listBioskop, b);
            printf("Bioskop berhasil ditambahkan.\n");

        } else if (pilihan == 2) {
            int id;
            printf("Masukkan ID bioskop yang ingin dihapus: ");
            scanf("%d", &id);
            DelPBioskop(&listBioskop, id);
            printf("Jika ID ditemukan, bioskop telah dihapus.\n");

        } else if (pilihan == 3) {
            int id;
            printf("Masukkan ID bioskop yang dicari: ");
            scanf("%d", &id);
            address P = SearchBioskop(listBioskop, id);
            if (P != NULL) {
                BioskopInfo *b = (BioskopInfo *)P->info;
                printf("Ditemukan: ID %d - %s (%s)\n", b->id, b->nama, b->kota);
            } else {
                printf("Bioskop tidak ditemukan.\n");
            }

        } else if (pilihan == 4) {
            PrintBioskop(listBioskop);

        } else if (pilihan == 5) {
            printf("Keluar...\n");

        } else {
            printf("Pilihan tidak valid.\n");
        }

    } while (pilihan != 5);

    // Bersihkan memori
    DelAllBioskop(&listBioskop);

    return 0;
}
