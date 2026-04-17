#include "avlLogic.h"

int nodeHeight(Node* node)
{
    if (node == NULL)
        return -1;

    int leftH = nodeHeight(node->left);

    int rightH = nodeHeight(node->right);

    return 1 + (leftH > rightH ? leftH : rightH);
}

int avlHeight(avl* tree)
{
    return nodeHeight(tree->root);
}


Node* leftRotate(Node* node)
{   
    Node* newRoot = node -> right;

    Node* newRootL = newRoot -> left;

    newRoot -> left = node;

    node -> right = newRootL;

    node -> height = 1 + (nodeHeight(node -> left) > nodeHeight(node -> right) ? nodeHeight(node -> left) : nodeHeight(node -> right));

    newRoot -> height = 1 + (nodeHeight(newRoot -> left) > nodeHeight(newRoot -> right) ? nodeHeight(newRoot -> left) : nodeHeight(newRoot -> right));

    return newRoot;

}

Node* rightRotate(Node* node)
{
    Node* newRoot = node -> left;

    Node* newRootR = newRoot -> right;

    newRoot -> right = node;

    node -> left = newRootR;

    node -> height = 1 + (nodeHeight(node -> left) > nodeHeight(node -> right) ? nodeHeight(node -> left) : nodeHeight(node -> right));

    newRoot -> height = 1 + (nodeHeight(newRoot -> left) > nodeHeight(newRoot -> right) ? nodeHeight(newRoot -> left) : nodeHeight(newRoot -> right));

    return newRoot;

}
Node* rebalanсeNode(Node* node)
{
    if(nodeHeight(node -> right) > nodeHeight(node -> left)){
        
        if(nodeHeight(node -> right -> left) <= nodeHeight(node -> right -> right)) return leftRotate(node);

        else 
            {
                node -> right = rightRotate(node-> right);

                return leftRotate(node);
            }

    }
    else if(nodeHeight(node -> right) < nodeHeight(node -> left)){
        
        if(nodeHeight(node -> left -> right) <= nodeHeight(node -> left -> left)) return rightRotate(node);

        else 
        {
            node -> left = leftRotate(node -> left);
            return rightRotate(node);
        }
    }   
    else return node;

}

Node* avlInsert(Node* node, char* code, char* name)
{   

    if (node == NULL)
    {
        if(strlen(code) != 3){ printf("Uncorrect airport code\n"); return NULL;}  
    
        Node* newNode = malloc(sizeof(Node));

        if(!newNode) {printf("not enough memory\n"); return NULL;}

        newNode->left = NULL;
        newNode->right = NULL;

        size_t lenName = strlen(name);
        char* newName = malloc(lenName + 1);

        if(!newName) {printf("error name saving\n"); return NULL;}

        strncpy(newName,name, lenName);

        newNode -> name = newName;
        
        newName = NULL;

        strncpy(newNode -> code, code, 3);

        return newNode;
    }
    else 
    {
        int cmp = strcmp(code, node->code);

        if (cmp > 0){
            node->right = avlInsert(node -> right, code, name);}

        else if(cmp < 0 ) {
            node->left = avlInsert(node -> left, code, name);}
        
        else {printf("this code already in datalist\n"); return node;}

    }


    node -> height = 1 + (nodeHeight(node -> left) > nodeHeight(node -> right) ? nodeHeight(node -> left) : nodeHeight(node -> right));

    return rebalanсeNode(node);

}
void avlRootInsert(avl* avl, char* code, char* name)
{
    avl -> root = avlInsert(avl->root, code, name);

    (avl -> nodeCount)++;

    return;
}




void avlFind(Node* node, char* code)
{

    Node* curr = node;

    if(!curr) return;

    while (curr != NULL) {

        int cmp = strcmp(code, curr->code);
        if (cmp > 0) {
            curr = curr -> right;
        }

        if (cmp < 0) {
            curr = curr -> left;
        } 
        if (cmp == 0) {

            for(int i = 0; i < 3; i++)
                printf("%c", curr -> code[i]);
            printf(" -> ");
            size_t len = strlen(curr -> name);
            for(int i = 0; i < len; i++)
                printf("%c", curr -> name[i]);
            printf("\n");
            return;
        }
    }

    printf("The base doesn't have this code\n");
    return;
    

}

/*void avlNodeRemove(Node* node ,char* code)
{

    Node* curr = node;
    Node* currPrev = NULL;

    while (curr != NULL) {

        if (curr->data == value) {

            if (currPrev != NULL) {

                if ((curr->left != NULL) && (curr->right != NULL)) {
                    curr->data = minData(curr->right);
                    nodeDeliter(curr->right, minData(curr->right));
                    return;
                } else if (((curr->left == NULL) && (curr->right != NULL))) {
                    if (currPrev->data > curr->data)
                        currPrev->left = curr->right;
                    else
                        currPrev->right = curr->right;
                    free(curr);
                    return;
                } else if (((curr->left != NULL) && (curr->right == NULL))) {
                    if (currPrev->data > curr->data)
                        currPrev->left = curr->left;
                    else
                        currPrev->right = curr->left;
                    free(curr);
                    return;
                } else {
                    if (currPrev->data > curr->data)
                        currPrev->left = NULL;
                    else
                        currPrev->right = NULL;
                    free(curr);
                    return;
                }
            } else {
                if ((curr->left != NULL) && (curr->right != NULL)) {
                    curr->data = minData(curr->right);
                    nodeDeliter(curr->right, minData(curr->right));
                    return;
                } else if (((curr->left == NULL) && (curr->right != NULL)) || ((curr->left != NULL) && (curr->right == NULL))) {

                    free(curr);
                    return;

                }

                else {
                    currPrev = NULL;
                    free(curr);
                    return;
                }
            }
        }

        if (curr->data > value) {
            currPrev = curr;
            curr = curr->left;
        } else {
            currPrev = curr;
            curr = curr->right;
        }
    }
    printf("takogo uzla net");
}

*/

//остановился на том что реализую функции поворота -> find -> удаление из дерева(думаю как удалять рекурсивно, потому что надо возвращать Node* и балансировать) -> добавить в базу -> сохранить текущее состояние базы
// реализовать через список
