#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../timing.h" 

void InisialisasiWaktu(TimeInfo *T) {
    T->jam = 0;
    T->menit = 0;
}

void SetTime(TimeInfo *T, int jam, int menit) {
    if (isValid(jam, menit)) {
        T->jam = jam;
        T->menit = menit;
    } else {
        InisialisasiWaktu(T);
    }
}

boolean isValid(int jam, int menit) {
    return (jam >= 0 && menit >= 0 && menit < 60);
}