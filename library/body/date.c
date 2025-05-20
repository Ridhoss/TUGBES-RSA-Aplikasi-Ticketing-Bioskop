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
	SetTgl (01, &(* D));
	SetBln (01, &(* D));
	SetThn (1900, &(* D));
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
boolean isKabisat (date D){
	int tahun = GetThn(D);
	if (tahun % 4 == 0){
		return true;
	}else {
		return false;
	}
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
}


/* Menampilkan tanggal sebelumnya dari sebuah Date
	I.S = Tanggal tertentu diketahui
	F.S = Tanggal sebelumnya diketahui
	Hal yang perlu diketahui : Batas akhir tiap bulan dan jika jan, thn-1 */
void DateBefore (date D){
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

	printf("\nMenggunakan perintah DateBefore(D2), Sebelum tanggal : ");
	PrintObj(D);
	printf("Adalah tanggal : ");
	PrintObj(hasilTanggal);

}

/* Menampilkan tanggal berikutnya dari sebuah Date
	I.S = Tanggal tertentu diketahui
	F.S = Tanggal berikutnya diketahui
	Hal yang perlu diketahui : Batas akhir tiap bulan dan jika des, thn+1 */
void NextDate (date D){
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

	printf("\nMenggunakan perintah NextDate(D2), Sesudah tanggal : ");
	PrintObj(D);
	printf("Adalah tanggal : ");
	PrintObj(hasilTanggal);
}

/* Menampilkan selisih dua tanggal
	I.S = 2 buah Tanggal tertentu diketahui
	F.S = Tampil selisih dua buah tanggal
	Asumsi : 1 tahun = 365 hari */
void DifferenceDate (date D1, date D2){
	int thnD1 = GetThn(D1);
	int thnD2 = GetThn(D2);
	int tglD1 = GetTgl(D1);
	int tglD2 = GetTgl(D2);
	int selTahun, totalHari1, totalHari2;

	totalHari1 = (thnD1 * 365) + tglD1;
	totalHari2 = (thnD2 * 365) + tglD2;

	selTahun = abs(totalHari2 - totalHari1);

	printf("\nMenggunakan Perintah DifferenceDate(D3), Selisih antara ");
	PrintObj(D1);
	printf("dan ");
	PrintObj(D2);
	printf("adalah %d hari", selTahun);

}

void GetToday(date *D){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    SetTgl(tm.tm_mday, D);
    SetBln(tm.tm_mon + 1, D); // bulan dimulai dari 0 di struct tm
    SetThn(tm.tm_year + 1900, D); // tahun sejak 1900
}

