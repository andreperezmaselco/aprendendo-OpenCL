#ifndef ARGUMENTS_H
#define ARGUMENTS_H

// C
#include <stdint.h>

typedef struct Arguments {
  struct {
    struct {
      uint8_t name : 1;
      uint8_t vendor : 1;
      uint8_t profile : 1;
      uint8_t extensions : 1;
      uint8_t devices : 1;
    } platform;

    struct {
      uint8_t name : 1;
      uint8_t vendor : 1;
      uint8_t profile : 1;
    } device;
  } print;
} Arguments;

void allocArguments(int argc, char *argv[]);

void freeArguments();

#endif
