#include "logic.h"
void addEdge(Node** graph, int city1, int city2, int roadLen)
{
    Node* newEdge = malloc(sizeof(Node));

    if (!newEdge){
    printf("error edge create\n");
    return;
    }

    newEdge -> target = city2; 
    newEdge -> weight = roadLen;
    newEdge -> next = graph[city1];
    graph[city1] = newEdge;

}

Node** roadsRead(char* fileName,int* capitalCount, int* cities, int*roads, FILE** capitals)
{
    FILE* inGraph = fopen(fileName,"r");
    if(!inGraph){ printf("error read file\n"); return NULL;}


    if(fscanf(inGraph, "%d %d", cities, roads) != 2){
        printf("error from read cities and road count\n");
        fclose(inGraph);
        return NULL;
    }
    
    Node** graph = calloc(*cities + 1, sizeof(Node*));//список смежности для каждой вершины
    if(!graph){
        printf("error from graph memmoy\n");
        fclose(inGraph);
        return NULL;
    }

    int city1, city2;

    int roadLen;

    char line[256];
    while(fgets(line, sizeof(line), inGraph)){

        if(sscanf(line, "%d %d %d", &city1, &city2, &roadLen) == 3){

            addEdge(graph, city1, city2, roadLen);

            addEdge(graph, city2, city1, roadLen);

        } else if(sscanf(line, "%d", capitalCount) == 1){
                 *capitals = inGraph;
                 return graph;
                }
    }

    printf("error on roads read\n");

    fclose(inGraph);
    return NULL;
}


void printStatesAndCities(Node** graph, int capitalCount, int cities, FILE* capitals)
{   
    int* cityOwner; //принадлежность государству
    MinHeap* heaps = malloc(capitalCount * sizeof(MinHeap)); //кучи для каждой столицы
    if(!heaps)
    {
        printf("Error heaps create\n");
        return;
    }

    for(int i = 0; i < capitalCount; i++) initHeap(&heaps[i], 16);

    if (cities >= 1) 
    {
        cityOwner = malloc((cities + 1) *sizeof(int));
        if(!cityOwner){
            free(heaps);
            printf("error create cityOwner array\n");
            return;
        }
        for(int i = 0; i <= cities; i++) cityOwner[i] = -1;
    }
    
    int i = 0;

    int capitalNum;

    int capitalCountTotal = 0;

    while(i < capitalCount && fscanf(capitals,"%d", &capitalNum) == 1)
    {
        if (capitalNum < 0){
            free(heaps);
            free(cityOwner);
            printf("enter correct capital index\n");
            return;
        }
        if(cityOwner[capitalNum] == -1)
        {
            cityOwner[capitalNum] = i+1;

            capitalCountTotal++;
        }
        Node* curr = graph[capitalNum];

        while(curr != NULL){

            if(cityOwner[curr->target] == -1){

                HeapElement el;

                el.cityIndex = curr->target;

                el.dist = curr->weight;

                push(&heaps[i], el); 
            }
            curr = curr->next;
        }
        i++;
    }
    while(capitalCountTotal < cities){

        for (int i = 0; i < capitalCount; i++)
        {
            while(heaps[i].size > 0)  //ищем ближайший свободный
            {
                HeapElement bestCity = pop(&heaps[i]);

                if (cityOwner[bestCity.cityIndex] == -1)
                {
                    cityOwner[bestCity.cityIndex] = i + 1;
                    capitalCountTotal++;

                    Node* neighbor = graph[bestCity.cityIndex]; //добавляем новых соседей в кучу
                    while (neighbor != NULL)
                    {
                        if (cityOwner[neighbor->target] == -1)
                        {
                            HeapElement newEl;
                            newEl.cityIndex = neighbor->target;
                            newEl.dist = neighbor->weight; //вес новой дороги
                            push(&heaps[i], newEl);
                        }
                        neighbor = neighbor->next;
                    }
                    break; 
                }
            }
        }
    }
    for (int state = 1; state <= capitalCount; state++)
    {
        printf("State %d:\n", state);
        for (int i = 0; i <= cities; i++)
            if (cityOwner[i] == state) printf("%d\n", i);
    }

    for (int i = 0; i < capitalCount; i++) {
        free(heaps[i].data);
    }
    free(heaps);
    free(cityOwner);
    fclose(capitals);
}

void push(MinHeap* heap, HeapElement el)
{
    if(heap -> size == heap -> capacity)
    {
        heap-> capacity *= 2;

        HeapElement* temp = realloc(heap -> data, heap -> capacity * sizeof(HeapElement));

        if(!temp) {printf("mem error int push");return;}

        heap -> data = temp;
    }
    int i = heap->size;

    heap->data[i] = el;

    heap->size++;

    siftUp(heap, i);
}
void siftUp(MinHeap* heap, int idx)
{

    while (idx > 0){
        int parent = (idx - 1) / 2;
        
        if (heap->data[idx].dist < heap->data[parent].dist) // если меньше родителя меняем
        {
            HeapElement temp = heap->data[idx];

            heap->data[idx] = heap->data[parent];

            heap->data[parent] = temp;

            idx = parent;

        }else break;
    }
}

HeapElement pop(MinHeap* heap)
{
    HeapElement root = heap->data[0];

    heap->size--;

    if (heap->size > 0){

        heap->data[0] = heap->data[heap->size];
        siftDown(heap, 0);
    }

    return root;
}

void siftDown(MinHeap* heap, int idx)
{
    while (2 * idx + 1 < heap->size){ //пока есть хотя бы левый ребенок
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = left; // пока что левый

        if(right < heap->size && heap->data[right].dist < heap->data[left].dist) smallest = right; //если есть правый и меньше левого

        if(heap->data[idx].dist > heap->data[smallest].dist){ //если больше ребенка меняем
            HeapElement temp = heap->data[idx]; 
            heap->data[idx] = heap->data[smallest];
            heap->data[smallest] = temp;
            idx = smallest;
        } else break;
    }
}


void initHeap(MinHeap* heap, int initCapacity)
{
    heap->size = 0;
    heap->capacity = initCapacity;
    heap->data = malloc(initCapacity * sizeof(HeapElement));
    
    if (heap->data == NULL) {
        printf("mem error for heap init\n");
        return;
    }
}

