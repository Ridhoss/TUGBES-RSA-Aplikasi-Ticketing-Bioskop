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

    char* rootStr = (char*) malloc(strlen(rootName) + 1);
    strcpy(rootStr, rootName);

    address root = CreateTree((infotype)rootStr);
    if (root == NULL) {
        printf("Gagal membuat tree.\n");
        return 1;
    }

    char parentName[100], childName[100];
    char pilihan;

    do {
        printf("\nMenu:\n");
        printf("1. Tambah kota\n");
        printf("2. Hapus node tertentu\n");
        printf("3. Hapus seluruh tree\n");
        printf("4. Cetak tree\n");
        printf("5. Keluar\n");
        printf("Pilih opsi (1-5): ");
        scanf(" %c", &pilihan);

        switch (pilihan) {
            case '1': {
                printf("Masukkan root: ");
                inputString(parentName);
                address parentNode = Search(root, parentName);

                if (parentNode == NULL) {

                    printf("Parent %s tidak ditemukan. Apakah ingin membuat parent baru? (y/n): ", parentName);

                    char pilihParentBaru;
                    scanf(" %c", &pilihParentBaru);

                    if (pilihParentBaru == 'y' || pilihParentBaru == 'Y') {
                        AddChild(root, parentName);
                        parentNode = Search(root, parentName);
                        if (parentNode == NULL) {
                            printf("Gagal membuat parent baru %s.\n", parentName);
                            break;
                        }
                    } else {
                        break;
                    }
                }
                printf("Masukkan nama anak dari %s: ", parentName);
                inputString(childName);
                AddChild(parentNode, childName);
                printf("Anak berhasil ditambahkan.\n");
                break;
            }
            case '2': {
                if (root->fs == NULL) {
                    printf("Tree kosong.\n");
                    break;
                }
                printf("Masukkan nama node yang ingin dihapus: ");
                char delNodeName[100];  
                inputString(delNodeName);

                address delNode = Search(root, delNodeName);
                if (delNode == NULL) {
                    printf("Node %s tidak ditemukan.\n", delNodeName);
                    break;
                }
                DeleteNode(&root, delNode);
                printf("Node %s berhasil dihapus.\n", delNodeName);
                break;
            }
            case '3': {
                if (root->fs == NULL) {
                    printf("Tree sudah kosong.\n");
                } else {
                    DeleteAllKeepRoot(root);
                    printf("Seluruh tree berhasil dihapus.\n");
                }
                break;
            }
            case '4': {
                if (root->fs == NULL) {
                    printf("Tree kosong.\n");
                } else {
                    printf("\nTree saat ini:\n");
                    printTree(root, 0);
                }
                break;
            }
            case '5': {
                printf("Keluar dari program.\n");
                break;
            }
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    
    } while (pilihan != '5');
    
    if (root != NULL) {
        DeleteAll(root);
        root = NULL;
    }
    
    return 0;
}


// int main() {
//     char rootName[100];
//     printf("Masukkan nama root tree: ");
//     inputString(rootName);

//     address root = CreateTree(rootName);
//     if (root == NULL) {
//         printf("Gagal membuat tree.\n");
//         return 1;
//     }

//     char childName[100];
//     char pilihan;

//     do {
//         printf("Masukkan nama anak dari %s: ", root->info);
//         inputString(childName);
//         AddChild(root, childName);

//         printf("Tambah anak lain? (y/n): ");
//         scanf(" %c", &pilihan);
//     } while (pilihan == 'y' || pilihan == 'Y');

//     printf("\nTree yang dibuat:\n");
//     printTree(root, 0);

//     return 0;
// }