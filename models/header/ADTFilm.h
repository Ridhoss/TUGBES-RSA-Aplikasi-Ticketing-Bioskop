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

void tambahFilm(List* L, FilmInfo data);
void editFilm(List* L, int id, FilmInfo newData);
void hapusFilm(List* L, int id);
FilmInfo* cariFilm(List L, int id);
void printFilm(List L);
void simpanKeFile(List L, const char* filename);

#endif
