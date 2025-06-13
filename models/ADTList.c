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
        addressList P = L->First;
        while (P->next != NULL) {
            P = P->next;
        }
        L->Last = P;
    }
}

addressList Allocation(infotype X) {
    addressList P = (addressList)malloc(sizeof(struct tElmtList));
    if (P != NULL) {
        P->info = X;
        P->next = NULL;
    }
    return P;
}

void DeAllocation(addressList P) {
    free(P->info);
    free(P);
}

addressList SearchList(List L, infotype X) {
    addressList P = L.First;
    while (P != NULL && P->info != X) {
        P = P->next;
    }
    return P;
}

addressList SearchPrec(List L, infotype X) {
    addressList P = L.First;
    addressList Prec = NULL;

    while (P != NULL && P->info != X) {
        Prec = P;
        P = P->next;
    }

    return (P != NULL) ? Prec : NULL;
}

void InsLast(List *L, infotype X) {
    addressList P = Allocation(X);
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
        addressList P = SearchList(*L, X);
        if (P != NULL) {
            addressList Prec = SearchPrec(*L, X);

            if (Prec == NULL) {
                // elemen di awal
                infotype dummy;
                DelFirst(L, &dummy);
            } else {
                Prec->next = P->next;
                DeAllocation(P);
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
    addressList P = L.First;
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
    addressList P = Allocation(X);
    if (P != NULL) {
        P->next = L->First;
        L->First = P;

        UpdateLast(L);
    }

}

void InsertAfter(List *L, infotype X, addressList Prec) {
    if (Prec != NULL) {
        addressList P = Allocation(X);
        if (P != NULL) {
            P->next = Prec->next;
            Prec->next = P;
        }

        UpdateLast(L);
    }
}

void DelFirst(List *L, infotype *X) {
    if (!ListEmpty(*L)) {
        addressList P = L->First;
        *X = P->info;
        L->First = P->next;
        DeAllocation(P);

        UpdateLast(L);
    }
}

void DelLast(List *L, infotype *X) {
    if (!ListEmpty(*L)) {
        addressList P = L->First;
        addressList Prec = NULL;

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
        DeAllocation(P);

        UpdateLast(L);
    }
}