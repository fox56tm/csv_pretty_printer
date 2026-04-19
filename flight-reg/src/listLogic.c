#include "listLogic.h"

void listInsert(List* list, char* code, char* name)
{
    Node* newNode = malloc(sizeof(Node));

    if (!newNode)
        return;

    if ((list->head == NULL) || (list->tail == NULL)) {
        list->head = newNode;
        list->tail = newNode;

        newNode->name = strdup(name);

        if (!newNode->name) {
            printf("error name saving\n");
            free(newNode);
            return NULL;
        }

        strncpy(newNode->code, code, 3);

        newNode->code[3] = '\0';

        (list->nodeCount)++;
    }
}
