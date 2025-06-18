#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../errorHandle.h"

// Mengecek apakah string hanya berisi digit (0-9)
int isNumber(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

// Membaca angka dengan validasi
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


int isValidUsername(char *str) {
    if (strlen(str) == 0) return 0;
    for (int i = 0; str[i]; i++) {
        if (!isalnum(str[i])) return 0;
    }
    return 1;
}


boolean isValidKursiFormat(const char *input) {
    int len = strlen(input);
    if (len < 2) return false;
    if (!isalpha(input[0])) return false;
    for (int i = 1; i < len; i++) {
        if (!isdigit(input[i])) return false;
    }
    return true;
}
