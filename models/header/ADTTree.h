#ifndef ADTTree_h
#define ADTTree_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../../library/boolean.h"

typedef void* infotype;

typedef struct tNode* address;
typedef struct tNode {
    int id;
    infotype info;
    address pr;
    address fs;
    address nb;
} Node;

typedef int (*CompareFunc)(infotype a, infotype b);


boolean IsTreeEmpty(address root);

address Alokasi(infotype X);

void Dealokasi(address P);

address CreateTree(infotype rootInfo);

void AddChild(address parent, infotype childInfo);

address Search(address root, infotype searchinfo, CompareFunc cmp);

void UbahNode(address node, infotype newInfo);

void DeleteAll(address root);

void DeleteAllKeepRoot(address node);

void DeleteNode(address *root, address delNode);

void PrintTree(address node, int level);

void PrintChildrenOnly(address node, int level);

void InputString(char* buffer);

#endif
