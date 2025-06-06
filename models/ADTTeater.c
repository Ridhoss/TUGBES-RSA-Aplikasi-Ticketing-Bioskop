#include "header/ADTTeater.h"

// modul-modul operasi file

void SimpanTeaterKeFile(const char* namaKota, const char* namaBioskop, const TeaterInfo* teater) {
    FILE* file = fopen("database/teater.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s|%s|%s|%d\n", namaKota, namaBioskop, teater->nama, teater->jumlahKursi);
        fclose(file);
    } else {
        printf("Gagal menyimpan teater ke file.\n");
    }
}

// int SearchTeaterFile(const char* namaBioskop, const char* namaTeater) {

// }

// void EditTeaterKeFile(const char* namaBioskop, const char* namaLama, const char* namaBaru) {

// }

// void HapusTeaterKeFile(const char* namaBioskop, const char* namaTeater) {

// }

// void KosongkanFileTeater() {

// }

void LoadTeater(address root) {
    FILE* file = fopen("database/teater.txt", "r");
    if (!file) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char* kotaNama = strtok(buffer, "|");
        char* bioskopNama = strtok(NULL, "|");
        char* teaterNama = strtok(NULL, "|");
        char* jumlahKursiStr = strtok(NULL, "|");
        int jumlahKursi = atoi(jumlahKursiStr);

        if (kotaNama && bioskopNama && teaterNama && jumlahKursi) {
            address kota = SearchKota(root, kotaNama);
            if (kota != NULL) {
              address bioskop = SearchBioskop(kota, bioskopNama);
              if (bioskop != NULL) {
                TambahTeater(bioskop, teaterNama, jumlahKursi);
              }
            }
        }
    }

    fclose(file);
}


//modul-modul utama

// Deskripsi : Fungsi untuk Alokasi memori TeaterInfo
// IS : menerima TeaterInfo X
// FS : mengembalikan address baru yang berisi alokasi memori untuk TeaterInfo
address AlokasiTeater(TeaterInfo X) {
    TeaterInfo* info = (TeaterInfo*) malloc(sizeof(TeaterInfo));
    if (info) {
        *info = X;
        return Alokasi((infotype)info);
    }

    return NULL;
}

// Deskripsi : Prosedur untuk Dealokasi memori TeaterInfo
// IS : menerima address P yang berisi TeaterInfo
// FS : menghapus alokasi memori TeaterInfo yang ada pada address P
void DeAlokasiTeater(address P){
    if (P != NULL) {
        free(P->info);
        Dealokasi(P);
    }
}

void TambahTeater(address bioskop, const char* namaTeater, int jumlahKursi) {
    if (bioskop == NULL) return;

    TeaterInfo Teater;
    strcpy(Teater.nama, namaTeater);
    Teater.jumlahKursi = jumlahKursi;

    address node = AlokasiTeater(Teater);
    if (node == NULL) {
        printf("Gagal mengalokasikan node Teater.\n");
        return;
    }

    AddChild(bioskop, node->info);
    
    printf("Teater '%s' berhasil ditambahkan.\n", namaTeater);
}

void TambahTeaterBaru(address kota, address bioskop, const char* namaTeater, int jumlahKursi) {
    TambahTeater(bioskop, namaTeater, jumlahKursi);

    TeaterInfo teater;
    strcpy(teater.nama, namaTeater);
    teater.jumlahKursi = jumlahKursi;

    KotaInfo* kInfo = (KotaInfo*) kota->info;
    BioskopInfo* bInfo = (BioskopInfo*) bioskop->info;
    SimpanTeaterKeFile(kInfo->nama, bInfo->nama, &teater);

    printf("Teater '%s' berhasil ditambahkan dan disimpan ke file.\n", namaTeater);
}

// void UbahTeater(address node, TeaterInfo dataBaru) {

// }

// void DeleteTeater(address bioskop, const char* namaTeater) {
  
// }

// void DeleteAllTeater(address bioskop) {

// }

// int CompareTeater(infotype a, infotype b) {

// }

// address SearchTeater(address bioskop, const char* namaTeater) {

// }

void PrintTeater(address node, int level) {
    if (IsTreeEmpty(node)) {
        printf("Tree kosong.\n");
        return;
    }
    
    printf("\nDaftar Teater :\n");

    PrintChildrenOnly(node, level);
}