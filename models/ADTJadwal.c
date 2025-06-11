#include "header/ADTJadwal.h"



// modul utama

address AlokasiJadwal(JadwalInfo X){
    JadwalInfo* info = (JadwalInfo*) malloc(sizeof(JadwalInfo));
    if (info) {
        *info = X;
        return Alokasi((infotype)info, JADWAL);
    }

    return NULL;
}

void DeAlokasiJadwal(address P) {
    if (P != NULL) {
        free(P->info);
        Dealokasi(P);
    }
}

void TambahJadwal(address teater, JadwalInfo jadwalBaru) {
    address node = AlokasiTeater(jadwalBaru);
    if (node == NULL) {
        printf("Gagal mengalokasikan node Jadwal.\n");
        return;
    }

    AddChild(bioskop, node->info, JADWAL);
    
    printf("Jadwal '%s' berhasil ditambahkan.\n", jadwalBaru.start);
}

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
