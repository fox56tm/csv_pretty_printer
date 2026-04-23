#include "../src/avlLogic.h"

int heightTest()
{
    avl t = { NULL, 0 };

    const char* codes[] = { "AAA", "BBB", "CCC", "DDD", "EEE", "FFF", "GGG" };
    for (int i = 0; i < 7; i++)
        avlRecInsert(&t, (char*)codes[i], "test");

    int h = nodeHeight(t.root);

    freeRecAvl(&t);

    return h;
}

int insertTest()
{
    avl t = { NULL, 0 };

    avlRecInsert(&t, "AMS", "Amsterdam");
    avlRecInsert(&t, "SVO", "Sheremetyevo");
    avlRecInsert(&t, "LED", "Pulkovo");

    int count = t.nodeCount;

    freeRecAvl(&t);

    return count;
}

int duplicateTest()
{
    avl t = { NULL, 0 };

    avlRecInsert(&t, "AMS", "Amsterdam");
    avlRecInsert(&t, "AMS", "Amsterdam");

    int count = t.nodeCount;

    freeRecAvl(&t);

    return count;
}

int containsTest()
{
    avl t = { NULL, 0 };

    avlRecInsert(&t, "SVO", "Sheremetyevo");

    int found = avlContains(t.root, "SVO");
    int notFound = avlContains(t.root, "LED");

    freeRecAvl(&t);

    return found == 1 && notFound == 0;
}
int removeTest()
{
    avl t = { NULL, 0 };

    avlRecInsert(&t, "BBB", "B");
    avlRecInsert(&t, "AAA", "A");
    avlRecInsert(&t, "CCC", "C");

    avlRemove(&t, "AAA");

    int count = t.nodeCount;
    int contains = avlContains(t.root, "AAA");

    freeRecAvl(&t);

    return count == 2 && contains == 0;
}

int removeNonexistentTest()
{
    avl t = { NULL, 0 };

    avlRecInsert(&t, "AMS", "Amsterdam");

    avlRemove(&t, "ZZZ");

    int count = t.nodeCount;

    freeRecAvl(&t);

    return count == 1;
}

int main()
{
    printf("insertTest (expected 3): %d\n", insertTest());
    printf("duplicateTest (expected 1): %d\n", duplicateTest());
    printf("containsTest (expected 1): %d\n", containsTest());
    printf("removeTest (expected 1): %d\n", removeTest());
    printf("removeNonexistent (expected 1): %d\n", removeNonexistentTest());
    printf("heightTest expected <= 3): %d\n", heightTest());

    return 0;
}