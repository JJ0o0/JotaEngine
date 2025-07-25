cmake_minimum_required(VERSION 3.15)
project(JotaEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE GLAD_SOURCE ${PROJECT_SOURCE_DIR}/external/glad/src/glad.c)

add_subdirectory(external/glfw)

# Desliga módulos desnecessários do Assimp
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Disable Assimp tests")
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "Disable Assimp samples")
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "Disable exporters")
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Disable Assimp tools")

add_subdirectory(external/assimp)
find_package(OpenGL REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD_SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/external/glad/include
  ${PROJECT_SOURCE_DIR}/external/glm
  ${PROJECT_SOURCE_DIR}/external/stb
  ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL assimp)
