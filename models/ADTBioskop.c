#include "header/ADTBioskop.h"

// modul-modul operasi file

// Deskripsi : Prosedur untuk menyimpan data bioskop ke file
// IS : menerima pointer ke BioskopInfo
// FS : menyimpan nama bioskop dan kota ke dalam file "database/bioskop.txt"
void SimpanBioskopKeFile(const char* namaKota, const BioskopInfo* bioskop) {
    FILE* file = fopen("database/bioskop.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s|%s\n", namaKota, bioskop->nama);
        fclose(file);
    } else {
        printf("Gagal menyimpan bioskop ke file.\n");
    }
}

int SearchBioskopFile(const char* namaKota, const char* namaBioskop) {
    FILE* file = fopen("database/bioskop.txt", "r");
    if (!file) return 0;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        char* kota = strtok(buffer, "|");
        char* bioskop = strtok(NULL, "|");
        
        if (kota && bioskop && strcmp(kota, namaKota) == 0 && strcmp(bioskop, namaBioskop) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Mengedit nama bioskop dalam file
void EditBioskopKeFile(const char* namaKota, const char* namaLama, const char* namaBaru) {
    FILE* file = fopen("database/bioskop.txt", "r");
    FILE* temp = fopen("database/temp.txt", "w");
    if (!file || !temp) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char kota[100], bioskop[100];
        sscanf(buffer, "%[^|]|%[^\n]", kota, bioskop);

        if (strcmp(kota, namaKota) == 0 && strcmp(bioskop, namaLama) == 0)
            fprintf(temp, "%s|%s\n", kota, namaBaru);
        else
            fprintf(temp, "%s\n", buffer);
    }

    fclose(file);
    fclose(temp);
    remove("database/bioskop.txt");
    rename("database/temp.txt", "database/bioskop.txt");
}

void HapusBioskopKeFile(const char* namaKota, const char* namaBioskop) {
    FILE* file = fopen("database/bioskop.txt", "r");
    FILE* temp = fopen("database/temp.txt", "w");
    if (!file || !temp) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char kota[100], bioskop[100];
        sscanf(buffer, "%[^|]|%[^\n]", kota, bioskop);

        // Tulis kembali hanya jika bukan yang ingin dihapus
        if (!(strcmp(kota, namaKota) == 0 && strcmp(bioskop, namaBioskop) == 0))
            fprintf(temp, "%s\n", buffer);
    }

    fclose(file);
    fclose(temp);
    remove("database/bioskop.txt");
    rename("database/temp.txt", "database/bioskop.txt");
}

void KosongkanFileBioskop() {
    FILE* file = fopen("database/bioskop.txt", "w");
    if (file != NULL) {
        fclose(file);
        printf("File Bioskop.txt berhasil dikosongkan.\n");
    } else {
        printf("Gagal mengosongkan file kota.txt.\n");
    }
}

void LoadBioskop(address root) {
    FILE* file = fopen("database/bioskop.txt", "r");
    if (!file) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char* kotaNama = strtok(buffer, "|");
        char* bioskopNama = strtok(NULL, "|");

        if (kotaNama && bioskopNama) {
            address kota = SearchKota(root, kotaNama);
            if (kota != NULL) {
                TambahBioskop(kota, bioskopNama);
            }
        }
    }

    fclose(file);
}


//modul-modul utama

// Deskripsi : Fungsi untuk Alokasi memori BioskopInfo
// IS : menerima BioskopInfo X
// FS : mengembalikan address baru yang berisi alokasi memori untuk BioskopInfo
address AlokasiBioskop(BioskopInfo X) {
    BioskopInfo* info = (BioskopInfo*) malloc(sizeof(BioskopInfo));
    if (info) {
        *info = X;
        return Alokasi((infotype)info);
    }
    return NULL;
}

// Deskripsi : Prosedur untuk Dealokasi memori BioskopInfo
// IS : menerima address P yang berisi BioskopInfo
// FS : menghapus alokasi memori BioskopInfo yang ada pada address P
void DeAlokasiBioskop(address P) {
    if (P != NULL) {
        free(P->info);
        Dealokasi(P);
    }
}

// Deskripsi : Prosedur untuk menambah bioskop ke dalam kota
// IS : menerima address kota dan namaBioskop sebagai string
// FS : menambah node baru bioskop menjadi anak dari node kota dalam tree
void TambahBioskop(address kota, const char* namaBioskop) {
    if (kota == NULL) return;

    BioskopInfo bioskop;
    strcpy(bioskop.nama, namaBioskop);

    address node = AlokasiBioskop(bioskop);
    if (node == NULL) {
        printf("Gagal mengalokasikan node bioskop.\n");
        return;
    }

    AddChild(kota, node->info);
    
    printf("Bioskop '%s' berhasil ditambahkan.\n", namaBioskop);
}

// Deskripsi : Prosedur untuk menambah bioskop baru dan menyimpannya ke file
// IS : menerima address kota dan namaBioskop sebagai string
// FS : node bioskop ditambahkan ke tree sebagai anak dari node kota, lalu disimpan ke file
void TambahBioskopBaru(address kota, const char* namaBioskop) {
    TambahBioskop(kota, namaBioskop);

    BioskopInfo bioskop;
    strcpy(bioskop.nama, namaBioskop);

    KotaInfo* kInfo = (KotaInfo*)kota->info;
    SimpanBioskopKeFile(kInfo->nama, &bioskop);

    printf("Bioskop '%s' berhasil ditambahkan dan disimpan ke file.\n", namaBioskop);
}


void UbahBioskop(address node, BioskopInfo dataBaru) {
    BioskopInfo* newInfo = (BioskopInfo*) malloc(sizeof(BioskopInfo));

    if (newInfo) {
        BioskopInfo* oldInfo = (BioskopInfo*) node->info;
        char namaLama[100];
        strcpy(namaLama, oldInfo->nama);

        *newInfo = dataBaru;
        UbahNode(node, (infotype)newInfo);

        KotaInfo* kInfo = (KotaInfo*) node->pr->info;
        EditBioskopKeFile(kInfo->nama, namaLama, dataBaru.nama);
    }
    
}

// Deskripsi : Prosedur untuk menghapus bioskop dari kota
// IS : menerima address kota dan namaBioskop sebagai string
// FS : menghapus node bioskop dari tree dan juga dari file
void DeleteBioskop(address kota, const char* namaBioskop) {
    address node = SearchBioskop(kota, namaBioskop);
    if (!node) {
        printf("Bioskop tidak ditemukan.\n");
        return;
    }

    KotaInfo* kInfo = (KotaInfo*) kota->info;
    HapusBioskopKeFile(kInfo->nama, namaBioskop);

    DeleteNode(&kota, node);
}

// Deskripsi : Prosedur untuk menghapus semua bioskop dari kota
// IS : menerima address kota
// FS : menghapus semua node bioskop dari tree dan juga mengosongkan file bioskop
void DeleteAllBioskop(address kota) {
    if (kota == NULL) {
        printf("Kota tidak valid atau kosong.\n");
        return;
    }

    DeleteAllKeepRoot(kota->fs);
    KosongkanFileBioskop(kota->info);
    
}

// Deskripsi : Fungsi untuk membandingkan dua bioskop berdasarkan nama
// IS : menerima dua infotype yang berisi BioskopInfo
// FS : mengembalikan nilai negatif jika a < b, 0 jika a == b, dan positif jika a > b
int CompareBioskop(infotype a, infotype b) {
    BioskopInfo* bioskop1 = (BioskopInfo*) a;
    BioskopInfo* bioskop2 = (BioskopInfo*) b;

    return strcmp(bioskop1->nama, bioskop2->nama);
}

// Deskripsi : Fungsi untuk mencari bioskop berdasarkan nama
// IS : menerima address kota dan namaBioskop sebagai string
// FS : mengembalikan address dari node yang sesuai, atau NULL jika tidak ditemukan
address SearchBioskop(address kota, const char* namaBioskop) {
    BioskopInfo target;
    strcpy(target.nama, namaBioskop);

    return Search(kota, (infotype)&target, CompareBioskop);
}

// Deskripsi : Prosedur untuk mencetak daftar bioskop
// IS : menerima address kota dan level untuk indentasi
// FS : mencetak daftar bioskop yang ada pada kota 
void PrintBioskop(address node, int level) {
    if (IsTreeEmpty(node)) {
        printf("Tree kosong.\n");
        return;
    }
    
    printf("\nDaftar Bioskop :\n");

    PrintChildrenOnly(node, level);
}
