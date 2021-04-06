cmake_minimum_required(VERSION 3.10)

project(learning-OpenCL VERSION 1.0)

add_executable(main
               main.c
               arguments.c
               OpenCL/platform.c
               OpenCL/device.c)

target_include_directories(main PUBLIC
                           ${PROJECT_SOURCE_DIR}
                           ${PROJECT_SOURCE_DIR}/dependencies/OpenCL-Headers)

target_link_directories(main PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/OpenCL-ICD-Loader/build)

target_link_libraries(main PUBLIC OpenCL)
