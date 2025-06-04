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
