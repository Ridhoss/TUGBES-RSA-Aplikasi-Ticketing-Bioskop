#include "header/ADTFilm.h"
#include "header/ADTList.h"

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
void tambahFilm(List* L, FilmInfo data) {
    FilmInfo* newFilm = (FilmInfo*)malloc(sizeof(FilmInfo));
    *newFilm = data;
    InsLast(L, (infotype)newFilm);
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
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file\n");
        return;
    }

    addressList P = L.First;
    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
        fprintf(file, "%d;%s;%s;%s\n", film->idFilm, film->judul, film->produser, film->deskripsi);
        P = P->next;
    }

    fclose(file);
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

