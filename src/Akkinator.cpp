#include "../lib/Stack.h"
#include "Akkinator.h"
#include "Akkinnator_Verbose.h"

const char* AKKINATOR_GRAPH_FILENAME = "log/Akk_GRAPH.dot";
const char* AKKINATOR_IMAGE_FILENAME = "log/Akk_GRAPH.png";

const size_t MAX_COMMAND_LEN = 100;

void akkinatorCtor(Akkinator* akkinator){
    LOG_ASSERT(akkinator != NULL);

    TreeCtor(&akkinator->tree);

    stringBufferCtor(&akkinator->stringBuf);    
}

//------------------------------------------------------------------------------------------------------------------------------------------

void akkinatorDtor(Akkinator* akkinator){
    LOG_ASSERT(akkinator != NULL);

    treeDtor(&akkinator->tree);

    stringBufferDtor(&akkinator->stringBuf);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void akkinatorPlayGame(Akkinator* akkinator){
    LOG_ASSERT(akkinator != NULL);
    
    Stack backTrace = {};
    stack_init(&backTrace);

    Node* curNode = akkinator->tree.root;
    int isWin = 0;

    while(!isWin){
        if(curNode == NULL){
            LOG_FATAL("Incorrect tree\n");
        }

        Answer ans = getAnswer(curNode->data);

        switch (ans)
        {
        case Answer::YES:
            if(curNode->left == NULL){
                isWin = 1;
                printWin();
                break;
            }
            curNode = curNode->left;
            break;

        case Answer::NO:
            if(curNode->right == NULL){
                if(backTrace.size > 0){
                    printNextTry();
                    stack_pop(&backTrace, (void**)&curNode);
                }
                else{
                    printLose();
                    isWin = -1;
                    break;
                }
            }
            curNode = curNode->right;
            break;

        case Answer::DONT_KNOW:
            if(curNode->left == NULL){
                printAngry();
                isWin = 1;
                break;
            }
            stack_push(&backTrace, curNode);
            curNode = curNode->left;
            break;
        default:
            LOG_FATAL("Incorrect answer\n");
            break;
        }
    }
    stack_free(&backTrace);

    if(isWin != -1)
        return;

    char* newPerson  = askAskedPerson();
    char* difference = askDifference(curNode->data, newPerson);

    stringBufferPush(&akkinator->stringBuf, newPerson);
    stringBufferPush(&akkinator->stringBuf, difference);

    curNode->left  = createNode();
    curNode->right = createNode();

    curNode->right->data = curNode->data;
    curNode->left->data  = newPerson;
    curNode->data        = difference;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void akkinatorGetDefinition(Akkinator* akkinator){
    LOG_ASSERT(akkinator != NULL);
    LOG_FATAL("%s not implemented yet", __func__);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void akkinatorSplitDifference(Akkinator* akkinator){
    LOG_ASSERT(akkinator != NULL);
    LOG_FATAL("%s not implemented yet", __func__);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void akkinatorGraph(Akkinator* akkinator){
    LOG_ASSERT(akkinator != NULL);
    LOG_ASSERT(akkinator->tree.root != NULL);

    FILE* file = fopen(AKKINATOR_GRAPH_FILENAME, "w");

    fprintf(file,   "digraph G{"
                    "   ");
    
    WalkParams params = {WalkMode::Postfix, &graphWriteIn, NULL, &graphWriteCur, NULL};
    treeWalk(akkinator->tree.root, &params, (void*)file);

    fprintf(file, "}");

    fclose(file);

    char command[MAX_COMMAND_LEN] = {};

    sprintf(command, "dot %s -T png -o %s", AKKINATOR_GRAPH_FILENAME, AKKINATOR_IMAGE_FILENAME);
    system(command);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void akkinatorRead(Akkinator* akkinator, const char* filename){
    LOG_ASSERT(akkinator != NULL);
    LOG_ASSERT(filename  != NULL);

    akkinator->tree.root = createNode();
    akkinator->tree.root->data = "NULL";
}

//------------------------------------------------------------------------------------------------------------------------------------------

void akkinatorWrite(Akkinator* akkinator, const char* filename){
    LOG_ASSERT(akkinator != NULL);
    LOG_ASSERT(akkinator->tree.root != NULL);
    LOG_ASSERT(filename != NULL);

    FILE* file = fopen(filename, "w");
    
    WalkParams params = {WalkMode::Prefix, &fileWriteIn, &fileWriteOut, &fileWriteCur, NULL};
    treeWalk(akkinator->tree.root, &params, (void*)file);

    fclose(file);
}

