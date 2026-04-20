#include "listLogic.h"

int main()
{

    List testList = { NULL, 0 };

    addListToList(&testList, "src/airtest.txt");

    interfaceFunctionList(&testList, "src/airtest.txt");

    freeList(&testList);
}