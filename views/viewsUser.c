#include "header/viewsUser.h"

void HalamanMenuUser(address root, List *L) {
    int idKotaDipilih;
    char namaKota[100];
    address kotaNode;
    List tampilFilm;
    
    printf("===================================================\n");
    printf("||          SELAMAT DATANG DI BIOSKOP            ||\n");
    printf("===================================================\n");
    PrintKota(root, 0);
    
    do {
        printf("\n>> Pilih kota: ");
        InputString(namaKota);

        kotaNode = SearchKotaByName(root, namaKota);

        if (!kotaNode) {
            printf("Kota '%s' tidak ditemukan. Silakan coba lagi.\n", namaKota);
        }
    } while (!kotaNode);

    int pilihan;
    do {
        printf("===================================================\n");
        KotaInfo* info = (KotaInfo*)(kotaNode->info);
        printf("           Menu User - Kota : %s            \n", info->nama);
        printf("===================================================\n");
        printf("||                                               ||\n");
        printf("||     1. Cari dan pilih film                    ||\n");
        printf("||     2. Lihat film upcoming                    ||\n");
        printf("||     3. Cari jadwal film                       ||\n");
        printf("||     4. Lihat daftar pesanan                   ||\n");
        printf("||     5. Keluar                                 ||\n");
        printf("||                                               ||\n");
        printf("|| Silakan pilih menu (1-5):                     ||\n");
        printf("===================================================\n");
        printf(">> ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: {
                KotaInfo* info = (KotaInfo*)(kotaNode->info);
                printf("\n=== Film yang tersedia di %s ===\n", info->nama);
                GetFilmByKota(kotaNode, &tampilFilm);

                if (ListEmpty(tampilFilm)) {
                    printf("Tidak ada film yang sedang tayang di kota ini.\n");
                } else {
                    printFilm(tampilFilm);
                }

                break;
            }
            case 2:
                printUpcomingFilmsByKota(kotaNode);
                
                break;
            case 3:
                 printf("belum tersedia)\n");
                break;
            case 4:
                 printf("belum tersedia)\n");
                break;
            case 5:
                printf("Terima kasih telah menggunakan aplikasi.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 5);
}
