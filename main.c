#include <stdio.h>
#include <string.h>
#include "models/header/ADTTree.h"
#include "models/header/ADTKota.h"

int main() {
    char* rootStr = (char*) malloc(strlen("Head") + 1);
    strcpy(rootStr, "Head");
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
        printf("2. Tambah child\n");
        printf("3. Hapus node tertentu\n");
        printf("4. Hapus seluruh tree\n");
        printf("5. Cetak tree\n");
        printf("6. Keluar\n");
        printf("Pilih opsi (1-5): ");
        scanf(" %c", &pilihan);

        switch (pilihan) {
            case '1': {
                printf("Masukkan nama kota baru: ");
                inputString(childName);

                TambahKota(root, childName);

                break;
            }
            case '2': {
                printf("Masukkan nama kota yang ingin ditambahkan sebagai anak dari %s: ", root->info);
                inputString(childName);

                TambahKota(root, childName);

                break;
            }
            case '3': {
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
            case '4': {
                if (root->fs == NULL) {
                    printf("Tree sudah kosong.\n");
                } else {
                    DeleteAllKeepRoot(root);
                    printf("Seluruh tree berhasil dihapus.\n");
                }
                break;
            }
            case '5': {
                if (root->fs == NULL) {
                    printf("Tree kosong.\n");
                } else {
                    printf("\nTree saat ini:\n");
                    printTree(root, 0);
                }
                break;
            }
            case '6': {
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