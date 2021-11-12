#include <string.h>

#include "../lib/Stack.h"
#include "../lib/File.h"

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

    char* str = askForDef();
    Stack stack = {};

    stack_init(&stack);

    treeFind(akkinator->tree.root, &stack, stringBufferFindSame(&akkinator->stringBuf, str));

    printDef(&stack);

    stack_free(&stack);
    free(str);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void akkinatorSplitDifference(Akkinator* akkinator){
    LOG_ASSERT(akkinator != NULL);

    char* str1 = askForDiff1();

    const char* trueStr1 = stringBufferFindSame(&akkinator->stringBuf, str1);

    if(!trueStr1){
        printDontKnow(str1);
        free(str1);
        return;
    }

    char* str2 = askForDiff2();
    const char* trueStr2 = stringBufferFindSame(&akkinator->stringBuf, str2);
    if(!trueStr2){
        printDontKnow(str2);
        free(str1);
        free(str2);
        return;
    }

    Stack st1 = {}, st2 = {};

    stack_init(&st1);
    stack_init(&st2);

    treeFind(akkinator->tree.root, &st1, trueStr1);
    treeFind(akkinator->tree.root, &st2, trueStr2);

    printDiff(&st1, &st2);

    stack_free(&st1);
    stack_free(&st2);
    free(str1);
    free(str2);
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

    FILE* file = fopen(filename, "r");

    char* text = NULL;
    size_t size = getFileSize(file);
    getText(file, &text, size);

    fclose(file);

    Node* curNode = createNode();
    
    akkinator->tree.root = curNode;

    Stack stack = {};
    stack_init(&stack);

    char* curChr = text;
    curChr += strspn(curChr, " \t\n");

    if(*curChr !=  '{'){
        LOG_FATAL("File has bad format\n");
        free(text);
        return;
    }
    
    curChr++;
    char* newStr = NULL;
    char* nxtQuote = NULL;

    while (*curChr != '\0')
    {
        curChr += strspn(curChr, " \t\n");

        switch (*curChr)
        {
        case '{':
            stack_push(&stack, curNode);
            if(!(curNode->left)){
                curNode->left = createNode();
                curNode = curNode->left;
            }
            else{
                if(curNode->right){
                    LOG_FATAL("File has bad format\n");
                    free(text);
                    return;
                }
                curNode->right = createNode();
                curNode = curNode->right;
            }
            curChr++;
            break;

        case '}':
            if(stack.size == 0){
                curChr++;
                if(sscanf(curChr, " %*s") > 0){
                    LOG_FATAL("Bad file format\n");
                    free(text);
                    return;
                }
                break;
            }

            stack_pop(&stack, (void**)&curNode);
            curChr++;
            break;

        case '\"':
            nxtQuote = strchr(curChr + 1, '\"');

            if(nxtQuote == NULL){
                LOG_FATAL("File has bad format\n");
                free(text);
                return;
            }
            newStr = (char*)mgk_calloc((size_t)(nxtQuote - (curChr + 1)), sizeof(char));
            strncpy(newStr, curChr + 1, (size_t)(nxtQuote - (curChr + 1)));
            
            curNode->data = newStr;
            stringBufferPush(&akkinator->stringBuf, newStr);
            
            curChr = nxtQuote + 1;
            break;

        case '\0':
            break;

        default:
            LOG_FATAL("File has bad format\n");
            free(text);
            return;
        }
    }

    free(text);
    return;
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


