#include "Tree.h"


Node* _createNode(MGK_CTOR_DEC){
    Node* node = (Node*)mgk_calloc(1, sizeof(Node));

    MGK_CTOR_DEF(node);

    return node;
}

//--------------------------------------------------------------------------

TreeError _TreeCtor(Tree* tree, MGK_CTOR_DEC){
    LOG_ASSERT(tree != NULL);

    MGK_CTOR_DEF(tree);

    return TreeError::OK;
}

void deleteNode(Node* node){
    LOG_ASSERT(node != NULL);

    if(node->left)
        deleteNode(node->left);
    if(node->right)
        deleteNode(node->right);
    
    node->left = NULL;
    node->right = NULL;
    
    node->data = NULL;

    free(node);
}

//--------------------------------------------------------------------------

void treeDtor(Tree* tree){
    LOG_ASSERT(tree != NULL);

    if(tree->root)
        deleteNode(tree->root);
    
}