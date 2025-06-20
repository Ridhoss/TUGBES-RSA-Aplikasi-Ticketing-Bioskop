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
    CreateQueue(&QueueETicket);
    LoadQueueFromFile(&QueueETicket);
    
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

    HalamanAwal(&root, &L);

    return 0;
}