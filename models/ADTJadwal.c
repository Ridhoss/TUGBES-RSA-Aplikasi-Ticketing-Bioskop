#include "header/ADTJadwal.h"

// modul-modul operasi file

// Deskripsi : Prosedur untuk menyimpan data jadwal ke file
// IS : menerima pointer ke JadwalInfo
// FS : menyimpan id kota, film, teater, dan bioskop serta informasi jadwal ke dalam file "database/jadwal.txt"
void SimpanJadwalKeFile(const int* idKota, const int* idBioskop, const int* idTeater, const JadwalInfo* jadwal) {
    FILE* file = fopen("database/jadwal.txt", "a");
    if (file != NULL) {
        fprintf(
            file, "%d|%d|%d|%d|%d/%d/%d|%02d:%02d|%02d:%02d|%d|\n", 
            jadwal->id, 
            *idKota, 
            *idBioskop, 
            *idTeater, 
            jadwal->tanggal.Tgl, jadwal->tanggal.Bln, jadwal->tanggal.Thn,
            jadwal->Start.jam, jadwal->Start.menit,
            jadwal->End.jam, jadwal->End.menit,
            jadwal->film->idFilm
        );
        fclose(file); 
    } else {
        printf("Gagal menyimpan teater ke file.\n");
    }
}

// Deskripsi : fungsi untuk mencari jadwal dalam file
// IS : menerima informasi jadwal  
// FS : mengembalikan 1 jika jadwal ditemukan, 0 jika tidak ditemukan
int SearchJadwalFile(const JadwalInfo* jadwal) {
    FILE* file = fopen("database/jadwal.txt", "r");
    if (!file) return 0;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        int id, idKota, idBioskop, idTeater, idFilm;
        TimeInfo start, end;
        date tanggal;

        int readData = sscanf(
            buffer, "%d|%d|%d|%d|%d/%d/%d|%d:%d|%d:%d|%d|",
            &id, &idKota, &idBioskop, &idTeater,
            &tanggal.Tgl, &tanggal.Bln, &tanggal.Thn,
            &start.jam, &start.menit,
            &end.jam, &end.menit,
            &idFilm
        );

        if (readData == 12) {
            if (id == jadwal->id) {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

// Deskripsi : Prosedur untuk mengedit info jadwal dalam file
// IS : menerima info lama dan info baru
// FS : mengubah info jadwal dalam file "database/jadwal.txt"
void EditJadwalKeFile(const JadwalInfo* jadwal, const JadwalInfo* jadwalLama) {
    if (!SearchJadwalFile(jadwalLama)) {
        printf("Jadwal %d:%d tidak ditemukan. Tidak dapat melakukan edit.\n", jadwalLama->Start.jam, jadwalLama->Start.menit);
        return;
    }

    FILE* file = fopen("database/jadwal.txt", "r");
    FILE* temp = fopen("database/temp.txt", "w");
    if (!file || !temp) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        int id, idKota, idBioskop, idTeater, idFilm;
        TimeInfo start, end;
        date tanggal;

        sscanf(
            buffer, "%d|%d|%d|%d|%d/%d/%d|%d:%d|%d:%d|%d|",
            &id, &idKota, &idBioskop, &idTeater,
            &tanggal.Tgl, &tanggal.Bln, &tanggal.Thn,
            &start.jam, &start.menit,
            &end.jam, &end.menit,
            &idFilm
        );

        if (id == jadwalLama->id) {

            fprintf(
                temp, "%d|%d|%d|%d|%d/%d/%d|%02d:%02d|%02d:%02d|%d|\n", 
                id, 
                idKota, 
                idBioskop, 
                idTeater, 
                jadwal->tanggal.Tgl, jadwal->tanggal.Bln, jadwal->tanggal.Thn,
                jadwal->Start.jam, jadwal->Start.menit,
                jadwal->End.jam, jadwal->End.menit,
                jadwal->film->idFilm
            );
        } else {
            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);

    remove("database/jadwal.txt");
    rename("database/temp.txt", "database/jadwal.txt");

    printf("Jadwal berhasil dirubah di file\n");
}

// Deskripsi : Prosedur untuk menghapus jadwal dari file
// IS : menerima info jadwal
// FS : menghapus info jadwal dari file "database/jadwal.txt"
void HapusJadwalKeFile(const JadwalInfo* jadwalLama) {
    if (!SearchJadwalFile(jadwalLama)) {
        printf("Jadwal %d:%d tidak ditemukan. Tidak dapat melakukan edit.\n", jadwalLama->Start.jam, jadwalLama->Start.menit);
        return;
    }

    FILE* file = fopen("database/jadwal.txt", "r");
    FILE* temp = fopen("database/temp.txt", "w");
    if (!file || !temp) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        int id, idKota, idBioskop, idTeater, idFilm;
        TimeInfo start, end;
        date tanggal;

        sscanf(
            buffer, "%d|%d|%d|%d|%d/%d/%d|%d:%d|%d:%d|%d|",
            &id, &idKota, &idBioskop, &idTeater,
            &tanggal.Tgl, &tanggal.Bln, &tanggal.Thn,
            &start.jam, &start.menit,
            &end.jam, &end.menit,
            &idFilm
        );

        if (id != jadwalLama->id) {

            fprintf(temp, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(temp);

    remove("database/jadwal.txt");
    rename("database/temp.txt", "database/jadwal.txt");

    printf("Jadwal berhasil di hapus dari file\n");
}

// Deskripsi : Prosedur untuk mengosongkan file jadwal.txt
// IS : membuka file "database/jadwal.txt" dalam mode tulis
// FS : mengosongkan isi file
void KosongkanFileJadwal() {
    FILE* file = fopen("database/jadwal.txt", "w");
    if (file != NULL) {
        fclose(file);
        printf("File jadwal.txt berhasil dikosongkan.\n");
    } else {
        printf("Gagal mengosongkan file jadwal.txt.\n");
    }
}

// Deskripsi : Prosedur untuk memuat data jadwal dari file
// IS : membuka file "database/jadwal.txt" dalam mode baca
// FS : membaca setiap baris dari file dan menambahkannya ke tree
void LoadJadwal(address root, List ListFilm) {
    FILE* file = fopen("database/jadwal.txt", "r");
    if (!file) {
        printf("File jadwal.txt tidak ditemukan atau gagal dibuka.\n");
        return;
    }

    JadwalInfo jadwal;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        int id, idKota, idBioskop, idTeater, idFilm;
        TimeInfo start, end;
        date tanggal;

        int readData = sscanf(
            buffer, "%d|%d|%d|%d|%d/%d/%d|%d:%d|%d:%d|%d|",
            &id, &idKota, &idBioskop, &idTeater,
            &tanggal.Tgl, &tanggal.Bln, &tanggal.Thn,
            &start.jam, &start.menit,
            &end.jam, &end.menit,
            &idFilm
        );

        if (readData == 12) {
            address kota = SearchKotaById(root, &idKota);
            if (kota != NULL) {
                address bioskop = SearchBioskopById(kota, &idBioskop);
                if (bioskop != NULL) {
                    address teater = SearchTeaterById(kota, &idTeater);
                    if(teater != NULL){
                        jadwal.id = id;
                        jadwal.Start = start;
                        jadwal.End = end;
                        jadwal.tanggal = tanggal;

                        addressList filmTerpilih = cariFilm(ListFilm, idFilm);
                        FilmInfo* film = (FilmInfo*)(filmTerpilih->info);

                        jadwal.film = film;
                        
                        TambahJadwal(teater, jadwal);
                    }
                }
            }
        }
    }

    fclose(file);
}

// Deskripsi : Prosedur untuk mengambil id terakhir dari data file
// IS : membuka file "database/jadwal.txt" dalam mode baca
// FS : membaca setiap baris dari file dan mencari id paling besar
int AmbilIdJadwalTerakhir() {
    FILE* file = fopen("database/jadwal.txt", "r");
    if (file == NULL) {
        return 0;
    }

    int idTerakhir = 0;
    char buffer[200];

    while (fgets(buffer, sizeof(buffer), file)) {
        char* idStr = strtok(buffer, "|");

        if (idStr)
        {
            int idSementara = atoi(idStr);
            if (idSementara > idTerakhir) {
                idTerakhir = idSementara;
            }
        } 
    }

    fclose(file);
    return idTerakhir;
}








// modul utama

// Deskripsi : Fungsi untuk Alokasi memori JadwalInfo
// IS : menerima JadwalInfo X
// FS : mengembalikan address baru yang berisi alokasi memori untuk JadwalInfo
address AlokasiJadwal(JadwalInfo X){
    JadwalInfo* info = (JadwalInfo*) malloc(sizeof(JadwalInfo));
    if (info) {
        *info = X;
        return Alokasi((infotype)info, JADWAL);
    }

    return NULL;
}

// Deskripsi : Prosedur untuk Dealokasi memori JadwalInfo
// IS : menerima address P yang berisi JadwalInfo
// FS : menghapus alokasi memori JadwalInfo yang ada pada address P
void DeAlokasiJadwal(address P) {
    if (P != NULL) {
        free(P->info);
        Dealokasi(P);
    }
}

// Deskripsi : Prosedur untuk menambah Jadwal ke dalam teater
// IS : menerima address teater dan info Jadwal serta info film
// FS : menambah node baru Jadwal menjadi anak dari node teater dalam tree
void TambahJadwal(address teater, JadwalInfo jadwalBaru) {
    if (teater == NULL) return;

    address node = AlokasiJadwal(jadwalBaru);
    if (node == NULL) {
        printf("Gagal mengalokasikan node Jadwal.\n");
        return;
    }

    InisialisasiKursi((JadwalInfo*) node->info, teater);

    AddChild(teater, node->info, JADWAL);
    
    printf("Jadwal berhasil ditambahkan.\n");
}

// Deskripsi : Prosedur untuk menambah jadwal baru dan menyimpannya ke file
// IS : menerima address kota dan bioskop serta info jadwal dan info film
// FS : node jadwal ditambahkan ke tree sebagai anak dari node teater, lalu disimpan ke file
void TambahJadwalBaru(address kota, address bioskop, address teater, JadwalInfo dataJadwal, int jmlHari) {
    KotaInfo* kInfo = (KotaInfo*) kota->info;
    BioskopInfo* bInfo = (BioskopInfo*) bioskop->info;
    TeaterInfo* tInfo = (TeaterInfo*) teater->info;

    if (dataJadwal.film == NULL) {
        printf("Film tidak valid. Gagal menambahkan semua jadwal.\n");
        return;
    }

    List listJadwal;
    AmbilJadwalTeaterKeList(teater, &listJadwal);

    for (int i = 0; i < jmlHari; i++) {
        JadwalInfo jadwalBaru = dataJadwal;

        jadwalBaru.id = AmbilIdJadwalTerakhir() + 1;
        jadwalBaru.tanggal = TambahHari(dataJadwal.tanggal, i);
        jadwalBaru.End = TambahWaktu(jadwalBaru.Start, jadwalBaru.film->durasi);

        if (AdaJadwalBentrok(listJadwal, jadwalBaru.tanggal, jadwalBaru.Start, jadwalBaru.End, jadwalBaru.id)) {
            printf("Jadwal gagal ditambahkan untuk tanggal %d/%d/%d karena bentrok.\n", jadwalBaru.tanggal.Tgl, jadwalBaru.tanggal.Bln, jadwalBaru.tanggal.Thn);

            continue;
        }

        TambahJadwal(teater, jadwalBaru);

        SimpanJadwalKeFile(&kInfo->id, &bInfo->id, &tInfo->id, &jadwalBaru);

        printf("Jadwal untuk tanggal %d/%d/%d berhasil ditambahkan (ID: %d).\n",
            jadwalBaru.tanggal.Tgl, jadwalBaru.tanggal.Bln, jadwalBaru.tanggal.Thn, jadwalBaru.id);
    }

    DelAll(&listJadwal);
}


// Deskripsi : prosedur untuk menginisialisasi array 2 dimensi
// IS : menerima jadwalInfo dan teaterinfo yang berisi jumlah kursi
// FS : array 2 dimensi terbuat dengan fix 10 kolom, dan membagi jumlah kursi dengan kolom lalu menentukan mana array yang bisa di isi dan tidak (tidak ada kursi)
void InisialisasiKursi(JadwalInfo *jadwal, address teaterAddress) {
    TeaterInfo teater = *((TeaterInfo*)(teaterAddress->info));

    int jumlahKursi = teater.jumlahKursi;
    int kolom = 10;
    int baris = (jumlahKursi + kolom - 1) / kolom;

    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            int index = i * kolom + j;
            if (index < jumlahKursi) {
                jadwal->kursi[i][j] = '0';
            } else {
                jadwal->kursi[i][j] = 'X';
            }
        }
    }
}

// Deskripsi : mengambil jadwal teater dari tree dijadikan linkedlist
// IS : menerima node teater dan list
// FS : List jadwal terisi dengan jadwal yang ada di teater yang dikirim
void AmbilJadwalTeaterKeList(address nodeTeater, List* L) {
    CreateList(L);

    if (nodeTeater == NULL || nodeTeater->fs == NULL) return;

    address nodeJadwal = nodeTeater->fs;

    while (nodeJadwal != NULL) {
        JadwalInfo* jadwal = (JadwalInfo*) nodeJadwal->info;
        InsLast(L, (infotype) jadwal);
        nodeJadwal = nodeJadwal->nb;
    }
}

// Deskripsi : mengecek apakah jadwal bentrok dengan jadwal yang sudah ada atau tidak
// IS : menerima node list, tanggal, timeinfo start dan end jadwal yang baru
// FS : mengembalikan true jika ada jadwal bentrok dan false jika tidak ada jadwal bentrok
boolean AdaJadwalBentrok(List L, date tanggal, TimeInfo start, TimeInfo end, int idKecuali) {
    addressList P = L.First;

    int startBaru = ConvertMenit(start);
    int endBaru = ConvertMenit(end);

    while (P != NULL) {
        JadwalInfo* j = (JadwalInfo*) P->info;

        if (j->id == idKecuali) {
            P = P->next;
            continue;
        }

        if (j->tanggal.Tgl == tanggal.Tgl &&
            j->tanggal.Bln == tanggal.Bln &&
            j->tanggal.Thn == tanggal.Thn) {

            int startLama = ConvertMenit(j->Start);
            int endLama = ConvertMenit(j->End);

            if (startBaru < endLama + 5 && endBaru > startLama - 5) {
                return true;
            }
        }

        P = P->next;
    }

    return false;
}

void AmbilJadwalTeaterTanggalKeList(address teater, date tanggal, List* hasil) {
    CreateList(hasil);

    address nodeJadwal = teater->fs;
    while (nodeJadwal != NULL) {
        JadwalInfo* j = (JadwalInfo*) nodeJadwal->info;

        if (j->tanggal.Tgl == tanggal.Tgl &&
            j->tanggal.Bln == tanggal.Bln &&
            j->tanggal.Thn == tanggal.Thn) {
            JadwalInfo* salinan = (JadwalInfo*) malloc(sizeof(JadwalInfo));
            *salinan = *j;

            InsLast(hasil, (infotype) salinan);
        }

        nodeJadwal = nodeJadwal->nb;
    }
}

void TampilkanListJadwal(List L) {
    if (ListEmpty(L)) {
        printf("Tidak ada jadwal ditemukan.\n");
        return;
    }

    int index = 1;
    addressList P = L.First;
    while (P != NULL) {
        JadwalInfo* j = (JadwalInfo*) P->info;
        printf("%d. ID: %d | Mulai: %02d:%02d | Selesai: %02d:%02d | Tanggal: %d/%d/%d | Film: %s\n",
            index,
            j->id,
            j->Start.jam, j->Start.menit,
            j->End.jam, j->End.menit,
            j->tanggal.Tgl, j->tanggal.Bln, j->tanggal.Thn,
            j->film->judul);
            
        P = P->next;
        index++;
    }
}


// Deskripsi : Prosedur untuk mengubah info Jadwal pada node
// IS : menerima address node dan dataBaru sebagai JadwalInfo
// FS : mengubah info Jadwal pada node dan memperbarui file
void UbahJadwal(address node, JadwalInfo jadwalBaru) {
    JadwalInfo* oldInfo = (JadwalInfo*) node->info;
    JadwalInfo* newInfo = (JadwalInfo*) malloc(sizeof(JadwalInfo));

    address nodeTeater = node->pr;
    if (nodeTeater == NULL || nodeTeater->type != TEATER) {
        printf("Error: nodeTeater tidak valid!\n");
        return;
    }

    List listJadwal;
    AmbilJadwalTeaterTanggalKeList(nodeTeater, oldInfo->tanggal, &listJadwal);

    if (!newInfo) return;

    jadwalBaru.id = oldInfo->id;
    jadwalBaru.End = TambahWaktu(jadwalBaru.Start, jadwalBaru.film->durasi);
    jadwalBaru.tanggal = oldInfo->tanggal;
    memcpy(jadwalBaru.kursi, oldInfo->kursi, sizeof(oldInfo->kursi));
    jadwalBaru.jumlahBaris = oldInfo->jumlahBaris;
    jadwalBaru.jumlahKolom = oldInfo->jumlahKolom;

    if (AdaJadwalBentrok(listJadwal, jadwalBaru.tanggal, jadwalBaru.Start, jadwalBaru.End, jadwalBaru.id)) {
        
        printf("Jadwal gagal ditambahkan untuk tanggal %d/%d/%d karena bentrok.\n", jadwalBaru.tanggal.Tgl, jadwalBaru.tanggal.Bln, jadwalBaru.tanggal.Thn);
        return;
    }

    *newInfo = jadwalBaru;
    UbahNode(node, (infotype)newInfo);

    EditJadwalKeFile(newInfo, oldInfo);

    DelAll(&listJadwal);

    printf("Jadwal '%d:%d' berhasil diubah dan disimpan ke file.\n", oldInfo->Start.jam, oldInfo->Start.menit);
}

// Deskripsi : Prosedur untuk menghapus Jadwal dari teater
// IS : menerima address Jadwal
// FS : menghapus node Jadwal dari tree dan juga dari file
void DeleteJadwal(address jadwal) {
    if (jadwal == NULL) return;

    JadwalInfo* oldInfo = (JadwalInfo*) jadwal->info;

    JadwalInfo jadwalLama;
    jadwalLama.id = oldInfo->id;
    jadwalLama.Start = oldInfo->Start;
    jadwalLama.End = oldInfo->End;
    jadwalLama.tanggal = oldInfo->tanggal;
    jadwalLama.film = oldInfo->film;
    memcpy(jadwalLama.kursi, oldInfo->kursi, sizeof(oldInfo->kursi));
    jadwalLama.jumlahBaris = oldInfo->jumlahBaris;
    jadwalLama.jumlahKolom = oldInfo->jumlahKolom;

    address nodeTeater = jadwal->pr;

    if (nodeTeater) {
        HapusJadwalKeFile(&jadwalLama);

        DeleteNode(&nodeTeater, jadwal);

        printf("Jadwal '%d:%d' berhasil dihapus.\n", jadwalLama.Start.jam, jadwalLama.Start.menit);
    }
}

// Deskripsi : Prosedur untuk menghapus semua jadwal dari teater
// IS : menerima address teater
// FS : menghapus semua node jadwal dari tree dan juga mengosongkan file jadwal
void DeleteAllJadwal(address teater) {
    if (IsTreeEmpty(teater)) {
        printf("Teater tidak valid atau kosong.\n");
        return;
    }

    DeleteAllKeepRoot(teater);
    KosongkanFileJadwal();
}

// Deskripsi : Fungsi untuk membandingkan dua Jadwal berdasarkan start
// IS : menerima dua infotype yang berisi JadwalInfo
// FS : mengembalikan nilai 0 jika Jadwal sama, dan 1 jika Jadwal berbeda
int CompareJadwal(infotype a, infotype b) {
    JadwalInfo* ja = (JadwalInfo*)a;
    JadwalInfo* jb = (JadwalInfo*)b;

    if (ja->tanggal.Tgl == jb->tanggal.Tgl &&
        ja->tanggal.Bln == jb->tanggal.Bln &&
        ja->tanggal.Thn == jb->tanggal.Thn &&
        ja->Start.jam == jb->Start.jam &&
        ja->Start.menit == jb->Start.menit) {
        return 0;
    }

    return 1;
}

// Deskripsi : Fungsi untuk membandingkan dua Jadwal berdasarkan id
// IS : menerima dua infotype yang berisi JadwalInfo
// FS : mengembalikan nilai 0 jika Jadwal sama, dan 1 jika Jadwal berbeda
int CompareJadwalId(infotype a, infotype b) {
    JadwalInfo* jadwal1 = (JadwalInfo*) a;
    JadwalInfo* jadwal2 = (JadwalInfo*) b;

    return jadwal1->id - jadwal2->id;
}

// Deskripsi : Fungsi untuk mencari Jadwal berdasarkan start
// IS : menerima address teater dan namaJadwal sebagai string
// FS : mengembalikan address dari node yang sesuai, atau NULL jika tidak ditemukan
address SearchJadwalByName(address teater, const date* tanggal, const TimeInfo* start) {
    JadwalInfo target;
    target.tanggal = *tanggal;
    target.Start = *start;

    return Search(teater, (infotype)&target, CompareJadwal, JADWAL);
}

// Deskripsi : Fungsi untuk mencari Jadwal berdasarkan id
// IS : menerima address teater dan namaJadwal sebagai string
// FS : mengembalikan address dari node yang sesuai, atau NULL jika tidak ditemukan
address SearchJadwalById(address teater, const int* idJadwal) {
    JadwalInfo target;
    target.id = *idJadwal;

    return Search(teater, (infotype)&target, CompareJadwalId, JADWAL);
}

// Deskripsi : Prosedur untuk mencetak daftar jadwal
// IS : menerima address teater dan level untuk indentasi
// FS : mencetak daftar jadwal yang ada pada bioskop 
void PrintJadwal(address node, int level) {
    if (IsTreeEmpty(node)) {
        printf("Tree kosong.\n");
        return;
    }
    
    printf("\nDaftar Jadwal :\n");

    PrintChildrenOnly(node, level);
}
