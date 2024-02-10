cmake_minimum_required(VERSION 3.10)

project(RayRay)

set(CMAKE_CXX_FLAGS_DEBUG  "/Z7")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG  "/DEBUG:FULL")
add_executable(RayRay src/main.cpp src/image_utils.cpp src/print_ppm.cpp src/gltf_utils.cpp )

find_path(TINYGLTF_INCLUDE_DIRS "tiny_gltf.h")
target_include_directories(RayRay PRIVATE ${TINYGLTF_INCLUDE_DIRS})