#ifndef ADTBioskop_h
#define ADTBioskop_h

#include "../../library/boolean.h"

#include "ADTKota.h"
#include "ADTTree.h"

typedef struct {
    char nama[100];
} BioskopInfo;

address AlokasiBioskop(BioskopInfo X);
void DeAlokasiBioskop(address P);

void TambahBioskop(address kota, const char* namaBioskop);


#endif