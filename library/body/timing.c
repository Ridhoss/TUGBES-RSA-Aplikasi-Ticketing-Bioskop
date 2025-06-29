#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../timing.h" 

// Deskripsi: Fungsi ini membantu memastikan waktu dimulai dari titik nol sebelum digunakan lebih lanjut.
// I.S.: T berisi nilai acak atau belum diatur.
// F.S.: T memiliki nilai jam = 0 dan menit = 0.
void InisialisasiWaktu(TimeInfo *T) {
    T->jam = 0;
    T->menit = 0;
}

// Deskripsi: Fungsi ini mengatur waktu pada TimeInfo jika valid, atau menginisialisasi ke 00:00 jika tidak valid.
// I.S: belum tentu memiliki nilai waktu yang valid.
// F.S: berisi waktu yang diatur sesuai parameter jika valid, atau diatur ke 00:00 jika tidak valid.
void SetTime(TimeInfo *T, int jam, int menit) {
    if (isValidTime(jam, menit)) {
        T->jam = jam;
        T->menit = menit;
    } else {
        InisialisasiWaktu(T);
    }
}

// Deskripsi: Mengisi waktu T dengan waktu sekarang dari sistem (jam & menit).
// I.S.: T belum diisi.
// F.S.: T berisi waktu sistem saat ini.
void GetTime(TimeInfo *T) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    T->jam = local->tm_hour;
    T->menit = local->tm_min;
}

// Deskripsi: Memvalidasi agar tanggal dan waktu input tidak lebih kecil dari tanggal dan waktu saat ini
// I.S.: tanggalInput dan waktuInput terdefinisi.
// F.S.: Mengembalikan true jika waktu input > waktu saat ini, false jika tidak.
boolean isDateTimeValid(date tanggalInput, TimeInfo waktuInput) {
    date today;
    GetToday(&today);  

    int selisih = DifferenceDate(today, tanggalInput);

    if (selisih < 0) {
        return false; 
    } else if (selisih == 0) {
        TimeInfo now;
        GetTime(&now); 
        return CompareTime(waktuInput, now) > 0;
    } else {
        return true; 
    }
}

// Deskripsi: Mengecek apakah nilai jam dan menit berada dalam rentang waktu yang valid (0–23 untuk jam, 0–59 untuk menit).
// I.S.: jam dan menit diberikan.
// F.S.: Mengembalikan true jika valid, false jika tidak.
boolean isValidTime(int jam, int menit) {
    return (jam >= 0 && jam < 24  && menit >= 0 && menit < 60);
}

// Deskripsi: Mengubah waktu T ke dalam bentuk total menit.
// I.S.: T berisi jam dan menit.
// F.S.: Menghasilkan jam * 60 + menit.
int ConvertMenit(TimeInfo T) {
    return T.jam * 60 + T.menit; 
}

// Deskripsi: Mengubah total menit menjadi waktu dengan jam dan menit.
// I.S.: totalMenit terdefinisi.
// F.S.: Menghasilkan TimeInfo yang sesuai.
TimeInfo ConvertTime(int totalMenit) {
    TimeInfo T;
    T.jam = totalMenit / 60;      
    T.menit = totalMenit % 60;     
    return T;
}

// Deskripsi: Menjumlahkan dua waktu bertipe TimeInfo.
// I.S.: A dan B adalah dua waktu valid.
// F.S.: Menghasilkan A + B dalam format waktu.
TimeInfo TambahWaktu(TimeInfo A, TimeInfo B) {
    int total = ConvertMenit(A) + ConvertMenit(B);
    return ConvertTime(total);
}

// Deskripsi: Menghitung selisih antara waktu A dan B. Jika hasil negatif, dianggap 0.
// I.S.: Dua waktu A dan B terdefinisi.
// F.S.: Menghasilkan waktu selisih A - B atau 0.
TimeInfo DifferenceTime(TimeInfo A, TimeInfo B) {
    int selisih = ConvertMenit(A) - ConvertMenit(B); 
    if (selisih < 0) selisih = 0;                
    return ConvertTime(selisih);
}

// Deskripsi: Fungsi untuk membandingkan dua waktu (A dan B) dan mengembalikan hasil perbandingan dalam bentuk int.
// I.S.: Dua waktu A dan B terdefinisi.
// F.S : Mengembalikan nilai -1, 1, atau 0
int CompareTime(TimeInfo A, TimeInfo B) {
    int a = ConvertMenit(A);
    int b = ConvertMenit(B);
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

// Deskripsi: Mengecek apakah new berada di luar rentang start dan end.
// I.S.: Tiga waktu terdefinisi.
// F.S.: true jika new < start atau new > end, false jika berada di tengah.
boolean CekBetweenTime(TimeInfo start, TimeInfo end, TimeInfo new) {
    int s = ConvertMenit(start);
    int e = ConvertMenit(end);
    int n = ConvertMenit(new);
    return (n < s || n > e); 
}

// Deskripsi: Fungsi ini mengubah data waktu TimeInfo menjadi format string
// I.S.: Waktu T dan memori buffer telah dialokasikan.
// F.S.: buffer berisi string dalam format "x jam y menit" sesuai nilai T.
void TimeString(TimeInfo T, char *buffer) {
    sprintf(buffer, "%d jam %d menit", T.jam, T.menit); 
}

// Deskripsi: Mencetak waktu T dalam format HH:MM.
// I.S.: T terdefinisi.
// F.S.: Waktu ditampilkan ke layar dalam format jam:menit.
void PrintTime(TimeInfo T) {
    printf("%02d:%02d\n", T.jam, T.menit);
}

// Deskripsi: Fungsi untuk mengecek apakah waktu sudah melewati tengah malam
// I.S.: start dan durasi terdefinisi
// F.S: Mengembalikan true jika hasil penjumlahan waktu melewati tengah malam (end.jam >= 24), false jika tidak.
boolean ApakahLewatTengahMalam(TimeInfo start, TimeInfo durasi) {
    TimeInfo end = TambahWaktu(start, durasi);
    return (end.jam >= 24);
}
