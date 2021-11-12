#include <string.h>
#include "Akkinnator_Verbose.h"

const size_t MAX_ANSWER_SZ = 10;

//TODO: Fool protection
Answer getAnswer(const char* question){
    LOG_ASSERT(question != NULL);
    
    printf("Это %s?\n", question);

    char answer[MAX_ANSWER_SZ] = {};
    scanf("%10s", answer);

    if(strcmp(answer, "Yes") == 0){
        return Answer::YES;
    }

    if(strcmp(answer, "No") == 0){
        return Answer::NO;
    }
    
    return Answer::DONT_KNOW;
}

AkkMode akkinatorAskMode(){
    int mode = -1;
    printf("Choose work mode: ");
    scanf("%d", &mode);
    return (AkkMode)mode;
}

void fileWriteIn (Node* node, int depth, void* args){
    LOG_ASSERT(node != NULL);
    LOG_ASSERT(args != NULL);

    FILE* file = (FILE*)args;

    for(int i = 0; i < depth; ++i){
        fprintf(file, "\t");
    }

    fprintf(file, "{");
    if(node->left){
        fprintf(file, "\n");
    }
}

void fileWriteOut(Node* node, int depth, void* args){
    LOG_ASSERT(node != NULL);
    LOG_ASSERT(args != NULL);

    FILE* file = (FILE*)args;

    if(node->left != NULL){
        for(int i = 0; i < depth; ++i){
            fprintf(file, "\t");
        }
    }
    fprintf(file, "}\n");
}

void fileWriteCur(Node* node, int depth, void* args){
    LOG_ASSERT(node != NULL);
    LOG_ASSERT(args != NULL);

    FILE* file = (FILE*)args;

    if(node->left != NULL){
        for(int i = 0; i < depth; ++i){
            fprintf(file, "\t");
        }
    }

    fprintf(file,"\"%s\"" ,node->data);
    if(node->left){
        fprintf(file, "\n");
    }
}


void graphWriteIn (Node* node, int, void* args){
    LOG_ASSERT(node != NULL);
    LOG_ASSERT(args != NULL);

    FILE* file = (FILE*)args;

    fprintf(file, "N%d[label=\"%s\"];\n", nodeHash(node), node->data);
    
}

void graphWriteCur(Node* node, int, void* args){
    LOG_ASSERT(node != NULL);
    LOG_ASSERT(args != NULL);

    FILE* file = (FILE*)args;

    if(node->left)
        fprintf(file, "N%d->N%d[label=\"+\"];\n", nodeHash(node), nodeHash(node->left));

    if(node->right)
        fprintf(file, "N%d->N%d[label=\"-\"];\n", nodeHash(node), nodeHash(node->right));
}

void printWin(){
    printf("Я победил, ха. Я самый умный у меня неуд(10)\n");
}

void printNextTry(){
    printf("Ладно, попробуем ещё...\n");
}

void printLose(){
    printf("Хорошо, я сдаюсь. Ты победил.\n");
}

void printAngry(){
    printf("Как я погляжу ты сам не знаешь кого загадал. Так что будем считать я победил.\n");
}


char* askAskedPerson(){
    printf("Так кто же это был?\n");
    char* str = NULL;
    scanf("%ms", &str);
    return str;
}

char* askDifference(const char* first, const char* second){
    LOG_ASSERT(first  != NULL);
    LOG_ASSERT(second != NULL);

    printf("Так а в чем разница меджу %s и %s?\n", first, second);

    char* str = NULL;
    scanf("%ms", &str);
    return str;
}

int askAgain(){
    printf("Ещё разочек?\n");

    char answer[MAX_ANSWER_SZ] = {};
    scanf("%s", answer);

    return answer[0] == 'Y' || answer[0] == 'y';
}