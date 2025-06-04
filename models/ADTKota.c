#include "header/ADTKota.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

address AlokasiKota(KotaInfo X) {
    KotaInfo *newInfo = (KotaInfo *)malloc(sizeof(KotaInfo));
    if (newInfo != NULL) {
        *newInfo = X;
        return Alokasi((infotype)newInfo);
    }
    return NULL;
}

void DeAlokasiKota(address P) {
    free(P->info);
    Dealokasi(P);
}


void TambahKota(address root, const char* namaKota) {
    if (root == NULL) {
        printf("Root tidak ditemukan.\n");
        return;
    }

    KotaInfo kotaBaru;
    strcpy(kotaBaru.nama, namaKota);

    address nodeBaru = AlokasiKota(kotaBaru);
    if (nodeBaru == NULL) {
        printf("Gagal mengalokasikan node kota.\n");
        return;
    }

    AddChild(root, nodeBaru->info);

    printf("Kota '%s' berhasil ditambahkan.\n", kotaBaru.nama);
}

void DeleteKota(address root, const char* namaKota) {
    if (IsTreeEmpty(root)) {
        printf("Tree kosong.\n");
        return;
    }

    address delNode = SearchKota(root, namaKota);
    
    if (delNode == NULL) {
        printf("Node %s tidak ditemukan.\n", namaKota);
        return;
    }

    DeleteNode(&root, delNode);

    printf("Node %s berhasil dihapus.\n", namaKota);
}

int CompareKota(infotype a, infotype b) {
    KotaInfo* kota1 = (KotaInfo*) a;
    KotaInfo* kota2 = (KotaInfo*) b;

    return strcmp(kota1->nama, kota2->nama);
}

address SearchKota(address root, const char* namaKota) {
    KotaInfo target;
    strcpy(target.nama, namaKota);

    return Search(root, (infotype)&target, CompareKota);
}