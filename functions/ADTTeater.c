#include "../models/ADTTeater.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../models/ADTBioskop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

address AlokasiTeater(TeaterInfo X) {
    TeaterInfo *newInfo = (TeaterInfo *)malloc(sizeof(TeaterInfo));
    if (newInfo != NULL) {
        *newInfo = X;
        return Alokasi((infotype)newInfo);
    }
    return NULL;
}

void DeAlokasiTeater(address P) {
    free(P->info);
    DeAlokasi(P);
}

address SearchTeater(List L, int id) {
    address P = L.First;
    while (P != NULL) {
        TeaterInfo *info = (TeaterInfo *)P->info;
        if (info->id == id) return P;
        P = P->next;
    }
    return NULL;
}

address SearchPrecTeater(List L, int id) {
    address P = L.First;
    address Prec = NULL;
    while (P != NULL) {
        TeaterInfo *info = (TeaterInfo *)P->info;
        if (info->id == id) return Prec;
        Prec = P;
        P = P->next;
    }
    return NULL;
}

void InsLastTeater(List *L, TeaterInfo X) {
    address P = AlokasiTeater(X);
    if (P != NULL) {
        InsLast(L, (infotype)P->info);
    }
}

void DelPTeater(List *L, int id) {
    address P = SearchTeater(*L, id);
    if (P != NULL) {
        address Prec = SearchPrecTeater(*L, id);
        if (Prec == NULL) {
            TeaterInfo dummy;
            DelFirstTeater(L, &dummy);
        } else {
            Prec->next = P->next;
            DeAlokasiTeater(P);
        }
    }
}

void DelAllTeater(List *L) {
    TeaterInfo temp;
    while (!ListEmpty(*L)) {
        DelFirstTeater(L, &temp);
    }
}

void PrintTeater(List L) {
    address P = L.First;
    printf("Daftar Teater:\n");
    while (P != NULL) {
        TeaterInfo *info = (TeaterInfo *)P->info;
        printf("ID: %d | Nama: %s \n", info->id, info->nama);
        P = P->next;
    }
}

// opsional (dipertimbangkan)

void InsFirstTeater(List *L, TeaterInfo X) {
    address P = AlokasiTeater(X);
    if (P != NULL) {
        InsFirst(L, (infotype)P->info);
    }
}

void InsertAfterTeater(List *L, TeaterInfo X, address Prec) {
    address P = AlokasiTeater(X);
    if (P != NULL) {
        InsertAfter(L, (infotype)P->info, Prec);
    }
}

void DelFirstTeater(List *L, TeaterInfo *X) {
    address P = L->First;
    if (P != NULL) {
        *X = *(TeaterInfo *)P->info;
        DelFirst(L, (infotype *)&P->info);
        DeAlokasiTeater(P);
    }
}

void DelLastTeater(List *L, TeaterInfo *X) {
    address P = L->First;
    if (P != NULL) {
        while (P->next != NULL && P->next->next != NULL) {
            P = P->next;
        }
        address last = (P->next == NULL) ? P : P->next;
        *X = *(TeaterInfo *)last->info;
        DelLast(L, (infotype *)&last->info);
        DeAlokasiTeater(last);
    }
}