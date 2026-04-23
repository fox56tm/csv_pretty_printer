#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int target;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    int cityIndex;
    int dist;
} HeapElement;

typedef struct {
    HeapElement* data;
    int size;
    int capacity;
} MinHeap;

Node** roadsRead(char* fileName, int* capitalCount, int* cities, int* roads, FILE** capitals);

void addEdge(Node** graph, int city1, int city2, int roadLen);

void printStatesAndCities(Node** graph, int capitalCount, int cities, FILE* capitals);
void push(MinHeap* heap, HeapElement el);

void siftUp(MinHeap* heap, int idx);

HeapElement pop(MinHeap* heap);
void siftDown(MinHeap* heap, int idx);
void initHeap(MinHeap* heap, int initCapacity);