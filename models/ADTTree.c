#include "header/ADTTree.h"

static int currentId = 1;

address Alokasi(infotype X) {
    address P = (address) malloc(sizeof(Node));
    if (P != NULL) {
        P->id = currentId++;
        P->info = X;
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

address Search(address root, infotype searchinfo) {
    if (root == NULL) return NULL;


    if (strcmp(root->info, searchinfo) == 0) {
        return root;
    }
    address found = Search(root->fs, searchinfo);
    if (found != NULL) {
        return found;
    }
    return Search(root->nb, searchinfo);
}

void DeleteAll(address node) {
    if (node == NULL) return;

    address nextSibling = node->nb;
    DeleteAll(node->fs);
    Dealokasi(node);
    DeleteAll(nextSibling);
}

void DeleteAllKeepRoot(address node) {
    if (node == NULL || node->fs == NULL) return;

    address child = node->fs;
    node->fs = NULL;

    while (child != NULL) {
        address next = child->nb;
        child->nb = NULL;
        child->pr = NULL;
        DeleteAll(child);
        child = next;
    }
}

void DeleteNode(address *root, address delNode) {
    if (delNode == NULL || root == NULL || *root == NULL) return;

    if (*root == delNode) {
        DeleteAll(*root);
        *root = NULL;
        return;
    }

    address parent = delNode->pr;
    if (parent == NULL) return;

    if (parent->fs == delNode) {
        parent->fs = delNode->nb;
        if (parent->fs != NULL) {
            parent->fs->pr = parent;
        }
    } else {
        address sibling = parent->fs;
        while (sibling != NULL && sibling->nb != delNode) {
            sibling = sibling->nb;
        }
        if (sibling != NULL) {
            sibling->nb = delNode->nb;
            if (sibling->nb != NULL) {
                sibling->nb->pr = parent;
            }
        }
    }

    delNode->pr = NULL;
    delNode->nb = NULL;

    DeleteAll(delNode);
}
