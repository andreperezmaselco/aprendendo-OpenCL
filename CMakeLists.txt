cmake_minimum_required(VERSION 3.22.1)

project(learning-OpenCL VERSION 1.0)

include(FetchContent)

FetchContent_Declare(OpenCL-Headers URL https://github.com/KhronosGroup/OpenCL-Headers/archive/refs/tags/v2024.10.24.tar.gz)

FetchContent_Declare(OpenCL-ICD-Loader URL https://github.com/KhronosGroup/OpenCL-ICD-Loader/archive/refs/tags/v2024.10.24.tar.gz)

FetchContent_MakeAvailable(OpenCL-Headers OpenCL-ICD-Loader)

add_executable(main
               src/main.c
               src/arguments.c
               src/platform.c
               src/device.c)

target_include_directories(main PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(main PUBLIC OpenCL)
