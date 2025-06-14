#ifndef FILM_H
#define FILM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTList.h"
#include "../../library/timing.h"

extern const char *films;
// Struct utama untuk informasi film
typedef struct {
    int idFilm;
    char judul [100];
    char produser[100];
    char deskripsi[100];
    TimeInfo durasi;
} FilmInfo;

FilmInfo* alokasiFilm(FilmInfo data);
void dealokasiFilm(FilmInfo* f);

void loadFilm(List* L, const char* filename);
int editFilmById(List* L, int id, const char* judulBaru, const char* produserBaru, const char* deskripsiBaru, int jamBaru, int menitBaru);
int get_last_film_id(const char* filename);
void TambahFilm(List* L, FilmInfo filmBaru);
void TambahFilmBaru(List* L, const char* judul, const char* produser, const char* deskripsi, int jam, int menit);
void editFilm(List* L, int id, FilmInfo newData);
void hapusFilm(List* L, int id);
FilmInfo* cariFilm(List L, int id);
addressList cariFilmByJudul(List L, const char* title);
void printFilm(List L);
void simpanKeFile(List L, const char* filename);

#endif
