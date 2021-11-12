#include "../../lib/Stack.h"
#undef LOCATION
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

//--------------------------------------------------------------------------

void treeWalk(Node* node, WalkParams* walkparams, void* args, int depth){
    LOG_ASSERT(node != NULL);
    LOG_ASSERT(walkparams != NULL);

    #define ACTION(f) if(f){f(node, depth, args);}

    ACTION(walkparams->inFunc);

    if(walkparams->walkMode == WalkMode::Prefix){
        ACTION(walkparams->curFunc);
    }

    if(node->left != NULL){
        treeWalk(node->left, walkparams, args, depth + 1);
    }
    else{
        ACTION(walkparams->nullFunc);
    }

    if(walkparams->walkMode == WalkMode::Infix){
        ACTION(walkparams->curFunc);
    }

    if(node->right != NULL){
        treeWalk(node->right, walkparams, args, depth + 1);
    }

    if(walkparams->walkMode == WalkMode::Postfix){
        ACTION(walkparams->curFunc);
    }

    ACTION(walkparams->outFunc);
    #undef ACTION
}

Node* treeFind(Node* node, Stack* stack, tree_data_t search){
    LOG_ASSERT(node  != NULL);
    LOG_ASSERT(stack != NULL);

    stack_push(stack, node);

    if(node->data == search){
        return node;
    }

    if(node->left && treeFind(node->left, stack, search)) return (Node*)stack->data[stack->size - 1];

    if(node->right && treeFind(node->right, stack, search)) return (Node*)stack->data[stack->size - 1];

    stack_pop(stack);

    return NULL;
}