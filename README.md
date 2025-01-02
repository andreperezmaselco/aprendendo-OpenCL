# Learning OpenCL

[![Linux](https://github.com/andreperezmaselco/learning-OpenCL/actions/workflows/linux.yml/badge.svg)](https://github.com/andreperezmaselco/learning-OpenCL/actions/workflows/linux.yml)

Project to learn the [OpenCL specifications](https://www.khronos.org/registry/OpenCL).
For now, the program prints information about the OpenCL platforms available on the host.

## Dependencies

```
git clone https://github.com/KhronosGroup/OpenCL-Headers.git dependencies/OpenCL-Headers
git clone https://github.com/KhronosGroup/OpenCL-ICD-Loader.git dependencies/OpenCL-ICD-Loader
```

## Build

```
cmake -B build && cmake --build build
```
