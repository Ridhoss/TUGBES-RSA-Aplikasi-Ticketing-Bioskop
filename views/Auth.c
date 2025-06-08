#include "header/Auth.h"

void HalamanRegister(Akun *akun, int role){

    char password_check[50];

    printf("== Registrasi Akun Baru ==\n");

    // Username
    printf("Masukkan Username: ");
    scanf("%49s", akun->username);

    // Password + konfirmasi
    for (;;) {
        printf("Masukkan Password: ");
        scanf("%49s", akun->password);

        printf("Konfirmasi Password: ");
        scanf("%49s", password_check);

        if (strcmp(akun->password, password_check) == 0) {
            break;
        }
        printf("Konfirmasi Password Salah! Silakan coba lagi.\n");
    }

    // Phone
    printf("Masukkan Nomor Telepon: ");
    scanf("%15s", akun->phone);

    // Alamat, hanya input jika role bukan 2 (admin)
    if (role != 2) {
        printf("Masukkan Alamat: ");
        getchar();
        fgets(akun->alamat, sizeof(akun->alamat), stdin);
        akun->alamat[strcspn(akun->alamat, "\n")] = '\0';
    } else {
        strcpy(akun->alamat, "null");
    }
}

void HalamanLogin(int *loggedIn, int *idLogin){
    char username[50];
    char password[50];
    Akun akun[100];
    int total_akun = BacaFileAkun(akun);

    printf("=======================\n");
    printf("======== MASUK ========\n");
    printf("=======================\n");

    printf("Masukan Username: ");
    scanf("%s", username);
    printf("Masukan Password: ");
    scanf("%s", password);

    *loggedIn = Login(username, password, akun, total_akun, idLogin);
    
    if (*loggedIn) {
        printf("Login berhasil!\n");
    } else {
        printf("=============================\n");
        printf("Username atau Password salah!\n");   
        printf("=============================\n");
    }
}