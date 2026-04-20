#include "avlLogic.h"

int main()
{

    avl testAvl = { NULL, 0 };

    addListToAvl(&testAvl, "src/airtest.txt");

    interfaceFunctionAvl(&testAvl, "src/airtest.txt");
}