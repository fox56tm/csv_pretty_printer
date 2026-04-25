#include "ListLogic.h"

void addToTail(List* myList, char** cells, int colCount)
{
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        for (int i = 0; i < colCount; i++)
            free(cells[i]);
        free(cells);
        printf("memory error");

        return;
    }
    newNode->Cells = cells;
    newNode->cols = colCount;
    newNode->next = NULL;
    (myList->nodeCount)++;
    if (myList->head == NULL && myList->tail == NULL) {
        myList->tail = newNode;
        myList->head = newNode;

        return;
    } else {
        (myList->tail)->next = newNode;
        myList->tail = newNode;
    }
}

int isNumber(char* str)
{
    int dotCount = 0;
    int numCount = 0;
    int pos = 0;
    if (str[0] == '+' || str[0] == '-')
        pos = 1;

    for (int i = pos; i < strlen(str); i++) {
        if (str[i] == '.') {
            dotCount++;
            if (dotCount > 1)
                return 0;
        } else if (str[i] >= '0' && str[i] <= '9') {
            numCount++;
        } else
            return 0;
    }
    if (numCount >= 1)
        return 1;
    else
        return 0;
}

void printHorizonLines(FILE* file, const int* width, int colCount, char sep)
{
    fprintf(file, "+");
    for (int i = 0; i < colCount; i++) {
        for (int j = 0; j < width[i] + 2; j++) {
            fprintf(file, "%c", sep);
        }
        fprintf(file, "+");
    }
    fprintf(file, "\n");
}

void freeList(List* list)
{
    Node* curr = list->head;
    while (curr != NULL) {
        Node* next = curr->next;
        for (int i = 0; i < curr->cols; i++) {
            free(curr->Cells[i]);
        }
        free(curr->Cells);
        free(curr);
        curr = next;
    }
    list->head = list->tail = NULL;
    list->nodeCount = 0;
}

char** parsing(char* line, int* colInd)
{
    *colInd = 0;
    char** cells = NULL;
    char* start = line; // начало текущей ячейки
    char* p = line; // указатель для прохода
    while (1) {
        if (*p == ',' || *p == '\0') {
            int end = (*p == '\0'); // дошли ли до конца
            *p = '\0';
            char** temp = realloc(cells, (*colInd + 1) * sizeof(char*));
            if (temp != NULL) {
                cells = temp;
            } else {
                printf("parsing error\n");
                free(cells);
                return NULL;
            }
            cells[*colInd] = strdup(start); // копируем кусок
            (*colInd)++;
            if (end) {
                break;
            }
            start = p + 1;
        }
        p++;
    }
    return cells;
}

int* maxColWidthsFunc(List* list, int* maxColCount) // считаем максимальную ширину
{
    *maxColCount = 0;
    for (Node* curr = list->head; curr != NULL; curr = curr->next) {
        if (curr->cols > *maxColCount)
            *maxColCount = curr->cols;
    }
    if (*maxColCount == 0) {
        freeList(list);
        return NULL;
    }
    int* maxColWidths = calloc(*maxColCount, sizeof(int));
    if (maxColWidths == NULL) {
        free(maxColWidths);
        freeList(list);
        printf("memmory error");
        return NULL;
    }
    for (Node* curr = list->head; curr != NULL; curr = curr->next) {
        for (int j = 0; j < curr->cols; j++) {
            if (strlen(curr->Cells[j]) > maxColWidths[j])
                maxColWidths[j] = (int)strlen(curr->Cells[j]);
        }
    }
    return maxColWidths;
}

void tableToFile(List* list, int* maxColWidths, int maxColCount, char* output) // функция записи в файл
{
    if (list->head == NULL)
        return;
    FILE* outTxt = fopen(output, "w");
    if (!outTxt) {
        free(maxColWidths);
        freeList(list);
        return;
    }
    printHorizonLines(outTxt, maxColWidths, maxColCount, '=');
    for (int i = 0; i < maxColCount; i++) {
        if (i < list->head->cols) {
            fprintf(outTxt, "| %-*s ", maxColWidths[i], list->head->Cells[i]);
        } else {
            fprintf(outTxt, "| %-*s ", maxColWidths[i], "");
        }
    }
    fprintf(outTxt, "|\n");
    printHorizonLines(outTxt, maxColWidths, maxColCount, '=');
    Node* curr2 = list->head->next;
    for (int i = 0; i < list->nodeCount - 1; i++) {
        if (curr2 == NULL)
            break;
        for (int j = 0; j < maxColCount; j++) {
            if (j < curr2->cols) {
                if (isNumber(curr2->Cells[j]))
                    fprintf(outTxt, "| %*s ", maxColWidths[j], curr2->Cells[j]);
                else
                    fprintf(outTxt, "| %-*s ", maxColWidths[j], curr2->Cells[j]);
            } else
                fprintf(outTxt, "| %*s ", maxColWidths[j], "");
        }
        fprintf(outTxt, "|\n");
        printHorizonLines(outTxt, maxColWidths, maxColCount, '-');
        curr2 = curr2->next;
    }
    fclose(outTxt);
    free(maxColWidths);
    freeList(list);
    printf("converting successfully!\n");
}

void csvConvert(char* filename, List* list, char* output) // основная функция
{
    FILE* csvIn = fopen(filename, "r");
    if (!csvIn) {
        printf("Error open");
        return;
    }
    fseek(csvIn, 0, SEEK_END);
    long size = ftell(csvIn);
    fseek(csvIn, 0, SEEK_SET);
    if (size == 0) {
        FILE* empty = fopen("tests/empty_expected.txt", "w");
        if (!empty) {
            fclose(csvIn);
            return;
        }
        fclose(csvIn);
        fclose(empty);
        printf("converting successfully!\n");
        return;
    }
    size_t capacity = 128;
    char* line = malloc(capacity);
    if (line == NULL) {
        printf("mem error");
        fclose(csvIn);
        return;
    }
    while (fgets(line, (int)capacity, csvIn) != NULL) {
        size_t currLen = strlen(line);
        while (currLen > 0 && line[strlen(line) - 1] != '\n' && !feof(csvIn)) {
            size_t oldLineLen = strlen(line);
            capacity *= 2;
            char* temp = realloc(line, capacity);
            if (temp != NULL) {
                line = temp;
            } else {
                free(line);
                fclose(csvIn);
                printf("memmory error");
                return;
            }
            if (fgets(line + oldLineLen, (int)(capacity - oldLineLen), csvIn) == NULL)
                break;
        }
        if (currLen == 0 || line[0] == '\0')
            continue;
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0'; // удаляем \n

        int colInd;
        char** cells = parsing(line, &colInd);

        if (!cells) {
            free(line);
            fclose(csvIn);
            freeList(list);
            printf("memmory error in cells");
            return;
        }

        addToTail(list, cells, colInd);
        cells = NULL;
    }
    fclose(csvIn);
    int maxColCount;
    int* maxColWidths = maxColWidthsFunc(list, &maxColCount); // считаем ширину столбцов
    if (!maxColWidths) {
        free(line);
        freeList(list);
        return;
    }
    free(line);
    tableToFile(list, maxColWidths, maxColCount, output);
}
