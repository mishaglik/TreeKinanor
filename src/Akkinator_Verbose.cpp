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

    fprintf(file, "N%p[label=\"%s\"];\n", node, node->data);
    
}

void graphWriteCur(Node* node, int, void* args){
    LOG_ASSERT(node != NULL);
    LOG_ASSERT(args != NULL);

    FILE* file = (FILE*)args;

    if(node->left)
        fprintf(file, "N%p->N%p[label=\"+\"];\n", node, node->left);

    if(node->right)
        fprintf(file, "N%p->N%p[label=\"-\"];\n", node, node->right);
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


char* askForDef(){
    printf("O чём тебе поведать дорогой друг?\n");
    char* str = NULL;
    scanf("%ms", &str);
    return str;
}

char* askForDiff1(){
    printf("Назови 1й объект.\n");
    char* str = NULL;
    scanf("%ms", &str);
    return str;
}

char* askForDiff2(){
    printf("Назови 2й объект.\n");
    char* str = NULL;
    scanf("%ms", &str);
    return str;
}

void printDef(Stack* stack){
    LOG_ASSERT(stack != NULL);
    printf("%s ", ((Node*)(stack->data[stack->size - 1]))->data);

    for(size_t i = 0; i < stack->size - 1; ++i){
        printOneEdje((Node*)(stack->data[i]), (Node*)(stack->data[i+1]));
    }
    printf("\n");
}

void printDiff(Stack* st1, Stack* st2){
    LOG_ASSERT(st1 != NULL);
    LOG_ASSERT(st2 != NULL);

    size_t nCommon = 0;

    if(st1->data[1] == st2->data[1]){
        printf("%s и %s похожи тем, что они оба ", ((Node*)(st1->data[st1->size - 1]))->data, ((Node*)(st2->data[st2->size - 1]))->data);
        
        for(size_t i = 0; i < st1->size - 1 && st1->data[i+1] == st2->data[i+1]; ++i){
            printOneEdje((Node*)(st1->data[i]), (Node*)st1->data[i+1]);
            nCommon++;
        }
    }    
    printf("\n");
    printf("Но %s ", ((Node*)(st1->data[st1->size - 1]))->data);
    for(size_t i = nCommon; i < st1->size - 1; ++i){
        printOneEdje((Node*)st1->data[i], (Node*)st1->data[i+1]);
    }
    printf("\n");
    printf("A %s ", ((Node*)(st2->data[st2->size - 1]))->data);
    for(size_t i = nCommon; i < st2->size - 1; ++i){
        printOneEdje((Node*)st2->data[i], (Node*)st2->data[i+1]);
    }
    printf("\n");

}

void printDontKnow(const char* s){
    LOG_ASSERT(s != NULL);

    printf("Увы я ничего не знаю о %s\n", s);
}

void printOneEdje(Node* par, Node* chld){
    LOG_ASSERT(par  != NULL);
    LOG_ASSERT(chld != NULL);

    if(chld == par->right){
        printf("не ");
    }
    printf("%s, ", par->data);
}