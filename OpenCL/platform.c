// C Library
#include <stdio.h>
#include <stdlib.h>

// OpenCL API
#include <CL/cl.h>

#include "mathematics/set.h"
#include "OpenCL/device.h"
#include "OpenCL/platform.h"

void *getOpenCLPlatformInfo(
    cl_platform_id platform_id,
    cl_platform_info platform_info
) {
    size_t param_value_size;
    cl_int error = clGetPlatformInfo(platform_id, platform_info, 0, NULL, &param_value_size);
    void *param_value = malloc(param_value_size);
    error = clGetPlatformInfo(platform_id, platform_info, param_value_size, param_value, NULL);
    return param_value;
}

void allocOpenCLPlatforms(Set *platforms) {
    if (platforms == NULL)
        return;

    cl_uint num_platforms;
    clGetPlatformIDs(0, NULL, &num_platforms);

    // If there are no platforms, then return.
    if (num_platforms == 0)
        return;

    cl_platform_id *platform_ids = calloc(num_platforms, sizeof(cl_platform_id));
    clGetPlatformIDs(num_platforms, platform_ids, NULL);

    platforms->cardinality = num_platforms;
    platforms->elements = calloc(platforms->cardinality, sizeof(OpenCLPlatform));

    for (
        OpenCLPlatform *platform = platforms->elements;
        platform <= (OpenCLPlatform *)platforms->elements + platforms->cardinality - 1;
        platform++
    ) {
        platform->id = platform_ids[platform - (OpenCLPlatform *)platforms->elements];
        platform->name = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_NAME);
        platform->vendor = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_VENDOR);
        platform->profile = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_PROFILE);
        platform->extensions = getOpenCLPlatformInfo(platform->id, CL_PLATFORM_EXTENSIONS);
        allocOpenCLDevices(platform);
    }

    free(platform_ids);
}

void freeOpenCLPlatforms(Set *platforms) {
    if (platforms == NULL ||
        platforms->elements == NULL)
        return;

    for (
        OpenCLPlatform *platform = platforms->elements;
        platform <= (OpenCLPlatform *)platforms->elements + platforms->cardinality - 1;
        platform++
    ) {
        free(platform->name);
        free(platform->vendor);
        free(platform->profile);
        free(platform->extensions);
        freeOpenCLDevices(&platform->devices);
    }

    free(platforms->elements);
}

void printOpenCLInfo(Set *platforms) {
    if (platforms == NULL ||
        platforms->elements == NULL) {
        puts("No OpenCL platforms allocated.");
        return;
    }

    for (
        OpenCLPlatform *platform = platforms->elements;
        platform <= (OpenCLPlatform *)platforms->elements + platforms->cardinality - 1;
        platform++
    ) {
        puts("OpenCL platforms:");
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
        for (
            OpenCLDevice *device = devices->elements;
            device <= (OpenCLDevice *)devices->elements + devices->cardinality - 1;
            device++
        ) {
            printf("        name: %s\n", device->name);
            printf("        vendor: %s\n", device->vendor);
            printf("        profile: %s\n", device->profile);
            char *deviceType;
            switch (device->type) {
                case CL_DEVICE_TYPE_DEFAULT:
                    deviceType = "DEFAULT";
                    break;
                case CL_DEVICE_TYPE_CPU:
                    deviceType = "CPU";
                    break;
                case CL_DEVICE_TYPE_GPU:
                    deviceType = "GPU";
                    break;
                case CL_DEVICE_TYPE_ACCELERATOR:
                    deviceType = "ACCELERATOR";
                    break;
                default:
                    break;
            }
            printf("        type: %s\n", deviceType);
        }
    }
}