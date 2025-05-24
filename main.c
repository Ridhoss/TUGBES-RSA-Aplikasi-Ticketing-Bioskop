#include <stdio.h>
#include <string.h>
#include "models/header/ADTTree.h"

void inputString(char* buffer) {
    scanf(" %[^\n]", buffer);
}

void printTree(address node, int level) {
    if (node == NULL) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("- %s\n", node->info);
    printTree(node->fs, level + 1);
    printTree(node->nb, level);
}

int main() {
    char rootName[100];
    printf("Masukkan nama root tree: ");
    inputString(rootName);

    address root = CreateTree(rootName);
    if (root == NULL) {
        printf("Gagal membuat tree.\n");
        return 1;
    }

    char childName[100];
    char pilihan;

    do {
        printf("Masukkan nama anak dari %s: ", root->info);
        inputString(childName);
        AddChild(root, childName);

        printf("Tambah anak lain? (y/n): ");
        scanf(" %c", &pilihan);
    } while (pilihan == 'y' || pilihan == 'Y');

    printf("\nTree yang dibuat:\n");
    printTree(root, 0);

    return 0;
}
