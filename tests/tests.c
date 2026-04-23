#include "../src/ListLogic.h"

int fileContains(const char* path, const char* word)
{
    FILE* f = fopen(path, "r");
    if (!f)
        return 0;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, word)) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int convertTest()
{
    FILE* f = fopen("tests/basic.csv", "w");
    fprintf(f, "name,age,city\n");
    fprintf(f, "Alice,25.76,New York\n");
    fprintf(f, "Bob,30.0\n");
    fprintf(f, "Charlie,22.34,London\n");
    fclose(f);

    List list = { NULL, NULL, 0 };

    csvConvert("tests/basic.csv", &list, "tests/basic-expected.txt");

    int name = fileContains("tests/basic-expected.txt", "name");
    int alice = fileContains("tests/basic-expected.txt", "Alice");
    int fl = fileContains("tests/basic-expected.txt", "25.76");
    int charlie = fileContains("tests/basic-expected.txt", "Charlie");
    int bob = fileContains("tests/basic-expected.txt", "Bob");

    return name && alice && fl && charlie && bob;
}

int emptyFileTest()
{
    FILE* f = fopen("tests/test-empty.csv", "w");
    fclose(f);

    List list = { NULL, NULL, 0 };
    csvConvert("tests/test-empty.csv", &list, "tests/test-empty-expected.txt");
    int emptyList = list.nodeCount == 0;

    return emptyList;
}

int isNumberTest()
{
    int t1 = isNumber("42") == 1;
    int t2 = isNumber("3.14") == 1;
    int t3 = isNumber("-7") == 1;
    int t4 = isNumber("+100") == 1;
    int t5 = isNumber("abc") == 0;
    int t6 = isNumber("1.2.3") == 0;
    int t7 = isNumber("") == 0;
    int t8 = isNumber("12abc") == 0;

    return t1 && t2 && t3 && t4 && t5 && t6 && t7 && t8;
}

int main(void)
{
    printf("isNumberTest (expected 1): %d\n", isNumberTest());
    printf("basicTableTest (expected 1): %d\n", convertTest());
    printf("emptyFileTest (expected 1): %d\n", emptyFileTest());

    return 0;
}