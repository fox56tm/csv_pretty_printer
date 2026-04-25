#include "ListLogic.h"

int main()
{
    List list = { NULL, NULL, 0 };
    csvConvert("tests/basic.csv", &list, "tests/basic-expected.txt");

    return 0;
}
