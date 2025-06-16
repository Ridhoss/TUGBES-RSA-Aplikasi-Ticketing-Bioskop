#include "header/ADTList.h"
#include <stdio.h>
#include <stdlib.h>

// Deskripsi: Fungsi untuk mengecek apakah list kosong, yaitu jika First dan Last bernilai NULL.
// IS: List L terdefinisi
// FS: Mengembalikan true jika list kosong, false jika tidak
boolean ListEmpty(List L) {
    return L.First == NULL && L.Last == NULL;
}

// Deskripsi: Procedure untuk menginisialisasi list agar kosong dengan mengatur First dan Last ke NULL.
// IS: List L belum terinisialisasi
// FS: List L terinisialisasi menjadi kosong
void CreateList(List *L) {
    L->First = NULL;
    L->Last = NULL;
}

// Deskripsi: Procedure untuk memperbarui pointer Last pada list agar menunjuk ke elemen terakhir
// IS: List L mungkin berisi elemen, mungkin juga kosong.
// FS: Pointer Last menunjuk ke elemen terakhir jika list tidak kosong, atau NULL jika list kosong.
void UpdateLast(List *L) {
    if (L->First == NULL) {
        // List kosong
        L->Last = NULL;
    } else {
        addressList P = L->First;
        while (P->next != NULL) {
            P = P->next;
        }
        L->Last = P;
    }
}

// Deskripsi: Function untuk Mengalokasikan memori untuk elemen list baru, mengisi datanya dengan X, dan mengembalikan alamatnya.
// IS: X terdefinisi
// FS: Terbentuk elemen list baru berisi X, dan dialokasikan di memori.
addressList Allocation(infotype X) {
    addressList P = (addressList)malloc(sizeof(struct tElmtList));
    if (P != NULL) {
        P->info = X;
        P->next = NULL;
    }
    return P;
}

// Deskripsi: Procedure untuk membebaskan memori dari elemen list P, termasuk data di dalamnya.
// IS: Tersedia alamat elemen list P yang dialokasikan sebelumnya.
// FS: Memori elemen list dan isinya telah dibebaskan (dihapus dari heap).
void DeAllocation(addressList P) {
    free(P->info);
    free(P);
}

// Deskripsi: Mencari elemen list yang memiliki info sama dengan X, dan mengembalikan alamatnya.
// IS: List L terdefinisi dan data X sudah tersedia.
// FS: Didapatkan alamat elemen yang info-nya sama dengan X, atau NULL jika tidak ditemukan.
addressList SearchList(List L, infotype X) {
    addressList P = L.First;
    while (P != NULL && P->info != X) {
        P = P->next;
    }
    return P;
}

// Deskripsi: Function untuk mencari dan mengembalikan alamat precursor (sebelum) elemen yang memiliki nilai info sama dengan X
// IS: List L dan nilai X yang ingin dicari sudah tersedia.
// FS: Mengembalikan alamat elemen sebelum elemen yang info-nya sama dengan X, atau NULL jika tidak ditemukan atau berada di awal list.
addressList SearchPrec(List L, infotype X) {
    addressList P = L.First;
    addressList Prec = NULL;

    while (P != NULL && P->info != X) {
        Prec = P;
        P = P->next;
    }

    return (P != NULL) ? Prec : NULL;
}

// Deskripsi: Procedure untuk menambahkan elemen baru berisi X di akhir list.
// IS: List L mungkin kosong atau sudah berisi elemen, dan data X tersedia.
// FS: Data X ditambahkan sebagai elemen terakhir di list.
void InsLast(List *L, infotype X) {
    addressList P = Allocation(X);
    if (P != NULL) {
        if (ListEmpty(*L)) {
            L->First = P;
        } else {
            L->Last->next = P;
        }
        UpdateLast(L);
    }
}

// Deskripsi: Procedure untuk menghapus elemen yang info-nya sama dengan X dari list, jika ada.
// IS: List L terdefinisi dan data X sudah tersedia.
// FS: Jika elemen dengan nilai X ditemukan, elemen tersebut dihapus dari list.
void DelP(List *L, infotype X) {
    if (!ListEmpty(*L)) {
        addressList P = SearchList(*L, X);
        if (P != NULL) {
            addressList Prec = SearchPrec(*L, X);

            if (Prec == NULL) {
                // elemen di awal
                infotype dummy;
                DelFirst(L, &dummy);
            } else {
                Prec->next = P->next;
                DeAllocation(P);
            }
        }

        UpdateLast(L);
    }
}

// Deskripsi: Procedure untuk menghapus semua elemen dari list hingga kosong. 
// IS: List L berisi nol atau lebih elemen.
// LS: List L menjadi kosong, seluruh elemen telah dihapus dari memori.
void DelAll(List *L) {
    infotype temp;
    while (!ListEmpty(*L)) {
        DelFirst(L, &temp);
    }

    UpdateLast(L);
}

// Deskripsi: Procedure untuk menampilkan seluruh isi elemen list dalam format 
// IS: List L sudah terdefinisi, bisa kosong atau berisi elemen.
// FS: Isi L ditampilkan ke layar dalam format list
void PrintInfo(List L) {
    addressList P = L.First;
    printf("[");
    while (P != NULL) {
        printf("%d", P->info);
        if (P->next != NULL) {
            printf(", ");
        }
        P = P->next;
    }
    printf("]\n");
}


// opsional (dipertimbangkan)

// Deskripsi: Procedure untuk menambahkan elemen baru berisi X di awal list.
// IS: List L bisa kosong atau sudah terisi, dan data X sudah tersedia.
// FS: Sebuah elemen baru berisi X ditambahkan sebagai elemen pertama list.
void InsFirst(List *L, infotype X) {
    addressList P = Allocation(X);
    if (P != NULL) {
        P->next = L->First;
        L->First = P;

        UpdateLast(L);
    }

}

// Deskripsi: Procedure untuk menyisipkan elemen baru berisi X setelah elemen Prec dalam list L.
// IS: List L sudah terdefinisi, Prec menunjuk ke elemen yang valid, dan data X tersedia.
// FS: Elemen baru berisi X disisipkan setelah Prec di dalam list.
void InsertAfter(List *L, infotype X, addressList Prec) {
    if (Prec != NULL) {
        addressList P = Allocation(X);
        if (P != NULL) {
            P->next = Prec->next;
            Prec->next = P;
        }

        UpdateLast(L);
    }
}

// Deskripsi: Procedure untuk menghapus elemen pertama dari list L dan menyimpan nilainya ke variabel X.
// IS: List L tidak kosong
// FS: Elemen pertama list dihapus dan nilainya disimpan ke *X
void DelFirst(List *L, infotype *X) {
    if (!ListEmpty(*L)) {
        addressList P = L->First;
        *X = P->info;
        L->First = P->next;
        DeAllocation(P);

        UpdateLast(L);
    }
}

// Deskripsi: Procedure untuk menghapus elemen terakhir dari list L dan menyimpan nilainya ke *X.
// IS: List L tidak kosong
// FS: Elemen terakhir list dihapus dan nilainya disimpan ke variabel *X.
void DelLast(List *L, infotype *X) {
    if (!ListEmpty(*L)) {
        addressList P = L->First;
        addressList Prec = NULL;

        while (P->next != NULL) {
            Prec = P;
            P = P->next;
        }

        *X = P->info;

        if (Prec == NULL) {
            L->First = NULL;
        } else {
            Prec->next = NULL;
        }
        DeAllocation(P);

        UpdateLast(L);
    }
}