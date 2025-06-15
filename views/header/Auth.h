#ifndef AUTH_H
#define AUTH_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../models/header/ADTAkun.h"

extern int loggedIn;
extern int idLogin; 

void HalamanAwal();
void HalamanRegister(Akun *akun, int role);
void HalamanLogin();

#endif