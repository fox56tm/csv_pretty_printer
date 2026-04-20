#ifndef LISTLOGIC_H_INCLUDED
#define LISTLOGIC_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char code[4];
    char* name;
    struct Node* next;
} Node;

typedef struct ListController {
    Node* head;
    int nodeCount;

} List;

void listInsert(List* list, char* code, char* name);
void listFind(List* list, char* code);
bool listContains(List* list, char* code);
void freeNode(Node* node);
void listRemove(List* list, char* code);
void freeList(List* list);
void addListToList(List* list, char* airportList);
void listSave(List* list, char* airportList);
void interfaceFunctionList(List* list, char* airportList);

#endif