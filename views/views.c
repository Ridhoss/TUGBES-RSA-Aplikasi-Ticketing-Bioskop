#include "header/views.h"

void HalamanManipulasiKota(address root) {
    char namaKota[100];

    int pil;
    int running = 1;

    while (running) {
        printf("\n==== Manipulasi Kota ====\n");
        printf("Pilihlah Menu Berikut : \n");
        printf("1. Tambah Kota\n");
        printf("2. Hapus Kota\n");
        printf("3. Print Kota\n");
        printf("4. Kembali Ke Menu Utama\n");
        printf("Pilih : ");
        scanf("%d", &pil);
        while (getchar() != '\n');

        printf("\n========================= \n");

        switch (pil)
        {
          case 1:
            printf("Masukkan nama kota baru: ");
            inputString(namaKota);

            TambahKota(root, namaKota);

            break;
          case 2:

            break;
          case 3:

            break;
          case 4:
            running = 0;

            break;
        }
    }
}