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
    DeAlokasi(P);
}


address SearchKota(List L, int id) {
    address P = L.First;
    while (P != NULL) {
        KotaInfo *info = (KotaInfo *)P->info;
        if (info->id == id) return P;
        P = P->next;
    }
    return NULL;
}

address SearchPrecKota(List L, int id) {
    address P = L.First;
    address Prec = NULL;
    while (P != NULL) {
        KotaInfo *info = (KotaInfo *)P->info;
        if (info->id == id) return Prec;
        Prec = P;
        P = P->next;
    }
    return NULL;
}

void InsLastKota(List *L, KotaInfo X) {
    address P = AlokasiKota(X);
    if (P != NULL) {
        InsLast(L, (infotype)P->info);
    }
}

void DelPKota(List *L, int id) {
    address P = SearchKota(*L, id);
    if (P != NULL) {
        address Prec = SearchPrecKota(*L, id);
        if (Prec == NULL) {
            KotaInfo dummy;
            DelFirstKota(L, &dummy);
        } else {
            Prec->next = P->next;
            DeAlokasiKota(P);
        }
    }
}

void DelAllKota(List *L) {
    KotaInfo temp;
    while (!ListEmpty(*L)) {
        DelFirstKota(L, &temp);
    }
}

void PrintKota(List L) {
    address P = L.First;
    printf("Daftar Kota:\n");
    while (P != NULL) {
        KotaInfo *info = (KotaInfo *)P->info;
        printf("ID: %d | Nama: %s\n", info->id, info->nama);
        P = P->next;
    }
}

void InsFirstKota(List *L, KotaInfo X) {
    address P = AlokasiKota(X);
    if (P != NULL) {
        InsFirst(L, (infotype)P->info);
    }
}

void InsertAfterKota(List *L, KotaInfo X, address Prec) {
    address P = AlokasiKota(X);
    if (P != NULL) {
        InsertAfter(L, (infotype)P->info, Prec);
    }
}

void DelFirstKota(List *L, KotaInfo *X) {
    address P = L->First;
    if (P != NULL) {
        *X = *(KotaInfo *)P->info;
        DelFirst(L, (infotype *)&P->info);
        DeAlokasiKota(P);
    }
}

void DelLastKota(List *L, KotaInfo *X) {
    address P = L->First;
    if (P != NULL) {
        while (P->next != NULL && P->next->next != NULL) {
            P = P->next;
        }
        address last = (P->next == NULL) ? P : P->next;
        *X = *(KotaInfo *)last->info;
        DelLast(L, (infotype *)&last->info);
        DeAlokasiKota(last);
    }
}
