#ifndef TREEKINATOR_AKKINATOR_H
#define TREEKINATOR_AKKINATOR_H

#include "Tree/Tree.h"
#include "StringBuffer/StringBuffer.h"

struct Akkinator
{
    Tree tree = {};
    
    StringBuffer stringBuf = {};    
};


void akkinatorCtor(Akkinator* akkinator);

void akkinatorDtor(Akkinator* akkinator);

void akkinatorPlayGame(Akkinator* akkinator);

void akkinatorGetDefinition(Akkinator* akkinator);

void akkinatorSplitDifference(Akkinator* akkinator);

void akkinatorGraph(Akkinator* akkinator);

void akkinatorRead(Akkinator* akkinator, const char* filename);

void akkinatorWrite(Akkinator* akkinator, const char* filename);


#endif