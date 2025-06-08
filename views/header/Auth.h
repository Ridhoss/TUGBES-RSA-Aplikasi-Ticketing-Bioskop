#ifndef AUTH_H
#define AUTH_H
#include <stdio.h>
#include <string.h>
#include "../../models/header/ADTAkun.h"

void HalamanRegister(Akun *akun, int role);
void HalamanLogin(int *loggedIn, int *idLogin);
#endif