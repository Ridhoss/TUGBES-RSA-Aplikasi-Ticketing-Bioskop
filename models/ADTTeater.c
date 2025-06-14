#include "header/ADTTeater.h"

// modul-modul operasi file

// Deskripsi : Prosedur untuk menyimpan data Teater ke file
// IS : menerima pointer ke TeaterInfo
// FS : menyimpan id kota dan bioskop serta informasi teater ke dalam file "database/teater.txt"
void SimpanTeaterKeFile(const int* idKota, const int* idBioskop, const TeaterInfo* teater) {
    FILE* file = fopen("database/teater.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d|%d|%d|%s|%d|%d|\n", teater->id, *idKota, *idBioskop, teater->nama, teater->jumlahKursi, teater->harga);
        fclose(file);
    } else {
        printf("Gagal menyimpan teater ke file.\n");
    }
}

// Deskripsi : fungsi untuk mencari teater dalam file
// IS : menerima informasi teater  
// FS : mengembalikan 1 jika teater ditemukan, 0 jika tidak ditemukan
int SearchTeaterFile(const TeaterInfo* teater) {
    FILE* file = fopen("database/teater.txt", "r");
    if (!file) return 0;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        int id, idKota, idBioskop, jmlKursi, hargaTeater;
        char teaterNama[100];
        sscanf(buffer, "%d|%d|%d|%[^|]|%d|%d|", &id, &idKota, &idBioskop, teaterNama, &jmlKursi, &hargaTeater);
        
        if (id && idKota && idBioskop && teaterNama && jmlKursi && hargaTeater) {
            if (id == teater->id) {

                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

// Deskripsi : Prosedur untuk mengedit info teater dalam file
// IS : menerima info lama dan info baru
// FS : mengubah info teater dalam file "database/teater.txt"
void EditTeaterKeFile(const TeaterInfo* teater, const TeaterInfo* teaterLama) {
    if (!SearchTeaterFile(teaterLama)) {
        printf("Teater '%s' tidak ditemukan. Tidak dapat melakukan edit.\n", teaterLama->nama);
        return;
    }

    FILE* file = fopen("database/teater.txt", "r");
    FILE* temp = fopen("database/temp.txt", "w");
    if (!file || !temp) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        int id, idKota, idBioskop, jmlKursi, hargaTeater;
        char teaterNama[100];
        sscanf(buffer, "%d|%d|%d|%[^|]|%d|%d|", &id, &idKota, &idBioskop, teaterNama, &jmlKursi, &hargaTeater);

        if (id == teaterLama->id) {

            fprintf(temp, "%d|%d|%d|%s|%d|%d|\n", id, idKota, idBioskop, teater->nama, teater->jumlahKursi, teater->harga);
        } else {
            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);

    remove("database/teater.txt");
    rename("database/temp.txt", "database/teater.txt");

    printf("Teater '%s' berhasil diubah menjadi '%s'.\n", teaterLama->nama, teater->nama);
}

// Deskripsi : Prosedur untuk menghapus teater dari file
// IS : menerima info teater
// FS : menghapus info teater dari file "database/teater.txt"
void HapusTeaterKeFile(const TeaterInfo* teaterLama) {
    if (!SearchTeaterFile(teaterLama)) {
        printf("Teater '%s' tidak ditemukan. Tidak dapat melakukan edit.\n", teaterLama->nama);
        return;
    }

    FILE* file = fopen("database/teater.txt", "r");
    FILE* temp = fopen("database/temp.txt", "w");
    if (!file || !temp) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        int id, idKota, idBioskop, jmlKursi, hargaTeater;
        char teaterNama[100];
        sscanf(buffer, "%d|%d|%d|%[^|]|%d|%d|", &id, &idKota, &idBioskop, teaterNama, &jmlKursi, &hargaTeater);

        if (id != teaterLama->id) {

            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);

    remove("database/teater.txt");
    rename("database/temp.txt", "database/teater.txt");

    printf("Teater '%s' berhasil dihapus.\n", teaterLama->nama);
}

// Deskripsi : Prosedur untuk mengosongkan file teater.txt
// IS : membuka file "database/teater.txt" dalam mode tulis
// FS : mengosongkan isi file
void KosongkanFileTeater() {
    FILE* file = fopen("database/teater.txt", "w");
    if (file != NULL) {
        fclose(file);
        printf("File teater.txt berhasil dikosongkan.\n");
    } else {
        printf("Gagal mengosongkan file teater.txt.\n");
    }
}

// Deskripsi : Prosedur untuk memuat data teater dari file
// IS : membuka file "database/teater.txt" dalam mode baca
// FS : membaca setiap baris dari file dan menambahkannya ke tree
void LoadTeater(address root) {
    FILE* file = fopen("database/teater.txt", "r");
    if (!file) {
        printf("File teater.txt tidak ditemukan atau gagal dibuka.\n");
        return;
    }

    TeaterInfo teater;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        int id, idKota, idBioskop, jmlKursi, hargaTeater;
        char teaterNama[100];
        sscanf(buffer, "%d|%d|%d|%[^|]|%d|%d|", &id, &idKota, &idBioskop, teaterNama, &jmlKursi, &hargaTeater);

        if (id && idKota && idBioskop && teaterNama && jmlKursi && hargaTeater) {

            address kota = SearchKotaById(root, &idKota);
            if (kota != NULL) {
                address bioskop = SearchBioskopById(kota, &idBioskop);
                if (bioskop != NULL) {

                    teater.id = id;
                    strcpy(teater.nama, teaterNama);
                    teater.jumlahKursi = jmlKursi;
                    teater.harga = hargaTeater;

                    TambahTeater(bioskop, teater);
                }
            }
        }
    }

    fclose(file);
}

// Deskripsi : Prosedur untuk mengambil id terakhir dari data file
// IS : membuka file "database/teater.txt" dalam mode baca
// FS : membaca setiap baris dari file dan mencari id paling besar
int AmbilIdTeaterTerakhir() {
    FILE* file = fopen("database/teater.txt", "r");
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

// Deskripsi : Fungsi untuk Alokasi memori TeaterInfo
// IS : menerima TeaterInfo X
// FS : mengembalikan address baru yang berisi alokasi memori untuk TeaterInfo
address AlokasiTeater(TeaterInfo X) {
    TeaterInfo* info = (TeaterInfo*) malloc(sizeof(TeaterInfo));
    if (info) {
        *info = X;
        return Alokasi((infotype)info, TEATER);
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

// Deskripsi : Prosedur untuk menambah Teater ke dalam bioskop
// IS : menerima address bioskop dan info teater
// FS : menambah node baru Teater menjadi anak dari node bioskop dalam tree
void TambahTeater(address bioskop, TeaterInfo teaterBaru){
    if (bioskop == NULL) return;

    address node = AlokasiTeater(teaterBaru);
    if (node == NULL) {
        printf("Gagal mengalokasikan node Teater.\n");
        return;
    }

    AddChild(bioskop, node->info, TEATER);
    
    printf("Teater '%s' berhasil ditambahkan.\n", teaterBaru.nama);
}

// Deskripsi : Prosedur untuk menambah teater baru dan menyimpannya ke file
// IS : menerima address kota dan bioskop serta info teater
// FS : node teater ditambahkan ke tree sebagai anak dari node bioskop, lalu disimpan ke file
void TambahTeaterBaru(address kota, address bioskop, TeaterInfo teaterBaru) {
    int idBaru = AmbilIdTeaterTerakhir() + 1;
    teaterBaru.id = idBaru;

    TambahTeater(bioskop, teaterBaru);

    KotaInfo* kInfo = (KotaInfo*) kota->info;
    BioskopInfo* bInfo = (BioskopInfo*) bioskop->info;
    SimpanTeaterKeFile(&kInfo->id, &bInfo->id, &teaterBaru);

    printf("Teater '%s' berhasil ditambahkan dan disimpan ke file.\n", teaterBaru.nama);
}

// Deskripsi : Prosedur untuk mengubah info teater pada node
// IS : menerima address node dan dataBaru sebagai TeaterInfo
// FS : mengubah info teater pada node dan memperbarui file
void UbahTeater(address node, TeaterInfo dataBaru) {
    TeaterInfo* oldInfo = (TeaterInfo*) node->info;
    TeaterInfo* newInfo = (TeaterInfo*) malloc(sizeof(TeaterInfo));

    if (!newInfo) return;

    dataBaru.id = oldInfo->id;

    *newInfo = dataBaru;
    UbahNode(node, (infotype)newInfo);

    EditTeaterKeFile(newInfo, oldInfo);

    printf("Teater '%s' berhasil diubah dan disimpan ke file.\n", oldInfo->nama);
}

// Deskripsi : Prosedur untuk menghapus Teater dari bioskop
// IS : menerima address teater
// FS : menghapus node teater dari tree dan juga dari file
void DeleteTeater(address teater) {
    if (teater == NULL) return;

    TeaterInfo* oldInfo = (TeaterInfo*) teater->info;

    TeaterInfo teaterLama;
    teaterLama.id = oldInfo->id;
    strcpy(teaterLama.nama, oldInfo->nama);
    teaterLama.jumlahKursi = oldInfo->jumlahKursi;
    teaterLama.harga = oldInfo->harga;

    address nodeBioskop = teater->pr;

    if (nodeBioskop) {
        HapusTeaterKeFile(&teaterLama);

        DeleteNode(&nodeBioskop, teater);

        printf("Teater '%s' berhasil dihapus.\n", teaterLama.nama);
    }
}

// Deskripsi : Prosedur untuk menghapus semua teater dari bioskop
// IS : menerima address bioskop
// FS : menghapus semua node teater dari tree dan juga mengosongkan file teater
void DeleteAllTeater(address bioskop) {
    if (IsTreeEmpty(bioskop)) {
        printf("Biioskop tidak valid atau kosong.\n");
        return;
    }

    DeleteAllKeepRoot(bioskop);
    KosongkanFileTeater();
}

// Deskripsi : Fungsi untuk membandingkan dua Teater berdasarkan nama
// IS : menerima dua infotype yang berisi TeaterInfo
// FS : mengembalikan nilai 0 jika teater sama, dan 1 jika teater berbeda
int CompareTeater(infotype a, infotype b) {
    TeaterInfo* teater1 = (TeaterInfo*) a;
    TeaterInfo* teater2 = (TeaterInfo*) b;

    return strcmp(teater1->nama, teater2->nama);
}

// Deskripsi : Fungsi untuk membandingkan dua Teater berdasarkan id
// IS : menerima dua infotype yang berisi TeaterInfo
// FS : mengembalikan nilai 0 jika Teater sama, dan 1 jika Teater berbeda
int CompareTeaterId(infotype a, infotype b) {
    TeaterInfo* teater1 = (TeaterInfo*) a;
    TeaterInfo* teater2 = (TeaterInfo*) b;

    return teater1->id - teater2->id;
}

// Deskripsi : Fungsi untuk mencari Teater berdasarkan nama
// IS : menerima address bioskop dan namaTeater sebagai string
// FS : mengembalikan address dari node yang sesuai, atau NULL jika tidak ditemukan
address SearchTeaterByName(address bioskop, const char* namaTeater) {
    TeaterInfo target;
    strcpy(target.nama, namaTeater);

    return Search(bioskop, (infotype)&target, CompareTeater, TEATER);
}

// Deskripsi : Fungsi untuk mencari Teater berdasarkan id
// IS : menerima address bioskop dan namaTeater sebagai string
// FS : mengembalikan address dari node yang sesuai, atau NULL jika tidak ditemukan
address SearchTeaterById(address bioskop, const int* idTeater) {
    TeaterInfo target;
    target.id = *idTeater;

    return Search(bioskop, (infotype)&target, CompareTeaterId, TEATER);
}

// Deskripsi : Prosedur untuk mencetak daftar teater
// IS : menerima address bioskop dan level untuk indentasi
// FS : mencetak daftar teater yang ada pada bioskop 
void PrintTeater(address node, int level) {
    if (IsTreeEmpty(node)) {
        printf("Tree kosong.\n");
        return;
    }
    
    printf("\nDaftar Teater :\n");

    PrintChildrenOnly(node, level);
}