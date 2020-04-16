cmake_minimum_required(VERSION 3.10)

# set the project name
project(learning-OpenCL VERSION 1.0)

add_executable(main main.c OpenCL/platform.c OpenCL/device.c)

target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}")

target_link_libraries(main PUBLIC
                      OpenCL)
