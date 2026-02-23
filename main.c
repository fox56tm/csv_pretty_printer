#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListLogic.h"

int main()
{
    List My_list = {NULL, NULL};

    FILE *file = fopen("test.csv", "r");

    size_t capacity = 128; // минимальный буфер

    char * line = malloc(capacity); // считанная строка

    while(!feof(file))
    {
        while(1)     //читаем пока не будет \n
        {
            fgets(line, capacity, file);

            if (line[strlen(line) - 1] == '\n') break;       //если все влезло идем делить на токены

            else
            {
                capacity *= 2;

                char * temp = realloc(line, capacity);

                if (temp != NULL) line = temp;

                else
                {
                    printf("memmory error");
                    return 0;
                }
            }
        }
        line[strlen(line) - 1] = '\0';   //убираем \n

        char * token = strtok(len, ",");

        int col_ind = 0; //номер столбца

        char ** cells = NULL;


        while(token != NULL)
        {

            char ** temp = realloc(cells, (col_ind + 1) * sizeof(char*));

            if (temp != NULL) cells = temp;

            else
            {
                for(int i = 0; i < col_ind; i++) free(cells[i]);  //очищаем все что уже навыделяли

                printf("memmory error");

                return 0;
            }

                cells[col_ind] = strdup(token);

                col_ind++;

                token = strtok(NULL, ",");

        }

        add_to_tail(&List.head, &List.tail, cells, col_ind);

        cells = NULL;

        col_ind = 0;


    }

    return 0;
}
void show(Node * head)
{
    Node * curr = head;
    while(curr != NULL){
        printf("%s\n", curr -> Data);
        curr = curr -> next;
    }


}
