#include "header/ADTFilm.h"
#include "header/ADTList.h"
#include "header/ADTAkun.h"

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
        printf("File '%s' tidak ditemukan atau gagal dibuka.\n", filename);
        return;
    }

    FilmInfo data;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        int parsed = sscanf(buffer, "%d|%[^|]|%[^|]|%[^|]|%d|%d",
                            &data.idFilm,
                            data.judul,
                            data.produser,
                            data.deskripsi,
                            &data.durasi.jam,
                            &data.durasi.menit);
        printf("BACA: '%s'\n", buffer);
        if (parsed == 6) {
            FilmInfo* filmPtr = alokasiFilm(data);
            if (filmPtr != NULL) {
                InsLast(L, filmPtr);
            }
        } else {
            printf(" → Parsed GAGAL (%d fields)\n", parsed);
        }
    }

    fclose(file);
}


int editFilmById(List* L, int id, const char* judulBaru, const char* produserBaru, const char* deskripsiBaru, int jamBaru, int menitBaru) {
    addressList P = L->First;

    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)P->info;

        if (film->idFilm == id) {
            if (judulBaru && strlen(judulBaru) > 0)
                strcpy(film->judul, judulBaru);

            if (produserBaru && strlen(produserBaru) > 0)
                strcpy(film->produser, produserBaru);

            if (deskripsiBaru && strlen(deskripsiBaru) > 0)
                strcpy(film->deskripsi, deskripsiBaru);

            if (jamBaru >= 0) {
                film->durasi.jam = jamBaru;
            }
            if (menitBaru >= 0 && menitBaru < 60) {
                film->durasi.menit = menitBaru;
            }

            return 1;
        }

        P = P->next;
    }

    return 0;
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

void TambahFilmBaru(List* L, const char* judul, const char* produser, const char* deskripsi, int jam, int menit) {
    FilmInfo filmBaru;
    filmBaru.idFilm = get_last_film_id(films) + 1;
    strcpy(filmBaru.judul, judul);
    strcpy(filmBaru.produser, produser);
    strcpy(filmBaru.deskripsi, deskripsi);
    filmBaru.durasi.jam = jam;
    filmBaru.durasi.menit = menit;
    TambahFilm(L, filmBaru);

    // Tambahkan juga ke file
    simpanKeFile(*L, films);
}

// Edit film berdasarkan id
void editFilm(List* L, int id, FilmInfo newData) {
    addressList P = L->First;
    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
        if (film->idFilm == id) {
            *film = newData;
            
            simpanKeFile(*L, films);
            return;
        }
        P = P->next;
    }
}

// Hapus film berdasarkan id
void hapusFilm(List* L, int id) {
    addressList P = L->First;
    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
        if (film->idFilm == id) {
            DelP(L, P->info);
            break;
        }
        P = P->next;
    }
    simpanKeFile(*L, films);
}

void simpanKeFile(List L, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file\n");
        return;
    }

    int current_id =  get_last_film_id(films); // Ambil ID terakhir yang sudah tersimpan

    addressList P = L.First;
    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);

        if (film->idFilm == 0) {
            current_id++;
            film->idFilm = current_id;
        }

        fprintf(file, "%d|%s|%s|%s|%d|%d\n", film->idFilm, film->judul, film->produser, film->deskripsi,
        film->durasi.jam, film->durasi.menit);

        P = P->next;
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

// Cari film berdasarkan id (return pointer ke FilmInfo)
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
