#include "listLogic.h"

int main()
{
    // srand(time(NULL));

    List testList = { NULL, 0 };

    addListToList(&testList, "../airports.txt");

    // interfaceFunctionList(&testList, "src/airtest.txt"); раскомментировать для работы с базой

    //----------------профилирование

    char(*codes)[4] = malloc(10000 * sizeof(*codes));

    if (!codes) {
        printf("not enough memory\n");
        return 1;
    }

    // int count = 0;  1й сценарий

    // collectCodesToArray(&testList, codes, &count);

    // int i = 0;
    // while (i < 50000) {
    //     listFind(&testList, codes[rand() % testList.nodeCount]);
    //     i++;
    // }

    int i = 0; /// 2 сценарий
    for (char a = 'A'; a <= 'Z' && i < 10000; a++) {
        for (char b = 'A'; b <= 'Z' && i < 10000; b++) {
            for (char c = 'A'; c <= 'Z' && i < 10000; c++) {
                codes[i][0] = a;
                codes[i][1] = b;
                codes[i][2] = c;
                codes[i][3] = '\0';
                i++;
            }
        }
    }
    i = 0;

    while (i < 10000) {
        listInsert(&testList, codes[i], "testname");
        // listFind(&testList, codes[rand() % 10000]);
        i++;
    }

    freeList(&testList);
}