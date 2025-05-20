#ifndef ADTTeater_h
#define ADTTeater_h

#include "../../library/boolean.h"

#include "ADTList.h"

typedef struct {
    int id;
    char nama[100];
} TeaterInfo;

address AlokasiTeater(TeaterInfo X);
void DeAlokasiTeater(address P);

void InsLastTeater(List *L, TeaterInfo X);

address SearchTeater(List L, int id);
address SearchPrecTeater(List L, int id);

void DelPTeater(List *L, int id);
void DelAllTeater(List *L);

void PrintTeater(List L);


void InsFirstTeater(List *L, TeaterInfo X);
void InsertAfterTeater(List *L, TeaterInfo X, address Prec);
void DelFirstTeater(List *L, TeaterInfo *X);
void DelLastTeater(List *L, TeaterInfo *X);

#endif