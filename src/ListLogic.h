#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char** Cells;
    int cols;
    struct ListNode* next;
} Node;

typedef struct ListControl {
    Node* head;
    Node* tail;
    int nodeCount;
} List;

void addToTail(List* myList, char** cells, int colCount);
void freeList(List* list);
void csvConvert(char* filename, List* list, char* output);
int isNumber(char* str);
void printHorizonLines(FILE* file, const int* width, int colCount, char sep);
