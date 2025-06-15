#include "header/viewsUser.h"

void HalamanMenuUser(address root, List *L, int *loggedIn, int *idLogin) {
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

    int pilihan;
    do {
        printf("===================================================\n");
        KotaInfo* info = (KotaInfo*)(kotaNode->info);
        printf("           Menu User - Kota : %s       \n", info->nama);
        printf("===================================================\n");
        printf("||                                               ||\n");
        printf("||     1. Cari dan pilih film                    ||\n");
        printf("||     2. Lihat film upcoming                    ||\n");
        printf("||     3. Cari jadwal film                       ||\n");
        printf("||     4. Lihat daftar pesanan                   ||\n");
        printf("||     5. Logout                                 ||\n");
        printf("||                                               ||\n");
        printf("|| Pilihan menu (1-5):                           ||\n");
        printf("===================================================\n");
        printf(">> ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
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
            printf("Apakah Anda yakin ingin logout? (y/n): ");
            scanf("%s", konfirmasi);
            if (strcmp(konfirmasi, "y") == 0 || strcmp(konfirmasi, "Y") == 0) {
                printf("Logout berhasil. Kembali ke halaman login.\n");
                *loggedIn = 0;
                HalamanAwal(loggedIn, idLogin); 
                return;
            } else {
                printf("Kembali ke menu.\n");
                pilihan = -1;
            }
            
            break;
        }
        default:
            printf("Pilihan tidak valid!\n");
    }
} while (loggedIn);
}
