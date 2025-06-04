#include "header/ADTTree.h"

static int currentId = 1;

boolean IsTreeEmpty(address root) {
    return (root == NULL || root->fs == NULL);
}

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
    free(P->info);
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

address Search(address root, infotype searchinfo, CompareFunc cmp) {
    if (root == NULL) return NULL;

    if (cmp(root->info, searchinfo) == 0) {
        return root;
    }

    address found = Search(root->fs, searchinfo, cmp);
    if (found != NULL) {
        return found;
    }

    return Search(root->nb, searchinfo, cmp);
}

void UbahNode(address node, infotype newInfo) {
    if (node != NULL) {
        node->info = newInfo;
    }
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

void PrintTree(address node, int level) {
    if (node == NULL) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("- %s\n", node->info);
    PrintTree(node->fs, level + 1);
    PrintTree(node->nb, level);
}

void PrintChildrenOnly(address node, int level) {
    if (node == NULL || node->fs == NULL) return;

    address child = node->fs;
    while (child != NULL) {
        for (int i = 0; i < level; i++) printf("  ");
        printf("- %s\n", child->info);
        PrintTree(child->fs, level + 1);
        child = child->nb;
    }
}

void InputString(char* buffer) {
    scanf(" %[^\n]", buffer);
}
