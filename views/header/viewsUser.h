#ifndef VIEWSUSER_H
#define VIEWSUSER_H

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
#include "../../models/header/ADTPemesanan.h"
#include "../../models/header/ADTStack.h"
#include "Auth.h"


void HalamanMenuUser(address root, List *L);
void HalamanPilihJadwal(address root, List *L, address kotaNode, addressList filmNode, date tanggalAwal);
void HalamanPilihKursi(address root, List *L, address nodeJadwal);
void HalamanKonfirmasiPemesanan(address nodeJadwal, Kursi kursiDipilih[], int jumlahDipilih);

#endif 