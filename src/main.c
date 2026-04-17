#include <stdio.h>
#include <stdlib.h>
#include "avlLogic.h"

int main()
{

    avl testAvl = {NULL,0};

    char *code = "COD";

    char* name = "Test name";

    avlRootInsert(&testAvl, code, name);

    avlRootInsert(&testAvl, "COD", "krya");
    avlRootInsert(&testAvl, "RUS", "PRIVET");
    avlRootInsert(&testAvl, "ART", "UBER");
    avlRootInsert(&testAvl, "MAK", "MEGA UBER");

    avlFind(testAvl.root, "COD");
    avlFind(testAvl.root, "ART");
    printf("%d\n", testAvl.nodeCount);
    
}