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
#include "views/header/viewsUser.h"
#include "views/header/Auth.h"

int main() {
    char* rootStr = (char*) malloc(strlen("Head") + 1);
    strcpy(rootStr, "Head");
    address root = CreateTree((infotype)rootStr, ROOT);

    if (root == NULL) {
        printf("Gagal membuat tree.\n");
        return 0;
    }
    
    List L;
    CreateList(&L);

    LoadKota(root);
    LoadBioskop(root);
    LoadTeater(root);
    loadFilm(&L, films);
    LoadJadwal(root, L);

    int loggedIn = 0; 
    int idLogin = 0; 

    HalamanAwal(&loggedIn, &idLogin);
    if (loggedIn) {
        Akun* akunLogin = CariAkunById(idLogin);
        if (akunLogin != NULL) {
            if (akunLogin->role == 0) {
                HalamanMenuAdmin(root, &L);
            } else if (akunLogin->role == 1) {
                HalamanMenuUser(root, &L);
            } else {
                printf("Role tidak dikenali. Hubungi admin sistem.\n");
            }
        } else {
            printf("Akun tidak ditemukan.\n");
        }
    }


    return 0;
}