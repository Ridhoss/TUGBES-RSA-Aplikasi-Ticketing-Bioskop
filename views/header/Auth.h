#ifndef AUTH_H
#define AUTH_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../../models/header/ADTAkun.h"
#include "../../models/header/ADTList.h"
#include "../../models/header/ADTTree.h"
#include "../../library/errorHandle.h"

#include "views.h"
#include "viewsUser.h"

extern int loggedIn;
extern int idLogin; 

void HalamanAwal(address *root, List *L);
void HalamanRegister(Akun *akun, int role);
void HalamanLogin();

#endif