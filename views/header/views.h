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

void HalamanManipulasiKota(address root);
void HalamanManipulasiBioskop(address root);
void HalamanManipulasiTeater(address root, address nodeKota);
void HalamanManipulasiJadwal(address root, address nodeKota, address nodeBioskop);
void HalamanManipulasiFilm(List *L);
void HalamanMenuAdmin();



#endif
