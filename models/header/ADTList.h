#ifndef ADTList_h
#define ADTList_h

#include "../../library/boolean.h"

typedef void* infotype;
typedef struct tElmtList *address;

typedef struct tElmtList {
  infotype info;
  address next;
} ListElmt;

typedef struct {
	  address First;
    address Last;
} List;

boolean ListEmpty(List L);

void CreateList(List * L);

address Alokasi(infotype X);
void DeAlokasi(address P);

address Search(List L, infotype X);
address SearchPrec(List L, infotype X);

void InsLast(List * L, infotype X);

void DelP(List * L, infotype X);
void DelAll(List * L);

void PrintInfo(List L);

void InsFirst(List * L, infotype X);
void InsertAfter(List *L, infotype X, address Prec);
void DelFirst(List * L, infotype * X);
void DelLast(List * L, infotype * X);

#endif