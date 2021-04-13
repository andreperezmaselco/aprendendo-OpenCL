// C
#include <stdio.h>
#include <stdlib.h>

// OpenCL API
#include <CL/cl.h>

// Aprendendo OpenCL
#include "arguments.h"
#include "mathematics/set.h"
#include "OpenCL/device.h"
#include "OpenCL/error.h"
#include "OpenCL/platform.h"

static Set *platforms = NULL;

static void *getOpenCLPlatformInfo(cl_platform_id platform_id,
                                   cl_platform_info platform_info) {
  // Tentar obter o tamanho do valor do parâmetro.
  size_t param_value_size;
  OpenCLError error = {clGetPlatformInfo(platform_id, platform_info, 0, NULL, &param_value_size)};

  // Se o tamanho do valor do parâmetro não foi retornado, então retornar NULL.
  if (error.code != CL_SUCCESS) {
    return NULL;
  }

  // Tentar obter o valor do parâmetro.
  void *param_value = malloc(param_value_size);
  error.code = clGetPlatformInfo(platform_id, platform_info, param_value_size, param_value, NULL);

  // Se o valor do parâmetro não foi retornado,
  // então desalocar 'param_value' e retornar NULL.
  if (error.code != CL_SUCCESS) {
    free(param_value);
    return NULL;
  }

  return param_value;
}

void allocOpenCLPlatforms() {
  // Se 'platforms' for um ponteiro nulo, então retornar.
  if (platforms == NULL) {
    platforms = malloc(sizeof(Set));
  }

  // Tentar obter a quantidade de plataformas.
  OpenCLError error = {clGetPlatformIDs(0, NULL, (cl_uint *)&platforms->cardinality)};

  // Se não houver plataformas, então retornar.
  if (error.code != CL_SUCCESS || platforms->cardinality == 0) {
    return;
  }

  // Tentar obter os IDs das plataformas.
  cl_platform_id platform_ids[platforms->cardinality];
  error.code = clGetPlatformIDs(platforms->cardinality, platform_ids, NULL);

  if (error.code != CL_SUCCESS) {
    return;
  }

  platforms->elements = calloc(platforms->cardinality, sizeof(OpenCLPlatform));

  for (register uint8_t i = 0; i < platforms->cardinality; i++) {
    OpenCLPlatform *platform = platforms->elements + i * sizeof(OpenCLPlatform);
    platform->id = platform_ids[i];

    if (getArgument(ARGUMENT_PRINT_PLATFORM_NAME)) {
      platform->name = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_NAME);
    }

    if (getArgument(ARGUMENT_PRINT_PLATFORM_VENDOR)) {
      platform->vendor = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_VENDOR);
    }

    if (getArgument(ARGUMENT_PRINT_PLATFORM_PROFILE)) {
      platform->profile = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_PROFILE);
    }

    if (getArgument(ARGUMENT_PRINT_PLATFORM_VERSION)) {
      platform->version = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_VERSION);
    }

    if (getArgument(ARGUMENT_PRINT_PLATFORM_EXTENSIONS)) {
      platform->extensions = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_EXTENSIONS);
    }

    if (getArgument(ARGUMENT_PRINT_PLATFORM_DEVICES)) {
      allocOpenCLDevices(platform);
    }
  }
}

void freeOpenCLPlatforms() {
  if (platforms == NULL || platforms->elements == NULL) {
    return;
  }

  for (register uint8_t i = 0; i < platforms->cardinality; i++) {
    OpenCLPlatform *platform = platforms->elements + i * sizeof(OpenCLPlatform);
    free(platform->name);
    free(platform->vendor);
    free(platform->profile);
    free(platform->version);
    free(platform->extensions);
    freeOpenCLDevices(&platform->devices);
  }

  free(platforms->elements);
  free(platforms);
  platforms = NULL;
}

void printOpenCLPlatforms() {
  if (platforms == NULL || platforms->elements == NULL) {
    puts("platforms: null");
    return;
  }

  puts("platforms:");
  for (register uint8_t i = 0; i < platforms->cardinality; i++) {
    const OpenCLPlatform *const platform = platforms->elements + i * sizeof(OpenCLPlatform);

    if (getArgument(ARGUMENT_PRINT_PLATFORM_NAME)) {
      printf("    name: %s\n", platform->name);
    }

    if (getArgument(ARGUMENT_PRINT_PLATFORM_VENDOR)) {
      printf("    vendor: %s\n", platform->vendor);
    }

    if (getArgument(ARGUMENT_PRINT_PLATFORM_PROFILE)) {
      printf("    profile: %s\n", platform->profile);
    }

    if (getArgument(ARGUMENT_PRINT_PLATFORM_VERSION)) {
      printf("    version: %s\n", platform->version);
    }

    if (getArgument(ARGUMENT_PRINT_PLATFORM_EXTENSIONS)) {
      printf("    extensions: %s\n", platform->extensions);
    }

    if (platform->devices.elements == NULL) {
      puts("    devices: null");
      continue;
    }

    puts("    devices:");
    for (register uint8_t j = 0; j < platform->devices.cardinality; j++) {
      const OpenCLDevice *const device = platform->devices.elements + j * sizeof(OpenCLDevice);

      if (getArgument(ARGUMENT_PRINT_DEVICE_NAME)) {
        printf("        name: %s\n", device->name);
      }

      if (getArgument(ARGUMENT_PRINT_DEVICE_VENDOR)) {
        printf("        vendor: %s\n", device->vendor);
      }

      if (getArgument(ARGUMENT_PRINT_DEVICE_PROFILE)) {
        printf("        profile: %s\n", device->profile);
      }

      if (getArgument(ARGUMENT_PRINT_DEVICE_VERSION)) {
        printf("        version: %s\n", device->version);
      }

      if (getArgument(ARGUMENT_PRINT_DEVICE_TYPE)) {
        const char *deviceType;
        switch (device->type) {
          case CL_DEVICE_TYPE_DEFAULT:
            deviceType = (const char []){"DEFAULT"};
            break;
          case CL_DEVICE_TYPE_CPU:
            deviceType = (const char []){"CPU"};
            break;
          case CL_DEVICE_TYPE_GPU:
            deviceType = (const char []){"GPU"};
            break;
          case CL_DEVICE_TYPE_ACCELERATOR:
            deviceType = (const char []){"ACCELERATOR"};
            break;
          default:
            break;
        }
        printf("        type: %s\n", deviceType);
      }

      // Adicionar linha vazia entre as plataformas.
    }
  }
}
