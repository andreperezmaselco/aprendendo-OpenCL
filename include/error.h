#ifndef OPENCL_ERROR_H
#define OPENCL_ERROR_H

// OpenCL API
#include <CL/cl.h>

typedef struct OpenCLError {
  cl_int code;
  cl_char *message;
} OpenCLError;

#endif
