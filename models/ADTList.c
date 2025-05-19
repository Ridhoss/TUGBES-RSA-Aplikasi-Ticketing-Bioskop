#include "header/ADTList.h"
#include <stdio.h>
#include <stdlib.h>

boolean ListEmpty(List L) {
    return L.First == NULL && L.Last == NULL;
}

void CreateList(List *L) {
    L->First = NULL;
    L->Last = NULL;
}

void UpdateLast(List *L) {
    if (L->First == NULL) {
        // List kosong
        L->Last = NULL;
    } else {
        address P = L->First;
        while (P->next != NULL) {
            P = P->next;
        }
        L->Last = P;
    }
}

address Alokasi(infotype X) {
    address P = (address)malloc(sizeof(struct tElmtList));
    if (P != NULL) {
        P->info = X;
        P->next = NULL;
    }
    return P;
}

void DeAlokasi(address P) {
    free(P->info);
    free(P);
}

address Search(List L, infotype X) {
    address P = L.First;
    while (P != NULL && P->info != X) {
        P = P->next;
    }
    return P;
}

address SearchPrec(List L, infotype X) {
    address P = L.First;
    address Prec = NULL;

    while (P != NULL && P->info != X) {
        Prec = P;
        P = P->next;
    }

    return (P != NULL) ? Prec : NULL;
}

void InsLast(List *L, infotype X) {
    address P = Alokasi(X);
    if (P != NULL) {
        if (ListEmpty(*L)) {
            L->First = P;
        } else {
            L->Last->next = P;
        }
        UpdateLast(L);
    }
}


void DelP(List *L, infotype X) {
    if (!ListEmpty(*L)) {
        address P = Search(*L, X);
        if (P != NULL) {
            address Prec = SearchPrec(*L, X);

            if (Prec == NULL) {
                // elemen di awal
                infotype dummy;
                DelFirst(L, &dummy);
            } else {
                Prec->next = P->next;
                DeAlokasi(P);
            }
        }

        UpdateLast(L);
    }
}

void DelAll(List *L) {
    infotype temp;
    while (!ListEmpty(*L)) {
        DelFirst(L, &temp);
    }

    UpdateLast(L);
}

void PrintInfo(List L) {
    address P = L.First;
    printf("[");
    while (P != NULL) {
        printf("%d", P->info);
        if (P->next != NULL) {
            printf(", ");
        }
        P = P->next;
    }
    printf("]\n");
}


// opsional (dipertimbangkan)

void InsFirst(List *L, infotype X) {
    address P = Alokasi(X);
    if (P != NULL) {
        P->next = L->First;
        L->First = P;

        UpdateLast(L);
    }

}

void InsertAfter(List *L, infotype X, address Prec) {
    if (Prec != NULL) {
        address P = Alokasi(X);
        if (P != NULL) {
            P->next = Prec->next;
            Prec->next = P;
        }

        UpdateLast(L);
    }
}

void DelFirst(List *L, infotype *X) {
    if (!ListEmpty(*L)) {
        address P = L->First;
        *X = P->info;
        L->First = P->next;
        DeAlokasi(P);

        UpdateLast(L);
    }
}

void DelLast(List *L, infotype *X) {
    if (!ListEmpty(*L)) {
        address P = L->First;
        address Prec = NULL;

        while (P->next != NULL) {
            Prec = P;
            P = P->next;
        }

        *X = P->info;

        if (Prec == NULL) {
            L->First = NULL;
        } else {
            Prec->next = NULL;
        }
        DeAlokasi(P);

        UpdateLast(L);
    }
}