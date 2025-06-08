#ifndef AUTH_H
#define AUTH_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../models/header/ADTAkun.h"

void HalamanAwal(int *loggedIn, int *idLogin);
void HalamanRegister(Akun *akun, int role);
void HalamanLogin(int *loggedIn, int *idLogin);

#endif