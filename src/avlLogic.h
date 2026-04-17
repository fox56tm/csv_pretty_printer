#ifndef AVLLOGIC_H_INCLUDED
#define AVLLOGIC_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct avlNode
{
    struct avlNode* right;

    struct avlNode* left;

    char code[4];
    char* name;
    int height;

} Node;

typedef struct avlTree
{
    Node* root;
    int nodeCount;

} avl;

int nodeHeight(Node* node);

int avlHeight(avl* tree);

Node* leftRotate(Node* node);

Node* rightRotate(Node* node);

Node* rebalanсeNode(Node* node);

Node* avlInsert(Node* node, char* code, char* name);

void avlRootInsert(avl* avl, char* code, char* name);
void avlFind(Node* node, char* code);

#endif //
