#include "listLogic.h"

void listInsert(List* list, char* code, char* name)
{

    if (strlen(code) != 3) {
        printf("Uncorrect airport code\n");
        return;
    }
    Node* newNode = malloc(sizeof(Node));

    if (!newNode)
        return;

    newNode->name = strdup(name);

    if (!newNode->name) {
        printf("error name saving\n");
        free(newNode);
        return;
    }

    strncpy(newNode->code, code, 3);

    newNode->code[3] = '\0';

    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        newNode->next = list->head;

        list->head = newNode;
    }
    (list->nodeCount)++;
}

void listFind(List* list, char* code)
{
    Node* curr = list->head;

    if (!curr)
        return;

    while (curr != NULL) {
        if (strcmp(curr->code, code) == 0) {
            // printf("%s -> %s\n", curr->code, curr->name); убрано для perf
            return;
        }

        else
            curr = curr->next;
    }

    // printf("Airport with code %s not found in the database.\n", code); для 2 сценария
}

bool listContains(List* list, char* code)
{
    Node* curr = list->head;

    if (!curr)
        return 0;

    while (curr != NULL) {
        if (strcmp(curr->code, code) == 0)
            return 1;

        else
            curr = curr->next;
    }

    return 0;
}

void freeNode(Node* node)
{
    if (node == NULL)
        return;

    free(node->name);

    node->next = NULL;

    free(node);
}
void listRemove(List* list, char* code)
{

    Node* curr = list->head;
    Node* prev = NULL;

    if (curr == NULL)
        return;

    if (strcmp(curr->code, code) == 0) {

        list->head = curr->next;

        freeNode(curr);

        (list->nodeCount)--;
        return;
    }
    prev = curr;
    curr = curr->next;
    while (curr != NULL) {
        if (strcmp(curr->code, code) == 0) {

            prev->next = curr->next;
            freeNode(curr);
            (list->nodeCount)--;
            return;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    printf("The database haven't had this code yet\n");
}

void freeList(List* list)
{
    Node* curr = list->head;

    if (!curr)
        return;

    while (curr != NULL) {
        Node* nextNode = curr->next;

        freeNode(curr);

        curr = nextNode;
    }
    list->head = NULL;
    list->nodeCount = 0;
}
void addListToList(List* list, char* airportList)
{
    FILE* input = fopen(airportList, "r");

    if (!input) {
        printf("error open input airport list file\n");
        return;
    }

    char code[4];
    char name[101];

    while (fscanf(input, " %3[^:]:%100[^\n]", code, name) == 2) {

        listInsert(list, code, name);
    }
    printf("Was downloded: %d airports.\n", list->nodeCount);

    fclose(input);
}

void listSave(List* list, char* airportList)
{
    FILE* output = fopen(airportList, "w");

    if (!output) {
        printf("file open error\n");
        return;
    }

    Node* curr = list->head;

    if (!curr)
        return;

    while (curr != NULL) {

        fprintf(output, "%s:%s\n", curr->code, curr->name);
        curr = curr->next;
    }

    fclose(output);

    printf("Base was saved of: %d airports.\n", list->nodeCount);
}

void interfaceFunctionList(List* list, char* airportList)
{
    char line[256];

    while (printf("> "), fgets(line, sizeof(line), stdin)) {

        line[strcspn(line, "\n")] = 0;

        if (strncmp(line, "quit", 4) == 0)
            break;

        if (strncmp(line, "find ", 5) == 0) {

            listFind(list, line + 5);
        } else if (strncmp(line, "add ", 4) == 0) {
            char code[4];

            char name[101];

            sscanf(line + 4, " %3[^:]:%100[^\n]", code, name);

            listInsert(list, code, name);

            printf("Add airport: %s\n", code);

        } else if (strncmp(line, "delete ", 7) == 0) {

            listRemove(list, line + 7);

            printf("Airport %s has been removed from the database.\n", line + 7);
        } else if (strncmp(line, "save", 4) == 0) {

            listSave(list, airportList);

        } else {
            printf("please, enter correct commands: find, add, save, delete, quite\n");
        }
    }
}

void collectCodesToArray(List* list, char codes[][4], int* count)
{
    if (list == NULL)
        return;

    Node* curr = list->head;

    while (curr != NULL) {
        strncpy(codes[*count], curr->code, 3);

        codes[*count][3] = '\0';

        (*count)++;

        curr = curr->next;
    }
}