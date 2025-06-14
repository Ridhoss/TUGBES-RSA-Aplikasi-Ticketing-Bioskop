#include "header/viewsUser.h"

void HalamanMenuUser(address root, List *L) {
    printf("===================================================\n");
    printf("||          SELAMAT DATANG DI BIOSKOP            ||\n");
    printf("===================================================\n");
    PrintKota(root, 0);

    char kotaDipilih[100];
    printf("\n>> Pilih kota: ");
    scanf(" %[^\n]", kotaDipilih); 


    // printf("\n=== Film yang sedang tayang di %s ===\n", kotaDipilih);

    int pilihan;
    do {
        printf("===================================================\n");
        printf("          MENU USER - Kota: %s\n", kotaDipilih        );
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
            case 1:
                printf("\n=== Film yang tersedia di %s ===\n", kotaDipilih);
                printFilm(*L); 
                break;
            case 2:
                printf("belum tersedia)\n");
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
