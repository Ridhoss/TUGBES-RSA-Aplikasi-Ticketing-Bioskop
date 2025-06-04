#include "header/ADTKota.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// modul modul operasi file

void SimpanKotaKeFile(const KotaInfo* kota) {
    FILE* file = fopen("database/kota.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s\n", kota->nama);
        fclose(file);
    } else {
        printf("Gagal membuka file untuk menyimpan data kota.\n");
    }
}

int SearchKotaFile(const char* namaKota) {
    FILE* file = fopen("database/kota.txt", "r");
    if (!file) return 0;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, namaKota) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void EditKotaKeFile(const char* namaLama, const char* namaBaru) {
    if (!SearchKotaFile(namaLama)) {
        printf("Kota '%s' tidak ditemukan. Tidak dapat melakukan edit.\n", namaLama);
        return;
    }

    FILE* file = fopen("database/kota.txt", "r");
    if (!file) {
        printf("Gagal membuka file untuk membaca data kota.\n");
        return;
    }

    char buffer[256];
    FILE* temp = fopen("database/temp.txt", "w");
    if (!temp) {
        printf("Gagal membuka file sementara.\n");
        fclose(file);
        return;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, namaLama) == 0) {
            fprintf(temp, "%s\n", namaBaru);
        } else {
            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);

    remove("database/kota.txt");
    rename("database/temp.txt", "database/kota.txt");

    printf("Kota '%s' berhasil diubah menjadi '%s'.\n", namaLama, namaBaru);
}

void HapusKotaKeFile(const char* namaKota) {
    if (!SearchKotaFile(namaKota)) {
        printf("Kota '%s' tidak ditemukan. Tidak dapat menghapus.\n", namaKota);
        return;
    }

    FILE* file = fopen("database/kota.txt", "r");
    if (!file) {
        printf("Gagal membuka file untuk membaca data kota.\n");
        return;
    }

    char buffer[256];
    FILE* temp = fopen("database/temp.txt", "w");
    if (!temp) {
        printf("Gagal membuka file sementara.\n");
        fclose(file);
        return;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, namaKota) != 0) {
            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);

    remove("database/kota.txt");
    rename("database/temp.txt", "database/kota.txt");

    printf("Kota '%s' berhasil dihapus.\n", namaKota);
}

void LoadKota(address root) {
    FILE* file = fopen("database/kota.txt", "r");
    if (!file) {
        printf("File kota.txt tidak ditemukan atau gagal dibuka.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        TambahKota(root, buffer);
    }

    fclose(file);
}


// modul modul utama

address AlokasiKota(KotaInfo X) {
    KotaInfo *newInfo = (KotaInfo *)malloc(sizeof(KotaInfo));
    if (newInfo != NULL) {
        *newInfo = X;
        return Alokasi((infotype)newInfo);
    }
    return NULL;
}

void DeAlokasiKota(address P) {
    free(P->info);
    Dealokasi(P);
}

void TambahKota(address root, const char* namaKota) {
    if (root == NULL) {
        printf("Root tidak ditemukan.\n");
        return;
    }

    KotaInfo kotaBaru;
    strcpy(kotaBaru.nama, namaKota);

    address nodeBaru = AlokasiKota(kotaBaru);
    if (nodeBaru == NULL) {
        printf("Gagal mengalokasikan node kota.\n");
        return;
    }

    AddChild(root, nodeBaru->info);

    printf("Kota '%s' berhasil ditambahkan.\n", kotaBaru.nama);
}

void TambahKotaBaru(address root, const char* namaKota) {
    TambahKota(root, namaKota);

    KotaInfo kota;
    strcpy(kota.nama, namaKota);
    SimpanKotaKeFile(&kota);

    printf("Kota '%s' berhasil ditambahkan dan disimpan ke file.\n", namaKota);
}

void UbahKota(address node, KotaInfo dataBaru) {
    KotaInfo* newInfo = (KotaInfo*) malloc(sizeof(KotaInfo));

    if (newInfo != NULL) {
        KotaInfo* oldInfo = (KotaInfo*) node->info;
        char namaLama[100];
        strcpy(namaLama, oldInfo->nama);

        *newInfo = dataBaru;
        UbahNode(node, (infotype)newInfo);

        EditKotaKeFile(namaLama, dataBaru.nama);
    }
}

void DeleteKota(address root, const char* namaKota) {
    if (IsTreeEmpty(root)) {
        printf("Tree kosong.\n");
        return;
    }

    address delNode = SearchKota(root, namaKota);
    
    if (delNode == NULL) {
        printf("Node %s tidak ditemukan.\n", namaKota);
        return;
    }

    HapusKotaKeFile(namaKota);

    DeleteNode(&root, delNode);

    printf("Node %s berhasil dihapus.\n", namaKota);
}

void DeleteAllKota(address root) {
    if (IsTreeEmpty(root)) {
        printf("Tree kosong.\n");
        return;
    }

    DeleteAllKeepRoot(root);
}

int CompareKota(infotype a, infotype b) {
    KotaInfo* kota1 = (KotaInfo*) a;
    KotaInfo* kota2 = (KotaInfo*) b;

    return strcmp(kota1->nama, kota2->nama);
}

address SearchKota(address root, const char* namaKota) {
    KotaInfo target;
    strcpy(target.nama, namaKota);

    return Search(root, (infotype)&target, CompareKota);
}

void PrintKota(address node, int level) {
    if (IsTreeEmpty(node)) {
        printf("Tree kosong.\n");
        return;
    }
    
    printf("\nDaftar Kota :\n");

    PrintChildrenOnly(node, level);
}