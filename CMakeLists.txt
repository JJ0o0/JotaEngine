cmake_minimum_required(VERSION 3.16)
project(JotaEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)

add_subdirectory(external/imgui)
add_subdirectory(src)