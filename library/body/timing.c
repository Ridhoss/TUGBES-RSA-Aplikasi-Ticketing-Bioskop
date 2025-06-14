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
    if (isValidTime(jam, menit)) {
        T->jam = jam;
        T->menit = menit;
    } else {
        InisialisasiWaktu(T);
    }
}

boolean isValidTime(int jam, int menit) {
    return (jam >= 0 && jam < 24  && menit >= 0 && menit < 60);
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

// Fungsi untuk menghitung selisih waktu
TimeInfo DifferenceTime(TimeInfo A, TimeInfo B) {
    int selisih = ConvertMenit(A) - ConvertMenit(B); 
    if (selisih < 0) selisih = 0;                
    return ConvertTime(selisih);
}

// Fungsi untuk membandingkan dua waktu
int CompareTime(TimeInfo A, TimeInfo B) {
    int a = ConvertMenit(A);
    int b = ConvertMenit(B);
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

// Fungsi untuk memeriksa apakah waktu baru berada di luar rentang waktu yang sudah ditentukan
boolean CekBetweenTime(TimeInfo start, TimeInfo end, TimeInfo new) {
    int s = ConvertMenit(start);
    int e = ConvertMenit(end);
    int n = ConvertMenit(new);
    return (n < s || n > e); 
}

// Fungsi untuk mengonversi TimeInfo menjadi string
void TimeString(TimeInfo T, char *buffer) {
    sprintf(buffer, "%d jam %d menit", T.jam, T.menit); 
}

// Fungsi untuk mencetak waktu dalam format jam:menit
void PrintTime(TimeInfo T) {
    printf("%02d:%02d\n", T.jam, T.menit);
}