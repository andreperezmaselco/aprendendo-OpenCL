#ifndef OPENCL_DEVICE_H
#define OPENCL_DEVICE_H

// OpenCL
#include <CL/cl.h>

// Aprendendo OpenCL
#include "set.h"
#include "platform.h"

typedef struct OpenCLDevice {
  cl_device_id id;
  cl_char *name;
  cl_char *vendor;
  cl_char *profile;
  cl_char *version;
  cl_device_type type;
} OpenCLDevice;

void *getOpenCLDeviceInfo(cl_device_id device_id,
                          cl_device_info device_info);

void allocOpenCLDevices(OpenCLPlatform *const platform);

void freeOpenCLDevices(Set *const devices);

#endif
