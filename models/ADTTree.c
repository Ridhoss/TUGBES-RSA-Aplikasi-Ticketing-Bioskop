#include "header/ADTTree.h"

static int currentId = 1;

address Alokasi(infotype X) {
    address P = (address) malloc(sizeof(Node));
    if (P != NULL) {
        P->id = currentId++;
        strcpy(P->info, X);
        P->pr = NULL;
        P->fs = NULL;
        P->nb = NULL;
    }
    return P;
}


void Dealokasi(address P) {
    free(P);
}

address CreateTree(infotype rootInfo) {
    return Alokasi(rootInfo);
}

void AddChild(address parent, infotype childInfo) {
    if (parent == NULL) return;

    address child = Alokasi(childInfo);
    if (child == NULL) return;

    child->pr = parent;

    if (parent->fs == NULL) {
        parent->fs = child;
    } else {
        address sibling = parent->fs;
        while (sibling->nb != NULL) {
            sibling = sibling->nb;
        }
        sibling->nb = child;
    }
}

