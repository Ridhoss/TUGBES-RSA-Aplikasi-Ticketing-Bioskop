#ifndef ADTStack_h
#define ADTStack_h

#include "../../library/boolean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTList.h"
#include "ADTTree.h"

typedef List Stack;

void CreateStack(Stack *S);
boolean IsEmptyStack(Stack S);

void Push(Stack *S, infotype data);
void* Pop(Stack* S);
void* Top(Stack S);

#endif