// C Library
#include <stdlib.h>

// OpenCL API
#include <CL/cl.h>

#include "mathematics/set.h"
#include "OpenCL/device.h"
#include "OpenCL/platform.h"

void *getOpenCLDeviceInfo(cl_device_id device_id,
                          cl_device_info device_info) {
  size_t param_value_size;
  cl_int error = clGetDeviceInfo(device_id, device_info, 0, NULL, &param_value_size);
  if (error != CL_SUCCESS) {
    return NULL;
  }

  void *param_value = malloc(param_value_size);
  error = clGetDeviceInfo(device_id, device_info, param_value_size, param_value, NULL);
  if (error != CL_SUCCESS) {
    return NULL;
  }

  return param_value;
}

void allocOpenCLDevices(OpenCLPlatform *platform) {
  if (platform == NULL) {
    return;
  }

  cl_uint num_devices;
  cl_int error = clGetDeviceIDs(platform->id, CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);

  // If 'clGetDeviceIDs' was not executed successfully
  // or there are no devices, then return.
  if (error != CL_SUCCESS ||
      num_devices == 0) {
    return;
  }

  cl_device_id device_ids[num_devices];
  clGetDeviceIDs(platform->id, CL_DEVICE_TYPE_ALL, num_devices, device_ids, NULL);

  Set *devices = &platform->devices;
  devices->cardinality = num_devices;
  devices->elements = calloc(devices->cardinality, sizeof(OpenCLDevice));

  for (OpenCLDevice *device = devices->elements;
       device < (OpenCLDevice *)devices->elements + devices->cardinality;
       device++) {
    device->id = device_ids[device - (OpenCLDevice *)devices->elements];
    device->name = getOpenCLDeviceInfo(device->id, CL_DEVICE_NAME);
    device->vendor = getOpenCLDeviceInfo(device->id, CL_DEVICE_VENDOR);
    device->profile = getOpenCLDeviceInfo(device->id, CL_DEVICE_PROFILE);
    cl_device_type *device_type = getOpenCLDeviceInfo(device->id, CL_DEVICE_TYPE);
    device->type = *device_type;
    free(device_type);
  }
}

void freeOpenCLDevices(Set *devices) {
  if (devices == NULL ||
      devices->elements == NULL) {
    return;
  }

  for (OpenCLDevice *device = devices->elements;
       device < (OpenCLDevice *)devices->elements + devices->cardinality;
       device++) {
    free(device->name);
    free(device->vendor);
    free(device->profile);
  }

  free(devices->elements);
}
