#ifndef ADTTree_h
#define ADTTree_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char infotype[100]; 

typedef struct tNode* address;
typedef struct tNode {
    int id;
    infotype info;
    address pr;
    address fs;
    address nb;
} Node;

// === FUNGSI DASAR ===
address Alokasi(infotype X);

void Dealokasi(address P);

address CreateTree(infotype rootInfo);

void AddChild(address parent, infotype childInfo);

#endif
