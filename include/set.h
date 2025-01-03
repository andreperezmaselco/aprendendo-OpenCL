#ifndef SET_H
#define SET_H

/* C */
#include <stddef.h>

typedef struct Set {
  size_t cardinality;
  void *elements;
} Set;

#endif
