#include "../src/logic.h"

int passed = 0;
int failed = 0;

void check(const char* testName, int condition)
{
    if (condition) {
        printf("passed: %s\n", testName);
        passed++;
    } else {
        printf("failed: %s\n", testName);
        failed++;
    }
}

void testHeapPushPop()
{
    MinHeap h;
    initHeap(&h, 4);
    HeapElement a = { 1, 10 };
    HeapElement b = { 2, 3 };
    HeapElement c = { 3, 7 };
    push(&h, a);
    push(&h, b);
    push(&h, c);
    HeapElement top = pop(&h);
    check("first min (dist=3)", top.dist == 3 && top.cityIndex == 2);
    top = pop(&h);
    check("second min (dist=7)", top.dist == 7 && top.cityIndex == 3);
    top = pop(&h);
    check("third min (last ,dist=10)", top.dist == 10 && top.cityIndex == 1);
    check("heap is empty", h.size == 0);
    free(h.data);
}

void testHeapGrowth()
{
    MinHeap h;
    initHeap(&h, 2);
    for (int i = 10; i >= 1; i--) {
        HeapElement el = { i, i };
        push(&h, el);
    }
    check("size after 10 pushes", h.size == 10);
    HeapElement top = pop(&h);
    check("min el after growth", top.dist == 1);
    free(h.data);
}

void testAddEdge()
{
    int n = 4;
    Node** graph = calloc(n + 1, sizeof(Node*));
    addEdge(graph, 1, 2, 5);
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 2, 1, 5);
    int count = 0;
    Node* curr = graph[1];
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    check("vertex 1 has 2 neighbors", count == 2);
    count = 0;
    curr = graph[2];
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    check("vertex 2 has 1 neighbor", count == 1);
    int found = 0;
    curr = graph[1];
    while (curr != NULL) {
        if (curr->target == 2 && curr->weight == 5)
            found = 1;
        curr = curr->next;
    }
    check("edge 1->2 has weight 5", found);
    for (int i = 0; i <= n; i++) {
        Node* cur = graph[i];
        while (cur) {
            Node* tmp = cur->next;
            free(cur);
            cur = tmp;
        }
    }
    free(graph);
}

void testRoadsRead()
{
    FILE* f = fopen("tmpTest.txt", "w");
    fprintf(f, "4 4\n");
    fprintf(f, "1 2 5\n");
    fprintf(f, "1 3 2\n");
    fprintf(f, "2 4 8\n");
    fprintf(f, "3 4 3\n");
    fprintf(f, "2\n");
    fprintf(f, "1 4\n");
    fclose(f);

    int capitalCount, cities, roads;
    FILE* capitals;
    Node** graph = roadsRead("tmpTest.txt", &capitalCount, &cities, &roads, &capitals);
    check("graph is not NULL", graph != NULL);
    check("cities == 4", cities == 4);
    check("roads == 4", roads == 4);
    check("capitalCount == 2", capitalCount == 2);
    if (graph != NULL) {
        check("vertex 1 has neighbors", graph[1] != NULL);
        for (int i = 0; i <= cities; i++) {
            Node* cur = graph[i];
            while (cur) {
                Node* tmp = cur->next;
                free(cur);
                cur = tmp;
            }
        }
        free(graph);
        fclose(capitals);
    }
}

int main()
{
    printf("running tests\n\n");
    testHeapPushPop();
    testHeapGrowth();
    testAddEdge();
    testRoadsRead();
    printf("\n--------------------------\n");
    if (failed == 0)
        printf("%d tests passed!\n", passed);
    else
        printf("%d passed, %d FAILED\n", passed, failed);

    return failed == 0 ? 0 : 1;
}