// Biblioteca padrão C
#include <stdlib.h>

// OpenCL API
#include <CL/cl.h>

// Aprendendo OpenCL
#include "mathematics/set.h"
#include "OpenCL/device.h"
#include "OpenCL/error.h"
#include "OpenCL/platform.h"

void *getOpenCLDeviceInfo(cl_device_id device_id,
                          cl_device_info device_info) {
  // Tentar obter o tamanho do valor do parâmetro.
  size_t param_value_size;
  OpenCLError error = {clGetDeviceInfo(device_id, device_info, 0, NULL, &param_value_size)};

  // Se o tamanho do valor do parâmetro não foi retornado, então retornar NULL.
  if (error.code != CL_SUCCESS) {
    return NULL;
  }

  // Tentar obter o valor do parâmetro.
  void *param_value = malloc(param_value_size);
  error.code = clGetDeviceInfo(device_id, device_info, param_value_size, param_value, NULL);

  // Se o valor do parâmetro não foi retornado,
  // então desalocar 'param_value' e retornar NULL.
  if (error.code != CL_SUCCESS) {
    free(param_value);
    return NULL;
  }

  return param_value;
}

void allocOpenCLDevices(OpenCLPlatform *const platform) {
  // Se 'platform' for um ponteiro nulo, então retornar.
  if (platform == NULL) {
    return;
  }

  // Tentar obter a quantidade de dispositivos.
  OpenCLError error = {clGetDeviceIDs(platform->id, CL_DEVICE_TYPE_ALL, 0, NULL, (cl_uint *)&platform->devices.cardinality)};

  // Se não houver dispositivos, então retornar.
  if (error.code != CL_SUCCESS || platform->devices.cardinality == 0) {
    return;
  }

  // Tentar obter os IDs dos dispositivos.
  cl_device_id device_ids[platform->devices.cardinality];
  error.code = clGetDeviceIDs(platform->id, CL_DEVICE_TYPE_ALL, platform->devices.cardinality, device_ids, NULL);

  if (error.code != CL_SUCCESS) {
    return;
  }

  platform->devices.elements = calloc(platform->devices.cardinality, sizeof(OpenCLDevice));

  for (register uint8_t i = 0; i < platform->devices.cardinality; i++) {
    OpenCLDevice *device = platform->devices.elements + i * sizeof(OpenCLDevice);
    device->id = device_ids[i];
    device->name = getOpenCLDeviceInfo(device->id, CL_DEVICE_NAME);
    device->vendor = getOpenCLDeviceInfo(device->id, CL_DEVICE_VENDOR);
    device->profile = getOpenCLDeviceInfo(device->id, CL_DEVICE_PROFILE);
    device->version = getOpenCLDeviceInfo(device->id, CL_DEVICE_VERSION);
    cl_device_type *device_type = getOpenCLDeviceInfo(device->id, CL_DEVICE_TYPE);
    device->type = *device_type;
    free(device_type);
  }
}

void freeOpenCLDevices(Set *const devices) {
  if (devices == NULL || devices->elements == NULL) {
    return;
  }

  for (register uint8_t i = 0; i < devices->cardinality; i++) {
    OpenCLDevice *device = devices->elements + i * sizeof(OpenCLDevice);
    free(device->name);
    free(device->vendor);
    free(device->profile);
    free(device->version);
  }

  free(devices->elements);
  devices->cardinality = 0;
  devices->elements = NULL;
}
