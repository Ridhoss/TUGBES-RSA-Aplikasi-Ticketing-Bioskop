#include "header/Auth.h"
#include <stdlib.h>

int loggedIn = 0; 
int idLogin = 0; 

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
    for (;;) {
        int valid = 1;
        printf("Masukkan Nomor Telepon: ");
        scanf("%15s", akun->phone);

        for (int i = 0; akun->phone[i] != '\0'; i++) {
            if (!isdigit(akun->phone[i])) {
                valid = 0;
                break;
            }
        }

        if (valid) break;
        else printf("Nomor telepon hanya boleh berisi angka! Silakan masukkan ulang.\n");
    }

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

void HalamanLogin(){

    char username[50];
    char password[50];
    Akun akun[100];
    int total_akun = BacaFileAkun(akun);

   printf("===================================================\n");
    printf("||                     Masuk                     ||\n");
    printf("===================================================\n");

    printf("Masukan Username: ");
    scanf(" %s", username);
    printf("Masukan Password: ");
    scanf(" %s", password);

    loggedIn = Login(username, password, akun, total_akun, &idLogin);
    
    if (loggedIn) {
        printf("Login berhasil!\n");
    } else {
        printf("=============================\n");
        printf("Username atau Password salah!\n");   
        printf("=============================\n");
    }
}

void HalamanAwal() {
    int masuk = 0;

    for (;;) {
        printf("===================================================\n");
        printf("|| SELAMAT DATANG DI APLIKASI TICKETING BIOSKOP  ||\n");
        printf("===================================================\n");
        printf("|| Apakah Anda sudah memiliki akun?              ||\n");
        printf("||                                               ||\n");
        printf("||     1. Masuk                                  ||\n");
        printf("||     2. Daftar                                 ||\n");
        printf("||     3. Keluar dari Aplikasi                   ||\n");
        printf("||                                               ||\n");
        printf("|| Silakan pilih menu (1-3):                     ||\n");
        printf("===================================================\n");
        printf(">> ");
        scanf("%d",&masuk);

        if (masuk == 1) {
            HalamanLogin();
            if (loggedIn) break;
        } else if (masuk == 2) {
            int role = 1;
            DaftarAkun(role);
        } else if (masuk == 3) {
            printf("Anda Berhasil Keluar Dari Aplikasi\n");
            exit(0);
        } else {
            printf("Error 404. Input Tidak Diketahui\n");
        }
    }
}
