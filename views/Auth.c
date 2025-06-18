#include "header/Auth.h"
#include <stdlib.h>

int loggedIn = 0; 
int idLogin = 0; 

void HalamanRegister(Akun *akun, int role){

    char password_check[50];

    printf("== Registrasi Akun Baru ==\n");
    
    do {
        printf("Masukkan Username: ");
        scanf("%49s", akun->username);
        if (!isValidUsername(akun->username)) {
            printf("Username tidak boleh kosong dan tidak boleh mengandung simbol!\n");
        }
    } while (!isValidUsername(akun->username));

   
    for (;;) {
        do {
            printf("Masukkan Password: ");
            scanf("%49s", akun->password);
            if (!isValidUsername(akun->password)) {
            printf("Password tidak valid. Hanya huruf/angka, tidak kosong.\n");
        }
    } while (!isValidUsername(akun->password));
    
    printf("Konfirmasi Password: ");
    scanf("%49s", password_check);
    
    if (strcmp(akun->password, password_check) == 0) {
        break;
    }
    printf("Konfirmasi Password Salah! Silakan coba lagi.\n");
}

    // Phone
    InputNomorTelepon(akun->phone, 16);

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

   do {
    printf("Masukan Username: ");
    scanf(" %49s", username);
    if (!isValidUsername(username)) {
        printf("Username tidak boleh kosong dan tidak boleh mengandung spasi atau simbol!\n");
    }
} while (!isValidUsername(username));

   do {
    printf("Masukan Password: ");
    scanf(" %49s", password);
    if (!isValidUsername(password)) {
        printf("Password tidak boleh kosong dan hanya boleh huruf/angka!\n");
    }
} while (!isValidUsername(password));

    loggedIn = Login(username, password, akun, total_akun, &idLogin);
    
    if (loggedIn) {
        printf("Login berhasil!\n");
    } else {
        printf("=============================\n");
        printf("Username atau Password salah!\n");   
        printf("=============================\n");
    }
}

void HalamanAwal(address *root, List *L) {
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
        masuk = InputAngkaValid(1, 3);
        // scanf("%d",&masuk);

        if (masuk == 1) {
            HalamanLogin();

            if (loggedIn) {
                Akun* akunLogin = CariAkunById(idLogin);
                if (akunLogin != NULL) {
                    if (akunLogin->role == 0) {
                        HalamanMenuAdmin(*root, L);
                    } else if (akunLogin->role == 1) {
                        HalamanMenuUser(*root, L);
                    } else {
                        printf("Role tidak dikenali. Hubungi admin sistem.\n");
                    }
                } else {
                    printf("Akun tidak ditemukan.\n");
                }
            }

        } else if (masuk == 2) {
            int role = 1;
            DaftarAkun(role);
            
        } else if (masuk == 3) {
            printf("Anda Berhasil Keluar Dari Aplikasi\n");

            DeleteAll(*root);
            DelAll(L);

            exit(0);
            
        } else {
            printf("Error 404. Input Tidak Diketahui\n");
        }
        
    }
}
