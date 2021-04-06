#include "arguments.h"

void allocArguments(int argc, char *argv[]) {
  extern Arguments arguments;
  *(uint16_t *)&arguments = 0b0000011100011111;
}
