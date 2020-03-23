#ifndef OPENCL_DEVICE_H
#define OPENCL_DEVICE_H

// OpenCL API
#include <CL/cl.h>

#include "mathematics/set.h"
#include "OpenCL/platform.h"

typedef struct OpenCLDevice {
    cl_device_id id;
    cl_char *name;
    cl_char *vendor;
    cl_char *profile;
    cl_device_type type;
} OpenCLDevice;

void *getOpenCLDeviceInfo(
    cl_device_id device_id,
    cl_device_info device_info
);

void allocOpenCLDevices(OpenCLPlatform *platform);

void freeOpenCLDevices(Set *devices);

#endif
