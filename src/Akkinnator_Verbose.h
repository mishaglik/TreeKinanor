#ifndef TREEKINATOR_AKKNATOR_VERBOSE_H
#define TREEKINATOR_AKKNATOR_VERBOSE_H
#include "Tree/Tree.h"

enum class Answer{
    NO,
    YES,
    DONT_KNOW,  
};

Answer getAnswer(const char* question);


void fileWriteIn(Node* node, int depth, void* args);

void fileWriteOut(Node* node, int depth, void* args);

void fileWriteCur(Node* node, int depth, void* args);

#endif
