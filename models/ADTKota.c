#include "header/ADTKota.h"

// modul modul operasi file

// Deskripsi : Prosedur untuk menyimpan data kota ke file
// IS : menerima pointer ke KotaInfo
// FS : menyimpan nama kota ke dalam file "database/kota.txt"
void SimpanKotaKeFile(const KotaInfo* kota) {
    FILE* file = fopen("database/kota.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d|%s|\n", kota->id, kota->nama);
        fclose(file);
    } else {
        printf("Gagal membuka file untuk menyimpan data kota.\n");
    }
}

// Deskripsi : fungsi untuk mencari kota dalam file
// IS : menerima nama kota sebagai string   
// FS : mengembalikan 1 jika kota ditemukan, 0 jika tidak ditemukan
int SearchKotaFile(const KotaInfo* kota) {
    FILE* file = fopen("database/kota.txt", "r");
    if (!file) return 0;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char* idStr = strtok(buffer, "|");
        char* kotaNama = strtok(NULL, "|");

        if(idStr && kotaNama) {
            int id = atoi(idStr);

            if (id == kota->id) {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

// Deskripsi : Prosedur untuk mengedit nama kota dalam file
// IS : menerima nama lama dan nama baru sebagai string
// FS : mengubah nama kota dalam file "database/kota.txt"
void EditKotaKeFile(const KotaInfo* kotaLama, const KotaInfo* kotaBaru) {
    if (!SearchKotaFile(kotaLama)) {
        printf("Kota '%s' tidak ditemukan. Tidak dapat melakukan edit.\n", kotaLama->nama);
        return;
    }

    FILE* file = fopen("database/kota.txt", "r");
    FILE* temp = fopen("database/temp.txt", "w");
    if (!file || !temp) return;
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        int id;
        char kotaNama[100];
        sscanf(buffer, "%d|%[^|\n]", &id, kotaNama);

        if (id == kotaLama->id) {
            fprintf(temp, "%d|%s|\n", kotaLama->id, kotaBaru->nama);
        } else {
            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);

    remove("database/kota.txt");
    rename("database/temp.txt", "database/kota.txt");

    printf("Kota '%s' berhasil diubah menjadi '%s'.\n", kotaLama->nama, kotaBaru->nama);
}

// Deskripsi : Prosedur untuk menghapus kota dari file
// IS : menerima nama kota sebagai string
// FS : menghapus nama kota dari file "database/kota.txt"
void HapusKotaKeFile(const KotaInfo* kotaLama) {
    if (!SearchKotaFile(kotaLama)) {
        printf("Kota '%s' tidak ditemukan. Tidak dapat menghapus.\n", kotaLama->nama);
        return;
    }

    FILE* file = fopen("database/kota.txt", "r");
    FILE* temp = fopen("database/temp.txt", "w");
    if (!file || !temp) return;
    
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        int id;
        char kotaNama[100];
        sscanf(buffer, "%d|%[^|\n]", &id, kotaNama);

        if (id != kotaLama->id) {
            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);

    remove("database/kota.txt");
    rename("database/temp.txt", "database/kota.txt");

    printf("Kota '%s' berhasil dihapus.\n", kotaLama->nama);
}

// Deskripsi : Prosedur untuk mengosongkan file kota.txt
// IS : membuka file "database/kota.txt" dalam mode tulis
// FS : mengosongkan isi file
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
// IS : membuka file "database/kota.txt" dalam mode baca
// FS : membaca setiap baris dari file dan menambahkannya ke tree
void LoadKota(address root) {
    FILE* file = fopen("database/kota.txt", "r");
    if (!file) {
        printf("File kota.txt tidak ditemukan atau gagal dibuka.\n");
        return;
    }

    KotaInfo kota;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char* idStr = strtok(buffer, "|");
        char* kotaNama = strtok(NULL, "|");

        if (idStr && kotaNama)
        {
            int id = atoi(idStr);

            kota.id = id;
            strcpy(kota.nama, kotaNama);

            TambahKota(root, kota);
        }

    }

    fclose(file);
}

// Deskripsi : Prosedur untuk mengambil id terakhir dari data file
// IS : membuka file "database/kota.txt" dalam mode baca
// FS : membaca setiap baris dari file dan mencari id paling besar
int AmbilIdKotaTerakhir() {
    FILE* file = fopen("database/kota.txt", "r");
    if (file == NULL) {
        return 0;
    }

    int idTerakhir = 0;
    char buffer[200];

    while (fgets(buffer, sizeof(buffer), file)) {
        char* idStr = strtok(buffer, "|");

        if (idStr)
        {
            int idSementara = atoi(idStr);
            if (idSementara > idTerakhir) {
                idTerakhir = idSementara;
            }
        } 
    }

    fclose(file);
    return idTerakhir;
}






// modul modul utama

// Deskripsi : Fungsi untuk Alokasi memori KotaInfo
// IS : menerima KotaInfo X
// FS : mengembalikan address yang berisi alokasi memori untuk KotaInfo
address AlokasiKota(KotaInfo X) {    
    KotaInfo *newInfo = (KotaInfo *)malloc(sizeof(KotaInfo));
    if (newInfo != NULL) {
        *newInfo = X;
        return Alokasi((infotype)newInfo, KOTA);
    }
    return NULL;
}

// Deskripsi : Prosedur untuk Dealokasi memori KotaInfo
// IS : menerima address P yang berisi KotaInfo
// FS : menghapus alokasi memori KotaInfo yang ada pada address P
void DeAlokasiKota(address P) {
    free(P->info);
    Dealokasi(P);
}

// Deskripsi : Prosedur untuk menambah kota ke dalam tree
// IS : menerima address root dan namaKota sebagai string
// FS : menambah node baru ke dalam tree sebagai anak dari root
void TambahKota(address root, KotaInfo kotaBaru) {
    if (root == NULL) {
        printf("Root tidak ditemukan.\n");
        return;
    }

    address nodeBaru = AlokasiKota(kotaBaru);
    if (nodeBaru == NULL) {
        printf("Gagal mengalokasikan node kota.\n");
        return;
    }

    AddChild(root, nodeBaru->info, KOTA);

    printf("Kota '%s' berhasil ditambahkan.\n", kotaBaru.nama);
}

// Deskripsi : Prosedur untuk menambah kota baru dan menyimpannya ke file
// IS : menerima address root dan namaKota sebagai string
// FS : menambah node baru ke dalam tree dan menyimpan nama kota ke dalam file
void TambahKotaBaru(address root, KotaInfo kotaBaru) {
    int idBaru = AmbilIdKotaTerakhir() + 1;
    kotaBaru.id = idBaru;

    TambahKota(root, kotaBaru);

    SimpanKotaKeFile(&kotaBaru);

    printf("Kota '%s' berhasil ditambahkan dan disimpan ke file.\n", kotaBaru.nama);
}

// Deskripsi : Prosedur untuk mengubah nama kota pada node
// IS : menerima address node dan dataBaru sebagai KotaInfo
// FS : mengubah nama kota pada node dan memperbarui file
void UbahKota(address dataLama, KotaInfo dataBaru) {
    KotaInfo* newInfo = (KotaInfo*) malloc(sizeof(KotaInfo));
    KotaInfo* oldInfo = (KotaInfo*) dataLama->info;

    if (!newInfo) return;

    dataBaru.id = oldInfo->id;

    *newInfo = dataBaru;
    UbahNode(dataLama, (infotype)newInfo);

    KotaInfo kotaLama;
    kotaLama.id = oldInfo->id;
    strcpy(kotaLama.nama, dataBaru.nama);

    EditKotaKeFile(oldInfo, newInfo);
        
    printf("Nama kota berhasil diubah!\n");
}

// Deskripsi : Prosedur untuk menghapus kota dari tree dan file
// IS : menerima address root dan namaKota sebagai string
// FS : menghapus node yang sesuai dari tree dan menghapus nama kota dari file
void DeleteKota(address kota) {
    if (kota == NULL) return;

    KotaInfo* oldInfo = (KotaInfo*) kota->info;

    KotaInfo kotaLama;
    kotaLama.id = oldInfo->id;
    strcpy(kotaLama.nama, oldInfo->nama);

    address nodeRoot = kota->pr;

    if (nodeRoot) {
        HapusKotaKeFile(&kotaLama);

        DeleteNode(&nodeRoot, kota);

        printf("Node %s berhasil dihapus.\n", kotaLama.nama);
    }
}

// Deskripsi : Prosedur untuk menghapus semua kota dari tree
// IS : menerima address root
// FS : menghapus semua node dari tree dan mengosongkan file kota.txt
void DeleteAllKota(address root) {
    if (IsTreeEmpty(root)) {
        printf("Tree kosong.\n");
        return;
    }

    DeleteAllKeepRoot(root);
    KosongkanFileKota();
}

// Deskripsi : Fungsi untuk membandingkan dua kota berdasarkan nama
// IS : menerima dua infotype yang berisi KotaInfo
// FS : mengembalikan nilai 0 jika kota sama, dan 1 jika kota berbeda
int CompareKota(infotype a, infotype b) {
    KotaInfo* kota1 = (KotaInfo*) a;
    KotaInfo* kota2 = (KotaInfo*) b;

    return strcmp(kota1->nama, kota2->nama);
}

// Deskripsi : Fungsi untuk membandingkan dua kota berdasarkan id
// IS : menerima dua infotype yang berisi KotaInfo
// FS : mengembalikan nilai 0 jika kota sama, dan 1 jika kota berbeda
int CompareKotaId(infotype a, infotype b) {
    KotaInfo* kota1 = (KotaInfo*) a;
    KotaInfo* kota2 = (KotaInfo*) b;

    return kota1->id - kota2->id;
}

// Deskripsi : Fungsi untuk mencari kota berdasarkan nama
// IS : menerima address root dan namaKota
// FS : mengembalikan address dari node yang sesuai, atau NULL jika tidak ditemukan
address SearchKotaByName(address root, const char* namaKota) {
    KotaInfo target;
    strcpy(target.nama, namaKota);

    return Search(root, (infotype)&target, CompareKota, KOTA);
}

// Deskripsi : Fungsi untuk mencari kota berdasarkan id
// IS : menerima address root dan idkota
// FS : mengembalikan address dari node yang sesuai, atau NULL jika tidak ditemukan
address SearchKotaById(address root, const int* idKota) {
    KotaInfo target;
    target.id = *idKota;

    return Search(root, (infotype)&target, CompareKotaId, KOTA);
}

// Deskripsi : Prosedur untuk mencetak daftar kota
// IS : menerima address node dan level untuk indentasi
// FS : mencetak daftar kota yang ada pada tree
void PrintKota(address node, int level) {
    if (IsTreeEmpty(node)) {
        printf("Tree kosong.\n");
        return;
    }
    
    printf("\nDaftar Kota :\n");

    PrintChildrenOnly(node, level);
}