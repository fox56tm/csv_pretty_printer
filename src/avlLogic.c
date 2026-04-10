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

Node* avlInsert(Node* node, char* code, char* name)
{   

    if (node == NULL)
    {
        if(strlen(code) != 3){ printf("Uncorrect airport code"); return NULL;}  
    
        Node* newNode = malloc(sizeof(Node));

        if(!newNode) {printf("not enough memory"); return NULL;}

        newNode->left = NULL;
        newNode->right = NULL;

        char* newName = malloc(strlen(name) + 1);

        if(!newName) {printf("error name saving"); return NULL;}

        newNode -> name = newName;
        newName = NULL;

        strncpy(newNode -> code, code, 3);

        return newNode;
    }
    else 
    {
        int cmp = strcmp(code, node->code);

        if (cmp > 0) node->right = avlInsert(node -> right, code, name);

        else if(cmp <0 ) node->right = avlInsert(node -> right, code, name);
        
        else {printf("this code already in datalist"); return node;}

    }

    node -> height = 1 + (nodeHeight(node -> left) > nodeHeight(node -> right) ? nodeHeight(node -> left) : nodeHeight(node -> right));

    return rebalanceNode(node);
}


Node* rebalanсeNode(Node* node)
{
    if(nodeHeight(node -> right) > nodeHeight(node -> left)){
        
        if(nodeHeight(node -> right -> left) <= nodeHeight(node -> right -> right)) return rightRotate(node);

        else return leftRotate(node);
    }
    else if(nodeHeight(node -> right) < nodeHeight(node -> left)){
        
        if(nodeHeight(node -> left -> right) <= nodeHeight(node -> left -> left)) return rightRotate(node);

        else return leftRotate(node);
    }
    else return node;

}
//остановился на том что реализую функции поворота -> удаление из дерева -> find -> добавить в базу -> сохранить текущее состояние базы
