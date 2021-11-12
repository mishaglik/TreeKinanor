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

typedef void (*walk_action_f)(Node*, int, void*);

enum class WalkMode{
    Prefix,
    Infix,
    Postfix,
};

struct WalkParams{
    WalkMode walkMode = WalkMode::Prefix;

    walk_action_f   inFunc = NULL;
    walk_action_f  outFunc = NULL;
    walk_action_f  curFunc = NULL;
    walk_action_f nullFunc = NULL;
};

#define createNode() _createNode(MGK_CTOR_CALL(NULL))
Node* _createNode(MGK_CTOR_DEC);


#define TreeCtor(tree) _TreeCtor(tree, MGK_CTOR_CALL(tree))
TreeError _TreeCtor(Tree* tree, MGK_CTOR_DEC);

void deleteNode(Node* node);

void treeDtor(Tree* tree);

void treeWalk(Node* node, WalkParams* walkparams, void* args = NULL, int depth = 0);


#endif