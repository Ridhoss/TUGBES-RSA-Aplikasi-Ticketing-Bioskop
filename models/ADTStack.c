#include "header/ADTStack.h"

// Deskripsi: Prosedur untuk membuat stack kosong dengan menginisialisasi list
// I.S.: Stack belum terdefinisi atau belum diinisialisasi
// F.S.: Stack S terinisialisasi sebagai list kosong
void CreateStack(Stack *S) {
    CreateList(S);
}
// Deskripsi: Fungsi untuk mengecek apakah stack kosong
// I.S.: Stack S terdefinisi
// F.S.: Mengembalikan true jika stack kosong, false jika tidak
boolean IsEmptyStack(Stack S) {
    return ListEmpty(S);
}

// Deskripsi: Prosedur untuk menambahkan data sebagai elemen stack S (ditambahkan ke paling depan)
// IS : S mungkin kosong
// FS : data menjadi elemen teratas (First) yang baru 
void Push(Stack* S, infotype data) {
    InsFirst(S, data);
}

// Deskripsi: Fungsi untuk menghapus elemen teratas dari Stack S dan mengembalikannya 
// IS : S tidak kosong 
// FS : Elemen TOP dihapus dari Stack dan nilainya dikembalikan 
void* Pop(Stack* S) {
    infotype temp;
    DelFirst(S, &temp);
    return temp;
}

// Deskripsi: Fungsi untuk mengambil elemen teratas dari Stack S tanpa menghapusnya
// IS : S terdefinisi (mungkin kosong) 
// FS : Mengembalikan nilai elemen TOP jika ada, NULL jika Stack kosong
void* Top(Stack S) {
    if (S.First != NULL) {
        return S.First->info;
    }
    return NULL;
}
