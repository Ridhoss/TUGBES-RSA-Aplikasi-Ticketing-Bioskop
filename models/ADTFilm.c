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

// Tambah film ke list
void tambahFilm(List* L, const char* judul, const char* produser, const char* deskripsi) {
    FilmInfo* film = malloc(sizeof(FilmInfo));
    film->idFilm = 0; // Agar auto-increment saat simpan
    strcpy(film->judul, judul);
    strcpy(film->produser, produser);
    strcpy(film->deskripsi, deskripsi);

    addressList newNode = malloc(sizeof(struct tElmtList));
    newNode->info = film;
    newNode->next = NULL;

    if (L->First == NULL) {
        L->First = newNode;
    } else {
        addressList last = L->First;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
    }
    simpanKeFile(*L, films);
}
// Edit film berdasarkan id
void editFilm(List* L, int id, FilmInfo newData) {
    addressList P = L->First;
    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
        if (film->idFilm == id) {
            *film = newData;
            return;
        }
        P = P->next;
    }
    simpanKeFile(*L, films);
}

// Hapus film berdasarkan id
void hapusFilm(List* L, int id) {
    addressList P = L->First;
    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
        if (film->idFilm == id) {
            DelP(L, (infotype)film);
            return;
        }
        P = P->next;
    }
}

void simpanKeFile(List L, const char* filename) {
    FILE* file = fopen(films, "w");
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

        fprintf(file, "%d|%s|%s|%s\n", film->idFilm, film->judul, film->produser, film->deskripsi);
        P = P->next;
    }

    fclose(file);
}

int get_last_film_id(const char* filename) {
    FILE* file = fopen(films, "r");
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
FilmInfo* cariFilm(List L, int id) {
    addressList P = L.First;
    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
        if (film->idFilm == id) {
            return film;
        }
        P = P->next;
    }
    return NULL;
}

void printFilm(List L) {
    addressList P = L.First;
    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
        printf("ID: %d\njudul: %s\nProduser: %s\nDeskripsi: %s\n\n",
               film->idFilm, film->judul, film->produser, film->deskripsi);
        P = P->next;
    }
    printf("Film tidak tersedia!\n");
}