#include "ListLogic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addToTail(List* myList, char** cells, int colCount)
{

    Node* newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("memmory error");

        return;
    }

    newNode->Cells = cells;

    newNode->cols = colCount;

    newNode->next = NULL;

    (myList->nodeCount)++;

    if (myList->head == NULL && myList->tail == NULL) {
        myList->tail = newNode;

        myList->head = newNode;

        return;
    }

    else {
        (myList->tail)->next = newNode;

        myList->tail = newNode;
    }
}
int isNumber(char* str)
{
    int dotCount = 0;

    int numCount = 0;

    int pos = 0;

    if (str[0] == '+' || str[0] == '-')
        pos = 1;

    for (int i = pos; i < strlen(str); i++) {
        if (str[i] == '.') {
            dotCount++;

            if (dotCount > 1)
                return 0;

        } else if (str[i] >= '0' && str[i] <= '9') {
            numCount++;
        } else
            return 0;
    }
    if (numCount >= 1)
        return 1;

    else
        return 0;
}
void printHorizonLines(FILE* file, const int* width, int colCount, char sep)
{
    fprintf(file, "+");

    for (int i = 0; i < colCount; i++) {

        for (int j = 0; j < width[i] + 2; j++) {
            fprintf(file, "%c", sep);
        }

        fprintf(file, "+");
    }
    fprintf(file, "\n");
}

void freeList(List* list)
{
    Node* curr = list->head;
    while (curr != NULL) {
        Node* next = curr->next;

        for (int i = 0; i < curr->cols; i++) {

            free(curr->Cells[i]);
        }

        free(curr->Cells);

        free(curr);

        curr = next;
    }
    list->head = list->tail = NULL;

    list->nodeCount = 0;
}
