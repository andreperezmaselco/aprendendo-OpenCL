// C
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Aprendendo OpenCL
#include "arguments.h"

static uint16_t arguments = 0b0000011111101111;

void parseArguments(const int argc, char *const argv[]) {
  for (register uint8_t i = 0; i < argc; i++) {
    // TODO
  }
}

uint8_t getArgument(const uint8_t shift) {
  return arguments >> shift & 1;
}
