#ifndef ADTQUEUE_H
#define ADTQUEUE_H

#include "../../library/boolean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTList.h"
#include "ADTTree.h"

typedef List Queue;
typedef struct transaksi Transaksi;

extern Queue QueueETicket;

void EnQueueFile(Queue* Q, Transaksi* data);
void LoadQueueFromFile(Queue* Q);
void DeQueueWithFile(Queue* Q);


void CreateQueue(Queue *S);
boolean IsEmptyQueue(Queue S);

void EnQueue(Queue* Q, infotype data);
void DeQueue(Queue* Q, infotype *data);
infotype InfoTop(Queue Q);
int TotalQueue(Queue Q);

#endif