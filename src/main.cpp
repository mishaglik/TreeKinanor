#include "../lib/Logger.h"
#include "Akkinator.h"
#include "Akkinnator_Verbose.h"

int main(int argc, char* argv[]){
    const char* db = "Akk.db";
    
    if(argc > 1){
        db = argv[1];
    }

    Akkinator akk = {};
    akkinatorCtor(&akk);

    akkinatorRead(&akk, db);
    do{
        AkkMode mode = akkinatorAskMode();

        switch (mode)
        {
        case AkkMode::GAME:
            akkinatorPlayGame(&akk);
            break;
        case AkkMode::DIFF:
            akkinatorSplitDifference(&akk);
            break;
        case AkkMode::DEF:
            akkinatorGetDefinition(&akk);
            break;
        case AkkMode::DUMP:
            akkinatorGraph(&akk);
            break;
        case AkkMode::NONE:
        default:
            LOG_FATAL("Wrong akkinator mode");
            break;
        }

    }while(askAgain());

    akkinatorWrite(&akk, db);

    akkinatorDtor(&akk);
    return 0;
}