#include "header/ADTJadwal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

address AlokasiJadwal(JadwalInfo X) {
    JadwalInfo *newInfo = (JadwalInfo *)malloc(sizeof(JadwalInfo));
    if (newInfo != NULL) {
        *newInfo = X;
        return Alokasi((infotype)newInfo);
    }
    return NULL;
}

void DeAlokasiJadwal(address P) {
    free(P->info);
    DeAlokasi(P);
}


address SearchJadwal(List L, int id) {
    address P = L.First;
    while (P != NULL) {
        JadwalInfo *info = (JadwalInfo *)P->info;
        if (info->id == id) return P;
        P = P->next;
    }
    return NULL;
}

address SearchPrecJadwal(List L, int id) {
    address P = L.First;
    address Prec = NULL;
    while (P != NULL) {
        JadwalInfo *info = (JadwalInfo *)P->info;
        if (info->id == id) return Prec;
        Prec = P;
        P = P->next;
    }
    return NULL;
}

void InsLastJadwal(List *L, JadwalInfo X) {
    address P = AlokasiJadwal(X);
    if (P != NULL) {
        InsLast(L, (infotype)P->info);
    }
}

void DelPJadwal(List *L, int id) {
    address P = SearchJadwal(*L, id);
    if (P != NULL) {
        address Prec = SearchPrecJadwal(*L, id);
        if (Prec == NULL) {
            JadwalInfo dummy;
            DelFirstJadwal(L, &dummy);
        } else {
            Prec->next = P->next;
            DeAlokasiJadwal(P);
        }
    }
}

void DelAllJadwal(List *L) {
    JadwalInfo temp;
    while (!ListEmpty(*L)) {
        DelFirstJadwal(L, &temp);
    }
}

void PrintJadwal(List L) {
    address P = L.First;
    printf("Daftar Jadwal:\n");
    while (P != NULL) {
        JadwalInfo *info = (JadwalInfo *)P->info;
        printf("ID: %d | Start: %s | End: %s | ID Film: %d\n", info->id, info->start, info->end, info->id_film);
        P = P->next;
    }
}

void InsFirstJadwal(List *L, JadwalInfo X) {
    address P = AlokasiJadwal(X);
    if (P != NULL) {
        InsFirst(L, (infotype)P->info);
    }
}

void InsertAfterJadwal(List *L, JadwalInfo X, address Prec) {
    address P = AlokasiJadwal(X);
    if (P != NULL) {
        InsertAfter(L, (infotype)P->info, Prec);
    }
}

void DelFirstJadwal(List *L, JadwalInfo *X) {
    address P = L->First;
    if (P != NULL) {
        *X = *(JadwalInfo *)P->info;
        DelFirst(L, (infotype *)&P->info);
        DeAlokasiJadwal(P);
    }
}

void DelLastJadwal(List *L, JadwalInfo *X) {
    address P = L->First;
    if (P != NULL) {
        while (P->next != NULL && P->next->next != NULL) {
            P = P->next;
        }
        address last = (P->next == NULL) ? P : P->next;
        *X = *(JadwalInfo *)last->info;
        DelLast(L, (infotype *)&last->info);
        DeAlokasiJadwal(last);
    }
}

// percobaan 
void UpdateJadwalByID(List *L, int id, char* newStart, char* newEnd) {
    address P = SearchJadwal(*L, id);
    if (P != NULL) {
        JadwalInfo *info = (JadwalInfo *)P->info;
        strcpy(info->start, newStart);
        strcpy(info->end, newEnd);
    }
}
// percobaan
address SearchJadwalByFilm(List L, int id_film) {
    address P = L.First;
    while (P != NULL) {
        JadwalInfo *info = (JadwalInfo *)P->info;
        if (info->id_film == id_film) return P;
        P = P->next;
    }
    return NULL;
}

void SortJadwalByTime(List *L) {
    address P, Q;
    JadwalInfo temp;
    for (P = L->First; P != NULL; P = P->next) {
        for (Q = P->next; Q != NULL; Q = Q->next) {
            JadwalInfo *infoP = (JadwalInfo *)P->info;
            JadwalInfo *infoQ = (JadwalInfo *)Q->info;
            if (strcmp(infoP->start, infoQ->start) > 0) {
                temp = *infoP;
                *infoP = *infoQ;
                *infoQ = temp;
            }
        }
    }
}
