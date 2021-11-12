#ifndef TREEKINATOR_AKKNATOR_VERBOSE_H
#define TREEKINATOR_AKKNATOR_VERBOSE_H
#include "Tree/Tree.h"

enum class Answer{
    NO,
    YES,
    DONT_KNOW,  
};

enum class AkkMode{
    GAME,
    DEF,
    DIFF,
    DUMP,
};

Answer getAnswer(const char* question);

AkkMode akkinatorAskMode();

int askAgain();


void fileWriteIn (Node* node, int depth, void* args);

void fileWriteOut(Node* node, int depth, void* args);

void fileWriteCur(Node* node, int depth, void* args);


void graphWriteIn (Node* node, int depth, void* args);

void graphWriteCur(Node* node, int depth, void* args);


void printWin();

void printNextTry();

void printLose();

void printAngry();


char* askAskedPerson();

char* askDifference(const char* first, const char* second);

#endif
