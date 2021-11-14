#include <string.h>
#include "Akkinnator_Verbose.h"

// #define printf(...) {voice(__VA_ARGS__); printf(__VA_ARGS__);}

const size_t MAX_ANSWER_SZ = 10;

const size_t MAX_TTS_COMMAND_SZ = 1000;

char PRINT_STRING[MAX_TTS_COMMAND_SZ] = {};
size_t print_string_iter = 0;

#define printf(...) myprintf(__VA_ARGS__)

Answer getAnswer(const char* question){
    LOG_ASSERT(question != NULL);
    
    printf("Это %s?\n", question);
    flush_global_string();

    char answer[MAX_ANSWER_SZ] = {};
    scanf("%10s", answer);

    if(answer[0] == 'y' || answer[0] == 'Y' || answer[0] == '1'){
        return Answer::YES;
    }

    if(answer[0] == 'n' || answer[0] == 'N' || answer[0] == '0'){
        return Answer::NO;
    }
    printf("Твоё мямленье истолковано как \"Не знаю\"\n");
    flush_global_string();
    return Answer::DONT_KNOW;
}

AkkMode akkinatorAskMode(){
    int mode = -1;
    if(mode >= (int)AkkMode::NONE || mode < 0){
        printf("Выберите режим работы: ");
        flush_global_string();
        scanf("%d", &mode);
    }
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
#ifdef DEBUG_GRAPH
    fprintf(file, "N%p[label=\"%s[%p]\"];\n", node, node->data, node);
#else
    fprintf(file, "N%p[label=\"%s\"];\n", node, node->data);
#endif
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
    printf("Я победил, ха. Я самый умный у меня неуд (11)\n");
    flush_global_string();
}

void printNextTry(){
    printf("Ладно, попробуем ещё...\n");
    flush_global_string();
}

void printLose(){
    printf("Хорошо, я сдаюсь. Ты победил.\n");
    flush_global_string();
}

void printAngry(){
    printf("Как я погляжу ты сам не знаешь кого загадал. Так что будем считать я победил.\n");
    flush_global_string();
}


char* askAskedPerson(){
    printf("Так кто же это был?\n");
    flush_global_string();
    return askString();
}

char* askDifference(const char* first, const char* second){
    LOG_ASSERT(first  != NULL);
    LOG_ASSERT(second != NULL);

    printf("Так а в чем разница меджу %s и %s?\n", first, second);
    flush_global_string();

    return askString();
}

int askAgain(){
    printf("Ещё разочек?\n");
    flush_global_string();

    char answer[MAX_ANSWER_SZ] = {};
    scanf("%s", answer);

    return answer[0] == 'Y' || answer[0] == 'y' || answer[0]=='1';
}


char* askForDef(){
    printf("O чём тебе поведать дорогой друг?\n");
    flush_global_string();
    return askString();
}

char* askForDiff1(){
    printf("Назови 1й объект.\n");
    flush_global_string();
    return askString();
}

char* askForDiff2(){
    printf("Назови 2й объект.\n");
    flush_global_string();
    return askString();
}

void printDef(Stack* stack){
    LOG_ASSERT(stack != NULL);
    printf("%s ", ((Node*)(stack->data[stack->size - 1]))->data);

    for(size_t i = 0; i < stack->size - 1; ++i){
        printOneEdje((Node*)(stack->data[i]), (Node*)(stack->data[i+1]));
    }
    printf("\n");
    flush_global_string();
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
        if(i == st1->size - 2){
            printf("и ");
        }
        printOneEdje((Node*)st1->data[i], (Node*)st1->data[i+1]);
    }
    printf("\n");
    printf("A %s ", ((Node*)(st2->data[st2->size - 1]))->data);
    for(size_t i = nCommon; i < st2->size - 1; ++i){
        if(i == st2->size - 2){
            printf("и ");
        }
        printOneEdje((Node*)st2->data[i], (Node*)st2->data[i+1]);
    }
    printf("\n");
    flush_global_string();
}

void printDontKnow(const char* s){
    LOG_ASSERT(s != NULL);

    printf("Увы я ничего не знаю о %s\n", s);
    flush_global_string();
}

void printOneEdje(Node* par, Node* chld){
    LOG_ASSERT(par  != NULL);
    LOG_ASSERT(chld != NULL);

    if(chld == par->right){
        printf("не ");
    }
    printf("%s, ", par->data);
}

char* askString(){
    char* string = NULL;
    while(string == NULL){
        scanf(" %m[^\n]", &string);
        LOG_DEBUG("Read string \"%s\"\n", string);
    }
    return string;
}

void voice(const char* format, ...){
    LOG_ASSERT(format != NULL);

    char command[2*MAX_TTS_COMMAND_SZ] = {};
    char string [MAX_TTS_COMMAND_SZ] = {};

    va_list args;
    va_start(args, format);
    vsprintf(string, format, args);
    va_end(args);

    sprintf(command,"./voice.sh \"%s\"", string);

    system(command);
}

#undef printf

void myprintf(const char* format, ...){

    va_list args;
    va_start(args, format);
    print_string_iter += vsprintf(PRINT_STRING + print_string_iter, format, args);
    va_end(args);

}

void flush_global_string(){
    printf("%s", PRINT_STRING);
    voice(PRINT_STRING);
    print_string_iter = 0;
}