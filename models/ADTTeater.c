#include "header/ADTTeater.h"

// modul-modul operasi file

void SimpanTeaterKeFile(const char* namaKota, const char* namaBioskop, const TeaterInfo* teater) {
    FILE* file = fopen("database/teater.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s|%s|%s|%d|%d\n", namaKota, namaBioskop, teater->nama, teater->jumlahKursi, teater->harga);
        fclose(file);
    } else {
        printf("Gagal menyimpan teater ke file.\n");
    }
}

int SearchTeaterFile(const char* namaKota, const char* namaBioskop, const TeaterInfo* teater) {
    FILE* file = fopen("database/teater.txt", "r");
    if (!file) return 0;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char* kotaNama = strtok(buffer, "|");
        char* bioskopNama = strtok(NULL, "|");
        char* teaterNama = strtok(NULL, "|");
        char* jumlahKursiStr = strtok(NULL, "|");
        char* hargaTeaterStr = strtok(NULL, "|");
        
        if (kotaNama && bioskopNama && teaterNama && jumlahKursiStr && hargaTeaterStr) {
            int jumlahKursi = atoi(jumlahKursiStr);
            int hargaTeater = atoi(hargaTeaterStr);

            if (strcmp(kotaNama, namaKota) == 0 &&
                strcmp(bioskopNama, namaBioskop) == 0 &&
                strcmp(teaterNama, teater->nama) == 0 &&
                jumlahKursi == teater->jumlahKursi &&
                hargaTeater == teater->harga) {

                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);
    return 0;
}

void EditTeaterKeFile(const char* namaKota, const char* namaBioskop, const TeaterInfo* teater, const TeaterInfo* teaterLama) {
    if (!SearchTeaterFile(namaKota, namaBioskop, teaterLama)) {
        printf("Teater '%s' tidak ditemukan. Tidak dapat melakukan edit.\n", teaterLama->nama);
        return;
    }

    FILE* file = fopen("database/teater.txt", "r");
    FILE* temp = fopen("database/temp.txt", "w");
    if (!file || !temp) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char kotaNama[100], bioskopNama[100], teaterNama[100];
        int jmlKursi, hargaTeater;
        sscanf(buffer, "%[^|]|%[^|]|%[^|]|%d|%d", kotaNama, bioskopNama, teaterNama, &jmlKursi, &hargaTeater);

        if (strcmp(kotaNama, namaKota) == 0 &&
            strcmp(bioskopNama, namaBioskop) == 0 &&
            strcmp(teaterNama, teaterLama->nama) == 0 &&
            jmlKursi == teaterLama->jumlahKursi &&
            hargaTeater == teaterLama->harga) {

            fprintf(temp, "%s|%s|%s|%d|%d\n", namaKota, namaBioskop, teater->nama, teater->jumlahKursi, teater->harga);
        } else {
            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);
    remove("database/teater.txt");
    rename("database/temp.txt", "database/teater.txt");
}

void HapusTeaterKeFile(const char* namaKota, const char* namaBioskop, const TeaterInfo* teaterLama) {
    if (!SearchTeaterFile(namaKota, namaBioskop, teaterLama)) {
        printf("Teater '%s' tidak ditemukan. Tidak dapat melakukan edit.\n", teaterLama->nama);
        return;
    }

    FILE* file = fopen("database/teater.txt", "r");
    FILE* temp = fopen("database/temp.txt", "w");
    if (!file || !temp) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char kotaNama[100], bioskopNama[100], teaterNama[100];
        int jmlKursi, hargaTeater;
        sscanf(buffer, "%[^|]|%[^|]|%[^|]|%d|%d", kotaNama, bioskopNama, teaterNama, &jmlKursi, &hargaTeater);

        if (!(strcmp(kotaNama, namaKota) == 0 &&
            strcmp(bioskopNama, namaBioskop) == 0 &&
            strcmp(teaterNama, teaterLama->nama) == 0 &&
            jmlKursi == teaterLama->jumlahKursi &&
            hargaTeater == teaterLama->harga)) {

            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);
    remove("database/teater.txt");
    rename("database/temp.txt", "database/teater.txt");
}

void KosongkanFileTeater() {
    FILE* file = fopen("database/teater.txt", "w");
    if (file != NULL) {
        fclose(file);
        printf("File teater.txt berhasil dikosongkan.\n");
    } else {
        printf("Gagal mengosongkan file teater.txt.\n");
    }
}

void LoadTeater(address root) {
    FILE* file = fopen("database/teater.txt", "r");
    if (!file) return;

    TeaterInfo teater;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char* kotaNama = strtok(buffer, "|");
        char* bioskopNama = strtok(NULL, "|");
        char* teaterNama = strtok(NULL, "|");
        char* jumlahKursiStr = strtok(NULL, "|");
        char* hargaTeaterStr = strtok(NULL, "|");
        int jumlahKursi = atoi(jumlahKursiStr);
        int hargaTeater = atoi(hargaTeaterStr);

        if (kotaNama && bioskopNama && teaterNama && jumlahKursi) {
            address kota = SearchKotaByName(root, kotaNama);
            if (kota != NULL) {
                address bioskop = SearchBioskopByName(kota, bioskopNama);
                if (bioskop != NULL) {

                    strcpy(teater.nama, teaterNama);
                    teater.jumlahKursi = jumlahKursi;
                    teater.harga = hargaTeater;

                    TambahTeater(bioskop, teater);
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

void TambahTeater(address bioskop, TeaterInfo teaterBaru){

    address node = AlokasiTeater(teaterBaru);
    if (node == NULL) {
        printf("Gagal mengalokasikan node Teater.\n");
        return;
    }

    AddChild(bioskop, node->info, TEATER);
    
    printf("Teater '%s' berhasil ditambahkan.\n", teaterBaru.nama);
}

void TambahTeaterBaru(address kota, address bioskop, TeaterInfo teaterBaru) {
    TambahTeater(bioskop, teaterBaru);

    KotaInfo* kInfo = (KotaInfo*) kota->info;
    BioskopInfo* bInfo = (BioskopInfo*) bioskop->info;
    SimpanTeaterKeFile(kInfo->nama, bInfo->nama, &teaterBaru);

    printf("Teater '%s' berhasil ditambahkan dan disimpan ke file.\n", teaterBaru.nama);
}

void UbahTeater(address node, TeaterInfo dataBaru) {
    TeaterInfo* oldInfo = (TeaterInfo*) node->info;
    TeaterInfo* newInfo = (TeaterInfo*) malloc(sizeof(TeaterInfo));

    if (!newInfo) return;

    *newInfo = dataBaru;
    UbahNode(node, (infotype)newInfo);

    TeaterInfo teaterLama;
    strcpy(teaterLama.nama, oldInfo->nama);
    teaterLama.jumlahKursi = oldInfo->jumlahKursi;
    teaterLama.harga = oldInfo->harga;

    address nodeBioskop = node->pr;
    address nodeKota = nodeBioskop ? nodeBioskop->pr : NULL;

    if (nodeBioskop && nodeKota) {
        BioskopInfo* bInfo = (BioskopInfo*) nodeBioskop->info;
        KotaInfo* kInfo = (KotaInfo*) nodeKota->info;

        EditTeaterKeFile(kInfo->nama, bInfo->nama, newInfo, &teaterLama);
    }

    printf("Teater '%s' berhasil diubah dan disimpan ke file.\n", teaterLama.nama);
}

void DeleteTeater(address teater) {
    if (teater == NULL) return;

    TeaterInfo* oldInfo = (TeaterInfo*) teater->info;

    TeaterInfo teaterLama;
    strcpy(teaterLama.nama, oldInfo->nama);
    teaterLama.jumlahKursi = oldInfo->jumlahKursi;
    teaterLama.harga = oldInfo->harga;

    address nodeBioskop = teater->pr;
    address nodeKota = nodeBioskop ? nodeBioskop->pr : NULL;

    if (nodeBioskop && nodeKota) {
        BioskopInfo* bInfo = (BioskopInfo*) nodeBioskop->info;
        KotaInfo* kInfo = (KotaInfo*) nodeKota->info;

        HapusTeaterKeFile(kInfo->nama, bInfo->nama, &teaterLama);
    }

    DeleteNode(&nodeBioskop, teater);

    printf("Teater '%s' berhasil dihapus.\n", teaterLama.nama);
}

void DeleteAllTeater(address bioskop) {
    if (IsTreeEmpty(bioskop)) {
        printf("Biioskop tidak valid atau kosong.\n");
        return;
    }

    DeleteAllKeepRoot(bioskop);
    KosongkanFileTeater();
}

int CompareTeater(infotype a, infotype b) {
    TeaterInfo* teater1 = (TeaterInfo*) a;
    TeaterInfo* teater2 = (TeaterInfo*) b;

    return strcmp(teater1->nama, teater2->nama);
}

address SearchTeater(address bioskop, const char* namaTeater) {
    TeaterInfo target;
    strcpy(target.nama, namaTeater);

    return Search(bioskop, (infotype)&target, CompareTeater, TEATER);
}

void PrintTeater(address node, int level) {
    if (IsTreeEmpty(node)) {
        printf("Tree kosong.\n");
        return;
    }
    
    printf("\nDaftar Teater :\n");

    PrintChildrenOnly(node, level);
}