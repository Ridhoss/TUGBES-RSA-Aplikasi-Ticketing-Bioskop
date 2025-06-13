#ifndef ADTList_h
#define ADTList_h

#include "../../library/boolean.h"

typedef void* infotype;
typedef struct tElmtList *addressList;

typedef struct tElmtList {
  infotype info;
  addressList next;
} ListElmt;

typedef struct {
	  addressList First;
    addressList Last;
} List;

boolean ListEmpty(List L);

void CreateList(List * L);

addressList Allocation(infotype X);
void DeAllocation(addressList P);

addressList SearchList(List L, infotype X);
addressList SearchPrec(List L, infotype X);

void InsLast(List * L, infotype X);

void DelP(List * L, infotype X);
void DelAll(List * L);

void PrintInfo(List L);

void InsFirst(List * L, infotype X);
void InsertAfter(List *L, infotype X, addressList Prec);
void InsLast(List* L, infotype X);
void DelFirst(List * L, infotype * X);
void DelLast(List * L, infotype * X);

#endif