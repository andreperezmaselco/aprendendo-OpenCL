#ifndef ARGUMENTS_H
#define ARGUMENTS_H

// C Library
#include <stdint.h>

typedef struct Arguments {
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
} Arguments;

void allocArguments(int argc, char *argv[]);

#endif
