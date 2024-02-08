cmake_minimum_required(VERSION 3.10)

project(RayRay)

# find_package(fmt CONFIG REQUIRED)

add_executable(RayRay src/main.cpp src/print_ppm.cpp)

# target_link_libraries(RayRay PRIVATE fmt::fmt)