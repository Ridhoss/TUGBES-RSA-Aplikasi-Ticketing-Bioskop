#include "header/Auth.h"
#include <stdlib.h>

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

void HalamanLogin(int *loggedIn, int *idLogin){

    char username[50];
    char password[50];
    Akun akun[100];
    int total_akun = BacaFileAkun(akun);

    printf("=======================\n");
    printf("======== MASUK ========\n");
    printf("=======================\n");

    printf("Masukan Username: ");
    scanf(" %s", username);
    printf("Masukan Password: ");
    scanf(" %s", password);

    *loggedIn = Login(username, password, akun, total_akun, idLogin);
    
    if (*loggedIn) {
        printf("Login berhasil!\n");
    } else {
        printf("=============================\n");
        printf("Username atau Password salah!\n");   
        printf("=============================\n");
    }
}

void HalamanAwal(int *loggedIn, int *idLogin) {
    int masuk = 0;

    for (;;) {
        printf("====================================\n");
        printf("=== Selamat Datang Di Aplikasi Ticketing Bioskop ===\n");
        printf("====================================\n");

        printf("Apakah Sudah Memiliki Akun?\n");
        printf("1. Masuk\n");
        printf("2. Daftar\n");
        printf("3. Keluar Dari Aplikasi\n");
        printf("Pilih:(1-3) ");
        scanf("%d", &masuk);

        if (masuk == 1) {
            HalamanLogin(loggedIn, idLogin);
            if (*loggedIn) break;
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
