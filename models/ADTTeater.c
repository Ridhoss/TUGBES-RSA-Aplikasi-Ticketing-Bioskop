#include "header/ADTTeater.h"

// modul-modul operasi file

// void SimpanTeaterKeFile(const char* namaBioskop, const TeaterInfo* teater) {

// }

// int SearchTeaterFile(const char* namaBioskop, const char* namaTeater) {

// }

// void EditTeaterKeFile(const char* namaBioskop, const char* namaLama, const char* namaBaru) {

// }

// void HapusTeaterKeFile(const char* namaBioskop, const char* namaTeater) {

// }

// void KosongkanFileTeater() {

// }

// void LoadTeater(address root){

// }


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

// void TambahTeaterBaru(address bioskop, const char* namaTeater) {

// }

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

// void PrintTeater(address node, int level) {

// }