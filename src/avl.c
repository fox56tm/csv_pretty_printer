#include "avlLogic.h"

int main()
{
    // srand(time(NULL));

    avl testAvl = { NULL, 0 };

    addListToAvl(&testAvl, "../airports.txt");

    // interfaceFunctionAvl(&testAvl, "src/airtest.txt"); раскомментировать для работы с базой

    //----------------профилирование

    char(*codes)[4] = malloc(10000 * sizeof(*codes));

    if (!codes) {
        printf("not enough memory\n");
        return 1;
    }

    // int count = 0;   для первого сценария

    // collectCodesToArray(testAvl.root, codes, &count);

    // int i = 0;
    // while (i < 50000) {
    //     avlFind(testAvl.root, codes[rand() % testAvl.nodeCount]);
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
        avlRecInsert(&testAvl, codes[i], "testname");
        // avlFind(testAvl.root, codes[rand() % 10000]);
        i++;
    }

    freeRecAvl(&testAvl);
}