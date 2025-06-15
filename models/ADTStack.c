#include "header/ADTStack.h"
#include <stdio.h>
#include <stdlib.h>


void CreateStack(Stack *S) {
    CreateList(S);
}

boolean IsEmptyStack(Stack S) {
    return ListEmpty(S);
}

void Push(Stack* S, infotype data) {
    InsFirst(S, data);
}

void* Pop(Stack* S) {
    infotype temp;
    DelFirst(S, &temp);
    return temp;
}

void* Top(Stack S) {
    if (S.First != NULL) {
        return S.First->info;
    }
    return NULL;
}
