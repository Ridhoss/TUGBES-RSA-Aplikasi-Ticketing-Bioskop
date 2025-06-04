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


void TambahKota(address root, char namaKota[100]) {
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

int CompareKota(infotype a, infotype b) {
    KotaInfo* kota1 = (KotaInfo*)a;
    KotaInfo* kota2 = (KotaInfo*)b;

    return strcmp(kota1->nama, kota2->nama);
}

address SearchKota(address root, const char* namaKota) {
    KotaInfo target;
    strcpy(target.nama, namaKota);

    return Search(root, (infotype)&target, CompareKota);
}


// address SearchKota(List L, int id) {
//     address P = L.First;
//     while (P != NULL) {
//         KotaInfo *info = (KotaInfo *)P->info;
//         if (info->id == id) return P;
//         P = P->next;
//     }
//     return NULL;
// }


// void DelPKota(List *L, int id) {
//     address P = SearchKota(*L, id);
//     if (P != NULL) {
//         address Prec = SearchPrecKota(*L, id);
//         if (Prec == NULL) {
//             KotaInfo dummy;
//             DelFirstKota(L, &dummy);
//         } else {
//             Prec->next = P->next;
//             DeAlokasiKota(P);
//         }
//     }
// }

// void DelAllKota(List *L) {
//     KotaInfo temp;
//     while (!ListEmpty(*L)) {
//         DelFirstKota(L, &temp);
//     }
// }

// void PrintKota(List L) {
//     address P = L.First;
//     printf("Daftar Kota:\n");
//     while (P != NULL) {
//         KotaInfo *info = (KotaInfo *)P->info;
//         printf("ID: %d | Nama: %s\n", info->id, info->nama);
//         P = P->next;
//     }
// }