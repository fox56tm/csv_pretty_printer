#include "logic.h"

int main()
{
    int capitalCount;
    int cities;
    int roads;
    FILE* capitals;
    Node** graph = roadsRead("tests/test.txt", &capitalCount, &cities, &roads, &capitals);

    if (graph != NULL)
        printStatesAndCities(graph, capitalCount, cities, capitals);

    else {
        printf("Error\n");
        return 1;
    }
}