#include <stdio.h>
#include <string.h>
#include "models/header/ADTTree.h"
#include "models/header/ADTList.h"
#include "models/header/ADTKota.h"
#include "models/header/ADTBioskop.h"
#include "models/header/ADTTeater.h"
#include "models/header/ADTAkun.h"
#include "models/header/ADTFilm.h"
#include "views/header/views.h"
#include "views/header/Auth.h"

int main() {
    int loggedIn = 0;
    int idLogin = 1;
    HalamanAwal(&loggedIn, &idLogin);
    HalamanMenuAdmin();
    return 0;
}