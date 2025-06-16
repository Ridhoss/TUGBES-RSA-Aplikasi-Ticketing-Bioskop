#include "header/ADTQueue.h"
#include "header/ADTPemesanan.h"

Queue QueueETicket;


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








void CreateQueue(Queue *Q) {
    CreateList(Q);
}

boolean IsEmptyQueue(Queue Q) {
    return ListEmpty(Q);
}

void EnQueue(Queue* Q, infotype data) {
    InsLast(Q, data);
}


void DeQueue(Queue* Q, infotype *data) {
    infotype temp;
    DelFirst(Q, &temp);
}

infotype InfoTop(Queue Q) {
    return Q.First->info;
}

int TotalQueue(Queue Q) {
    int count = 0;
    addressList current = Q.First;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}
