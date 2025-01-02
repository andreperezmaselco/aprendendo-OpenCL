// C
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Aprendendo OpenCL
#include "arguments.h"

static uint16_t arguments = 0b0000011111101111;

void parseArguments(const int argc, char *const argv[]) {
  for (register uint8_t i = 0; i < argc; i++) {
    if (strcmp(argv[i], "--platform") == 0 && argv[i + 1]) {
      arguments &= 0b0000011111000000;
      const char *token = strtok(argv[i + 1], ",");
      do {
        if (strcmp(token, "name") == 0) {
          arguments |= 1 << ARGUMENT_PRINT_PLATFORM_NAME;
        } else if (strcmp(token, "vendor") == 0) {
          arguments |= 1 << ARGUMENT_PRINT_PLATFORM_VENDOR;
        } else if (strcmp(token, "profile") == 0) {
          arguments |= 1 << ARGUMENT_PRINT_PLATFORM_PROFILE;
        } else if (strcmp(token, "version") == 0) {
          arguments |= 1 << ARGUMENT_PRINT_PLATFORM_VERSION;
        } else if (strcmp(token, "extensions") == 0) {
          arguments |= 1 << ARGUMENT_PRINT_PLATFORM_EXTENSIONS;
        } else if (strcmp(token, "devices") == 0) {
          arguments |= 1 << ARGUMENT_PRINT_PLATFORM_DEVICES;
        }
      } while (token = strtok(NULL, ","));
    } else if (strcmp(argv[i], "--device") == 0 && argv[i + 1]) {
      arguments &= 0b0000000000111111;
      const char *token = strtok(argv[i + 1], ",");
      do {
        if (strcmp(token, "name") == 0) {
          arguments |= 1 << ARGUMENT_PRINT_DEVICE_NAME;
        } else if (strcmp(token, "vendor") == 0) {
          arguments |= 1 << ARGUMENT_PRINT_DEVICE_VENDOR;
        } else if (strcmp(token, "profile") == 0) {
          arguments |= 1 << ARGUMENT_PRINT_DEVICE_PROFILE;
        } else if (strcmp(token, "version") == 0) {
          arguments |= 1 << ARGUMENT_PRINT_DEVICE_VERSION;
        } else if (strcmp(token, "type") == 0) {
          arguments |= 1 << ARGUMENT_PRINT_DEVICE_TYPE;
        }
      } while (token = strtok(NULL, ","));
    }
  }
}

uint8_t getArgument(const uint8_t shift) {
  return arguments >> shift & 1;
}
