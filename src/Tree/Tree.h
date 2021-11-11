#ifndef TREELINATOR_TREE_H
#define TREELINATOR_TREE_H

#include "stdlib.h"
#include "../../lib/Logger.h"
#include "../../lib/utils.h"

typedef char* tree_data_t;

enum class TreeError{
    OK = 0,

};

struct Node
{
    MGK_OBJECT

    Node* left  = NULL;
    Node* right = NULL;

    tree_data_t data;
};

struct Tree
{
    MGK_OBJECT

    Node* root;
};

#define createNode() _createNode(MGK_CTOR_CALL)
Node* _createNode(MGK_CTOR_DEC);


#define TreeCtor(...) _TreeCtor(__VA_ARGS__, MGK_CTOR_CALL)
TreeError _TreeCtor(Tree* tree, MGK_CTOR_DEC);

void deleteNode(Node* node);

void treeDtor(Tree* tree);


#endif