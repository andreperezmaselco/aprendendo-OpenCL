// C
#include <stdint.h>
#include <stdlib.h>

// Aprendendo OpenCL
#include "arguments.h"

static Arguments *arguments = NULL;

void allocArguments(int argc, char *argv[]) {
  if (arguments == NULL && (arguments = malloc(sizeof(Arguments))) == NULL) {
    return;
  }

  *(uint16_t *)arguments = 0b0000111100111111;
}

void freeArguments() {
  free(arguments);
  arguments = NULL;
}
