#include "header/ADTBioskop.h"

// modul-modul operasi file

// Deskripsi : Prosedur untuk menyimpan data bioskop ke file
// IS : menerima pointer ke BioskopInfo
// FS : menyimpan nama bioskop dan kota ke dalam file "database/bioskop.txt"
void SimpanBioskopKeFile(const int* idkota, const BioskopInfo* bioskop) {
    FILE* file = fopen("database/bioskop.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d|%d|%s\n", bioskop->id, idkota, bioskop->nama);
        fclose(file);
    } else {
        printf("Gagal menyimpan bioskop ke file.\n");
    }
}

int SearchBioskopFile(const BioskopInfo* bioskop) {
    FILE* file = fopen("database/bioskop.txt", "r");
    if (!file) return 0;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        
        char* idStr = strtok(buffer, "|");
        char* idKotaStr = strtok(NULL, "|");
        char* bioskopNama = strtok(NULL, "|");
        
        if (idStr && idKotaStr && bioskopNama) {

            int id = atoi(idStr);

            if (id == bioskop->id) {

                fclose(file);
                return 1; 
            }
        }
    }
    fclose(file);
    return 0;
}

void EditBioskopKeFile(const BioskopInfo* bioskop, const BioskopInfo* bioskopLama) {
    if (!SearchBioskopFile(bioskopLama)) {
        printf("Bioskop '%s' tidak ditemukan. Tidak dapat melakukan edit.\n", bioskopLama->nama);
        return;
    }

    FILE* file = fopen("database/bioskop.txt", "r");
    FILE* temp = fopen("database/temp.txt", "w");
    if (!file || !temp) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char bioskopNama[100];
        int id, idKota;
        sscanf(buffer, "%[^|]|%[^|]|%[^\n]", id, idKota, bioskopNama);

        if (id == bioskopLama->id) {

            fprintf(temp, "%d|%d|%s\n", id, idKota, bioskop->nama);
        } else {

            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);
    remove("database/bioskop.txt");
    rename("database/temp.txt", "database/bioskop.txt");
}

void HapusBioskopKeFile(const BioskopInfo* bioskopLama) {
    if (!SearchBioskopFile(bioskopLama)) {
        printf("Bioskop '%s' tidak ditemukan. Tidak dapat melakukan edit.\n", bioskopLama->nama);
        return;
    }
    
    FILE* file = fopen("database/bioskop.txt", "r");
    FILE* temp = fopen("database/temp.txt", "w");
    if (!file || !temp) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char bioskopNama[100];
        int id, idKota;
        sscanf(buffer, "%[^|]|%[^|]|%[^\n]", id, idKota, bioskopNama);

        if (id != bioskopLama->id) {

            fprintf(temp, "%s\n", buffer);
        }
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
        printf("File bioskop.txt berhasil dikosongkan.\n");
    } else {
        printf("Gagal mengosongkan file bioskop.txt.\n");
    }
}

void LoadBioskop(address root) {
    FILE* file = fopen("database/bioskop.txt", "r");
    if (!file) return;

    BioskopInfo bioskop;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char* idStr = strtok(buffer, "|");
        char* idKotaStr = strtok(NULL, "|");
        char* bioskopNama = strtok(NULL, "|");

        if (idStr && idKotaStr && bioskopNama) {
            int id = atoi(idStr);
            int idKota = atoi(idKotaStr);

            address kota = SearchKotaById(root, &idKota);
            if (kota != NULL) {

                strcpy(bioskop.nama, bioskopNama);

                TambahBioskop(kota, bioskop);
            } else {
                printf("dasdasdas\n");
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
        return Alokasi((infotype)info, BIOSKOP);
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
void TambahBioskop(address kota, BioskopInfo bioskopBaru) {
    if (kota == NULL) return;

    address node = AlokasiBioskop(bioskopBaru);
    if (node == NULL) {
        printf("Gagal mengalokasikan node bioskop.\n");
        return;
    }

    AddChild(kota, node->info, BIOSKOP);
    
    printf("Bioskop '%s' berhasil ditambahkan.\n", bioskopBaru.nama);
}

// Deskripsi : Prosedur untuk menambah bioskop baru dan menyimpannya ke file
// IS : menerima address kota dan namaBioskop sebagai string
// FS : node bioskop ditambahkan ke tree sebagai anak dari node kota, lalu disimpan ke file
void TambahBioskopBaru(address kota, BioskopInfo bioskopBaru) {
    TambahBioskop(kota, bioskopBaru);

    KotaInfo* kInfo = (KotaInfo*)kota->info;
    SimpanBioskopKeFile(&kInfo->id, &bioskopBaru);

    printf("Bioskop '%s' berhasil ditambahkan dan disimpan ke file.\n", bioskopBaru.nama);
}


void UbahBioskop(address node, BioskopInfo dataBaru) {
    BioskopInfo* oldInfo = (BioskopInfo*) node->info;
    BioskopInfo* newInfo = (BioskopInfo*) malloc(sizeof(BioskopInfo));

   if (!newInfo) return;

    *newInfo = dataBaru;
    UbahNode(node, (infotype)newInfo);

    BioskopInfo bioskopLama;
    strcpy(bioskopLama.nama, oldInfo->nama);

    address nodeKota = node->pr;

    if (nodeKota) {
        KotaInfo* kInfo = (KotaInfo*) nodeKota->info;

        EditBioskopKeFile(newInfo, &bioskopLama);
    }

    printf("Informasi bioskop berhasil diubah.\n");
}

// Deskripsi : Prosedur untuk menghapus bioskop dari kota
// IS : menerima address kota dan namaBioskop sebagai string
// FS : menghapus node bioskop dari tree dan juga dari file
void DeleteBioskop(address bioskop) {
    if (bioskop == NULL) return;

    BioskopInfo* oldInfo = (BioskopInfo*) bioskop->info;

    BioskopInfo bioskopLama;
    strcpy(bioskopLama.nama, oldInfo->nama);

    address nodeKota = bioskop->pr;

    if (nodeKota) {
        KotaInfo* kInfo = (KotaInfo*) nodeKota->info;
        HapusBioskopKeFile(&bioskopLama);
    }

    DeleteNode(&nodeKota, bioskop);

    printf("Bioskop '%s' berhasil dihapus.\n", bioskopLama.nama);
}

// Deskripsi : Prosedur untuk menghapus semua bioskop dari kota
// IS : menerima address kota
// FS : menghapus semua node bioskop dari tree dan juga mengosongkan file bioskop
void DeleteAllBioskop(address kota) {
   if (IsTreeEmpty(kota)) {
        printf("Kota tidak valid atau kosong.\n");
        return;
    }

    DeleteAllKeepRoot(kota);
    KosongkanFileBioskop(); 
   
   
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

    return Search(kota, (infotype)&target, CompareBioskop, BIOSKOP);
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
