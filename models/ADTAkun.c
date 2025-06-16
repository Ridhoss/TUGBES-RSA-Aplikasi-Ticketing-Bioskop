#include "header/ADTAkun.h"
#include "../views/header/Auth.h"

const char *users = "database/users.txt";

// Deskripsi: Fungsi ini membaca data akun dari file teks (users) dan menyimpannya ke dalam array akun.
// I.S.: File users ada di direktori, dan parameter akun dialokasikan.
// F.S.: akun terisi dengan data dari file, dan fungsi mengembalikan jumlah akun yang berhasil dibaca.
int BacaFileAkun(Akun *akun){
    FILE *file = fopen(users, "r");
    if (file == NULL) return 0;

    int index = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; 
        if (sscanf(line, "%d|%49[^|]|%49[^|]|%14[^|]|%99[^|]|%d|%d",
            &akun[index].id,
            akun[index].username,
            akun[index].password,
            akun[index].phone,
            akun[index].alamat,
            &akun[index].saldo,
            &akun[index].role) == 7) {
                
            index++;
        }
    }
    fclose(file);
    return index;
}

// Deskripsi: Fungsi ini mengecek apakah username yang diberikan sudah ada di file users.
// I.S.: Parameter username diberikan, file users tersedia atau belum ada.
// F.S.: Mengembalikan 1 jika username ada (duplikat) dan 0 jika username tidak ada. 
int CekDuplikat(const char *username) {
    FILE *file = fopen(users, "r");
    if (file == NULL) return 0; // file belum ada, jadi username belum ada

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char file_username[50];
        sscanf(line, "%*d|%49[^|]", file_username);
        if (strcmp(username, file_username) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Deskripsi: Fungsi ini membaca file users dan mengembalikan ID terakhir yang ditemukan.
// I.S.: File users tersedia atau tidak
// F.S.: fungsi mengembalikan ID tertinggi yang ditemukan di file users
int get_last_id() {
    FILE *file = fopen(users, "r");
    if (file == NULL) return 0;

    int last_id = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int temp_id;
        sscanf(line, "%d|", &temp_id);
        if (temp_id > last_id) {
            last_id = temp_id;
        }
    }
    fclose(file);
    return last_id;
}

// Deskripsi: Procedure ini melakukan proses registrasi akun baru, memastikan username tidak duplikat, lalu menyimpan data akun ke file users.
// I.S.: Parameter role diterima
// F.S.: Data akun tersimpan di file users jika username tidak duplikat dan file berhasil dibuka.
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
    fprintf(file, "%d|%s|%s|%s|%s|%d|%d\n",
        akun.id, akun.username, akun.password,
        akun.phone, akun.alamat, akun.saldo, akun.role);

    fclose(file);

    printf("Registrasi berhasil!\n");
}

// Deskripsi: Fungsi ini memverifikasi apakah kombinasi username dan password cocok dengan salah satu akun dalam array, lalu mengembalikan ID akun yang berhasil login.
// I.S.: Semua parameter terisi dan data akun tersedia.
// F.S.: Jika login berhasil, *idLogin berisi ID akun dan fungsi return 1. Jika gagal, return 0.   
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

// Deskripsi: Fungsi ini mencari dan mengembalikan pointer ke data akun dengan id yang cocok dari file users.
// I.S.: File users tersedia dan idLogin diberikan.
// F.S.: Mengembalikan pointer ke elemen akun[i] jika ditemukan, atau NULL jika tidak ditemukan.
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