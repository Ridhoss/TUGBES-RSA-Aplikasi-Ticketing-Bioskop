#include "header/ADTKota.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// modul modul operasi file

// Deskripsi : Prosedur untuk menyimpan data kota ke file
void SimpanKotaKeFile(const KotaInfo* kota) {
    FILE* file = fopen("database/kota.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s\n", kota->nama);
        fclose(file);
    } else {
        printf("Gagal membuka file untuk menyimpan data kota.\n");
    }
}

// Deskripsi : fungsi untuk mencari kota dalam file
// IS/FS : input namakota dan mengembalikan 1 jika ditemukan, 0 jika tidak
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

// Deskripsi : Prosedur untuk mengedit nama kota dalam file
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

// Deskripsi : Prosedur untuk menghapus kota dari file
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

// Deskripsi : Prosedur untuk mengosongkan file kota.txt
void KosongkanFileKota() {
    FILE* file = fopen("database/kota.txt", "w");
    if (file != NULL) {
        fclose(file);
        printf("File kota.txt berhasil dikosongkan.\n");
    } else {
        printf("Gagal mengosongkan file kota.txt.\n");
    }
}

// Deskripsi : Prosedur untuk memuat data kota dari file
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

// Deskripsi : Fungsi untuk Alokasi memori KotaInfo
// IS/FS : Alokasi memori untuk KotaInfo dan mengembalikan address
address AlokasiKota(KotaInfo X) {
    KotaInfo *newInfo = (KotaInfo *)malloc(sizeof(KotaInfo));
    if (newInfo != NULL) {
        *newInfo = X;
        return Alokasi((infotype)newInfo);
    }
    return NULL;
}

// Deskripsi : Prosedur untuk Dealokasi memori KotaInfo
void DeAlokasiKota(address P) {
    free(P->info);
    Dealokasi(P);
}

// Deskripsi : Prosedur untuk menambah kota ke dalam tree
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

// Deskripsi : Prosedur untuk menambah kota baru dan menyimpannya ke file
void TambahKotaBaru(address root, const char* namaKota) {
    TambahKota(root, namaKota);

    KotaInfo kota;
    strcpy(kota.nama, namaKota);
    SimpanKotaKeFile(&kota);

    printf("Kota '%s' berhasil ditambahkan dan disimpan ke file.\n", namaKota);
}


// Deskripsi : Prosedur untuk mengubah nama kota pada node
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

// Deskripsi : Prosedur untuk menghapus kota dari tree dan file
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

// Deskripsi : Prosedur untuk menghapus semua kota dari tree
void DeleteAllKota(address root) {
    if (IsTreeEmpty(root)) {
        printf("Tree kosong.\n");
        return;
    }

    DeleteAllKeepRoot(root);
    KosongkanFileKota();
}

// Deskripsi : Fungsi untuk membandingkan dua kota berdasarkan nama
// IS/FS :  Mengembalikan nilai negatif jika a < b, 0 jika a == b, dan positif jika a > b
int CompareKota(infotype a, infotype b) {
    KotaInfo* kota1 = (KotaInfo*) a;
    KotaInfo* kota2 = (KotaInfo*) b;

    return strcmp(kota1->nama, kota2->nama);
}

// Deskripsi : Fungsi untuk mencari kota berdasarkan nama
// IS/FS : Mengembalikan address dari node yang ditemukan, atau NULL jika tidak ditemukan
address SearchKota(address root, const char* namaKota) {
    KotaInfo target;
    strcpy(target.nama, namaKota);

    return Search(root, (infotype)&target, CompareKota);
}

// Deskripsi : Prosedur untuk mencetak daftar kota
void PrintKota(address node, int level) {
    if (IsTreeEmpty(node)) {
        printf("Tree kosong.\n");
        return;
    }
    
    printf("\nDaftar Kota :\n");

    PrintChildrenOnly(node, level);
}