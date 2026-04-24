#include "../src/listLogic.h"

int insertTest()
{
    List t = { NULL, 0 };
    listInsert(&t, "AMS", "Amsterdam");
    listInsert(&t, "SVO", "Sheremetyevo");
    listInsert(&t, "LED", "Pulkovo");
    int count = t.nodeCount;
    freeList(&t);

    return count;
}
int containsTest()
{
    List t = { NULL, 0 };
    listInsert(&t, "SVO", "Sheremetyevo");
    int found = listContains(&t, "SVO");
    int notFound = listContains(&t, "LED");
    freeList(&t);

    return found == 1 && notFound == 0;
}
int containsEmptyTest()
{
    List t = { NULL, 0 };
    int result = listContains(&t, "SVO");

    return result == 0;
}
int removeHeadTest()
{
    List t = { NULL, 0 };
    listInsert(&t, "AAA", "A");
    listInsert(&t, "BBB", "B");
    listRemove(&t, "BBB");
    int count = t.nodeCount;
    int contains = listContains(&t, "BBB");
    freeList(&t);

    return count == 1 && contains == 0;
}
int removeMiddleTest()
{
    List t = { NULL, 0 };
    listInsert(&t, "AAA", "A");
    listInsert(&t, "BBB", "B");
    listInsert(&t, "CCC", "C");
    listRemove(&t, "AAA");
    int count = t.nodeCount;
    int contains = listContains(&t, "AAA");
    freeList(&t);

    return count == 2 && contains == 0;
}

int removeNonexistentTest()
{
    List t = { NULL, 0 };
    listInsert(&t, "AMS", "Amsterdam");
    listRemove(&t, "ZZZ");
    int count = t.nodeCount;
    freeList(&t);

    return count == 1;
}

int removeOnlyNodeTest()
{
    List t = { NULL, 0 };
    listInsert(&t, "AMS", "Amsterdam");
    listRemove(&t, "AMS");

    return t.nodeCount == 0 && t.head == NULL;
}

int main()
{
    printf("insertTest (expected 3): %d\n", insertTest());
    printf("containsTest (expected 1): %d\n", containsTest());
    printf("containsEmptyTest (expected 1): %d\n", containsEmptyTest());
    printf("removeHeadTest (expected 1): %d\n", removeHeadTest());
    printf("removeMiddleTest (expected 1): %d\n", removeMiddleTest());
    printf("removeNonexistent (expected 1): %d\n", removeNonexistentTest());
    printf("removeOnlyNode (expected 1): %d\n", removeOnlyNodeTest());

    return 0;
}