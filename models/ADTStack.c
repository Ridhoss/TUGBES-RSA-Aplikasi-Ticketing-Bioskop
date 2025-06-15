#include "header/ADTStack.h"
#include <stdio.h>
#include <stdlib.h>


void CreateStack(StackMenu *S) {
    CreateList(S);
}

boolean IsEmptyStack(StackMenu S) {
    return ListEmpty(S);
}

void Push(StackMenu *S, const char *menu) {
    char *newMenu = (char *)malloc(strlen(menu) + 1);
    strcpy(newMenu, menu);
    InsFirst(S, newMenu); 
}

void Pop(StackMenu *S) {
    if (!IsEmptyStack(*S)) {
        char *temp;
        DelFirst(S, (infotype *)&temp);  
        free(temp);  
    }
}

char* Top(StackMenu S) {
    if (!IsEmptyStack(S)) {
        return (char *)S.First->info; 
    }
    return NULL;
}
