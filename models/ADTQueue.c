#include "header/ADTQueue.h"
#include "header/ADTPemesanan.h"

Queue QueueETicket;

// Deskripsi: Procedure untuk menambahkan data transaksi ke dalam queue dan menyimpannya ke file
// I.S.: Queue Q terdefinisi dan data berisi transaksi yang akan dimasukkan
// F.S.: data ditambahkan ke queue dan ID-nya ditulis ke file queue_eticket.txt
void EnQueueFile(Queue* Q, Transaksi* data) {
    EnQueue(Q, data);

    FILE* file = fopen("database/queue_eticket.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan queue.\n");
        return;
    }

    fprintf(file, "%d\n", data->id);
    fclose(file);
}

// Deskripsi: Procedure untuk memuat data antrian transaksi dari file ke dalam queue.
// I.S.: File queue_eticket.txt berisi ID transaksi, dan queue Q terdefinisi.
// F.S.: Semua ID transaksi di file dimasukkan ke queue Q jika ditemukan datanya.
void LoadQueueFromFile(Queue* Q) {
    FILE* file = fopen("database/queue_eticket.txt", "r");
    if (file == NULL) {
        printf("Tidak ada file antrian ditemukan.\n");
        return;
    }

    int idTransaksi;
    while (fscanf(file, "%d", &idTransaksi) == 1) {
        Transaksi* trx = SearchTransaksiById(idTransaksi);
        if (trx != NULL) {
            EnQueue(Q, trx);
        }
    }

    fclose(file);

    printf("Queue terload\n");
}

// Deskripsi: Procedure untuk menghapus satu elemen dari queue dan memperbarui file
// I.S.: Q berisi data transaksi
// F.S.: Satu data terdepan queue dihapus
void DeQueueWithFile(Queue* Q) {
    if (IsEmptyQueue(*Q)) {
        printf("Queue kosong.\n");
        return;
    }

    infotype temp;
    DeQueue(Q, &temp);
    int targetId = ((Transaksi*)temp)->id;

    FILE* file = fopen("database/queue_eticket.txt", "r");
    FILE* tempFile = fopen("database/temp_queue_eticket.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Gagal membuka file untuk update queue.\n");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        int id;
        sscanf(buffer, "%d", &id);

        if (id != targetId) {

            fputs(buffer, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("database/queue_eticket.txt");
    rename("database/temp_queue_eticket.txt", "database/queue_eticket.txt");
}

// Deskripsi: Procedure untuk menginisialisasi atau membuat queue kosong.
// I.S.: Queue belum terinisialisasi
// F.S.: Queue  terinisialisasi sebagai queue kosong.
void CreateQueue(Queue *Q) {
    CreateList(Q);
}

// Deskripsi: Fungsi untuk Mengecek apakah queue kosong atau tidak.
// I.S.: Queue terdefinisi.
// F.S.: Mengembalikan true jika queue kosong, false jika tidak.
boolean IsEmptyQueue(Queue Q) {
    return ListEmpty(Q);
}

// Deskripsi: Procedure untuk menambahkan data ke akhir queue
// I.S.: Queue Q terdefinisi, data berisi nilai yang akan dimasukkan.
// F.S.: data berhasil ditambahkan ke akhir queue Q.
void EnQueue(Queue* Q, infotype data) {
    InsLast(Q, data);
}

// Deskripsi: Procedure untuk Menghapus elemen pertama dari queue dan menyimpannya ke variabel output.
// I.S.: Queue tidak kosong dan terdefinisi.
// F.S.: Elemen pertama queue dihapus dan disimpan ke *data.
void DeQueue(Queue* Q, infotype *data) {
    infotype temp;
    DelFirst(Q, &temp);
}

// Deskripsi: Fungsi untuk Mengembalikan nilai (info) dari elemen pertama queue tanpa menghapusnya.
// I.S.: Queue Q terdefinisi dan tidak kosong
// F.S.: Nilai dari elemen depan dikembalikan, queue tetap tidak berubah
infotype InfoTop(Queue Q) {
    return Q.First->info;
}

// Deskripsi: Fungsi untuk Menghitung dan mengembalikan jumlah elemen yang ada di dalam queue.
// I.S.: Queue terdefinisi
// F.S.: Menghasilkan nilai berupa jumlah elemen dalam queue
int TotalQueue(Queue Q) {
    int count = 0;
    addressList current = Q.First;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}
