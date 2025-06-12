#include "header/ADTJadwal.h"

// modul-modul operasi file

// Deskripsi : Prosedur untuk menyimpan data jadwal ke file
// IS : menerima pointer ke JadwalInfo
// FS : menyimpan id kota, film, teater, dan bioskop serta informasi jadwal ke dalam file "database/jadwal.txt"
void SimpanJadwalKeFile(const int* idKota, const int* idBioskop, const int* idTeater, const int* idFilm, const JadwalInfo* jadwal) {
    FILE* file = fopen("database/jadwal.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d|%d|%d|%d|%s|%s|%d\n", jadwal->id, *idKota, *idBioskop, *idTeater, jadwal->start, jadwal->end, *idFilm);
        fclose(file);
    } else {
        printf("Gagal menyimpan teater ke file.\n");
    }
}

// Deskripsi : Prosedur untuk mengambil id terakhir dari data file
// IS : membuka file "database/jadwal.txt" dalam mode baca
// FS : membaca setiap baris dari file dan mencari id paling besar
int AmbilIdJadwalTerakhir() {
    FILE* file = fopen("database/jadwal.txt", "r");
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












// modul utama

// Deskripsi : Fungsi untuk Alokasi memori JadwalInfo
// IS : menerima JadwalInfo X
// FS : mengembalikan address baru yang berisi alokasi memori untuk JadwalInfo
address AlokasiJadwal(JadwalInfo X){
    JadwalInfo* info = (JadwalInfo*) malloc(sizeof(JadwalInfo));
    if (info) {
        *info = X;
        return Alokasi((infotype)info, JADWAL);
    }

    return NULL;
}

// Deskripsi : Prosedur untuk Dealokasi memori JadwalInfo
// IS : menerima address P yang berisi JadwalInfo
// FS : menghapus alokasi memori JadwalInfo yang ada pada address P
void DeAlokasiJadwal(address P) {
    if (P != NULL) {
        free(P->info);
        Dealokasi(P);
    }
}

// Deskripsi : Prosedur untuk menambah Jadwal ke dalam teater
// IS : menerima address teater dan info Jadwal serta info film
// FS : menambah node baru Jadwal menjadi anak dari node teater dalam tree
void TambahJadwal(address teater, JadwalInfo jadwalBaru) {
    if (teater == NULL) return;

    address node = AlokasiJadwal(jadwalBaru);
    if (node == NULL) {
        printf("Gagal mengalokasikan node Jadwal.\n");
        return;
    }

    InisialisasiKursi((JadwalInfo*) node->info, teater);

    AddChild(teater, node->info, JADWAL);
    
    printf("Jadwal '%s' berhasil ditambahkan.\n", jadwalBaru.start);
}

// Deskripsi : Prosedur untuk menambah jadwal baru dan menyimpannya ke file
// IS : menerima address kota dan bioskop serta info jadwal dan info film
// FS : node jadwal ditambahkan ke tree sebagai anak dari node teater, lalu disimpan ke file
void TambahJadwalBaru(address kota, address bioskop, address teater, JadwalInfo jadwalBaru) {
    int idBaru = AmbilIdJadwalTerakhir() + 1;
    jadwalBaru.id = idBaru;

    TambahJadwal(teater, jadwalBaru);

    int idFilm = 1;

    KotaInfo* kInfo = (KotaInfo*) kota->info;
    BioskopInfo* bInfo = (BioskopInfo*) bioskop->info;
    TeaterInfo* tInfo = (TeaterInfo*) teater->info;
    SimpanJadwalKeFile(&kInfo->id, &bInfo->id, &tInfo->id, &idFilm, &jadwalBaru);

    printf("Jadwal '%s' berhasil ditambahkan dan disimpan ke file.\n", jadwalBaru.start);
}

// Deskripsi : prosedur untuk menginisialisasi array 2 dimensi
// IS : menerima jadwalInfo dan teaterinfo yang berisi jumlah kursi
// FS : array 2 dimensi terbuat dengan fix 10 kolom, dan membagi jumlah kursi dengan kolom lalu menentukan mana array yang bisa di isi dan tidak (tidak ada kursi)
void InisialisasiKursi(JadwalInfo *jadwal, address teaterAddress) {
    TeaterInfo teater = *((TeaterInfo*)(teaterAddress->info));

    int jumlahKursi = teater.jumlahKursi;
    int kolom = 10;
    int baris = (jumlahKursi + kolom - 1) / kolom;

    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            int index = i * kolom + j;
            if (index < jumlahKursi) {
                jadwal->kursi[i][j] = '0';
            } else {
                jadwal->kursi[i][j] = 'X';
            }
        }
    }
}
