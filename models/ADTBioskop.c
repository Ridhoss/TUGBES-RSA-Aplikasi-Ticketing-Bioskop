#include "header/ADTBioskop.h"
#include "header/ADTTree.h"
#include "header/ADTKota.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

address AlokasiBioskop(BioskopInfo X) {
    BioskopInfo* info = (BioskopInfo*) malloc(sizeof(BioskopInfo));
    if (info) {
        *info = X;
        return Alokasi((infotype)info);
    }
    return NULL;
}

void DeAlokasiBioskop(address P) {
    if (P != NULL) {
        free(P->info);
        Dealokasi(P);
    }
}

void TambahBioskop(address kota, const char* namaBioskop) {
    if (kota == NULL) return;

    BioskopInfo bioskop;
    strcpy(bioskop.nama, namaBioskop);

    address node = AlokasiBioskop(bioskop);
    if (node == NULL) {
        printf("Gagal mengalokasikan node bioskop.\n");
        return;
    }
    AddChild(kota, node->info);
    printf("Bioskop '%s' berhasil ditambahkan.\n", namaBioskop);
}
