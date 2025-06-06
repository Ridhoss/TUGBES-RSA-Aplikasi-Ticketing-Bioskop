#include <stdio.h>
#include <string.h>
#include "models/header/ADTTree.h"
#include "models/header/ADTKota.h"
#include "models/header/ADTBioskop.h"
#include "models/header/ADTTeater.h"
#include "views/header/views.h"

int main() {
    char* rootStr = (char*) malloc(strlen("Head") + 1);
    strcpy(rootStr, "Head");
    address root = CreateTree((infotype)rootStr);

    if (root == NULL) {
        printf("Gagal membuat tree.\n");
        return 1;
    }

    LoadKota(root);
    LoadBioskop(root);
    LoadTeater(root);

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