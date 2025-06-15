#include "header/viewsUser.h"

void HalamanMenuUser(address root, List *L) {
    StackMenu stackMenu;
    CreateStack(&stackMenu);

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

    Push(&stackMenu, "Menu Utama");

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
        printf("||     0. Kembali                                ||\n");
        printf("||     5. Keluar                                 ||\n");
        printf("||                                               ||\n");
        printf("|| Pilihan menu (1-5, atau 0 untuk kembali):     ||\n");
        printf("===================================================\n");
        printf(">> ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 0:
            if (IsEmptyStack(stackMenu) || strcmp(Top(stackMenu), "Menu Utama") == 0) {
                printf("Anda sudah di menu utama.\n");
            } else {
                Pop(&stackMenu); 
                printf("Kembali ke menu sebelumnya: %s\n", Top(stackMenu));
            }
            break;

        case 1: {
            Push(&stackMenu, "Cari dan Pilih Film");
            printf("\n=== Film yang tersedia di %s ===\n", info->nama);
            GetFilmByKota(kotaNode, &tampilFilm);
            if (ListEmpty(tampilFilm)) {
                printf("Tidak ada film yang sedang tayang di kota ini.\n");
            } else {
                printFilm(tampilFilm);
            }
            Pop(&stackMenu);
            break;
        }

        case 2:
            Push(&stackMenu, "Upcoming Film");
            PrintFilmUpcoming(kotaNode);
            Pop(&stackMenu);
            break;

        case 3:
            Push(&stackMenu, "Cari Jadwal");
            printf("Fitur belum tersedia.\n");
            Pop(&stackMenu);
            break;

        case 4:
            Push(&stackMenu, "Lihat Pesanan");
            printf("Fitur belum tersedia.\n");
            Pop(&stackMenu);
            break;

        case 5: {
            char konfirmasi[5];
            printf("Apakah Anda yakin ingin keluar? (y/n): ");
            scanf("%s", konfirmasi);
            if (strcmp(konfirmasi, "y") == 0 || strcmp(konfirmasi, "Y") == 0) {
                printf("Terima kasih telah menggunakan aplikasi.\n");
                return; // keluar dari fungsi
            } else {
                printf("Kembali ke menu.\n");
                pilihan = -1; // agar tidak keluar dari loop
            }
            break;
        }

        default:
            printf("Pilihan tidak valid!\n");
    }

} while (pilihan != 5);
}
