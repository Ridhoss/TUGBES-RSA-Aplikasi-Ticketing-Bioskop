#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../errorHandle.h"

// Deskripsi: Mengecek apakah sebuah string hanya terdiri dari karakter angka (0-9).
// I.S.: str berisi string sembarang.
// F.S.: Mengembalikan 1 (true) jika semua karakter di str adalah digit, 0 (false)
int isNumber(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

// Deskripsi: Membaca input dari user dan memastikan bahwa input adalah angka dalam rentang [min, max].
// I.S.: min dan max terdefinisi, pengguna belum memasukkan input atau input belum valid.
// F.S.: Mengembalikan angka valid dari user yang berada di antara min dan max
int InputAngkaValid(int min, int max) {
    char input[100];
    int angka;

    while (1) {
        scanf("%s", input);

        if (!isNumber(input)) {
            printf("Input harus berupa angka! Coba lagi: ");
            continue;
        }

        angka = atoi(input);
        if (angka < min || angka > max) {
            printf("Input harus antara %d - %d. Coba lagi: ", min, max);
            continue;
        }

        return angka;
    }
}

// Deskripsi: Membaca input nomor telepon dari user dan memastikan hanya terdiri dari digit (0-9).
// I.S.: maxLen ditentukan, pengguna belum memasukkan input atau input belum valid.
// F.S.: output berisi string nomor telepon valid yang hanya terdiri dari angka dan sesuai panjang maksimum
void InputNomorTelepon(char *output, int maxLen) {
    char input[100];
    int valid;

    do {
        valid = 1;
        printf("Masukkan Nomor Telepon: ");
        scanf("%s", input);

        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Nomor telepon hanya boleh berisi angka! Silakan ulangi.\n");
        }

    } while (!valid);

    strncpy(output, input, maxLen);
    output[maxLen - 1] = '\0'; 
}

// Deskripsi: Mengecek apakah username hanya terdiri dari huruf dan angka, dan tidak kosong.
// I.S.: str berisi string sembarang (hasil input username).
// F.S.: Mengembalikan 1 (true) jika semua karakter adalah alfanumerik dan tidak kosong, 0 jika tidak valid
int isValidUsername(char *str) {
    if (strlen(str) == 0) return 0;
    for (int i = 0; str[i]; i++) {
        if (!isalnum(str[i])) return 0;
    }
    return 1;
}

// Deskripsi: Mengecek apakah format input kursi valid (huruf diikuti angka, seperti A1, B12).
// I.S.: input berisi string dari input user.
// F.S.: Mengembalikan true jika karakter pertama huruf, sisanya angka. Mengembalikan false jika tidak sesuai forma
boolean isValidKursiFormat(const char *input) {
    int len = strlen(input);
    if (len < 2) return false;
    if (!isalpha(input[0])) return false;
    for (int i = 1; i < len; i++) {
        if (!isdigit(input[i])) return false;
    }
    return true;
}
