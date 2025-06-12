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

//  Fungsi untuk mengonversi TimeInfo menjadi total menit
int ConvertMenit(TimeInfo T) {
    return T.jam * 60 + T.menit; 
}

//  Fungsi untuk mengonversi total menit menjadi format waktu
TimeInfo ConvertTime(int totalMenit) {
    TimeInfo T;
    T.jam = totalMenit / 60;      
    T.menit = totalMenit % 60;     
    return T;
}

// Fungsi untuk menjumlahkan dua waktu bertipe TimeInfo
TimeInfo TambahWaktu(TimeInfo A, TimeInfo B) {
    int total = ConvertMenit(A) + ConvertMenit(B);
    return ConvertTime(total);
}
