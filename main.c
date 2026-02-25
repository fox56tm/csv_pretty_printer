#include "ListLogic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    List myList = { NULL, NULL, 0 };

    FILE* csvIn = fopen("test1.csv", "r");

    size_t capacity = 128; // минимальный буфер

    char* line = malloc(capacity);
    if (line == NULL) {
        printf("mem error");
        fclose(csvIn);
        return 1;
    }

    while (fgets(line, (int)capacity, csvIn) != NULL) {
        size_t currLen = strlen(line);

        while (currLen > 0 && line[strlen(line) - 1] != '\n' && !feof(csvIn)) {
            size_t oldLineLen = strlen(line);

            capacity *= 2;

            char* temp = realloc(line, capacity);

            if (temp != NULL)
                line = temp;

            else {
                free(line);
                fclose(csvIn);
                printf("memmory error");
                return 1;
            }

            if (fgets(line + oldLineLen, (int)(capacity - oldLineLen), csvIn) == NULL)
                break;
        }

        if (currLen == 0 || line[0] == '\0')
            continue;

        line[strlen(line) - 1] = '\0'; // убираем \n

        char* token = strtok(line, ",");

        int colInd = 0; // номер столбца

        char** cells = NULL;

        //--------------------------------

        while (token != NULL) {

            char** temp = realloc(cells, (colInd + 1) * sizeof(char*));

            if (temp != NULL)
                cells = temp;

            else {
                for (int i = 0; i < colInd; i++)
                    free(cells[i]);

                free(cells);
                free(line);
                fclose(csvIn);

                printf("memmory error");

                return 1;
            }

            cells[colInd] = strdup(token);

            colInd++;

            token = strtok(NULL, ",");
        }

        addToTail(&myList, cells, colInd);

        cells = NULL;
    }
    fclose(csvIn);
    //--------------------------------

    int maxColCount = 0;

    Node* curr = myList.head;

    for (int i = 0; i < myList.nodeCount; i++) {
        if ((curr->cols) > maxColCount)
            maxColCount = (curr->cols);

        curr = curr->next;
    }
    if (maxColCount == 0) {
        freeList(&myList);
        free(line);
        return 1;
    }
    int* maxColWidths = calloc(maxColCount, sizeof(int));

    if (maxColWidths == NULL) {
        free(maxColWidths);
        free(line);
        freeList(&myList);
        printf("memmory error");
        return 1;
    }
    curr = myList.head;

    for (int i = 0; i < myList.nodeCount; i++) {

        for (int j = 0; j < curr->cols; j++) {

            if (strlen(curr->Cells[j]) > maxColWidths[j])
                maxColWidths[j] = (int)strlen(curr->Cells[j]);
        }
        curr = curr->next;
    }

    //--------------------------------
    FILE* outTxt = fopen("csv_to_txt.txt", "w");

    printHorizonLines(outTxt, maxColWidths, myList.head->cols, '=');

    for (int i = 0; i < (myList.head->cols); i++) {
        fprintf(outTxt, "| %-*s ", maxColWidths[i], myList.head->Cells[i]);
    }
    fprintf(outTxt, "|\n");

    printHorizonLines(outTxt, maxColWidths, myList.head->cols, '=');

    Node* curr2 = myList.head->next;

    for (int i = 0; i < myList.nodeCount - 1; i++) {
        for (int j = 0; j < curr2->cols; j++) {
            if (isNumber(curr2->Cells[j]))
                fprintf(outTxt, "| %*s ", maxColWidths[j], curr2->Cells[j]);

            else
                fprintf(outTxt, "| %-*s ", maxColWidths[j], curr2->Cells[j]);
        }
        fprintf(outTxt, "|\n");

        printHorizonLines(outTxt, maxColWidths, myList.head->cols, '-');

        curr2 = curr2->next;
    }
    fclose(outTxt);
    free(line);
    free(maxColWidths);
    freeList(&myList);

    printf("converting is ready!");

    return 0;
}
