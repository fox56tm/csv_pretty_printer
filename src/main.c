#include "avlLogic.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

    avl testAvl = { NULL, 0 };

    addListToAvl(&testAvl, "src/airtest.txt");

    interfaceFunctionAvl(&testAvl, "src/airtest.txt");
}