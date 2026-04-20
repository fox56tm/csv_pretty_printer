#ifndef AVLLOGIC_H_INCLUDED
#define AVLLOGIC_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AvlNode {
    struct AvlNode* right;

    struct AvlNode* left;

    char code[4];
    char* name;
    int height;

} Node;

typedef struct AvlTree {
    Node* root;
    int nodeCount;

} avl;

int nodeHeight(Node* node);

int avlHeight(avl* tree);

Node* leftRotate(Node* node);

Node* rightRotate(Node* node);

Node* rebalanceNode(Node* node);

Node* avlInsert(Node* node, char* code, char* name);

void avlRecInsert(avl* avl, char* code, char* name);

void avlFind(Node* node, char* code);

void freeNode(Node* node);

Node* minData(Node* node);

Node* avlNodeRemove(Node* node, char* code);

void avlRemove(avl* avlNode, char* code);

void interfaceFunctionAvl(avl* tree, char* airportList);

void addListToAvl(avl* tree, char* airportList);

void avlSave(avl* tree, char* airportList);

bool avlContains(Node* node, char* code);

void nodesAddToFile(Node* node, FILE* output);
#endif //
