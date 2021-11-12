#include "StringBuffer.h"
#include "../../lib/Logger.h"
#include "../../lib/utils.h"


const size_t BUFFER_INIT_SZ = 16;
const size_t EXPAND_COEF    = 2;

void stringBufferCtor(StringBuffer* buffer){
    LOG_ASSERT(buffer != NULL);

    buffer->strings = (const char**)mgk_calloc(BUFFER_INIT_SZ, sizeof(const char*));

    buffer->capacity = BUFFER_INIT_SZ;
    buffer->size = 0;
}

void stringBufferExpand(StringBuffer* buffer){
    LOG_ASSERT(buffer != NULL);
    LOG_ASSERT(buffer->strings != NULL);

    buffer->strings = (const char**)mgk_realloc(buffer->strings, buffer->capacity * EXPAND_COEF, sizeof(const char*));
}

size_t stringBufferPush(StringBuffer* buffer, const char* string){
    LOG_ASSERT(buffer != NULL);
    LOG_ASSERT(buffer->strings != NULL);

    if(buffer->size == buffer->capacity){
        stringBufferExpand(buffer);
    }

    buffer->strings[buffer->size] = string;
    return buffer->size++;
}

void stringBufferDtor(StringBuffer* buffer){
    LOG_ASSERT(buffer != NULL);
    LOG_ASSERT(buffer->strings != NULL);

    for(size_t i = 0; i < buffer->size; ++i){
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wcast-qual"
        free((char*)(buffer->strings[i]));
        #pragma GCC diagnostic pop
    }

    free(buffer->strings);
    buffer->strings = NULL;

    buffer->size = 0;
    buffer->capacity = 0;

}