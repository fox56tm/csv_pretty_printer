#include "ListLogic.h"

int main()
{
    List myList = { NULL, NULL, 0 };

    FILE* csvIn = fopen("tests/float.csv", "r");
    if (csvIn == NULL) {
        printf("Error open");
        return 1;
    }

    fseek(csvIn, 0, SEEK_END);

    long size = ftell(csvIn);
    fseek(csvIn, 0, SEEK_SET);

    if (size == 0) {
        FILE* empty = fopen("tests/empty_expected.txt", "w");
        if (!empty) {
            fclose(csvIn);
            return 1;
        }
        fclose(csvIn);
        fclose(empty);
        printf("converting successfully!\n");
        return 0;
    }

    size_t capacity = 128;

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

        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0'; // удялем \n

        int colInd = 0;

        char** cells = NULL;

        //--------------------------------  массив токенов

        char* start = line; // начало текущей ячейки
        char* p = line; // указатель для прохода

        while (1) {

            if (*p == ',' || *p == '\0') {
                int end = (*p == '\0'); // дошли ли до конца

                *p = '\0';

                char** temp = realloc(cells, (colInd + 1) * sizeof(char*));

                if (temp != NULL) {
                    cells = temp;
                } else {
                    for (int i = 0; i < colInd; i++)
                        free(cells[i]);

                    free(cells);
                    free(line);
                    fclose(csvIn);

                    printf("memory error");
                    return 1;
                }

                // копируем кусок
                cells[colInd] = strdup(start);
                colInd++;

                if (end) {
                    break;
                }

                start = p + 1;
            }
            p++;
        }

        addToTail(&myList, cells, colInd);

        cells = NULL;
    }
    fclose(csvIn);
    //--------------------------------  считаем ширину столбцов

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

    //--------------------------------  записываем таблицу в файл
    FILE* outTxt = fopen("tests/float_expected.txt", "w");

    printHorizonLines(outTxt, maxColWidths, myList.head->cols, '=');

    for (int i = 0; i < (myList.head->cols); i++) {
        fprintf(outTxt, "| %-*s ", maxColWidths[i], myList.head->Cells[i]);
    }
    fprintf(outTxt, "|\n");

    printHorizonLines(outTxt, maxColWidths, maxColCount, '=');

    Node* curr2 = myList.head->next;

    for (int i = 0; i < myList.nodeCount - 1; i++) {
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
    free(line);
    free(maxColWidths);
    freeList(&myList);

    printf("converting successfully!\n");

    return 0;
}
