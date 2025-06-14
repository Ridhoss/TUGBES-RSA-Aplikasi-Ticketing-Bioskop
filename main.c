#include <stdio.h>
#include <string.h>
#include "models/header/ADTTree.h"
#include "models/header/ADTList.h"
#include "models/header/ADTKota.h"
#include "models/header/ADTBioskop.h"
#include "models/header/ADTTeater.h"
#include "models/header/ADTAkun.h"
#include "models/header/ADTFilm.h"
#include "views/header/views.h"
#include "views/header/Auth.h"

int main() {
    int loggedIn = 0;  // status login, 0 = belum login
    int idLogin = 1; // 1 = sudah login
    HalamanAwal(&loggedIn, &idLogin);
    
    char* rootStr = (char*) malloc(strlen("Head") + 1);
    strcpy(rootStr, "Head");
    address root = CreateTree((infotype)rootStr, ROOT);

    if (root == NULL) {
        printf("Gagal membuat tree.\n");
        return 1;
    }
    
    List L;
    CreateList(&L);

    // Load data dari database
    LoadKota(root);
    LoadBioskop(root);
    LoadTeater(root);
    loadFilm(&L, films);


    char parentName[100], childName[100];
    char pilihan;

    do {
        printf("\nMenu:\n");
        printf("1. Manipulasi Kota\n");
        printf("2. Manipulasi Bioskop\n");
        printf("3. Manipulasi Film\n");
        printf("4. -\n");
        printf("5. -\n");
        printf("6. Keluar\n");
        printf("Pilih opsi (1-6): ");
        scanf(" %c", &pilihan);

        switch (pilihan) {
            case '1': {
                HalamanManipulasiKota(root);

                break;
            }
            case '2': {
                HalamanManipulasiBioskop(root);

                break;
            }
            case '3': {
                HalamanManipulasiFilm(&L);
                break;
            }
            case '4': {

                break;
            }
            case '5': {

                break;
            }
            case '6': {
                printf("Keluar dari program.\n");
                
                break;
            }
            default:
                printf("Pilihan tidak valid.\n");

                break;
        }
    
    } while (pilihan != '6');
    
    if (root != NULL) {
        DeleteAll(root);
        root = NULL;
    }
    
    return 0;
}