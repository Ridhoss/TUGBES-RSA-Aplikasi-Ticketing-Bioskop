#ifndef ADTStack_h
#define ADTStack_h

#include "../../library/boolean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTList.h"
#include "ADTTree.h"

typedef List StackMenu;

void CreateStack(StackMenu *S);
bool IsEmptyStack(StackMenu S);
// void Push(StackMenu *S, const char *menu);
// void Pop(StackMenu *S);
// char* Top(StackMenu S);

#endif