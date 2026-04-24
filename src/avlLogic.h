#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
Node* recNodeRemove(Node* node);
void freeRecAvl(avl* tree);
void collectCodesToArray(Node* node, char codes[][4], int* count);
