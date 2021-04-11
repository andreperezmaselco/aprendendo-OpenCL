#ifndef OPENCL_PLATFORM_H
#define OPENCL_PLATFORM_H

// OpenCL API
#include <CL/cl.h>

// Aprendendo OpenCL
#include "mathematics/set.h"

typedef struct OpenCLPlatform {
  cl_platform_id id;
  cl_char *name;
  cl_char *vendor;
  cl_char *profile;
  cl_char *version;
  cl_char *extensions;
  Set devices;
} OpenCLPlatform;

void allocOpenCLPlatforms();

void freeOpenCLPlatforms();

void printOpenCLPlatforms();

#endif
