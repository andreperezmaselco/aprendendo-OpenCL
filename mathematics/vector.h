#ifndef MATHEMATICS_VECTOR_H
#define MATHEMATICS_VECTOR_H

#include <stdio.h>

typedef struct Vector
{
    union {
        struct
        {
            size_t dimension;
            void *components;
        };
        struct
        {
            const size_t dimension = 3;
            float x;
            float y;
            float z;
        };
    };
} Vector;

#endif
