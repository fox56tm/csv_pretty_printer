#ifndef LISTLOGIC_H_INCLUDED
#define LISTLOGIC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char code[4];
    char* name;
    struct node* next;
} Node;

typedef struct listController {
    Node* head;
    Node* tail;

    int nodeCount;

} List;

#endif