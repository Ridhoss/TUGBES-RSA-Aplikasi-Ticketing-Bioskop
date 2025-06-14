#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../date.h"


// Deskripsi: Membuat tanggal default (1 Januari 1900)
// I.S.: Variabel D belum diisi tanggal
// F.S.: Variabel D berisi tanggal 01/01/1900
void CreateDate (date * D){
  SetTgl(1, D);
  SetBln(1, D);
  SetThn(1900, D);
}

/******* Selector komponen **********/
/* Mengambil bagian Tgl dari date */
int GetTgl (date D){
	return(D.Tgl);
}

/* Mengambil bagian Bln dari date */
int GetBln (date D){
	return(D.Bln);
}

/* Mengambil bagian Thn dari date */
int GetThn (date D){
	return(D.Thn);
}

/****** Pengubah komponen ******/
/* Memberi nilai untuk Tgl */
void SetTgl (int NewTgl, date * D){
	(* D).Tgl = NewTgl;
}

/* Memberi nilai untuk Bln */
void SetBln (int NewBln, date * D){
	(* D).Bln = NewBln;
}

/* Memberi nilai untuk Thn */
void SetThn (int NewThn, date * D){
	(* D).Thn = NewThn;
}

// Deskripsi: Mengisi tanggal berdasarkan input parameter hari, bulan, dan tahun
// I.S.: Variabel D kosong atau berisi tanggal lama
// F.S.: D diisi dengan tanggal itgl/ibln/ithn. Jika tidak valid, tampil pesan error
void ReadDate (int itgl, int ibln, int ithn, date * D){
	SetTgl (itgl, &(* D));
	SetBln (ibln, &(* D));
	SetThn (ithn, &(* D));

	if(!isValidDate((* D))){
		printf("Tanggal tidak valid! Program Error.\n");
	}
}

// Deskripsi: Mengecek apakah tanggal valid (misal: 31 Februari tidak valid)
// I.S.: Tanggal D memiliki nilai
// F.S.: Mengembalikan true jika valid, false jika tidak
boolean isValidDate(date D){
	if ((GetThn(D) < 1900)||(GetThn(D) > 30000)||(GetBln(D) < 1) ||(GetBln(D) > 12)||(GetTgl(D) < 1)||(GetTgl(D) > getEndDate(D)))
		return (false);
	else
		return (true);
}

// Deskripsi: Menampilkan tanggal dalam format dd/mm/yyyy
// I.S.: Tanggal D berisi nilai tertentu
// F.S.: Tanggal ditampilkan di layar
void PrintObjDate(date D){
	printf ("%d/%d/%d\n", GetTgl(D), GetBln(D), GetThn(D));
}

// Deskripsi: Mengecek apakah tahun pada tanggal D adalah tahun kabisat
// I.S.: Tahun sudah diketahui
// F.S.: Mengembalikan true jika kabisat, false jika bukan
boolean isKabisat(date D) {
    int tahun = D.Thn;
    return (tahun % 4 == 0 && tahun % 100 != 0) || (tahun % 400 == 0);
}


// Deskripsi: Memberikan tanggal terakhir dari sebuah bulan 
// I.S.: Tanggal D sudah diketahui
// F.S.: Mengembalikan nilai 28-31 tergantung bulan dan kabisat
int getEndDate (date D){
	int bulan = GetBln(D);
	int tanggal = GetTgl(D);
	int bulangenap[4] = {4,6,9,11};
	int bulanganjil[7] = {1,3,5,7,8,10,12};

		if (bulan == 2)
		{
			if(isKabisat(D)){
				return 29;
			}else {
				return 28;
			}
		}else {
			for (int i = 0; i < 4; i++) {
				if (bulan == bulangenap[i])
				{
					return 30;
				}
			}

			for (int i = 0; i < 7; i++) {
				if (bulan == bulanganjil[i])
				{
					return 31;
				}	
			}
		}

	return 0;
}

// Deskripsi: Menampilkan tanggal sebelumnya dari sebuah Date
// I.S = Tanggal tertentu diketahui
// F.S = Tanggal sebelumnya diketahui
date DateBefore (date D){
	int tgl = GetTgl(D);
	int bln = GetBln(D);
	int thn = GetThn(D);
	date TglSementara, hasilTanggal;

	if(tgl == 1){
		if(bln == 1){
			tgl = 31;
			bln = 12;
			thn = thn - 1;
		}else {
			bln = bln - 1;
			ReadDate(1, bln, thn, &TglSementara);
			tgl = getEndDate(TglSementara);
		}
	}else {
		tgl = tgl - 1;
	}

	ReadDate(tgl, bln, thn, &hasilTanggal);

	return(hasilTanggal);
}

// Deskripsi: Menampilkan tanggal berikutnya dari sebuah Date
// I.S = Tanggal tertentu diketahui
// F.S = Tanggal berikutnya diketahui
date NextDate (date D){
	int tgl = GetTgl(D);
	int bln = GetBln(D);
	int thn = GetThn(D);
	date hasilTanggal;

	if(tgl == getEndDate(D) ){
		tgl = 1;
		if(bln == 12){
			bln = 1;
			thn = thn + 1;
		}else {
			bln = bln + 1;
		}
	}else {
		tgl = tgl + 1;
	}

	ReadDate(tgl, bln, thn, &hasilTanggal);

	return(hasilTanggal);
}

// Deskripsi: Menampilkan selisih dua tanggal
// I.S = 2 buah Tanggal tertentu diketahui
// F.S = Tampil selisih dua buah tanggal
// Asumsi : 1 tahun = 365 hari 
int DifferenceDate(date D1, date D2) {
    struct tm tm1 = {0}, tm2 = {0};
    tm1.tm_mday = D1.Tgl;
    tm1.tm_mon  = D1.Bln - 1;
    tm1.tm_year = D1.Thn - 1900;

    tm2.tm_mday = D2.Tgl;
    tm2.tm_mon  = D2.Bln - 1;
    tm2.tm_year = D2.Thn - 1900;

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    double diff = difftime(time2, time1);
    return (int)(diff / (60 * 60 * 24));
}

// Deskripsi: Mengambil tanggal hari ini dari sistem dan menyimpannya ke D
// I.S.: Variabel D kosong 
// F.S.: D berisi tanggal hari ini (tanggal saat program dijalankan)
void GetToday(date *D){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    SetTgl(tm.tm_mday, D);
    SetBln(tm.tm_mon + 1, D); // bulan dimulai dari 0 di struct tm
    SetThn(tm.tm_year + 1900, D); // tahun sejak 1900
}

date AddDays(date D, int n) {
    struct tm tmD = {0};
    tmD.tm_mday = D.Tgl + n;
    tmD.tm_mon = D.Bln - 1;
    tmD.tm_year = D.Thn - 1900;

    mktime(&tmD);

    date hasil;
    SetTgl(tmD.tm_mday, &hasil);
    SetBln(tmD.tm_mon + 1, &hasil);
    SetThn(tmD.tm_year + 1900, &hasil);
    return hasil;
}

// Deskripsi: Mengembalikan nama hari (Senin, Selasa, dst.) dari tanggal D
// I.S.: Tanggal D valid
// F.S.: Mengembalikan string nama hari dari tanggal tersebut
const char* NamaHari(date D) {
    struct tm waktu = {0};
    waktu.tm_mday = D.Tgl;
    waktu.tm_mon = D.Bln - 1;
    waktu.tm_year = D.Thn - 1900;
    mktime(&waktu);  // isi tm_wday

    const char *hari[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
    return hari[waktu.tm_wday];
}

// Deskripsi: Menambahkan sejumlah hari ke tanggal D
// I.S.: D adalah tanggal awal
// F.S.: Tanggal D bertambah sejumlah hariTambahan
date TambahHari(date D, int hariTambahan) {
    for (int i = 0; i < hariTambahan; i++) {
        D = NextDate(D);
    }
		
    return D;
}

// Deskripsi: Mengecek apakah dua tanggal yang sama 
// I.S.: Diketahui dua tanggal
// F.S.: Mengembalikan true jika hari, bulan, dan tahun sama
boolean isSameDate(date D1, date D2) {
    return (D1.Tgl == D2.Tgl && D1.Bln == D2.Bln && D1.Thn == D2.Thn);
}

// Deskripsi: Membandingkan dua tanggal
int CompareDate(date d1, date d2) {
    if (d1.Thn != d2.Thn) return d1.Thn - d2.Thn;
    if (d1.Bln != d2.Bln) return d1.Bln - d2.Bln;
    return d1.Tgl - d2.Tgl;
}

// Deskripsi: Mengecek apakah tanggal D adalah hari ini atau setelah hari ini
// I.S.: Tanggal D valid.
// F.S.: Mengembalikan true jika D hari ini
boolean IsDateLessToday(date D) {
    date today;
    GetToday(&today);

    if (D.Thn < today.Thn) return true;
    if (D.Thn > today.Thn) return false;

    if (D.Bln < today.Bln) return true;
    if (D.Bln > today.Bln) return false;

    return D.Tgl < today.Tgl;
}

// Deskripsi: Mengembalikan hari keberapa dalam seminggu (0 = Minggu, 6 = Sabtu)
// I.S.: Tanggal d valid
// F.S.: Mengembalikan indeks hari dalam minggu
int GetHariDalamMinggu(date d) {
    struct tm waktu = {0};
    waktu.tm_year = d.Thn - 1900;
    waktu.tm_mon = d.Bln - 1;
    waktu.tm_mday = d.Tgl;

    mktime(&waktu);
    return waktu.tm_wday;
}

// Deskripsi: Mengecek apakah tanggal d jatuh pada hari weekend
// I.S.: Tanggal d valid.
// F.S.: Mengembalikan true jika Sabtu atau Minggu, false jika hari biasa
boolean IsWeekend(date d) {
    int hari = GetHariDalamMinggu(d);
    return (hari == 0 || hari == 6);
}