#ifndef ARGUMENTS_H
#define ARGUMENTS_H

// C
#include <stdint.h>

// Deslocamento dos argumentos
#define ARGUMENT_PRINT_PLATFORM_NAME 0
#define ARGUMENT_PRINT_PLATFORM_VENDOR 1
#define ARGUMENT_PRINT_PLATFORM_PROFILE 2
#define ARGUMENT_PRINT_PLATFORM_VERSION 3

typedef uint16_t Arguments;

void allocArguments(int argc, char *argv[]);

uint8_t getArgument(uint8_t shift);

#endif
