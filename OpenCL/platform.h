#ifndef OPENCL_PLATFORM_H
#define OPENCL_PLATFORM_H

// OpenCL API
#include <CL/cl.h>

#include "mathematics/set.h"

typedef struct OpenCLPlatform {
    cl_platform_id id;
    cl_char *name;
    cl_char *vendor;
    cl_char *profile;
    cl_char *extensions;
    Set devices;
} OpenCLPlatform;

void *getOpenCLPlatformInfo(
    cl_platform_id platform_id,
    cl_platform_info platform_info
);

void allocOpenCLPlatforms(Set *platforms);

void freeOpenCLPlatforms(Set *platforms);

void printOpenCLInfo(Set *platforms);

#endif
