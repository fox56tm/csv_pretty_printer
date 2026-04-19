#include "avlLogic.h"

int nodeHeight(Node* node)
{
    if (node == NULL)
        return -1;

    int leftH = nodeHeight(node->left);

    int rightH = nodeHeight(node->right);

    return 1 + (leftH > rightH ? leftH : rightH);
}

Node* leftRotate(Node* node)
{
    Node* newRoot = node->right;

    Node* newRootL = newRoot->left;

    newRoot->left = node;

    node->right = newRootL;

    node->height = 1 + (nodeHeight(node->left) > nodeHeight(node->right) ? nodeHeight(node->left) : nodeHeight(node->right));

    newRoot->height = 1 + (nodeHeight(newRoot->left) > nodeHeight(newRoot->right) ? nodeHeight(newRoot->left) : nodeHeight(newRoot->right));

    return newRoot;
}

Node* rightRotate(Node* node)
{
    Node* newRoot = node->left;

    Node* newRootR = newRoot->right;

    newRoot->right = node;

    node->left = newRootR;

    node->height = 1 + (nodeHeight(node->left) > nodeHeight(node->right) ? nodeHeight(node->left) : nodeHeight(node->right));

    newRoot->height = 1 + (nodeHeight(newRoot->left) > nodeHeight(newRoot->right) ? nodeHeight(newRoot->left) : nodeHeight(newRoot->right));

    return newRoot;
}
Node* rebalanceNode(Node* node)
{
    if (node == NULL)
        return NULL;

    int heightR = nodeHeight(node->right);
    int heightL = nodeHeight(node->left);
    if ((heightR - heightL) > 1) {

        if (nodeHeight(node->right->left) <= nodeHeight(node->right->right))
            return leftRotate(node);

        else {
            node->right = rightRotate(node->right);

            return leftRotate(node);
        }

    } else if ((heightL - heightR) > 1) {

        if (nodeHeight(node->left->right) <= nodeHeight(node->left->left))
            return rightRotate(node);

        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    } else
        return node;
}

Node* avlInsert(Node* node, char* code, char* name)
{

    if (node == NULL) {
        if (strlen(code) != 3) {
            printf("Uncorrect airport code\n");
            return NULL;
        }

        Node* newNode = malloc(sizeof(Node));

        if (!newNode) {
            printf("not enough memory\n");
            return NULL;
        }

        newNode->left = NULL;
        newNode->right = NULL;

        newNode->name = strdup(name);

        if (!newNode->name) {
            printf("error name saving\n");
            free(newNode);
            return NULL;
        }

        strncpy(newNode->code, code, 3);

        newNode->code[3] = '\0';

        newNode->height = 0;

        return newNode;
    } else {
        int cmp = strcmp(code, node->code);

        if (cmp > 0) {
            node->right = avlInsert(node->right, code, name);
        }

        else if (cmp < 0) {
            node->left = avlInsert(node->left, code, name);
        }

        else {
            printf("this code already in datalist\n");
            return node;
        }
    }

    node->height = 1 + (nodeHeight(node->left) > nodeHeight(node->right) ? nodeHeight(node->left) : nodeHeight(node->right));

    return rebalanceNode(node);
}
void avlRecInsert(avl* avl, char* code, char* name)
{
    int beforeInsert = avlContains(avl->root, code);

    avl->root = avlInsert(avl->root, code, name);

    int afterInsert = avlContains(avl->root, code);

    if (beforeInsert == 0 && afterInsert == 1)
        (avl->nodeCount)++;
}

void avlFind(Node* node, char* code)
{

    Node* curr = node;

    if (!curr)
        return;

    while (curr != NULL) {

        int cmp = strcmp(code, curr->code);

        if (cmp == 0) {

            printf("%s -> %s\n", curr->code, curr->name);
            return;
        }

        else if (cmp > 0) {
            curr = curr->right;
        }

        else
            curr = curr->left;
    }

    printf("Airport with code %s not found in the database.\n", code);
}

int avlContains(Node* node, char* code)
{

    Node* curr = node;

    if (!curr)
        return 0;

    while (curr != NULL) {

        int cmp = strcmp(code, curr->code);

        if (cmp == 0)
            return 1;

        else if (cmp > 0)
            curr = curr->right;

        else
            curr = curr->left;
    }

    return 0;
}
void freeNode(Node* node)
{
    if (node == NULL)
        return;

    free(node->name);

    node->right = NULL;

    node->left = NULL;

    free(node);
}
Node* avlNodeRemove(Node* node, char* code)
{
    if (node == NULL) {
        printf("The database haven't had this code yet\n");
        return NULL;
    }

    if (strcmp(node->code, code) == 0) {

        if ((node->left != NULL) && (node->right != NULL)) { // 2 ребенка

            Node* minNode = minData(node->right);

            strncpy(node->code, minNode->code, 3);

            node->code[3] = '\0';

            free(node->name);

            node->name = strdup(minNode->name);

            node->right = avlNodeRemove(node->right, minNode->code);

        } else if (((node->left == NULL) && (node->right != NULL))) {

            Node* curr = node;

            node = curr->right;

            freeNode(curr);

        } else if (((node->left != NULL) && (node->right == NULL))) {

            Node* curr = node;

            node = curr->left;

            freeNode(curr);

        } else {

            freeNode(node);
            node = NULL;
        }
    } else {
        int cmp = strcmp(node->code, code);
        if (cmp > 0)
            node->left = avlNodeRemove(node->left, code);

        else
            node->right = avlNodeRemove(node->right, code);
    }

    if (node == NULL)
        return NULL;

    node->height = 1 + (nodeHeight(node->left) > nodeHeight(node->right) ? nodeHeight(node->left) : nodeHeight(node->right));

    return rebalanceNode(node);
}

Node* minData(Node* node)
{
    if (node == NULL)
        return NULL;

    if (node->left != NULL)
        return minData(node->left);

    else
        return node;
}

void avlRemove(avl* avl, char* code)
{
    int beforeRemove = avlContains(avl->root, code);

    avl->root = avlNodeRemove(avl->root, code);

    int afterRemove = avlContains(avl->root, code);

    if (beforeRemove == 1 && afterRemove == 0)
        (avl->nodeCount)--;
}

void nodesAddToFile(Node* node, FILE* output)
{

    if (node == NULL)
        return;

    nodesAddToFile(node->left, output);

    fprintf(output, "%s:%s\n", node->code, node->name);

    nodesAddToFile(node->right, output);
}

void avlSave(avl* tree, char* airportList)
{
    FILE* output = fopen(airportList, "w");

    if (!output) {
        printf("file open error\n");
        return;
    }

    nodesAddToFile(tree->root, output);

    fclose(output);

    printf("Base was saved of: %d airports.\n", tree->nodeCount);
}

void addListToAvl(avl* tree, char* airportList)
{
    FILE* input = fopen(airportList, "r");

    if (!input) {
        printf("error open input airport list file\n");
        return;
    }

    char code[4];
    char name[101];

    while (fscanf(input, " %3[^:]:%100[^\n]", code, name) == 2) {

        avlRecInsert(tree, code, name);
    }
    printf("Was downloded: %d airports.\n", tree->nodeCount);

    fclose(input);
}

void interfaceFunctionAvl(avl* tree, char* airportList)
{
    char line[256];

    while (printf("> "), fgets(line, sizeof(line), stdin)) {

        line[strcspn(line, "\n")] = 0;

        if (strncmp(line, "quit", 4) == 0)
            break;

        if (strncmp(line, "find ", 5) == 0) {

            avlFind(tree->root, line + 5);
        } else if (strncmp(line, "add ", 4) == 0) {
            char code[4];

            char name[101];

            sscanf(line + 4, " %3[^:]:%100[^\n]", code, name);

            avlRecInsert(tree, code, name);

            printf("Add airport: %s\n", code);

        } else if (strncmp(line, "delete ", 7) == 0) {

            avlRemove(tree, line + 7);

            printf("Airport %s has been removed from the database.\n", line + 7);
        } else if (strncmp(line, "save", 4) == 0) {

            avlSave(tree, airportList);

        } else {
            printf("please, enter correct commands: find, add, save, delete, quite\n");
        }
    }
}
// остановился на том что реализую функции: добавить в базу -> сохранить текущее состояние базы
//  реализовать через список
