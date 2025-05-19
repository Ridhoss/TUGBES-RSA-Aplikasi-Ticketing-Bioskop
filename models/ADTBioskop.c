#include "header/ADTBioskop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

address AlokasiBioskop(BioskopInfo X) {
    BioskopInfo *newInfo = (BioskopInfo *)malloc(sizeof(BioskopInfo));
    if (newInfo != NULL) {
        *newInfo = X;
        return Alokasi((infotype)newInfo);
    }
    return NULL;
}

void DeAlokasiBioskop(address P) {
    free(P->info);
    DeAlokasi(P);
}

address SearchBioskop(List L, int id) {
    address P = L.First;
    while (P != NULL) {
        BioskopInfo *info = (BioskopInfo *)P->info;
        if (info->id == id) return P;
        P = P->next;
    }
    return NULL;
}

address SearchPrecBioskop(List L, int id) {
    address P = L.First;
    address Prec = NULL;
    while (P != NULL) {
        BioskopInfo *info = (BioskopInfo *)P->info;
        if (info->id == id) return Prec;
        Prec = P;
        P = P->next;
    }
    return NULL;
}

void InsLastBioskop(List *L, BioskopInfo X) {
    address P = AlokasiBioskop(X);
    if (P != NULL) {
        InsLast(L, (infotype)P->info);
    }
}

void DelPBioskop(List *L, int id) {
    address P = SearchBioskop(*L, id);
    if (P != NULL) {
        address Prec = SearchPrecBioskop(*L, id);
        if (Prec == NULL) {
            BioskopInfo dummy;
            DelFirstBioskop(L, &dummy);
        } else {
            Prec->next = P->next;
            DeAlokasiBioskop(P);
        }
    }
}

void DelAllBioskop(List *L) {
    BioskopInfo temp;
    while (!ListEmpty(*L)) {
        DelFirstBioskop(L, &temp);
    }
}

void PrintBioskop(List L) {
    address P = L.First;
    printf("Daftar Bioskop:\n");
    while (P != NULL) {
        BioskopInfo *info = (BioskopInfo *)P->info;
        printf("ID: %d | Nama: %s | Kota: %s\n", info->id, info->nama, info->kota);
        P = P->next;
    }
}

// opsional (dipertimbangkan)

void InsFirstBioskop(List *L, BioskopInfo X) {
    address P = AlokasiBioskop(X);
    if (P != NULL) {
        InsFirst(L, (infotype)P->info);
    }
}

void InsertAfterBioskop(List *L, BioskopInfo X, address Prec) {
    address P = AlokasiBioskop(X);
    if (P != NULL) {
        InsertAfter(L, (infotype)P->info, Prec);
    }
}

void DelFirstBioskop(List *L, BioskopInfo *X) {
    address P = L->First;
    if (P != NULL) {
        *X = *(BioskopInfo *)P->info;
        DelFirst(L, (infotype *)&P->info);
        DeAlokasiBioskop(P);
    }
}

void DelLastBioskop(List *L, BioskopInfo *X) {
    address P = L->First;
    if (P != NULL) {
        while (P->next != NULL && P->next->next != NULL) {
            P = P->next;
        }
        address last = (P->next == NULL) ? P : P->next;
        *X = *(BioskopInfo *)last->info;
        DelLast(L, (infotype *)&last->info);
        DeAlokasiBioskop(last);
    }
}