// C
#include <stdint.h>
#include <stdlib.h>

// Aprendendo OpenCL
#include "arguments.h"

static Arguments arguments = 0b0000111100111111;

void parseArguments(int argc, char *argv[]) {
  // TODO
}

uint8_t getArgument(uint8_t shift) {
  return arguments >> shift & 1;
}
