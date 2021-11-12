#include "Akkinator.h"
#include "Akkinnator_Verbose.h"

void akkinatorCtor(Akkinator* akkinator){
    LOG_ASSERT(akkinator != NULL);

    TreeCtor(&akkinator->tree);

    stringBufferCtor(&akkinator->stringBuf);    
}

void akkinatorDtor(Akkinator* akkinator);

void akkinatorPlayGame(Akkinator* akkinator);

void akkinatorGetDefinition(Akkinator* akkinator);

void akkinatorSplitDifference(Akkinator* akkinator);

void akkinatorGraph(Akkinator* akkinator);

void akkinatorRead(Akkinator* akkinator, const char* filename);

void akkinatorWrite(Akkinator* akkinator, const char* filename){
    LOG_ASSERT(akkinator != NULL);
    LOG_ASSERT(akkinator->tree.root != NULL);
    LOG_ASSERT(filename != NULL);

    FILE* file = fopen(filename, "w");
    
    WalkParams params = {WalkMode::Prefix, &fileWriteIn, &fileWriteOut, &fileWriteCur, NULL};
    treeWalk(akkinator->tree.root, &params, (void*)file);

    fclose(file);
}