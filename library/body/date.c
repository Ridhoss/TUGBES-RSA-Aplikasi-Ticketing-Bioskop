/* File        : date.c */
/* Deskripsi   : Unit untuk keperluan ADT Date */

/***************************/
/*  BODY PRIMITIF DATE     */
/***************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../date.h"


/*********** Operasi Primitif ************/
/* Constructor Membentuk sebuah DATE, dengan nilai default adalah 01/01/1900 */
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


/****** Kelompok Interaksi dengan I/O device, BACA/TULIS ******/
/* Membentuk DATE dari iTgl, iBln dan iThn yang dibaca dari keyboard */
void ReadDate (int itgl,int ibln, int ithn, date * D){
	SetTgl (itgl, &(* D));
	SetBln (ibln, &(* D));
	SetThn (ithn, &(* D));

	if(!isValid((* D))){
		printf("Tanggal tidak valid! Program Error.\n");
		exit(1);
	}
}

/* Memeriksa apakah suatu tanggal valid, yaitu dengan memperhatikan batas akhir per bulan */
boolean isValid(date D){
	if ((GetThn(D) < 1900)||(GetThn(D) > 30000)||(GetBln(D) < 1) ||(GetBln(D) > 12)||(GetTgl(D) < 1)||(GetTgl(D) > getEndDate(D)))
		return (false);
	else
		return (true);
}

/* Print nilai D dengan format dd/mm/yyyy */
void PrintObj (date D){
	printf ("%d/%d/%d\n", GetTgl(D), GetBln(D), GetThn(D));
}

/****** Operator Relasional ******/
/* Memeriksa apakah suatu tanggal adalah kabisat; Dipakai untuk bulan == 2 saja
Harusnya kabisat adalah thn yang habis dibagi 4, atau habis dibagi 100 dan 400, tapi implementasinya seringkali hanya menggunakan 4 sebagai pembagi */
boolean isKabisat(date D) {
    int tahun = D.Thn;
    return (tahun % 4 == 0 && tahun % 100 != 0) || (tahun % 400 == 0);
}

/***** Predikat lain *******/

/* Memberikan tanggal terakhir dari sebuah bulan */
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


/* Menampilkan tanggal sebelumnya dari sebuah Date
	I.S = Tanggal tertentu diketahui
	F.S = Tanggal sebelumnya diketahui
	Hal yang perlu diketahui : Batas akhir tiap bulan dan jika jan, thn-1 */
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

/* Menampilkan tanggal berikutnya dari sebuah Date
	I.S = Tanggal tertentu diketahui
	F.S = Tanggal berikutnya diketahui
	Hal yang perlu diketahui : Batas akhir tiap bulan dan jika des, thn+1 */
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

/* Menampilkan selisih dua tanggal
	I.S = 2 buah Tanggal tertentu diketahui
	F.S = Tampil selisih dua buah tanggal
	Asumsi : 1 tahun = 365 hari */
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

const char* NamaHari(date D) {
    struct tm waktu = {0};
    waktu.tm_mday = D.Tgl;
    waktu.tm_mon = D.Bln - 1;
    waktu.tm_year = D.Thn - 1900;
    mktime(&waktu);  // isi tm_wday

    const char *hari[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
    return hari[waktu.tm_wday];
}
