#ifndef views_h
#define views_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../../models/header/ADTTree.h"
#include "../../models/header/ADTKota.h"
#include "../../models/header/ADTBioskop.h"
#include "../../models/header/ADTTeater.h"
#include "../../models/header/ADTFilm.h"
#include "../../models/header/ADTJadwal.h"
#include "../../models/header/ADTList.h"
#include "../../models/header/ADTPemesanan.h"
#include "Auth.h"

void HalamanMenuAdmin(address root, List *L);
void HalamanManipulasiKota(address root, List *L);
void HalamanManipulasiBioskop(address root, List *L);
void HalamanManipulasiTeater(address root, List *L, address nodeKota);
void HalamanManipulasiJadwal(address root, List *L, address nodeKota, address nodeBioskop);
void HalamanManipulasiFilm(List *L);
void HalamanHistoryTransaksi(address root, List *L);



#endif
