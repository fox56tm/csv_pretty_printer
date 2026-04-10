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

} avl;

int nodeHeight(Node* node);

int avlHeight(avl* tree);

