#include "ListLogic.h"

int isNumberTest()
{
    char* p1 = "sbc";
    char* p2 = "123";
    char* p3 = "1.23";
    if (isNumber(p1) == 1) {
        printf("isNumberTest is faile\n");
        return 1;
    }
    if (isNumber(p2) == 0) {
        printf("isNumberTest is faile\n");
        return 1;
    }
    if (isNumber(p3) == 0) {
        printf("isNumberTest is faile\n");
        return 1;
    }

    return 0;
}

int testListInsert()
{
    List testList = { NULL, NULL, 0 };

    char** testArr = malloc(3 * sizeof(char*) + 3 * 4 * sizeof(char));
    if (!testArr)
        return 1;

    char* data = (char*)(testArr + 3);

    for (int i = 0; i < 3; i++) {
        testArr[i] = data + (i * 4);
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == 0)
                testArr[i][j] = 'a';
            if (i == 1)
                testArr[i][j] = 'b';
            if (i == 2)
                testArr[i][j] = 'c';
        }
    }
    addToTail(&testList, testArr, 4);

    /*for(int i = 0; i < 3; i++){
        for (int j = 0; j< 4; j++){
            printf("%c ", testList.head->Cells[i][j]);

        }
        printf("\n");
    }*/
    if (testList.nodeCount == 0) {
        printf("testListInsert is faile(node count = %d)", testList.nodeCount);
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {

            if (testList.head->Cells[i][j] != 'a' && testList.head->Cells[i][j] != 'b' && testList.head->Cells[i][j] != 'c') {
                printf("testListInsert is faile, uncorrect elements in list");
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    int a = testListInsert();
    int d = isNumberTest();
    int failed = a + d;
    if (failed != 0)
        printf("tests don't pass\n");

    else
        printf("tests passed\n");
}