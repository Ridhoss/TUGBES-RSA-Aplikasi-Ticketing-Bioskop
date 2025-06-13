#ifndef FILM_H
#define FILM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTList.h"

// Struct utama untuk informasi film
typedef struct {
    int idFilm;
    char judul [100];
    char produser[100];
    char deskripsi[100];
    // time durasi;
} FilmInfo;

FilmInfo* alokasiFilm(FilmInfo data);
void dealokasiFilm(FilmInfo* f);

int editFilmById(List* L, int id, const char* judulBaru, const char* produserBaru, const char* deskripsiBaru);
int get_last_film_id(const char* filename);
void tambahFilm(List* L, const char* judul, const char* produser, const char* deskripsi);
void editFilm(List* L, int id, FilmInfo newData);
void hapusFilm(List* L, int id);
FilmInfo* cariFilm(List L, int id);
void printFilm(List L);
void simpanKeFile(List L, const char* filename);

#endif
