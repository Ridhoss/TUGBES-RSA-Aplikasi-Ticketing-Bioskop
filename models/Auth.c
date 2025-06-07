#include <stdio.h>
#include "header/Auth.h"
#include "../views/header/views.h"

const char *users = "database/users.txt";

int BacaFileAkun(Akun *akun){
    FILE *file = fopen(users, "r");
    if (file == NULL) return 0;

    int index = 0;
    while (fscanf(file, "%d,%49[^,],%49[^,],%15[^,],%49[^,],%d,%d\n", 
                &akun[index].id, akun[index].username, 
                akun[index].password, akun[index].phone, 
                akun[index].alamat, &akun[index].saldo,&akun[index].role ) == 7) {
        index++;
    }
    fclose(file);
    return index;
}


int CekDuplikat(const char *username) {
    FILE *file = fopen(users, "r");
    if (file == NULL) return 0; // file belum ada, jadi username belum ada

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char file_username[50];
        sscanf(line, "%*d,%49[^,]", file_username);
        if (strcmp(username, file_username) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int get_last_id() {
    FILE *file = fopen(users, "r");
    if (file == NULL) return 0;

    int last_id = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int temp_id;
        sscanf(line, "%d,", &temp_id);
        if (temp_id > last_id) {
            last_id = temp_id;
        }
    }
    fclose(file);
    return last_id;
}

void DaftarAkun(int role) {
    Akun akun;
    akun.role = role;
    akun.saldo = 0;

    // Input user (view)
    for (;;) {
        HalamanRegister(&akun, role);

        if (CekDuplikat(akun.username)) {
            printf("Username sudah digunakan! Silakan coba username lain.\n");
        } else {
            break;
        }
    }

    int last_id = get_last_id();
    akun.id = last_id + 1;

    FILE *file = fopen(users, "a");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data!\n");
        return;
    }

    fclose(file);

    printf("Registrasi berhasil!\n");
}