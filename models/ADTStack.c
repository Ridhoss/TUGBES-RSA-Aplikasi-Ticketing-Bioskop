#include "header/ADTStack.h"
#include <stdio.h>
#include <stdlib.h>


void CreateStack(StackMenu *S) {
    CreateList(S);
}

bool IsEmptyStack(StackMenu S) {
    return ListEmpty(S);
}