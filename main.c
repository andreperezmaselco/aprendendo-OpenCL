// Biblioteca padrão C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// APIs gráficas
#include <CL/cl.h>

#include "mathematics/set.h"

typedef struct OpenCLPlatform
{
	cl_platform_id id;
	cl_char *name;
	cl_char *vendor;
	cl_char *profile;
	cl_char *extensions;
	Set devices;
} OpenCLPlatform;

typedef struct OpenCLDevice
{
	cl_device_id id;
	cl_char *name;
	cl_char *vendor;
	cl_char *profile;
	cl_device_type type;
} OpenCLDevice;

void allocOpenCLDevices(OpenCLPlatform *platform)
{
	cl_uint num_devices;
	clGetDeviceIDs(platform->id, CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);

	cl_device_id *device_ids = calloc(num_devices, sizeof(cl_device_id));
	clGetDeviceIDs(platform->id, CL_DEVICE_TYPE_ALL, num_devices, device_ids, NULL);

	Set *devices = &platform->devices;
	devices->cardinality = num_devices;
	devices->elements = calloc(devices->cardinality, sizeof(OpenCLDevice));

	for (
		OpenCLDevice *device = devices->elements;
		device <= (OpenCLDevice *)devices->elements + devices->cardinality - 1;
		device++
	)
	{
		device->id = device_ids[device - (OpenCLDevice *)devices->elements];

		// Obtém o nome do dispositivo.
		size_t param_value_size;
		clGetDeviceInfo(device->id, CL_DEVICE_NAME, 0, NULL, &param_value_size);
		device->name = malloc(param_value_size);
		clGetDeviceInfo(device->id, CL_DEVICE_NAME, param_value_size, device->name, NULL);

		// Obtém o vendor do dispositivo.
		clGetDeviceInfo(device->id, CL_DEVICE_VENDOR, 0, NULL, &param_value_size);
		device->vendor = malloc(param_value_size);
		clGetDeviceInfo(device->id, CL_DEVICE_VENDOR, param_value_size, device->vendor, NULL);

		// Obtém o perfil do dispositivo.
		clGetDeviceInfo(device->id, CL_DEVICE_PROFILE, 0, NULL, &param_value_size);
		device->profile = malloc(param_value_size);
		clGetDeviceInfo(device->id, CL_DEVICE_PROFILE, param_value_size, device->profile, NULL);

		// Obtém o tipo do dispositivo.
		clGetDeviceInfo(device->id, CL_DEVICE_TYPE, 0, NULL, &param_value_size);
		clGetDeviceInfo(device->id, CL_DEVICE_TYPE, param_value_size, &device->type, NULL);
	}

	free(device_ids);
}

void freeOpenCLDevices(Set *devices) {
	for (
		OpenCLDevice *device = devices->elements;
		device <= (OpenCLDevice *)devices->elements + devices->cardinality - 1;
		device++
	)
	{
		free(device->name);
		free(device->vendor);
		free(device->profile);
	}

	free(devices->elements);
}

void allocOpenCLPlatforms(Set *platforms)
{
	cl_uint num_platforms;
	clGetPlatformIDs(0, NULL, &num_platforms);

	cl_platform_id *platform_ids = calloc(num_platforms, sizeof(cl_platform_id));
	clGetPlatformIDs(num_platforms, platform_ids, NULL);

	platforms->cardinality = num_platforms;
	platforms->elements = calloc(platforms->cardinality, sizeof(OpenCLPlatform));

	for (
		OpenCLPlatform *platform = platforms->elements;
		platform <= (OpenCLPlatform *)platforms->elements + platforms->cardinality - 1;
		platform++
	)
	{
		platform->id = platform_ids[platform - (OpenCLPlatform *)platforms->elements];

		// Obtém o nome da plataforma.
		size_t param_value_size;
		clGetPlatformInfo(platform->id, CL_PLATFORM_NAME, 0, NULL, &param_value_size);
		platform->name = malloc(param_value_size);
		clGetPlatformInfo(platform->id, CL_PLATFORM_NAME, param_value_size, platform->name, NULL);

		// Obtém o vendor da plataforma.
		clGetPlatformInfo(platform->id, CL_PLATFORM_VENDOR, 0, NULL, &param_value_size);
		platform->vendor = malloc(param_value_size);
		clGetPlatformInfo(platform->id, CL_PLATFORM_VENDOR, param_value_size, platform->vendor, NULL);

		// Obtém o perfil da plataforma.
		clGetPlatformInfo(platform->id, CL_PLATFORM_PROFILE, 0, NULL, &param_value_size);
		platform->profile = malloc(param_value_size);
		clGetPlatformInfo(platform->id, CL_PLATFORM_PROFILE, param_value_size, platform->profile, NULL);

		// Obtém as extensões da plataforma.
		clGetPlatformInfo(platform->id, CL_PLATFORM_EXTENSIONS, 0, NULL, &param_value_size);
		platform->extensions = malloc(param_value_size);
		clGetPlatformInfo(platform->id, CL_PLATFORM_EXTENSIONS, param_value_size, platform->extensions, NULL);

		// Obtém os dispositivos da plataforma.
		allocOpenCLDevices(platform);
	}

	free(platform_ids);
}

void freeOpenCLPlatforms(Set *platforms) {
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

int main(int argc, char **argv)
{
	Set platforms;
	allocOpenCLPlatforms(&platforms);

	for (
		OpenCLPlatform *platform = platforms.elements;
		platform <= (OpenCLPlatform *)platforms.elements + platforms.cardinality - 1;
		platform++
	)
	{
		puts("OpenCL platforms:");
		printf("    name: %s\n", platform->name);
		printf("    vendor: %s\n", platform->vendor);
		printf("    profile: %s\n", platform->profile);

		Set *devices = &platform->devices;
		for (
			OpenCLDevice *device = devices->elements;
			device <= (OpenCLDevice *)devices->elements + devices->cardinality - 1;
			device++
		)
		{
			puts("    devices:");
			printf("        name: %s\n", device->name);
			printf("        vendor: %s\n", device->vendor);
			printf("        profile: %s\n", device->profile);
			char *deviceType;
			switch (device->type)
			{
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
			}
			printf("        type: %s\n", deviceType);
		}
	}

	freeOpenCLPlatforms(&platforms);
	return 0;
}