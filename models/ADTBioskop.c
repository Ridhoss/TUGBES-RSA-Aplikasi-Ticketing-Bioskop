#include "header/ADTBioskop.h"

// modul-modul operasi file

// Deskripsi : Prosedur untuk menyimpan data bioskop ke file
// IS : menerima pointer ke BioskopInfo
// FS : menyimpan id bioskop dan informasi kota ke dalam file "database/bioskop.txt"
void SimpanBioskopKeFile(const int* idkota, const BioskopInfo* bioskop) {
    FILE* file = fopen("database/bioskop.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d|%d|%s|\n", bioskop->id, *idkota, bioskop->nama);
        fclose(file);
    } else {
        printf("Gagal menyimpan bioskop ke file.\n");
    }
}

// Deskripsi : fungsi untuk mencari bioskop dalam file
// IS : menerima informasi bioskop 
// FS : mengembalikan 1 jika bioskop ditemukan, 0 jika tidak ditemukan
int SearchBioskopFile(const BioskopInfo* bioskop) {
    FILE* file = fopen("database/bioskop.txt", "r");
    if (!file) return 0;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        
        int id, idKota;
        char bioskopNama[100];
        sscanf(buffer, "%d|%d|%[^|\n]", &id, &idKota, bioskopNama);
        
        if (id && idKota && bioskopNama) {
            if (id == bioskop->id) {

                fclose(file);
                return 1; 
            }
        }
    }

    fclose(file);
    return 0;
}

// Deskripsi : Prosedur untuk mengedit info bioskop dalam file
// IS : menerima info lama dan info baru
// FS : mengubah info bioskop dalam file "database/bioskop.txt"
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

        int id, idKota;
        char bioskopNama[100];
        sscanf(buffer, "%d|%d|%[^|\n]", &id, &idKota, bioskopNama);

        if (id == bioskopLama->id) {
            fprintf(temp, "%d|%d|%s|\n", id, idKota, bioskop->nama);
        } else {
            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);

    remove("database/bioskop.txt");
    rename("database/temp.txt", "database/bioskop.txt");

    printf("Bioskop '%s' berhasil diubah menjadi '%s'.\n", bioskopLama->nama, bioskop->nama);
}

// Deskripsi : Prosedur untuk menghapus bioskop dari file
// IS : menerima info bioskop
// FS : menghapus info bioskop dari file "database/bioskop.txt"
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

        int id, idKota;
        char bioskopNama[100];
        sscanf(buffer, "%d|%d|%[^|\n]", &id, &idKota, bioskopNama);

        if (id != bioskopLama->id) {
            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);

    remove("database/bioskop.txt");
    rename("database/temp.txt", "database/bioskop.txt");

    printf("Kota '%s' berhasil dihapus.\n", bioskopLama->nama);
}

// Deskripsi : Prosedur untuk mengosongkan file bioskop.txt
// IS : membuka file "database/bioskop.txt" dalam mode tulis
// FS : mengosongkan isi file
void KosongkanFileBioskop() {
    FILE* file = fopen("database/bioskop.txt", "w");
    if (file != NULL) {
        fclose(file);
        printf("File bioskop.txt berhasil dikosongkan.\n");
    } else {
        printf("Gagal mengosongkan file bioskop.txt.\n");
    }
}

// Deskripsi : Prosedur untuk menghapus semua bioskop yang ada di kota dari file bioskop.txt
// IS : menerima address kota info
// FS : menghapus semua data bioskop dari file sesuai kota
void HapusSemuaBioskopDariFileByKota(address kota) {
    KotaInfo* kInfo = (KotaInfo*)kota->info;

    List listBioskop;
    CreateList(&listBioskop);

    FILE* file = fopen("database/bioskop.txt", "r");
    if (!file) {
        printf("Gagal membuka file bioskop.txt untuk dibaca.\n");
        return;
    }

    FILE* temp = fopen("database/temp.txt", "w");
    if (!temp) {
        fclose(file);
        printf("Gagal membuka file sementara.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        int id, idKota;
        char bioskopNama[100];
        sscanf(buffer, "%d|%d|%[^|\n]", &id, &idKota, bioskopNama);

        if (idKota != kInfo->id) {

            fputs(buffer, temp);
        } else if (idKota == kInfo->id) {
            address nodeBioskop = SearchBioskopById(kota, &id);
            if (nodeBioskop != NULL) {
                InsLast(&listBioskop, (infotype)nodeBioskop);
            }
        }
    }

    fclose(file);
    fclose(temp);

    remove("database/bioskop.txt");
    rename("database/temp.txt", "database/bioskop.txt");

    addressList p = listBioskop.First;
    while (p != NULL) {
        address nodeBioskop = (address)p->info;
        HapusSemuaTeaterDariFileByBioskop(nodeBioskop);
        p = p->next;
    }

    DelAll(&listBioskop);

    printf("Semua bioskop dari kota '%s' berhasil dihapus dari file.\n", kInfo->nama);
}

// Deskripsi : Prosedur untuk memuat data bioskop dari file
// IS : membuka file "database/bioskop.txt" dalam mode baca
// FS : membaca setiap baris dari file dan menambahkannya ke tree
void LoadBioskop(address root) {
    FILE* file = fopen("database/bioskop.txt", "r");
    if (!file) {
        printf("File bioskop.txt tidak ditemukan atau gagal dibuka.\n");
        return;
    }

    BioskopInfo bioskop;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        int id, idKota;
        char bioskopNama[100];
        sscanf(buffer, "%d|%d|%[^|\n]", &id, &idKota, bioskopNama);

        if (id && idKota && bioskopNama) {
            address kota = SearchKotaById(root, &idKota);
            if (kota != NULL) {

                bioskop.id = id;
                strcpy(bioskop.nama, bioskopNama);

                TambahBioskop(kota, bioskop);
            }
        }
    }

    fclose(file);
}

// Deskripsi : Prosedur untuk mengambil id terakhir dari data file
// IS : membuka file "database/bioskop.txt" dalam mode baca
// FS : membaca setiap baris dari file dan mencari id paling besar
int AmbilIdBioskopTerakhir() {
    FILE* file = fopen("database/bioskop.txt", "r");
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
// IS : menerima address kota dan namaBioskop
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
    int idBaru = AmbilIdBioskopTerakhir() + 1;
    bioskopBaru.id = idBaru;
    
    TambahBioskop(kota, bioskopBaru);

    KotaInfo* kInfo = (KotaInfo*)kota->info;
    SimpanBioskopKeFile(&kInfo->id, &bioskopBaru);

    printf("Bioskop '%s' berhasil ditambahkan dan disimpan ke file.\n", bioskopBaru.nama);
}

// Deskripsi : Prosedur untuk mengubah info Bioskop pada node
// IS : menerima address node dan dataBaru sebagai BioskopInfo
// FS : mengubah info Bioskop pada node dan memperbarui file
void UbahBioskop(address node, BioskopInfo dataBaru) {
    BioskopInfo* oldInfo = (BioskopInfo*) node->info;
    BioskopInfo* newInfo = (BioskopInfo*) malloc(sizeof(BioskopInfo));

    if (!newInfo) return;

    dataBaru.id = oldInfo->id;

    *newInfo = dataBaru;
    UbahNode(node, (infotype)newInfo);

    EditBioskopKeFile(newInfo, oldInfo);

    printf("Informasi bioskop berhasil diubah.\n");
}

// Deskripsi : Prosedur untuk menghapus bioskop dari kota
// IS : menerima address bioskop
// FS : menghapus node bioskop dari tree dan juga dari file
void DeleteBioskop(address bioskop) {
    if (bioskop == NULL) return;

    BioskopInfo* oldInfo = (BioskopInfo*) bioskop->info;

    BioskopInfo bioskopLama;
    bioskopLama.id = oldInfo->id;
    strcpy(bioskopLama.nama, oldInfo->nama);

    address nodeKota = bioskop->pr;

    if (nodeKota) {
        HapusBioskopKeFile(&bioskopLama);

        DeleteNode(&nodeKota, bioskop);

        printf("Bioskop '%s' berhasil dihapus.\n", bioskopLama.nama);
    }
}

// Deskripsi : Prosedur untuk menghapus semua bioskop dari kota
// IS : menerima address kota
// FS : menghapus semua node bioskop dari tree dan juga mengosongkan file bioskop
void DeleteAllBioskop(address kota) {
    if (IsTreeEmpty(kota)) {
        printf("Kota tidak valid atau kosong.\n");
        return;
    }

    HapusSemuaBioskopDariFileByKota(kota);
    DeleteAllKeepRoot(kota);
}

// Deskripsi : Fungsi untuk membandingkan dua bioskop berdasarkan nama
// IS : menerima dua infotype yang berisi BioskopInfo
// FS : mengembalikan nilai 0 jika bioskop sama, dan 1 jika bioskop berbeda
int CompareBioskop(infotype a, infotype b) {
    BioskopInfo* bioskop1 = (BioskopInfo*) a;
    BioskopInfo* bioskop2 = (BioskopInfo*) b;

    return strcmp(bioskop1->nama, bioskop2->nama);
}

// Deskripsi : Fungsi untuk membandingkan dua Bioskop berdasarkan id
// IS : menerima dua infotype yang berisi BioskopInfo
// FS : mengembalikan nilai 0 jika Bioskop sama, dan 1 jika Bioskop berbeda
int CompareBioskopId(infotype a, infotype b) {
    BioskopInfo* bioskop1 = (BioskopInfo*) a;
    BioskopInfo* bioskop2 = (BioskopInfo*) b;

    return bioskop1->id - bioskop2->id;
}

// Deskripsi : Fungsi untuk mencari bioskop berdasarkan nama
// IS : menerima address kota dan namaBioskop sebagai string
// FS : mengembalikan address dari node yang sesuai, atau NULL jika tidak ditemukan
address SearchBioskopByName(address kota, const char* namaBioskop) {
    BioskopInfo target;
    strcpy(target.nama, namaBioskop);

    return Search(kota, (infotype)&target, CompareBioskop, BIOSKOP);
}

// Deskripsi : Fungsi untuk mencari Bioskop berdasarkan id
// IS : menerima address root dan idBioskop
// FS : mengembalikan address dari node yang sesuai, atau NULL jika tidak ditemukan
address SearchBioskopById(address root, const int* idBioskop) {
    BioskopInfo target;
    target.id = *idBioskop;

    return Search(root, (infotype)&target, CompareBioskopId, BIOSKOP);
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




// modul tambahan


void AmbilSemuaBioskopKeList(address root, List* L) {
    CreateList(L);

    if (root == NULL || root->fs == NULL) return;

    address nodeKota = root->fs;
    while (nodeKota != NULL) {
        address nodeBioskop = nodeKota->fs;
        while (nodeBioskop != NULL) {
            BioskopInfo* bioskop = (BioskopInfo*) nodeBioskop->info;

            BioskopInfo* salinan = (BioskopInfo*) malloc(sizeof(BioskopInfo));
            *salinan = *bioskop;

            InsLast(L, (infotype)salinan);

            nodeBioskop = nodeBioskop->nb;
        }

        nodeKota = nodeKota->nb;
    }
}
