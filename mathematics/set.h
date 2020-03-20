#ifndef MATHEMATICS_SET_H
#define MATHEMATICS_SET_H

// C Library
#include <stddef.h>

typedef struct Set
{
    size_t cardinality;
    void *elements;
} Set;

#endif
