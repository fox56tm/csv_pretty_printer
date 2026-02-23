#include "ListLogic.h"
#include <stdio.h>
#include <stdlib.h>

void add_to_tail(Node ** head, Node ** tail, char ** cells, int col_count)
{

    Node * new_node = malloc(sizeof(Node));

    new_node -> Cells = cells;

    new_node -> cols = col_count;

    new_node -> next = NULL;

    if (*head == NULL && *tail == NULL)
    {
        *tail = new_node;

        *head = new_node;

        return;
    }

    else
    {
        (*tail) -> next = new_node;

        *tail = new_node;
    }

}
