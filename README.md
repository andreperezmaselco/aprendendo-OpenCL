# Aprendendo OpenCL

[![Linux](https://github.com/andreperezmaselco/learning-OpenCL/actions/workflows/linux.yml/badge.svg)](https://github.com/andreperezmaselco/learning-OpenCL/actions/workflows/linux.yml)

Este é um projeto para aprender as [especificações OpenCL](https://www.khronos.org/registry/OpenCL). Por enquanto, o programa imprime informações sobre as plataformas OpenCL disponíveis no computador em execução.

## Dependências

```
git clone https://github.com/KhronosGroup/OpenCL-Headers.git dependencies/OpenCL-Headers
git clone https://github.com/KhronosGroup/OpenCL-ICD-Loader.git dependencies/OpenCL-ICD-Loader
```

## Compilação

```
mkdir build
cmake -B build
cmake --build build
```
