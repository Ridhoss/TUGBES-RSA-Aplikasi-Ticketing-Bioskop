#include "header/ADTAkun.h"
#include "../views/header/Auth.h"

const char *users = "../database/users.txt";

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

int Login(const char *username, const char *password, Akun *akun, int total_akun, int *idLogin){
    for (int i = 0; i < total_akun; i++)
    {
        if (strcmp(username, akun[i].username) == 0 && strcmp(password, akun[i].password) == 0)
        {
            *idLogin = akun[i].id;
            return 1;
        }
    }
    return 0;
}

Akun* CariAkunById(int idLogin) {
    static Akun akun[100];
    int totalAkun = BacaFileAkun(akun);

    for (int i = 0; i < totalAkun; i++) {
        if (akun[i].id == idLogin) {
            return &akun[i];
        }
    }

    return NULL;
}

void Logout(int *con){
    *con = 0;
}

void Clear(int *idLogin, char *username, char *password, char *phone, char *alamat, int *saldo, int *role){
    strcpy(username,"");
    strcpy(password,"");
    strcpy(phone,"");
    strcpy(alamat,"");
    *saldo = 0;
    *role = 0;
    *idLogin = 0;
}