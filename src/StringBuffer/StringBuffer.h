#ifndef STRING_BUFFER_H
#define STRING_BUFFER_H

#include <stdlib.h>

struct StringBuffer
{
    const char** strings = NULL;
    size_t size          = 0;
    size_t capacity      = 0;
};

void stringBufferCtor(StringBuffer* buffer);

void stringBufferExpand(StringBuffer* buffer);

size_t stringBufferPush(StringBuffer* buffer, const char* string);

void stringBufferDtor(StringBuffer* buffer);

#endif
