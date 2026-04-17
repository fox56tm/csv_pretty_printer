#ifndef LISTLOGIC_H_INCLUDED
#define LISTLOGIC_H_INCLUDED

typedef struct node
{
    char code[4];
    char* name;
    struct node* next;
}Node;

typedef struct listController
{
    Node* head;
    Node* tail;

} List;


#endif