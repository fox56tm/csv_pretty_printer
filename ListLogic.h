#ifndef LISTLOGIC_H_INCLUDED
#define LISTLOGIC_H_INCLUDED
typedef struct list_node
{
    char ** Cells;

    int cols;

    struct list_node * next;

} Node;

typedef struct list_control
{
    Node * head;
    Node * tail;

} List;



#endif // LISTLOGIC_H_INCLUDED
