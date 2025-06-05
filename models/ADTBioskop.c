#include "header/ADTBioskop.h"
#include "header/ADTTree.h"
#include "header/ADTKota.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SimpanBioskopKeFile(const char* namaKota, const BioskopInfo* bioskop) {
    FILE* file = fopen("database/bioskop.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s|%s\n", namaKota, bioskop->nama);
        fclose(file);
    } else {
        printf("Gagal menyimpan bioskop ke file.\n");
    }
}

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

void TambahBioskopBaru(address kota, const char* namaBioskop) {
    TambahBioskop(kota, namaBioskop);

    BioskopInfo bioskop;
    strcpy(bioskop.nama, namaBioskop);

    KotaInfo* kInfo = (KotaInfo*)kota->info;
    SimpanBioskopKeFile(kInfo->nama, &bioskop);

    printf("Bioskop '%s' berhasil ditambahkan dan disimpan ke file.\n", namaBioskop);
}

int CompareBioskop(infotype a, infotype b) {
    BioskopInfo* bioskop1 = (BioskopInfo*) a;
    BioskopInfo* bioskop2 = (BioskopInfo*) b;

    return strcmp(bioskop1->nama, bioskop2->nama);
}

address SearchBioskop(address kota, const char* namaBioskop) {
    BioskopInfo target;
    strcpy(target.nama, namaBioskop);

    return Search(kota, (infotype)&target, CompareBioskop);
}

void PrintBioskop(address node, int level) {
    if (IsTreeEmpty(node)) {
        printf("Tree kosong.\n");
        return;
    }
    
    printf("\nDaftar Bioskop :\n");

    PrintChildrenOnly(node, level);
}
