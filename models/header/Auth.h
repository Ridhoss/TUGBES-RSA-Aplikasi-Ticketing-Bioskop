#ifndef AUTH_H
#define AUTH_H

typedef struct {
    int id;
    char username[50];
    char password[50];
    char phone[16];
    char alamat[50];
    int saldo;
    int role;
} Akun;

//* Baca file akun
int BacaFileAkun(Akun *akun);
//* Cek duplikat username
int CekDuplikat(const char *username);
//* Cek id terakhir
int get_last_id();  
//* Procedure daftar user
void DaftarAkun(int role);
//* Procedure login
int Login(const char *username, const char *password, Akun *akun, int total_akun, int *idLogin);
//* Function CariAkun
Akun* CariAkunById(int idLogin);
//* Procedure logout
void Logout(int *con);
//* Clear Account
void Clear(int *idLogin, char *username, char *password, char *phone, char *alamat, int *saldo, int *role);
#endif