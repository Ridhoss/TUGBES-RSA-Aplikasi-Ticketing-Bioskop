#ifndef ADTJadwal_h
#define ADTJadwal_h

#include "boolean.h"
#include "ADTList.h"

typedef struct {
    int id;
    char start[20];
    char end[20];
    int id_film;
} JadwalInfo;

address AlokasiJadwal(JadwalInfo X);
void DeAlokasiJadwal(address P);

void InsLastJadwal(List *L, JadwalInfo X);

address SearchJadwal(List L, int id);
address SearchPrecJadwal(List L, int id);

void DelPJadwal(List *L, int id);
void DelAllJadwal(List *L);

void PrintJadwal(List L);

void InsFirstJadwal(List *L, JadwalInfo X);
void InsertAfterJadwal(List *L, JadwalInfo X, address Prec);
void DelFirstJadwal(List *L, JadwalInfo *X);
void DelLastJadwal(List *L, JadwalInfo *X);

void UpdateJadwalByID(List *L, int id, char* newStart, char* newEnd);
address SearchJadwalByFilm(List L, int id_film);
void SortJadwalByTime(List *L);

#endif
