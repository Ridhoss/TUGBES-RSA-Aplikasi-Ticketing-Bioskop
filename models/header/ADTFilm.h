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
int get_last_film_id(const char* filename);
void TambahFilm(List* L, FilmInfo filmBaru);
void TambahFilmBaru(List* L, const char* judul, const char* produser, const char* deskripsi, int jam, int menit);
void editFilmByName(FilmInfo filmBaru, addressList filmLama);
void hapusFilm(List* L, int id);
addressList cariFilm(List L, int id);
addressList cariFilmByJudul(List L, const char* title);
void printFilm(List L);
void simpanKeFile(List L, const char* filename);

#endif
