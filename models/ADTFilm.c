#include "header/ADTFilm.h"
#include "header/ADTList.h"
#include "header/ADTAkun.h"
#include "header/ADTJadwal.h"
#include "header/ADTTeater.h"
#include "header/ADTBioskop.h"
#include "header/ADTTree.h"
#include "../library/date.h"

const char *films = "database/film.txt";

// Deskripsi: Untuk mengalokasikan memori film
// I.S.: menerima data film
// F.S.: mengembalikan pointer ke hasil alokasi FilmInfo
FilmInfo* alokasiFilm(FilmInfo data) {
    FilmInfo* f = (FilmInfo*)malloc(sizeof(FilmInfo));
    if (f != NULL) {
        *f = data;
    }
    return f;
}

// Deskripsi: Untuk menghapus alokasi memori film
// I.S.: memori film telah dialokasikan
// F.S.: memori dihapus dengan free()
void dealokasiFilm(FilmInfo* f) {
    free(f);
}

// Deskripsi: Untuk membaca dan memuat data film dari file
// I.S.: file tersedia
// F.S.: L terisi semua data FilmInfo dari file.
void loadFilm(List* L, const char* filename) {
    printf("Trying to open: %s\n", filename);
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Gagal membuka file");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        FilmInfo data;
        buffer[strcspn(buffer, "\n")] = 0;

        if (sscanf(buffer, "%d|%99[^|]|%99[^|]|%99[^|]|%d|%d",
                   &data.idFilm,
                   data.judul,
                   data.produser,
                   data.deskripsi,
                   &data.durasi.jam,
                   &data.durasi.menit) == 6) {
            
            FilmInfo* filmPtr = alokasiFilm(data);
            if (filmPtr) {
                InsLast(L, filmPtr);
            } else {
                printf(" → Gagal alokasi memori untuk film ID %d\n", data.idFilm);
            }

        } else {
            printf(" → Format tidak valid: %s\n", buffer);
        }
    }

    fclose(file);
}

// Deskripsi: Menambahkan  film ke dalam list
// I.S.: List telah didefinisikan
// F.S.: Film ditambahkan ke List
void TambahFilm(List* L, FilmInfo filmBaru) {
    FilmInfo* node = alokasiFilm(filmBaru);
    if (node == NULL) {
        printf("Gagal mengalokasikan node Film.\n");
        return;
    }

    InsLast(L, node);
    printf("Film '%s' berhasil ditambahkan ke list.\n", filmBaru.judul);
}

// Deskripsi: Menambahkan film baru yang ditambahkan ke List
// I.S.: List Film tersedia
// F.S.: Film ditambahkan ke akhir list
void TambahFilmBaru(List* L, FilmInfo filmBaru) {
    filmBaru.idFilm = get_last_film_id(films) + 1;
    TambahFilm(L, filmBaru);
    simpanKeFile(*L, films);
}

// Deskripsi: Mengedit data film yang sudah ada
// I.S.: filmLama tersedia 
// F.S.: Data film diperbarui 
void editFilmByName(FilmInfo filmBaru, addressList filmLama) {
    if (filmLama == NULL) return;

    FilmInfo* film = (FilmInfo*)(filmLama->info);

    // Hanya ubah jika data baru tidak kosong
    if (strlen(filmBaru.judul) > 0)
        strcpy(film->judul, filmBaru.judul);

    if (strlen(filmBaru.produser) > 0)
        strcpy(film->produser, filmBaru.produser);

    if (strlen(filmBaru.deskripsi) > 0)
        strcpy(film->deskripsi, filmBaru.deskripsi);

    if (filmBaru.durasi.jam >= 0)
        film->durasi.jam = filmBaru.durasi.jam;

    if (filmBaru.durasi.menit >= 0 && filmBaru.durasi.menit < 60)
        film->durasi.menit = filmBaru.durasi.menit;
}

// Deskripsi: Menghapus film berdasarkan ID
// I.S.: ID tersedia di list 
// F.S.: film dengan ID tsb dihapus
void hapusFilm(List* L, int id) {
    addressList filmNode = cariFilm(*L, id);
    if (filmNode != NULL) {
        DelP(L, filmNode->info);  // Hapus berdasarkan info-nya
        simpanKeFile(*L, films);
        printf("Film dengan ID %d berhasil dihapus.\n", id);
    } else {
        printf("Film dengan ID %d tidak ditemukan.\n", id);
    }
}

// Deskripsi: Menyimpan seluruh data film dari list ke file
// I.S.: List film tersedia
// F.S.: file berisi seluruh data film
void simpanKeFile(List L, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Gagal membuka file");
        return;
    }

    int current_id = get_last_film_id(films);

    for (addressList P = L.First; P != NULL; P = P->next) {
        FilmInfo* film = (FilmInfo*)(P->info);

        if (film->idFilm == 0) {
            film->idFilm = ++current_id;
        }

        fprintf(file, "%d|%s|%s|%s|%d|%d\n",
                film->idFilm,
                film->judul,
                film->produser,
                film->deskripsi,
                film->durasi.jam,
                film->durasi.menit);
    }

    fclose(file);
}

// Deskripsi: Mengambil ID film terbesar dari file
// I.S.: file tersedia
// F.S.: mengembalikan ID film terakhir yang ada di file
int get_last_film_id(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return 0; 

    int last_id = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        int temp_id;
        if (sscanf(line, "%d|", &temp_id) == 1) {
            if (temp_id > last_id) {
                last_id = temp_id;
            }
        }
    }

    fclose(file);
    return last_id;
}

// Deskripsi: Mencari node film berdasarkan ID
// I.S.: List berisi film
// F.S.: node film dengan ID dikembalikan sesuai dengan yang dicari
addressList cariFilm(List L, int id) {
    addressList P = L.First;
    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
        if (film->idFilm == id) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

// Deskripsi: Mencari node film berdasarkan judul.
// I.S.: List terisi
// F.S.: node film dengan judul yang dicari
addressList cariFilmByJudul(List L, const char* title) {
    addressList P = L.First;

    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
        if (strcmp(film->judul, title) == 0) {
            return P;
        }
        P = P->next;
    }

    return NULL;
}

// Deskripsi: Menampilkan seluruh film dari list
// I.S.: list film berisi data film
// F.S.: semua film pada list ditampilkan ke layar
void printFilm(List L) {
    addressList P = L.First;
    if (P == NULL) {
        printf("Film tidak tersedia!\n");
        return;
    }

    while (P != NULL) {
        FilmInfo* film = (FilmInfo*)(P->info);
            printf("===================================================\n");
            printf("Judul      : %s\n", film->judul);
            printf("Produser   : %s\n", film->produser);
            printf("Deskripsi  : %s\n", film->deskripsi);
            printf("Durasi     : %d\n", ConvertMenit(film->durasi));

        P = P->next;
    }
}

// Deskripsi: Mengisi list dengan film yang tayang di suatu kota
// I.S.: kota memiliki node dan jadwal
// F.S.: LIstFilmKota berisi film yang tayang
void GetFilmByKota(address KotaNode, List *ListFilmKota) {
    CreateList(ListFilmKota);

    List listJadwal;
    AmbilSeluruhJadwalKotaKeList(KotaNode, &listJadwal);

    date today;
    GetToday(&today);

    addressList p = listJadwal.First;
    while (p != NULL) {
        address nodeJadwal = (address)p->info;

        if (nodeJadwal != NULL && nodeJadwal->info != NULL) {
            JadwalInfo* jadwal = (JadwalInfo*) nodeJadwal->info;

            if (jadwal->film != NULL && !ApakahFilmSudahAda(*ListFilmKota, jadwal->film) && !IsDateLessToday(jadwal->tanggal)) {
                FilmInfo* salinanFilm = (FilmInfo*) malloc(sizeof(FilmInfo));
                if (salinanFilm != NULL) {
                    *salinanFilm = *(jadwal->film);
                    InsLast(ListFilmKota, (infotype)salinanFilm);
                }
            }
        }

        p = p->next;
    }

    DelAll(&listJadwal);
}

// Deskripsi: Mengecek apakah film sudah ada dalam list
// I.S.: L berisi daftar film
// F.S.: mengembalikan true jika film sudah ada dalam list
boolean ApakahFilmSudahAda(List L, FilmInfo* target) {
    addressList P = L.First;
    while (P != NULL) {
        FilmInfo* f = (FilmInfo*)P->info;
        if (strcmp(f->judul, target->judul) == 0) {
            return true;
        }
        P = P->next;
    }
    return false;
}

// Deskripsi: Mengambil daftar film yang belum tayang hari ini.
// I.S.: kota memiliki data jadwal
// F.S.: ListFilmKota berisi film yang belum tayang hari ini
void GetFilmUpcoming(address KotaNode, List *ListFilmKota) {
    CreateList(ListFilmKota);

    List listJadwal;
    AmbilSeluruhJadwalKotaKeList(KotaNode, &listJadwal);

    date today;
    GetToday(&today);

    TimeInfo now;
    GetTime(&now);

    List filmMasihAkanTayang;
    CreateList(&filmMasihAkanTayang);

    List filmSudahPernahTayang;
    CreateList(&filmSudahPernahTayang);

    addressList p = listJadwal.First;
    while (p != NULL) {
        address nodeJadwal = (address)p->info;
        if (nodeJadwal != NULL && nodeJadwal->info != NULL) {
            JadwalInfo* jadwal = (JadwalInfo*)nodeJadwal->info;
            if (jadwal->film != NULL) {
                boolean sudahTayang = false;
                boolean akanTayang = false;

                // Cek status jadwal
                if (IsDateLessToday(jadwal->tanggal)) {
                    sudahTayang = true;
                } else if (isSameDate(jadwal->tanggal, today)) {
                    if (CompareTime(jadwal->Start, now) <= 0) {
                        sudahTayang = true;
                    } else {
                        akanTayang = true;
                    }
                } else {
                    akanTayang = true;
                }

                if (sudahTayang && !ApakahFilmSudahAda(filmSudahPernahTayang, jadwal->film)) {
                    FilmInfo* salinan = (FilmInfo*)malloc(sizeof(FilmInfo));
                    *salinan = *(jadwal->film);
                    InsLast(&filmSudahPernahTayang, (infotype)salinan);
                }

                if (akanTayang && !ApakahFilmSudahAda(filmMasihAkanTayang, jadwal->film)) {
                    FilmInfo* salinan = (FilmInfo*)malloc(sizeof(FilmInfo));
                    *salinan = *(jadwal->film);
                    InsLast(&filmMasihAkanTayang, (infotype)salinan);
                }
            }
        }

        p = p->next;
    }

    // Masukkan ke ListFilmKota hanya film yang belum pernah tayang sama sekali
    addressList f = filmMasihAkanTayang.First;
    while (f != NULL) {
        FilmInfo* film = (FilmInfo*)f->info;

        if (!ApakahFilmSudahAda(filmSudahPernahTayang, film)) {
            FilmInfo* salinan = (FilmInfo*)malloc(sizeof(FilmInfo));
            *salinan = *film;
            InsLast(ListFilmKota, (infotype)salinan);
        }

        f = f->next;
    }

    DelAll(&listJadwal);
    DelAll(&filmSudahPernahTayang);
    DelAll(&filmMasihAkanTayang);
}

// Deskripsi: Mencari tanggal tayang pertama dari sebuah film.
// I.S.: Kota memiliki data film & jadwal
// F.S.: Dikembalikan tanggal tayang terawal (setelah hari ini)
date CariTanggalTayangPertama(address kotaNode, FilmInfo* film) {
    List listJadwal;
    AmbilSeluruhJadwalKotaKeList(kotaNode, &listJadwal);

    date hasil = {-1, -1, -1};
    bool pertama = true;

    addressList p = listJadwal.First;
    date hariIni;
    GetToday(&hariIni);

    while (p != NULL) {
        JadwalInfo* jadwal = (JadwalInfo*)((address)p->info)->info;
        if (jadwal->film == film && CompareDate(jadwal->tanggal, hariIni) > 0) {
            if (pertama || CompareDate(jadwal->tanggal, hasil) < 0) {
                hasil = jadwal->tanggal;
                pertama = false;
            }
        }
        p = p->next;
    }

    DelAll(&listJadwal);
    return hasil;
}

// Deskripsi: Mengambil daftar film sesuai tanggal dan jam tayang
// I.S.: Data kota dan waktu pencarian tersedia
// F.S.: ListFilm berisi film yang tayang dalam range waktu tertentu
void GetFilmByRangeWaktu(address kotaNode, date selectedDate, TimeInfo jamAwal, TimeInfo jamAkhir, List *ListFilm) {
    if (kotaNode == NULL || ListFilm == NULL) return;

    CreateList(ListFilm);

    List listJadwal;
    AmbilSeluruhJadwalKotaKeList(kotaNode, &listJadwal);

    List semuaFilm;
    CreateList(&semuaFilm);

    addressList p = listJadwal.First;
    while (p != NULL) {
        address nodeJadwal = (address)p->info;
        if (nodeJadwal != NULL && nodeJadwal->info != NULL) {
            JadwalInfo* jadwal = (JadwalInfo*) nodeJadwal->info;
            if (jadwal->film != NULL) {

                if (isSameDate(jadwal->tanggal, selectedDate) &&
                    CompareTime(jadwal->Start, jamAwal) >= 0 &&
                    CompareTime(jadwal->Start, jamAkhir) <= 0) {
                    
                    if (!ApakahFilmSudahAda(semuaFilm, jadwal->film)) {
                        FilmInfo* salinan = (FilmInfo*) malloc(sizeof(FilmInfo));
                        if (salinan != NULL) {
                            *salinan = *(jadwal->film);
                            InsLast(&semuaFilm, (infotype)salinan);
                        }
                    }
                }
            }
        }
        p = p->next;
    }

    addressList f = semuaFilm.First;
    while (f != NULL) {
        FilmInfo* film = (FilmInfo*) f->info;
        FilmInfo* salinanFinal = (FilmInfo*) malloc(sizeof(FilmInfo));
        if (salinanFinal != NULL) {
            *salinanFinal = *film;
            InsLast(ListFilm, (infotype)salinanFinal);
        }
        f = f->next;
    }

    DelAll(&listJadwal);
    DelAll(&semuaFilm);
}



