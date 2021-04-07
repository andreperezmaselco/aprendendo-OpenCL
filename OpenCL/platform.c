// C Library
#include <stdio.h>
#include <stdlib.h>

// OpenCL API
#include <CL/cl.h>

#include "mathematics/set.h"
#include "OpenCL/device.h"
#include "OpenCL/error.h"
#include "OpenCL/platform.h"

void *getOpenCLPlatformInfo(cl_platform_id platform_id,
                            cl_platform_info platform_info) {
  size_t param_value_size;
  OpenCLError error = {clGetPlatformInfo(platform_id, platform_info, 0, NULL, &param_value_size)};

  // If 'clGetPlatformInfo' was not executed
  // successfully, then return.
  if (error.code != CL_SUCCESS) {
    return NULL;
  }

  void *param_value = malloc(param_value_size);
  error.code = clGetPlatformInfo(platform_id, platform_info, param_value_size, param_value, NULL);
  if (error.code != CL_SUCCESS) {
    return NULL;
  }

  return param_value;
}

void allocOpenCLPlatforms(Set *const platforms) {
  if (platforms == NULL) {
    return;
  }

  OpenCLError error = {clGetPlatformIDs(0, NULL, (cl_uint *)&platforms->cardinality)};

  // If there are no platforms, then return.
  if (error.code != CL_SUCCESS || platforms->cardinality == 0) {
    return;
  }

  cl_platform_id platform_ids[platforms->cardinality];
  error.code = clGetPlatformIDs(platforms->cardinality, platform_ids, NULL);

  if (error.code != CL_SUCCESS) {
    return;
  }

  platforms->elements = calloc(platforms->cardinality, sizeof(OpenCLPlatform));

  for (register uint8_t i = 0; i < platforms->cardinality; i++) {
    OpenCLPlatform *platform = platforms->elements + i * sizeof(OpenCLPlatform);
    platform->id = platform_ids[platform - (OpenCLPlatform *)platforms->elements];
    platform->name = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_NAME);
    platform->vendor = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_VENDOR);
    platform->profile = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_PROFILE);
    platform->extensions = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_EXTENSIONS);
    allocOpenCLDevices(platform);
  }
}

void freeOpenCLPlatforms(Set *const platforms) {
  if (platforms == NULL ||
      platforms->elements == NULL) {
    return;
  }

  for (register uint8_t i = 0; i < platforms->cardinality; i++) {
    OpenCLPlatform *platform = platforms->elements + i * sizeof(OpenCLPlatform);
    free(platform->name);
    free(platform->vendor);
    free(platform->profile);
    free(platform->extensions);
    freeOpenCLDevices(&platform->devices);
  }

  free(platforms->elements);
  platforms->cardinality = 0;
  platforms->elements = NULL;
}

void printOpenCLPlatforms(const Set *const platforms) {
  if (platforms == NULL ||
      platforms->elements == NULL) {
    puts("No OpenCL platforms allocated.");
    return;
  }

  puts("OpenCL platforms:");
  for (register uint8_t i = 0; i < platforms->cardinality; i++) {
    OpenCLPlatform *platform = platforms->elements + i * sizeof(OpenCLPlatform);
    printf("    name: %s\n", platform->name);
    printf("    vendor: %s\n", platform->vendor);
    printf("    profile: %s\n", platform->profile);

    Set *devices = &platform->devices;
    if (devices == NULL ||
        devices->elements == NULL) {
      puts("    devices: (null)");
      continue;
    }

    puts("    devices:");
    for (register uint8_t j = 0; j < devices->cardinality; j++) {
      OpenCLDevice *device = devices->elements + j * sizeof(OpenCLDevice);
      printf("        name: %s\n", device->name);
      printf("        vendor: %s\n", device->vendor);
      printf("        profile: %s\n", device->profile);
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
  }
}
