#include "header/ADTFilm.h"
#include "header/ADTList.h"
#include "header/ADTAkun.h"
#include "header/ADTJadwal.h"
#include "header/ADTTeater.h"
#include "header/ADTBioskop.h"
#include "header/ADTTree.h"
#include "../library/date.h"

const char *films = "database/film.txt";

FilmInfo* alokasiFilm(FilmInfo data) {
    FilmInfo* f = (FilmInfo*)malloc(sizeof(FilmInfo));
    if (f != NULL) {
        *f = data;
    }
    return f;
}

void dealokasiFilm(FilmInfo* f) {
    free(f);
}

void loadFilm(List* L, const char* filename) {
    printf("Trying to open: %s\n", filename);
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Gagal membuka file");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        FilmInfo data;
        buffer[strcspn(buffer, "\n")] = 0;

        if (sscanf(buffer, "%d|%99[^|]|%99[^|]|%99[^|]|%d|%d",
                   &data.idFilm,
                   data.judul,
                   data.produser,
                   data.deskripsi,
                   &data.durasi.jam,
                   &data.durasi.menit) == 6) {
            
            FilmInfo* filmPtr = alokasiFilm(data);
            if (filmPtr) {
                InsLast(L, filmPtr);
            } else {
                printf(" → Gagal alokasi memori untuk film ID %d\n", data.idFilm);
            }

        } else {
            printf(" → Format tidak valid: %s\n", buffer);
        }
    }

    fclose(file);
}


// Tambah film ke list
void TambahFilm(List* L, FilmInfo filmBaru) {
    FilmInfo* node = alokasiFilm(filmBaru);
    if (node == NULL) {
        printf("Gagal mengalokasikan node Film.\n");
        return;
    }

    InsLast(L, node);
    printf("Film '%s' berhasil ditambahkan ke list.\n", filmBaru.judul);
}

void TambahFilmBaru(List* L, FilmInfo filmBaru) {
    filmBaru.idFilm = get_last_film_id(films) + 1;
    TambahFilm(L, filmBaru);
    simpanKeFile(*L, films);
}


// Edit film
void editFilmByName(FilmInfo filmBaru, addressList filmLama) {
    if (filmLama == NULL) return;

    FilmInfo* film = (FilmInfo*)(filmLama->info);

    // Hanya ubah jika data baru tidak kosong
    if (strlen(filmBaru.judul) > 0)
        strcpy(film->judul, filmBaru.judul);

    if (strlen(filmBaru.produser) > 0)
        strcpy(film->produser, filmBaru.produser);

    if (strlen(filmBaru.deskripsi) > 0)
        strcpy(film->deskripsi, filmBaru.deskripsi);

    if (filmBaru.durasi.jam >= 0)
        film->durasi.jam = filmBaru.durasi.jam;

    if (filmBaru.durasi.menit >= 0 && filmBaru.durasi.menit < 60)
        film->durasi.menit = filmBaru.durasi.menit;
}


// Hapus film berdasarkan id
void hapusFilm(List* L, int id) {
    addressList filmNode = cariFilm(*L, id);
    if (filmNode != NULL) {
        DelP(L, filmNode->info);  // Hapus berdasarkan info-nya
        simpanKeFile(*L, films);
        printf("Film dengan ID %d berhasil dihapus.\n", id);
    } else {
        printf("Film dengan ID %d tidak ditemukan.\n", id);
    }
}


void simpanKeFile(List L, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Gagal membuka file");
        return;
    }

    int current_id = get_last_film_id(films);

    for (addressList P = L.First; P != NULL; P = P->next) {
        FilmInfo* film = (FilmInfo*)(P->info);

        if (film->idFilm == 0) {
            film->idFilm = ++current_id;
        }

        fprintf(file, "%d|%s|%s|%s|%d|%d\n",
                film->idFilm,
                film->judul,
                film->produser,
                film->deskripsi,
                film->durasi.jam,
                film->durasi.menit);
    }

    fclose(file);
}


int get_last_film_id(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return 0; 

    int last_id = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        int temp_id;
        if (sscanf(line, "%d|", &temp_id) == 1) {
            if (temp_id > last_id) {
                last_id = temp_id;
            }
        }
    }

    fclose(file);
    return last_id;
}

// Cari film
addressList cariFilm(List L, int id) {
    addressList P = L.First;
    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
        if (film->idFilm == id) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

addressList cariFilmByJudul(List L, const char* title) {
    addressList P = L.First;

    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
        if (strcmp(film->judul, title) == 0) {
            return P;
        }
        P = P->next;
    }

    return NULL;
}


void printFilm(List L) {
    addressList P = L.First;
    if (P == NULL) {
        printf("Film tidak tersedia!\n");
        return;
    }

    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
            printf("ID         : %d\n", film->idFilm);
            printf("Judul      : %s\n", film->judul);
            printf("Produser   : %s\n", film->produser);
            printf("Deskripsi  : %s\n", film->deskripsi);
            printf("Durasi     : %d jam %d menit\n", film->durasi.jam, film->durasi.menit);
        P = P->next;
    }
}

void GetFilmByKota(address KotaNode, List *ListFilmKota) {
    CreateList(ListFilmKota);

    List listJadwal;
    AmbilSeluruhJadwalKotaKeList(KotaNode, &listJadwal);

    addressList p = listJadwal.First;
    while (p != NULL) {
        address nodeJadwal = (address)p->info;

        if (nodeJadwal != NULL && nodeJadwal->info != NULL) {
            JadwalInfo* jadwal = (JadwalInfo*) nodeJadwal->info;

            if (jadwal->film != NULL && !ApakahFilmSudahAda(*ListFilmKota, jadwal->film)) {
                FilmInfo* salinanFilm = (FilmInfo*) malloc(sizeof(FilmInfo));
                if (salinanFilm != NULL) {
                    *salinanFilm = *(jadwal->film);
                    InsLast(ListFilmKota, (infotype)salinanFilm);
                }
            }
        }

        p = p->next;
    }

    DelAll(&listJadwal);
}

boolean ApakahFilmSudahAda(List L, FilmInfo* target) {
    addressList P = L.First;
    while (P != NULL) {
        FilmInfo* f = (FilmInfo*)P->info;
        if (strcmp(f->judul, target->judul) == 0) {
            return true;
        }
        P = P->next;
    }
    return false;
}

void PrintFilmUpcoming(address KotaNode) {
    if (KotaNode == NULL) {
        printf("Kota tidak ditemukan.\n");
        return;
    }

    KotaInfo* infoKota = (KotaInfo*)KotaNode->info;
    printf("\n=== Daftar Film Upcoming di Kota %s ===\n", infoKota->nama);

    date today;
    GetToday(&today);

    List listJadwal;
    AmbilSeluruhJadwalKotaKeList(KotaNode, &listJadwal);

    List listFilmSudahCetak;
    CreateList(&listFilmSudahCetak);

    boolean adaFilm = false;

    addressList p = listJadwal.First;
    while (p != NULL) {
        address nodeJadwal = (address)p->info;
        JadwalInfo* jadwal = (JadwalInfo*)nodeJadwal->info;

        if (jadwal->film != NULL) {
            int selisih = DifferenceDate(today, jadwal->tanggal);
            if (selisih >= 1) {
                FilmInfo* film = jadwal->film;

                if (!ApakahFilmSudahAda(listFilmSudahCetak, film)) {
                    // Cari nama bioskop
                    const char* namaBioskop = "Tidak Diketahui";
                    address nodeBioskop = KotaNode->fs;
                    while (nodeBioskop != NULL) {
                        address nodeTeater = nodeBioskop->fs;
                        while (nodeTeater != NULL) {
                            address nodeJ = nodeTeater->fs;
                            while (nodeJ != NULL) {
                                if (nodeJ == nodeJadwal) {
                                    namaBioskop = ((BioskopInfo*)nodeBioskop->info)->nama;
                                }
                                nodeJ = nodeJ->nb;
                            }
                            nodeTeater = nodeTeater->nb;
                        }
                        nodeBioskop = nodeBioskop->nb;
                    }

                    printf("----------------------------------------------\n");
                    printf("Judul      : %s\n", film->judul);
                    printf("Produser   : %s\n", film->produser);
                    printf("Deskripsi  : %s\n", film->deskripsi);
                    printf("Durasi     : %02d:%02d\n", film->durasi.jam, film->durasi.menit);
                    printf("Tanggal    : %02d-%02d-%d\n", jadwal->tanggal.Tgl, jadwal->tanggal.Bln, jadwal->tanggal.Thn);
                    printf("Bioskop    : %s\n", namaBioskop);
                    adaFilm = true;

                    // Masukkan film ke listFilmSudahCetak
                    FilmInfo* salinan = malloc(sizeof(FilmInfo));
                    if (salinan != NULL) {
                        *salinan = *film;
                        InsLast(&listFilmSudahCetak, (infotype)salinan);
                    }
                }
            }
        }

        p = p->next;
    }

    if (!adaFilm) {
        printf("Tidak ada film upcoming di kota %s.\n", infoKota->nama);
    }

    DelAll(&listJadwal);
    DelAll(&listFilmSudahCetak);
}
