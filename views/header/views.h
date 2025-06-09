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


void HalamanManipulasiKota(address root);
void HalamanManipulasiBioskop(address root);
void HalamanManipulasiTeater(address root, address nodeKota);



#endif
