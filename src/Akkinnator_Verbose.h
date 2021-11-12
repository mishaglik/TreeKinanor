#ifndef TREEKINATOR_AKKNATOR_VERBOSE_H
#define TREEKINATOR_AKKNATOR_VERBOSE_H
#include "Tree/Tree.h"

// #define DEBUG_GRAPH

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
    NONE,
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

char* askForDef();

char* askForDiff1();

char* askForDiff2();

void printDef(Stack* stack);

void printDiff(Stack* st1, Stack* st2);

void printDontKnow(const char* s);

void printOneEdje(Node* par, Node* chld);

char* askString();

#endif
